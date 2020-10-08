/* Copyright 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_BROWSER_ADS_P2A_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_BROWSER_ADS_P2A_H_

#include <string>
#include <vector>

class PrefService;
class PrefRegistrySimple;

namespace brave_ads {

const std::vector<std::string> kP2AQuestionList = {
    // Ad Opportunities
    "Brave.P2A.TotalAdOpportunities",
    "Brave.P2A.AdOpportunitiesPerSegment.architecture",
    "Brave.P2A.AdOpportunitiesPerSegment.artsentertainment",
    "Brave.P2A.AdOpportunitiesPerSegment.automotive",
    "Brave.P2A.AdOpportunitiesPerSegment.business",
    "Brave.P2A.AdOpportunitiesPerSegment.careers",
    "Brave.P2A.AdOpportunitiesPerSegment.cellphones",
    "Brave.P2A.AdOpportunitiesPerSegment.crypto",
    "Brave.P2A.AdOpportunitiesPerSegment.education",
    "Brave.P2A.AdOpportunitiesPerSegment.familyparenting",
    "Brave.P2A.AdOpportunitiesPerSegment.fashion",
    "Brave.P2A.AdOpportunitiesPerSegment.folklore",
    "Brave.P2A.AdOpportunitiesPerSegment.fooddrink",
    "Brave.P2A.AdOpportunitiesPerSegment.gaming",
    "Brave.P2A.AdOpportunitiesPerSegment.healthfitness",
    "Brave.P2A.AdOpportunitiesPerSegment.history",
    "Brave.P2A.AdOpportunitiesPerSegment.hobbiesinterests",
    "Brave.P2A.AdOpportunitiesPerSegment.home",
    "Brave.P2A.AdOpportunitiesPerSegment.law",
    "Brave.P2A.AdOpportunitiesPerSegment.military",
    "Brave.P2A.AdOpportunitiesPerSegment.other",
    "Brave.P2A.AdOpportunitiesPerSegment.personalfinance",
    "Brave.P2A.AdOpportunitiesPerSegment.pets",
    "Brave.P2A.AdOpportunitiesPerSegment.realestate",
    "Brave.P2A.AdOpportunitiesPerSegment.science",
    "Brave.P2A.AdOpportunitiesPerSegment.sports",
    "Brave.P2A.AdOpportunitiesPerSegment.technologycomputing",
    "Brave.P2A.AdOpportunitiesPerSegment.travel",
    "Brave.P2A.AdOpportunitiesPerSegment.weather",
    "Brave.P2A.AdOpportunitiesPerSegment.untargeted",
    // Ad Impressions
    "Brave.P2A.TotalAdImpressions",
    "Brave.P2A.AdImpressionsPerSegment.architecture",
    "Brave.P2A.AdImpressionsPerSegment.artsentertainment",
    "Brave.P2A.AdImpressionsPerSegment.automotive",
    "Brave.P2A.AdImpressionsPerSegment.business",
    "Brave.P2A.AdImpressionsPerSegment.careers",
    "Brave.P2A.AdImpressionsPerSegment.cellphones",
    "Brave.P2A.AdImpressionsPerSegment.crypto",
    "Brave.P2A.AdImpressionsPerSegment.education",
    "Brave.P2A.AdImpressionsPerSegment.familyparenting",
    "Brave.P2A.AdImpressionsPerSegment.fashion",
    "Brave.P2A.AdImpressionsPerSegment.folklore",
    "Brave.P2A.AdImpressionsPerSegment.fooddrink",
    "Brave.P2A.AdImpressionsPerSegment.gaming",
    "Brave.P2A.AdImpressionsPerSegment.healthfitness",
    "Brave.P2A.AdImpressionsPerSegment.history",
    "Brave.P2A.AdImpressionsPerSegment.hobbiesinterests",
    "Brave.P2A.AdImpressionsPerSegment.home",
    "Brave.P2A.AdImpressionsPerSegment.law",
    "Brave.P2A.AdImpressionsPerSegment.military",
    "Brave.P2A.AdImpressionsPerSegment.other",
    "Brave.P2A.AdImpressionsPerSegment.personalfinance",
    "Brave.P2A.AdImpressionsPerSegment.pets",
    "Brave.P2A.AdImpressionsPerSegment.realestate",
    "Brave.P2A.AdImpressionsPerSegment.science",
    "Brave.P2A.AdImpressionsPerSegment.sports",
    "Brave.P2A.AdImpressionsPerSegment.technologycomputing",
    "Brave.P2A.AdImpressionsPerSegment.travel",
    "Brave.P2A.AdImpressionsPerSegment.weather",
    "Brave.P2A.AdImpressionsPerSegment.untargeted"
};

void RegisterP2APrefs(PrefRegistrySimple* prefs);

void RecordInWeeklyStorageAndEmitP2AHistogramAnswer(
    PrefService* prefs,
    const std::string& name);

void EmitP2AHistogramAnswer(
    const std::string& name,
    int count_value);

void SuspendP2AHistograms();

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_BROWSER_ADS_P2A_H_
