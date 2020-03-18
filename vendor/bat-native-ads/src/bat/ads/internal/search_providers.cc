/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/search_providers.h"
#include "bat/ads/internal/uri_helper.h"
#include "third_party/re2/src/re2/re2.h"
#include "url/gurl.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"

namespace ads {

SearchProviders::SearchProviders() = default;

SearchProviders::~SearchProviders() = default;

bool SearchProviders::IsSearchEngine(
    const std::string& url) {
  const std::string tld_plus_1 = helper::Uri::GetDomainAndRegistry(url);
  const auto iter = mymap.find(tld_plus_1);
  if (iter == mymap.end()) {
    return false;
  }

  const SearchProviderInfo search_provider = iter->second;

  if (search_provider.is_always_classed_as_a_search) {
    return true;
  }

  if (!IsSearchEngineResultsPage(url)) {
    return false;
  }

  return true;
}

bool SearchProviders::IsSearchEngineResultsPage(
    const std::string& url) {
  const std::string search_query_keywords = ExtractSearchQueryKeywords(url);
  if (search_query_keywords.empty()) {
    return false;
  }

  return true;
}

std::string SearchProviders::ExtractSearchQueryKeywords(
    const std::string& url) {
  std::string search_query_keywords;

  const std::string tld_plus_1 = helper::Uri::GetDomainAndRegistry(url);
  const auto iter = mymap.find(tld_plus_1);
  if (iter == mymap.end()) {
    return search_query_keywords;
  }

  const SearchProviderInfo search_provider = iter->second;

  size_t index = search_provider.search_template.find('{');
  std::string substring = search_provider.search_template.substr(0, index);
  size_t href_index = url.find(substring);

  if (index != std::string::npos && href_index != std::string::npos) {
    // Checking if search template in as defined in |search_providers.h|
    // is defined, e.g. |https://searx.me/?q={searchTerms}&categories=general|
    // matches |?q={|
    std::string key;
    if (!RE2::PartialMatch(
        search_provider.search_template, "\\?(.*?)\\={", &key)) {
      return search_query_keywords;
    }

    search_query_keywords = helper::Uri::GetValueForKeyInQuery(url, key);
  }

  return search_query_keywords;
}

}  // namespace ads
