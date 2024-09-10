int
DNSlookup_name(
	const char *name,
	int ai_family,
	struct hostent **Addresses
)
{
	char buffer[sizeof(WSAQUERYSET) + 2048];
	WSAQUERYSET query;
	struct hostent *addr = NULL;
	char *bufaddr = NULL;
	char ** addrlist = &bufaddr;
	int addrcnt = 0;
	WSAQUERYSET *results = (WSAQUERYSET *) buffer;
	GUID	HostnameGUID = SVCID_INET_HOSTADDRBYNAME;
	HANDLE	handle;
	DWORD dwLength;
	int err = 0;
	int retcode = 0;
	int errcode = 0;
	DWORD i;

	/*
	 * First we must create a query set
	 */
	memset(&query, 0, sizeof(query));
	query.dwSize = sizeof(query);
	query.lpszServiceInstanceName = (char *)name;
	query.dwNameSpace = NS_DNS;
	query.lpServiceClassId = &HostnameGUID;

	err = WSALookupServiceBegin(&query,
                                 LUP_RETURN_NAME | LUP_RETURN_BLOB | LUP_RETURN_ADDR,
                                 &handle);

	if(err == SOCKET_ERROR)
	{
		/*
		 * Convert the error code and return
		 */
		return (ReturnCode(WSAGetLastError()));
	}

	/*
	 * Initially none
	 * Change if we get something
	 */
	retcode = EAI_NONAME;
	dwLength = sizeof(buffer);

	while(err == 0)		/* Drop out when error */
	{
		memset(&buffer, 0, dwLength);
		err = WSALookupServiceNext(
			                handle,
			                0,
			                &dwLength,
			                results);
		errcode = WSAGetLastError();
		if (results->dwNumberOfCsAddrs > 0)
		{
			if (addr == NULL)
			{
				addr = (struct hostent *) malloc(sizeof(struct hostent));
				memset(addr, 0, sizeof(struct hostent));
				addr->h_addrtype = (short) results->lpcsaBuffer->iSocketType;
				addr->h_length = sizeof(struct in_addr); /* Only passing back the address */
				addrlist = malloc(sizeof(char *));
				*addrlist = NULL;
			}
			for (i = 0; i < results->dwNumberOfCsAddrs; i++)
			{
				AddToAddresses(addrlist, &addrcnt, &results->lpcsaBuffer[i]);
			}
		}

	}
	if (addr != NULL)
	{
		addr->h_name = (char *) name;
		addr->h_addr_list = addrlist;
		retcode = 0;
		*Addresses = addr;
	}
	else
	{
#ifdef FORCE_DNSRETRY
		/*
		 * We do this or the error would never be logged
		 */
		if (errcode == WSANO_DATA)
			msyslog(LOG_ERR, "Address not found for %s", name);
#endif
		retcode = ReturnCode(errcode);
	}
	WSALookupServiceEnd(handle);
	return (retcode);
}