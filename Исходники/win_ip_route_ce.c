static Boolean ssh_ip_route_lookup_ipv4(
  SshIpAddr destination, DWORD *ifindex, SshIpAddr nexthop, DWORD *mtu)
{
  DWORD d, error;
  MIB_IPFORWARDROW ifr;

  SSH_IP4_ENCODE(destination, &d);
  error = GetBestRoute(d, 0, &ifr);
  if (error != NO_ERROR)
    {
      if (error == ERROR_CAN_NOT_COMPLETE)
        {
          SSH_DEBUG(SSH_D_LOWOK, ("No route found"));
          return FALSE;
        }
      else
        {
          SSH_DEBUG(SSH_D_FAIL,
            ("GetBestRoute: error 0x%08X", (unsigned)error));
          return FALSE;
        }
    }

  /* Do not consider local routes via loopback interfaces. */
  if (ifr.dwForwardProto == MIB_IPPROTO_LOCAL &&
      (ifr.dwForwardDest & ifr.dwForwardMask) !=
      (ifr.dwForwardNextHop & ifr.dwForwardMask))
    {
      SSH_DEBUG(SSH_D_LOWOK, ("Ignoring loopback route"));
      return FALSE;
    }

  *ifindex = ifr.dwForwardIfIndex;

  /* For directly connected destinatinations report the destination as
     the next hop. */
  if (ifr.dwForwardType == MIB_IPROUTE_TYPE_DIRECT)
    SSH_IP4_DECODE(nexthop, &d);
  else
    SSH_IP4_DECODE(nexthop, &ifr.dwForwardNextHop);

  /* No route MTU; use link MTU. */
  *mtu = 0;

  return TRUE;
}