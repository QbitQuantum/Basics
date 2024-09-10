/*
 * Remove a route from the kernel
 * @param destination the route to remove
 * @return negative on error
 */
int
os_route_del_rtentry(const struct rt_entry *rt, int ip_version)
{
  MIB_IPFORWARDROW Row;
  union olsr_ip_addr mask;
  unsigned long Res;
  struct interface *iface = rt->rt_nexthop.interface;

  if (AF_INET != ip_version) {
    /*
     * Not implemented
     */
    return -1;
  }

  OLSR_DEBUG(LOG_NETWORKING, "KERN: Deleting %s\n", olsr_rt_to_string(rt));

  memset(&Row, 0, sizeof(Row));

  Row.dwForwardDest = rt->rt_dst.prefix.v4.s_addr;

  if (!olsr_prefix_to_netmask(&mask, rt->rt_dst.prefix_len)) {
    return -1;
  }
  Row.dwForwardMask = mask.v4.s_addr;
  Row.dwForwardPolicy = 0;
  Row.dwForwardNextHop = rt->rt_nexthop.gateway.v4.s_addr;
  Row.dwForwardIfIndex = iface->if_index;
  // MIB_IPROUTE_TYPE_DIRECT and MIB_IPROUTE_TYPE_INDIRECT
  Row.dwForwardType = (rt->rt_dst.prefix.v4.s_addr == rt->rt_nexthop.gateway.v4.s_addr) ? 3 : 4;
  Row.dwForwardProto = 3;       // MIB_IPPROTO_NETMGMT
  Row.dwForwardAge = INFINITE;
  Row.dwForwardNextHopAS = 0;
  Row.dwForwardMetric1 = olsr_fib_metric(&rt->rt_metric);
  Row.dwForwardMetric2 = -1;
  Row.dwForwardMetric3 = -1;
  Row.dwForwardMetric4 = -1;
  Row.dwForwardMetric5 = -1;

  Res = DeleteIpForwardEntry(&Row);

  if (Res != NO_ERROR) {
    OLSR_WARN(LOG_NETWORKING, "DeleteIpForwardEntry() = %08lx, %s", Res, win32_strerror(Res));

    // XXX - report error in a different way

    errno = Res;

    return -1;
  }
  return 0;
}