/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_SEARCH_PROVIDERS_H_
#define BAT_ADS_INTERNAL_SEARCH_PROVIDERS_H_

#include <map>
#include <string>
#include <vector>

#include "bat/ads/internal/search_provider_info.h"

const std::map<std::string, SearchProviderInfo> _search_providers = {
    "amazon.com", {
      "Amazon",
      "https://www.amazon.com/s?k={searchTerms}",
      false
    }
  },
  {
    "bing.com", {
      "Bing",
      "https://www.bing.com/search?q={searchTerms}",
      true
    }
  },
  {
    "duckduckgo.com", {
      "DuckDuckGo",
      "https://duckduckgo.com/?q={searchTerms}&t=brave",
      true
    }
  },
  {
    "fireball.com", {
      "Fireball",
      "https://fireball.com/search?q={searchTerms}",
      true
    }
  },
  {
    "github.com", {
      "GitHub",
      "https://github.com/search?q={searchTerms}",
      false
    }
  },
  {
    // TODO(https://github.com/brave/brave-browser/issues/8487): Brave Ads
    // search providers definition doesn't match all patterns
    "google.com", {
      "Google",
      "https://www.google.com/search?q={searchTerms}",
      true
    }
  },
  {
    "stackoverflow.com", {
      "Stack Overflow",
      "https://stackoverflow.com/search?q={searchTerms}",
      false
    }
  },
  {
    "developer.mozilla.org", {
      "MDN Web Docs",
      "https://developer.mozilla.org/search?q={searchTerms}",
      false
    }
  },
  {
    "twitter.com", {
      "Twitter",
      "https://twitter.com/search?q={searchTerms}",
      false
    }
  },
  {
    "en.wikipedia.org", {
      "Wikipedia",
      "https://en.wikipedia.org/wiki/Special:Search?search={searchTerms}",
      false
    }
  },
  {
    // TODO(https://github.com/brave/brave-browser/issues/8487): Brave Ads
    // search providers definition doesn't match all patterns
    "search.yahoo.com", {
      "Yahoo",
      "https://search.yahoo.com/search?p={searchTerms}&fr=opensearch",
      true
    }
  },
  {
    "youtube.com", {
      "YouTube",
      "https://www.youtube.com/results?search_query={searchTerms}",
      false
    }
  },
  {
    // TODO(https://github.com/brave/brave-browser/issues/8487): Brave Ads
    // search providers definition doesn't match all patterns
    "startpage.com", {
      "StartPage",
      "https://www.startpage.com/do/dsearch?query={searchTerms}&pl=opensearch",
      true
    }
  },
  {
    "infogalactic.com", {
      "Infogalactic",
      "https://infogalactic.com/w/index.php?title=Special:Search&search={searchTerms}",  // NOLINT
      false
    }
  },
  {
    "wolframalpha.com", {
      "Wolfram Alpha",
      "https://www.wolframalpha.com/input/?i={searchTerms}",
      false
    }
  },
  {
    "semanticscholar.org", {
      "Semantic Scholar",
      "https://www.semanticscholar.org/search?q={searchTerms}",
      true
    }
  },
  {
    "qwant.com", {
      "Qwant",
      "https://www.qwant.com/?q={searchTerms}&client=brave",
      true
    }
  },
  {
    "yandex.com", {
      "Yandex",
      "https://yandex.com/search/?text={searchTerms}&clid=2274777",
      true
    }
  },
  {
    "ecosia.org", {
      "Ecosia",
      "https://www.ecosia.org/search?q={searchTerms}",
      true
    }
  },
  {
    "searx.me", {
      "searx",
      "https://searx.me/?q={searchTerms}&categories=general",
      true
    }
  },
  {
    "findx.com", {
      "findx",
      "https://www.findx.com/search?q={searchTerms}&type=web",
      true
    }
  }
};

class SearchProviders {
 public:
  SearchProviders();
  ~SearchProviders();

  static bool IsSearchEngine(
      const std::string& url);

  static bool IsSearchEngineResultsPage(
      const std::string& url);

  static std::string ExtractSearchQueryKeywords(
      const std::string& url);
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_SEARCH_PROVIDERS_H_
