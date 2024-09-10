void genInterfaceAddress(const std::string& name,
                         const IP_ADAPTER_UNICAST_ADDRESS* ipaddr,
                         QueryData& results) {
  Row r;
  r["interface"] = name;

  switch (ipaddr->SuffixOrigin) {
  case IpSuffixOriginManual:
    r["type"] = "manual";
    break;
  case IpSuffixOriginDhcp:
    r["type"] = "dhcp";
    break;
  case IpSuffixOriginLinkLayerAddress:
  case IpSuffixOriginRandom:
    r["type"] = "auto";
    break;
  default:
    r["type"] = "unknown";
  }

  if (ipaddr->Address.lpSockaddr->sa_family == AF_INET) {
    ULONG mask;
    ConvertLengthToIpv4Mask(ipaddr->OnLinkPrefixLength, &mask);
    in_addr maskAddr;
    maskAddr.s_addr = mask;

    char addrBuff[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &maskAddr, addrBuff, INET_ADDRSTRLEN);
    r["mask"] = addrBuff;

    inet_ntop(
        AF_INET,
        &reinterpret_cast<sockaddr_in*>(ipaddr->Address.lpSockaddr)->sin_addr,
        addrBuff,
        INET_ADDRSTRLEN);
    r["address"] = addrBuff;
  } else if (ipaddr->Address.lpSockaddr->sa_family == AF_INET6) {
    in6_addr netmask;
    memset(&netmask, 0x0, sizeof(netmask));
    for (long i = ipaddr->OnLinkPrefixLength, j = 0; i > 0; i -= 8, ++j) {
      netmask.s6_addr[j] = i >= 8 ? 0xff : (ULONG)((0xffU << (8 - i)));
    }

    char addrBuff[INET6_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET6, &netmask, addrBuff, INET6_ADDRSTRLEN);
    r["mask"] = addrBuff;

    inet_ntop(
        AF_INET6,
        &reinterpret_cast<sockaddr_in6*>(ipaddr->Address.lpSockaddr)->sin6_addr,
        addrBuff,
        INET6_ADDRSTRLEN);
    r["address"] = addrBuff;
  }
  results.emplace_back(r);
}