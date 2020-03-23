/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <stdint.h>
#include <memory>
#include <vector>

#include "testing/gtest/include/gtest/gtest.h"

#include "base/time/time.h"
#include "bat/ads/creative_ad_info.h"
#include "bat/ads/internal/ads_client_mock.h"
#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/internal/frequency_capping/exclusion_rule.h"
#include "bat/ads/internal/frequency_capping/exclusion_rules/daily_cap_frequency_cap.h"

// npm run test -- brave_unit_tests --filter=BraveAds*

using std::placeholders::_1;

namespace ads {

namespace {

const std::vector<std::string> kCampaignIds = {
  "60267cee-d5bb-4a0d-baaf-91cd7f18e07e",
  "90762cee-d5bb-4a0d-baaf-61cd7f18e07e"
};

const uint64_t kSecondsPerDay =
    base::Time::kSecondsPerHour * base::Time::kHoursPerDay;

}  // namespace

class BraveAdsDailyCapFrequencyCapTest : public ::testing::Test {
 protected:
  BraveAdsDailyCapFrequencyCapTest()
      : ads_client_mock_(std::make_unique<AdsClientMock>()),
        ads_(std::make_unique<AdsImpl>(ads_client_mock_.get())) {
    // You can do set-up work for each test here
  }

  ~BraveAdsDailyCapFrequencyCapTest() override {
    // You can do clean-up work that doesn't throw exceptions here
  }

  // If the constructor and destructor are not enough for setting up and
  // cleaning up each test, you can use the following methods

  void SetUp() override {
    // Code here will be called immediately after the constructor (right before
    // each test)

    auto callback = std::bind(
        &BraveAdsDailyCapFrequencyCapTest::OnAdsImplInitialize, this, _1);
    ads_->Initialize(callback);

    frequency_cap_ = std::make_unique<DailyCapFrequencyCap>(ads_.get());
  }

  void OnAdsImplInitialize(const Result result) {
    EXPECT_EQ(Result::SUCCESS, result);
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right before the
    // destructor)
  }

  void GeneratePastHistory(
      const std::string& campaign_id,
      const uint64_t time_offset_in_seconds,
      const uint8_t count) {
    uint64_t now_in_seconds = base::Time::Now().ToDoubleT();

    for (uint8_t i = 0; i < count; i++) {
      now_in_seconds -= time_offset_in_seconds;

      ads_->get_client()->AppendTimestampToCampaignHistory(campaign_id,
          now_in_seconds);
    }
  }

  std::unique_ptr<AdsClientMock> ads_client_mock_;
  std::unique_ptr<AdsImpl> ads_;

  std::unique_ptr<DailyCapFrequencyCap> frequency_cap_;
};

TEST_F(BraveAdsDailyCapFrequencyCapTest,
    AdAllowedWhenNoAds) {
  // Arrange
  CreativeAdInfo ad_info;
  ad_info.campaign_id = kCampaignIds.at(0);
  ad_info.daily_cap = 2;

  // Act
  const bool should_exclude = frequency_cap_->ShouldExclude(ad_info);

  // Assert
  EXPECT_FALSE(should_exclude);
}

TEST_F(BraveAdsDailyCapFrequencyCapTest,
    AdAllowedWithAds) {
  // Arrange
  CreativeAdInfo ad_info;
  ad_info.campaign_id = kCampaignIds.at(0);
  ad_info.daily_cap = 2;

  GeneratePastHistory(ad_info.campaign_id, 0, 1);

  // Act
  const bool should_exclude = frequency_cap_->ShouldExclude(ad_info);

  // Assert
  EXPECT_FALSE(should_exclude);
}

TEST_F(BraveAdsDailyCapFrequencyCapTest,
    AdAllowedWithAdsWithinTheDay) {
  // Arrange
  CreativeAdInfo ad_info;
  ad_info.campaign_id = kCampaignIds.at(0);
  ad_info.daily_cap = 2;

  GeneratePastHistory(ad_info.campaign_id, kSecondsPerDay - 1, 1);

  // Act
  const bool should_exclude = frequency_cap_->ShouldExclude(ad_info);

  // Assert
  EXPECT_FALSE(should_exclude);
}

TEST_F(BraveAdsDailyCapFrequencyCapTest,
    AdAllowedWithAdsOverTheDay) {
  // Arrange
  CreativeAdInfo ad_info;
  ad_info.campaign_id = kCampaignIds.at(0);
  ad_info.daily_cap = 2;

  GeneratePastHistory(ad_info.campaign_id, kSecondsPerDay, 1);

  // Act
  const bool should_exclude = frequency_cap_->ShouldExclude(ad_info);

  // Assert
  EXPECT_FALSE(should_exclude);
}

TEST_F(BraveAdsDailyCapFrequencyCapTest,
    AdExcludedWithMatchingCampaignAds) {
  // Arrange
  CreativeAdInfo ad_info;
  ad_info.campaign_id = kCampaignIds.at(0);
  ad_info.daily_cap = 2;

  GeneratePastHistory(ad_info.campaign_id, 0, 2);

  // Act
  const bool should_exclude = frequency_cap_->ShouldExclude(ad_info);

  // Assert
  EXPECT_TRUE(should_exclude);
  EXPECT_EQ(frequency_cap_->get_last_message(), "campaignId 60267cee-d5bb-4a0d-baaf-91cd7f18e07e has exceeded the frequency capping for dailyCap");  // NOLINT
}

TEST_F(BraveAdsDailyCapFrequencyCapTest,
    AdNotExcludedWithNoMatchingCampaignAds) {
  // Arrange
  CreativeAdInfo ad_info;
  ad_info.campaign_id = kCampaignIds.at(1);
  ad_info.daily_cap = 1;

  GeneratePastHistory(kCampaignIds.at(0), 0, 2);

  // Act
  const bool should_exclude = frequency_cap_->ShouldExclude(ad_info);

  // Assert
  EXPECT_FALSE(should_exclude);
}

TEST_F(BraveAdsDailyCapFrequencyCapTest,
    AdExcludedForIssue4207) {
  // Arrange
  const uint64_t ads_per_day = 20;

  CreativeAdInfo ad_info;
  ad_info.campaign_id = kCampaignIds.at(0);
  ad_info.daily_cap = ads_per_day;

  const uint64_t ads_per_hour = 5;
  const uint64_t time_offset = base::Time::kSecondsPerHour / ads_per_hour;
  GeneratePastHistory(ad_info.campaign_id, time_offset, ads_per_day);

  // Act
  const bool should_exclude = frequency_cap_->ShouldExclude(ad_info);

  // Assert
  EXPECT_TRUE(should_exclude);
  EXPECT_EQ(frequency_cap_->get_last_message(), "campaignId 60267cee-d5bb-4a0d-baaf-91cd7f18e07e has exceeded the frequency capping for dailyCap");  // NOLINT
}

}  // namespace ads
