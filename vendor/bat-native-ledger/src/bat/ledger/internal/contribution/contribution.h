/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_CONTRIBUTION_CONTRIBUTION_H_
#define BRAVELEDGER_CONTRIBUTION_CONTRIBUTION_H_

#include <stdint.h>

#include <map>
#include <memory>
#include <string>

#include "base/gtest_prod_util.h"
#include "bat/ledger/ledger.h"

namespace bat_ledger {
class LedgerImpl;
}

namespace braveledger_uphold {
class Uphold;
}

namespace braveledger_contribution {

class Unverified;
class Unblinded;

class Contribution {
 public:
  explicit Contribution(bat_ledger::LedgerImpl* ledger);

  ~Contribution();

  void Initialize();

  // Start point for contribution
  // In this step we get balance from the server
  void Start(ledger::ContributionQueuePtr info);

  // Called when timer is triggered
  void OnTimer(uint32_t timer_id);

  // Sets new reconcile timer for monthly contribution in 30 days
  void SetReconcileTimer();

  // Does final stage in contribution
  // Sets reports and contribution info
  void ContributionCompleted(
      const std::string& contribution_id,
      const ledger::RewardsType type,
      const double amount,
      const ledger::Result result);

  void HasSufficientBalance(
    ledger::HasSufficientBalanceToReconcileCallback callback);

  // Fetches recurring tips that will be then used for the contribution.
  // This is called from global timer in impl.
  // Can be also called manually
  void StartMonthlyContribution();

  void SetTimer(uint32_t* timer_id, uint64_t start_timer_in = 0);

  // Resets reconcile stamps
  void ResetReconcileStamp();

  // Triggers contribution process for auto contribute table
  void StartAutoContribute(uint64_t reconcile_stamp);

  void ContributeUnverifiedPublishers();

  void OneTimeTip(
      const std::string& publisher_key,
      const double amount,
      ledger::ResultCallback callback);

 private:
  void CheckContributionQueue();

  void ProcessContributionQueue();

  void OnProcessContributionQueue(ledger::ContributionQueuePtr info);

  // RECURRING TIPS: from the list gets only verified publishers and
  // save unverified to the db
  ledger::PublisherInfoList GetVerifiedListRecurring(
      const ledger::PublisherInfoList& all);

  void OnSavePendingContribution(const ledger::Result result);

  void PrepareACList(ledger::PublisherInfoList list);

  void StartRecurringTips(ledger::ResultCallback callback);

  void PrepareRecurringList(
      ledger::PublisherInfoList list,
      ledger::ResultCallback callback);

  void OnStartRecurringTips(const ledger::Result result);

  void OnBalance(
      const std::string& contribution_queue,
      const ledger::Result result,
      ledger::BalancePtr info);

  void OnHasSufficientBalance(
      const ledger::PublisherInfoList& publisher_list,
      const double balance,
      ledger::HasSufficientBalanceToReconcileCallback callback);

  void OnSufficientBalanceWallet(
      ledger::Result result,
      ledger::BalancePtr properties,
      ledger::HasSufficientBalanceToReconcileCallback callback);

  void SavePendingContribution(
      const std::string& publisher_key,
      double amount,
      const ledger::RewardsType type,
      ledger::ResultCallback callback);

  void OneTimeTipServerPublisher(
      ledger::ServerPublisherInfoPtr server_info,
      const std::string& publisher_key,
      double amount,
      ledger::ResultCallback callback);

  void OnSavePendingOneTimeTip(
      const ledger::Result result,
      ledger::ResultCallback callback);

  void CreateNewEntry(
      const std::string& wallet_type,
      ledger::BalancePtr balance,
      ledger::ContributionQueuePtr queue);

  void OnEntrySaved(
      const ledger::Result result,
      const std::string& contribution_id,
      const std::string& current_wallet_type,
      const ledger::Balance& balance,
      const std::string& queue_string);

  void OnProcessExternalWalletSaved(
      const ledger::Result result,
      const std::string& contribution_id,
      base::flat_map<std::string, double> wallet_balances);

  void Process(
      ledger::ContributionQueuePtr queue,
      ledger::BalancePtr balance);

  void DeleteContributionQueue(const uint64_t id);

  void AdjustTipsAmounts(
      ledger::ContributionQueuePublisherList publishers,
      ledger::ContributionQueuePublisherList* publishers_new,
      ledger::ContributionQueuePublisherList* publishers_left,
      double reduce_fee_for);

  void OnExternalWallets(
      const std::string& contribution_id,
      std::map<std::string, ledger::ExternalWalletPtr> wallets);

  void ExternalWalletContributionInfo(
      ledger::ContributionInfoPtr contribution,
      const ledger::ExternalWallet& wallet);

  void OnExternalWalletServerPublisherInfo(
      ledger::ServerPublisherInfoPtr info,
      const std::string& contribution_id,
      double amount,
      const ledger::ExternalWallet& wallet,
      const ledger::RewardsType type);

  void OnUpholdAC(ledger::Result result,
                  bool created,
                  const std::string& contribution_id);

  void OnDeleteContributionQueue(const ledger::Result result);

  void ExternalWalletCompleted(
      const ledger::Result result,
      const double amount,
      const std::string& contribution_id,
      const ledger::RewardsType type);

  bat_ledger::LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<Unverified> unverified_;
  std::unique_ptr<Unblinded> unblinded_;
  std::unique_ptr<braveledger_uphold::Uphold> uphold_;
  uint32_t last_reconcile_timer_id_;
  std::map<std::string, uint32_t> retry_timers_;
  uint32_t queue_timer_id_;
  bool queue_in_progress_ = false;

  // For testing purposes
  friend class ContributionTest;
  FRIEND_TEST_ALL_PREFIXES(ContributionTest, GetAmountFromVerifiedAuto);
};

}  // namespace braveledger_contribution
#endif  // BRAVELEDGER_CONTRIBUTION_CONTRIBUTION_H_
