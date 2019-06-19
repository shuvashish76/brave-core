/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

export const enum types {
  CREATE_WALLET = '@@rewards/CREATE_WALLET',
  WALLET_CREATED = '@@rewards/WALLET_CREATED',
  WALLET_CREATE_FAILED = '@@rewards/WALLET_CREATE_FAILED',
  ON_SETTING_SAVE = '@@rewards/ON_SETTING_SAVE',
  ON_WALLET_PROPERTIES = '@@rewards/ON_WALLET_PROPERTIES',
  GET_WALLET_PROPERTIES = '@@rewards/GET_WALLET_PROPERTIES',
  GET_GRANTS = '@@rewards/GET_GRANTS',
  ON_GRANT = '@@rewards/ON_GRANTS',
  GET_GRANT_CAPTCHA = '@@rewards/GET_GRANT_CAPTCHA',
  ON_GRANT_CAPTCHA = '@@rewards/ON_GRANT_CAPTCHA',
  SOLVE_GRANT_CAPTCHA = '@@rewards/SOLVE_GRANT_CAPTCHA',
  ON_GRANT_RESET = '@@rewards/ON_GRANT_RESET',
  ON_GRANT_DELETE = '@@rewards/ON_GRANT_DELETE',
  ON_GRANT_FINISH = '@@rewards/ON_GRANT_FINISH',
  GET_WALLLET_PASSPHRASE = '@@rewards/GET_WALLLET_PASSPHRASE',
  ON_WALLLET_PASSPHRASE = '@@rewards/ON_WALLLET_PASSPHRASE',
  RECOVER_WALLET = '@@rewards/RECOVER_WALLET',
  ON_RECOVER_WALLET_DATA = '@@rewards/ON_RECOVER_WALLET_DATA',
  ON_MODAL_BACKUP_CLOSE = '@@rewards/ON_MODAL_BACKUP_CLOSE',
  ON_MODAL_BACKUP_OPEN = '@@rewards/ON_MODAL_BACKUP_OPEN',
  ON_CLEAR_ALERT = '@@rewards/ON_CLEAR_ALERT',
  ON_RECONCILE_STAMP = '@@rewards/ON_RECONCILE_STAMP',
  GET_ADDRESSES = '@@rewards/GET_ADDRESSES',
  ON_ADDRESSES = '@@rewards/ON_ADDRESSES',
  ON_QR_GENERATED = '@@rewards/ON_QR_GENERATED',
  ON_CONTRIBUTE_LIST = '@@rewards/ON_CONTRIBUTE_LIST',
  ON_BALANCE_REPORTS = '@@rewards/ON_BALANCE_REPORTS',
  ON_EXCLUDE_PUBLISHER = '@@rewards/ON_EXCLUDE_PUBLISHER',
  ON_RESTORE_PUBLISHERS = '@@rewards/ON_RESTORE_PUBLISHERS',
  CHECK_WALLET_EXISTENCE = '@@rewards/CHECK_WALLET_EXISTENCE',
  ON_WALLET_EXISTS = '@@rewards/ON_WALLET_EXISTS',
  ON_EXCLUDED_PUBLISHERS_NUMBER = '@@rewards/ON_EXCLUDED_PUBLISHERS_NUMBER',
  ON_CONTRIBUTION_AMOUNT = '@@rewards/ON_CONTRIBUTION_AMOUNT',
  ON_RECURRING_TIPS = '@@rewards/ON_RECURRING_TIPS',
  REMOVE_RECURRING_TIP = '@@rewards/REMOVE_RECURRING_TIP',
  ON_CURRENT_TIPS = '@@rewards/ON_CURRENT_TIPS',
  GET_TIP_TABLE = '@@rewards/GET_TIP_TABLE',
  GET_CONTRIBUTE_LIST = '@@rewards/GET_CONTRIBUTE_LIST',
  INIT_AUTOCONTRIBUTE_SETTINGS = '@@rewards/INIT_AUTOCONTRIBUTE_SETTINGS',
  CHECK_IMPORTED = '@@rewards/CHECK_IMPORTED',
  ON_IMPORTED_CHECK = '@@rewards/ON_IMPORTED_CHECK',
  GET_ADS_DATA = '@@rewards/GET_ADS_DATA',
  ON_ADS_DATA = '@@rewards/ON_ADS_DATA',
  ON_ADS_SETTING_SAVE = '@@rewards/ON_ADS_SETTING_SAVE',
  GET_CURRENT_REPORT = '@@rewards/GET_CURRENT_REPORT',
  GET_RECONCILE_STAMP = '@@rewards/GET_RECONCILE_STAMP',
  GET_PENDING_CONTRIBUTIONS = '@@rewards/GET_PENDING_CONTRIBUTIONS',
  ON_PENDING_CONTRIBUTIONS = '@@rewards/ON_PENDING_CONTRIBUTIONS',
  ON_REWARDS_ENABLED = '@@rewards/ON_REWARDS_ENABLED',
  GET_ADDRESSES_FOR_PAYMENT_ID = '@@rewards/GET_ADDRESSES_FOR_PAYMENT_ID',
  ON_ADDRESSES_FOR_PAYMENT_ID = '@@rewards/ON_ADDRESSES_FOR_PAYMENT_ID',
  GET_TRANSACTION_HISTORY = '@@rewards/GET_TRANSACTION_HISTORY',
  ON_TRANSACTION_HISTORY = '@@rewards/ON_TRANSACTION_HISTORY',
  ON_TRANSACTION_HISTORY_CHANGED = '@@rewards/ON_TRANSACTION_HISTORY_CHANGED',
  GET_REWARDS_MAIN_ENABLED = '@@rewards/GET_REWARDS_MAIN_ENABLED',
  ON_RECURRING_TIP_SAVED = '@@rewards/ON_RECURRING_TIP_SAVED',
  ON_RECURRING_TIP_REMOVED = '@@rewards/ON_RECURRING_TIP_REMOVED',
  ON_CONTRIBUTION_SAVED = '@@rewards/ON_CONTRIBUTION_SAVED',
  ON_INLINE_TIP_SETTINGS_CHANGE = '@@rewards/ON_INLINE_TIP_SETTINGS_CHANGE',
  REMOVE_PENDING_CONTRIBUTION = '@@rewards/REMOVE_PENDING_CONTRIBUTION',
  REMOVE_ALL_PENDING_CONTRIBUTION = '@@rewards/REMOVE_ALL_PENDING_CONTRIBUTION',
  ON_EXCLUDED_LIST = '@@rewards/ON_EXCLUDED_LIST',
  ON_RESTORE_PUBLISHER = '@@rewards/ON_RESTORE_PUBLISHER',
  GET_EXCLUDED_SITES = '@@rewards/GET_EXCLUDED_SITES',
  GET_BALANCE = '@@rewards/GET_BALANCE',
  ON_BALANCE = '@@rewards/ON_BALANCE'
}
