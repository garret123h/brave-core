/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_SORTS_AD_CONVERSIONS_AD_CONVERSIONS_ASCENDING_SORT_H_
#define BAT_ADS_INTERNAL_SORTS_AD_CONVERSIONS_AD_CONVERSIONS_ASCENDING_SORT_H_

#include "bat/ads/internal/sorts/ad_conversions/ad_conversions_sort.h"

namespace ads {

class AdConversionsAscendingSort : public AdConversionsSort {
 public :
  AdConversionsAscendingSort();
  ~AdConversionsAscendingSort() override;

  AdConversionList Apply(
      const AdConversionList& list) const override;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_SORTS_AD_CONVERSIONS_AD_CONVERSIONS_ASCENDING_SORT_H_  // NOLINT
