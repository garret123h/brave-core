// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_URL_AUTH_UTIL_H_
#define NET_BASE_URL_AUTH_UTIL_H_

#include "net/base/net_export.h"

namespace net {

NET_EXPORT bool ParseAuthHostAndPort(
    base::StringPiece input,
    std::string* up_host_ret,
    int* port);

}

#endif  // NET_BASE_URL_AUTH_UTIL_H_
