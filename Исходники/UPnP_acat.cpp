int SSDP_sendRequest(int s, uint32 ip, uint16 port, const CString& request)
{
	char buffer[10240];

	const CStringA sa(request);
	int length = sa.GetLength();
	strcpy(buffer, (const char*)sa);

	struct sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);

	MIB_IPFORWARDROW ip_forward;
	if ( GetBestRoute(inet_addr("223.255.255.255"), 0, &ip_forward) != NO_ERROR) return 0;
	sockaddr.sin_addr.S_un.S_addr = ip_forward.dwForwardNextHop;
	return sendto(s, buffer, length, 0, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
}