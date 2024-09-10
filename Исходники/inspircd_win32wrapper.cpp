CoreExport int insp_inet_pton(int af, const char *src, void *dst)
{
	sockaddr_in sa;
	int len = sizeof(SOCKADDR);
	int rv = WSAStringToAddressA((LPSTR)src, af, NULL, (LPSOCKADDR)&sa, &len);
	if(rv >= 0)
	{
		if(WSAGetLastError() == WSAEINVAL)
			rv = 0;
		else
			rv = 1;
	}
	memcpy(dst, &sa.sin_addr, sizeof(struct in_addr));
	return rv;
}