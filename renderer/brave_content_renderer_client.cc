/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/renderer/brave_content_renderer_client.h"
#include "third_party/blink/public/platform/web_runtime_features.h"

BraveContentRendererClient::BraveContentRendererClient()
    : ChromeContentRendererClient() {}

void BraveContentRendererClient::
SetRuntimeFeaturesDefaultsBeforeBlinkInitialization() {
  ChromeContentRendererClient::
      SetRuntimeFeaturesDefaultsBeforeBlinkInitialization();

  blink::WebRuntimeFeatures::EnableSharedArrayBuffer(false);

  // These features don't have dedicated WebRuntimeFeatures wrappers.
  blink::WebRuntimeFeatures::EnableFeatureFromString("DigitalGoods", false);
  // Need to disable NativeFileSystem feature here in addition to disabling
  // blink::features::kNativeFileSystemAPI in brave_main_delegate.cc because
  // this feature is not part of SetRuntimeFeaturesFromChromiumFeatures function
  // and instead can only be turned on (not off) via kNativeFileSystemAPI in
  // SetCustomizedRuntimeFeaturesFromCombinedArgs.
  blink::WebRuntimeFeatures::EnableFeatureFromString("NativeFileSystem", false);
}

BraveContentRendererClient::~BraveContentRendererClient() = default;
