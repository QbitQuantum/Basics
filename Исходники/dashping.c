int
inet_pton (int af, const char* src, void* dest)
{
	int					destSize;
	int					rc;
	int					ret;
	struct sockaddr_in	sockAddr;

	destSize = sizeof (sockAddr);
	rc = WSAStringToAddressA ((char*)src, 
							 af, 
							 0, 
							 (LPSOCKADDR)&sockAddr,
							 &destSize);
	if (0 != rc)
	{
		if (WSAGetLastError () == WSAEINVAL) { ret = -1; }
		else { ret = 0; }
	}
	else
	{
		memcpy (dest, &sockAddr.sin_addr, sizeof (sockAddr.sin_addr)); 
		ret = 1;
	}

	return ret;
}