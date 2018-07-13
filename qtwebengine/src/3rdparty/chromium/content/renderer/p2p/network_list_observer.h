// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_P2P_NETWORK_LIST_OBSERVER_H_
#define CONTENT_RENDERER_P2P_NETWORK_LIST_OBSERVER_H_

#include <vector>

#include "net/base/ip_address_number.h"

namespace net {
struct NetworkInterface;
typedef std::vector<NetworkInterface> NetworkInterfaceList;
}  // namespace net

namespace content {

class NetworkListObserver {
 public:
  virtual ~NetworkListObserver() {}

  virtual void OnNetworkListChanged(
      const net::NetworkInterfaceList& list,
      const net::IPAddressNumber& default_ipv4_local_address,
      const net::IPAddressNumber& default_ipv6_local_address) = 0;

 protected:
  NetworkListObserver() {}
};

}  // namespace content

#endif  // CONTENT_RENDERER_P2P_NETWORK_LIST_OBSERVER_H_