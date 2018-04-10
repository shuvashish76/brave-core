/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_profile_prefs.h"

#include "brave/components/brave_shields/browser/brave_shields_web_contents_observer.h"
#include "components/content_settings/core/common/pref_names.h"
#include "components/pref_registry/pref_registry_syncable.h"

namespace brave {

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry) {
  brave_shields::BraveShieldsWebContentsObserver::RegisterProfilePrefs(registry);

  // This is registered from ProfileImpl::ProfileImpl in
  // BrowserContextDependencyManager::GetInstance()->
  //   RegisterProfilePrefsForServices(this, pref_registry_.get());
  // We re-regsiter it here to override.
  registry->RegisterBooleanPref(
      prefs::kBlockThirdPartyCookies, true,
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
}

}  // namespace brave


