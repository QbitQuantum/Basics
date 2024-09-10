/*
 * Adds or removes a route from the supplied request
 */
DWORD add_remove_route(Packet *packet, BOOLEAN add)
{
	MIB_IPFORWARDROW route;
	DWORD (WINAPI *LocalGetBestInterface)(IPAddr, LPDWORD) = NULL;
	LPCSTR subnet;
	LPCSTR netmask;
	LPCSTR gateway;

	subnet  = packet_get_tlv_value_string(packet, TLV_TYPE_SUBNET_STRING);
	netmask = packet_get_tlv_value_string(packet, TLV_TYPE_NETMASK_STRING);
	gateway = packet_get_tlv_value_string(packet, TLV_TYPE_GATEWAY_STRING);

	memset(&route, 0, sizeof(route));

	route.dwForwardDest    = inet_addr(subnet);
	route.dwForwardMask    = inet_addr(netmask);
	route.dwForwardNextHop = inet_addr(gateway);
	route.dwForwardType    = 4; // Assume next hop.
	route.dwForwardProto   = 3;
	route.dwForwardAge     = -1;

	if ((LocalGetBestInterface = (DWORD (WINAPI *)(IPAddr, LPDWORD))GetProcAddress(
			GetModuleHandle("iphlpapi"),
			"GetBestInterface")))
	{
		DWORD result = LocalGetBestInterface(route.dwForwardDest, 
				&route.dwForwardIfIndex);

		if (result != ERROR_SUCCESS)
			return result;
	}
	// I'm lazy.  Need manual lookup of ifindex based on gateway for NT.
	else
		return ERROR_NOT_SUPPORTED;

	if (add)
		return CreateIpForwardEntry(&route);
	else
		return DeleteIpForwardEntry(&route);
}