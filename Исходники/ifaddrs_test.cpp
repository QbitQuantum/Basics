TEST(ifaddrs, inet6_scope_ids) {
  ifaddrs* addrs;
  ASSERT_EQ(0, getifaddrs(&addrs));

  for (ifaddrs* ifa = addrs; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET6) {
      sockaddr_in6* sa6 = reinterpret_cast<sockaddr_in6*>(ifa->ifa_addr);
      // Any link-local IPv6 address should have a scope id. (http://b/27219454.)
      // 0 isn't a valid interface index, so that would mean the scope id wasn't set.
      if (IN6_IS_ADDR_LINKLOCAL(&sa6->sin6_addr) || IN6_IS_ADDR_MC_LINKLOCAL(&sa6->sin6_addr)) {
        ASSERT_NE(sa6->sin6_scope_id, 0U);
      }
    }
  }

  freeifaddrs(addrs);
}