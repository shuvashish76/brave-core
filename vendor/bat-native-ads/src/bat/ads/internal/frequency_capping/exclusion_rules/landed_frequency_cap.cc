/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/exclusion_rules/landed_frequency_cap.h"
#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/creative_ad_info.h"
#include "base/strings/stringprintf.h"

namespace ads {

LandedFrequencyCap::LandedFrequencyCap(
    const AdsImpl* const ads)
    : ads_(ads) {
  DCHECK(ads_);
}

LandedFrequencyCap::~LandedFrequencyCap() = default;

bool LandedFrequencyCap::ShouldExclude(
    const CreativeAdInfo& ad) {
  if (DoesAdRespectCap(ad)) {
    return false;
  }

  last_message_ = base::StringPrintf("creativeSetId %s has exceeded the "
      "frequency capping for landed", ad.creative_set_id);

  return true;
}

const std::string& TotalMaxFrequencyCap::get_last_message() const {
  return last_message_;
}

std::deque<uint64_t> TotalMaxFrequencyCap::GetHistory(
    const std::string& creative_set_id) const {
  std::deque<uint64_t> filtered_history;

  const std::deque<uint64_t> history =
      ads_->get_client()->GetCreativeSetHistory();
  if (history.find(creative_set_id) != history.end()) {
    filtered_history = history.at(creative_set_id);
  }

  return filtered_history;
}

bool TotalMaxFrequencyCap::DoesAdRespectCap(
    const CreativeAdInfo& ad) const {
  const std::deque<uint64_t> history = GetHistory(ad.creative_set_id);

  if (history.size() >= ad.total_max) {
    return false;
  }

  return true;
}

}  // namespace ads
