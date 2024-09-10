int getdefaultgateway(in_addr_t *addr)
{
  MIB_IPFORWARDROW ip_forward = {0};
	if(GetBestRoute(inet_addr("0.0.0.0"), 0, &ip_forward) != NO_ERROR)
		return -1;
	*addr = ip_forward.dwForwardNextHop;
	return 0;
}