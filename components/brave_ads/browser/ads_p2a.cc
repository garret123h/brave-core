/* Copyright 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/browser/ads_p2a.h"

#include <stdint.h>
#include <map>
#include <string>

#include "base/metrics/histogram_macros.h"
#include "brave/components/brave_ads/common/pref_names.h"
#include "brave/components/weekly_storage/weekly_storage.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace brave_ads {
namespace {

const uint16_t kBinIntervals[] =
    { 0, 5, 10, 20, 50, 100, 250, 500 };

}  // namespace

void RegisterP2APrefs(
    PrefRegistrySimple* registry) {
  for (auto const& question_name : kP2AQuestionList) {
      std::string pref_path(prefs::kP2AStoragePrefNamePrefix);
      pref_path.append(question_name);
      registry->RegisterListPref(pref_path);
  }
}

void RecordInWeeklyStorageAndEmitP2AHistogramAnswer(
    PrefService* prefs,
    const std::string& name) {
  std::string pref_path(prefs::kP2AStoragePrefNamePrefix);
  pref_path.append(name);
  if (!prefs->FindPreference(pref_path)) {
    return;
  }
  WeeklyStorage storage(prefs, pref_path.c_str());
  storage.AddDelta(1);
  EmitP2AHistogramAnswer(name, storage.GetWeeklySum());
}

void EmitP2AHistogramAnswer(
    const std::string& name,
    int count_value) {
  const uint16_t* it =
      std::lower_bound(kBinIntervals, std::end(kBinIntervals), count_value);
  const uint16_t answer = it - kBinIntervals;

  if (name == "Brave.P2A.TotalAdOpportunities") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.TotalAdOpportunities",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.architecture") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.architecture",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.artsentertainment") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.artsentertainment",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.automotive") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.automotive",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.business") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.business",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.careers") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.careers",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.cellphones") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.cellphones",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.crypto") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.crypto",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.education") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.education",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.familyparenting") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.familyparenting",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.fashion") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.fashion",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.folklore") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.folklore",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.fooddrink") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.fooddrink",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.gaming") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.gaming",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.healthfitness") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.healthfitness",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.history") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.history",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.hobbiesinterests") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.hobbiesinterests",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.home") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.home",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.law") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.law",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.military") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.military",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.other") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.other",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.personalfinance") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.personalfinance",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.pets") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.pets",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.realestate") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.realestate",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.science") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.science",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.sports") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.sports",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.technologycomputing") {  // NOLINT
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.technologycomputing",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.travel") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.travel",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.weather") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.weather",
        answer, 8);
  } else if (name == "Brave.P2A.AdOpportunitiesPerSegment.untargeted") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdOpportunitiesPerSegment.untargeted",
        answer, 8);
  } else if (name == "Brave.P2A.TotalAdImpressions") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.TotalAdImpressions",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.architecture") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.architecture",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.artsentertainment") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.artsentertainment",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.automotive") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.automotive",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.business") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.business",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.careers") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.careers",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.cellphones") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.cellphones",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.crypto") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.crypto",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.education") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.education",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.familyparenting") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.familyparenting",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.fashion") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.fashion",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.folklore") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.folklore",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.fooddrink") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.fooddrink",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.gaming") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.gaming",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.healthfitness") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.healthfitness",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.history") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.history",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.hobbiesinterests") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.hobbiesinterests",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.home") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.home",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.law") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.law",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.military") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.military",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.other") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.other",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.personalfinance") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.personalfinance",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.pets") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.pets",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.realestate") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.realestate",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.science") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.science",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.sports") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.sports",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.technologycomputing") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.technologycomputing",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.travel") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.travel",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.weather") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.weather",
        answer, 8);
  } else if (name == "Brave.P2A.AdImpressionsPerSegment.untargeted") {
    UMA_HISTOGRAM_EXACT_LINEAR(
        "Brave.P2A.AdImpressionsPerSegment.untargeted",
        answer, 8);
  } else {
    return;
  }
}

void SuspendP2AHistograms() {
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.TotalAdOpportunities",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.architecture",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.artsentertainment",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.automotive",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.business",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.careers",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.cellphones",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.crypto",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.education",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.familyparenting",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.fashion",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.folklore",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.fooddrink",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.gaming",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.healthfitness",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.history",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.hobbiesinterests",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.home",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.law",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.military",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.other",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.personalfinance",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.pets",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.realestate",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.science",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.sports",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.technologycomputing",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.travel",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.weather",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdOpportunitiesPerSegment.untargeted",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.TotalAdImpressions",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.architecture",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.artsentertainment",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.automotive",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.business",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.careers",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.cellphones",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.crypto",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.education",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.familyparenting",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.fashion",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.folklore",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.fooddrink",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.gaming",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.healthfitness",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.history",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.hobbiesinterests",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.home",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.law",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.military",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.other",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.personalfinance",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.pets",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.realestate",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.science",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.sports",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.technologycomputing",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.travel",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.weather",
      INT_MAX, 8);
  UMA_HISTOGRAM_EXACT_LINEAR(
      "Brave.P2A.AdImpressionsPerSegment.untargeted",
      INT_MAX, 8);
}

}  // namespace brave_ads
