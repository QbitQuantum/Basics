bool NameServers(vector<IPV4Address> *name_servers) {
#if HAVE_DECL_RES_NINIT
  struct __res_state res;
  memset(&res, 0, sizeof(struct __res_state));

  // Init the resolver info each time so it's always current for the RDM
  // responders in case we've set it via RDM too
  if (res_ninit(&res) != 0) {
    OLA_WARN << "Error getting nameservers via res_ninit";
    return false;
  }

  for (int32_t i = 0; i < res.nscount; i++) {
    IPV4Address addr = IPV4Address(res.nsaddr_list[i].sin_addr.s_addr);
    OLA_DEBUG << "Found Nameserver " << i << ": " << addr;
    name_servers->push_back(addr);
  }

  res_nclose(&res);
#elif defined(_WIN32)
  ULONG size = sizeof(FIXED_INFO);
  PFIXED_INFO fixed_info = NULL;
  while (1) {
    fixed_info = reinterpret_cast<PFIXED_INFO>(new uint8_t[size]);
    DWORD result = GetNetworkParams(fixed_info, &size);
    if (result == ERROR_SUCCESS) {
      break;
    }

    if (result != ERROR_BUFFER_OVERFLOW) {
      OLA_WARN << "GetNetworkParams failed with: " << GetLastError();
      return false;
    }

    delete[] fixed_info;
  }

  IP_ADDR_STRING* addr = &(fixed_info->DnsServerList);
  for (; addr; addr = addr->Next) {
    IPV4Address ipv4addr = IPV4Address(inet_addr(addr->IpAddress.String));
    OLA_DEBUG << "Found nameserver: " << ipv4addr;
    name_servers->push_back(ipv4addr);
  }

  delete[] fixed_info;
#else
  // Init the resolver info each time so it's always current for the RDM
  // responders in case we've set it via RDM too
  if (res_init() != 0) {
    OLA_WARN << "Error getting nameservers via res_init";
    return false;
  }

  for (int32_t i = 0; i < _res.nscount; i++) {
    IPV4Address addr = IPV4Address(_res.nsaddr_list[i].sin_addr.s_addr);
    OLA_DEBUG << "Found Nameserver " << i << ": " << addr;
    name_servers->push_back(addr);
  }
#endif

  return true;
}