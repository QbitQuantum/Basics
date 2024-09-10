//
// GetHostByName
//
struct hostent *Xbox::GetHostByName(const char *name)
{
	static struct hostent *he = NULL;
	unsigned long          addr = INADDR_NONE;
	WSAEVENT               hEvent;
	XNDNS                 *pDns = NULL;
	INT                    err;
	
	if(!name)
		return NULL;

	// This data is static and it should not be freed.
	if(!he)
	{
		he = (struct hostent *)malloc(sizeof(struct hostent));
		if(!he)
		{
			// Failed to allocate!
			return NULL;
		}

		he->h_addr_list = (char **)malloc(sizeof(char*));
		he->h_addr_list[0] = (char *)malloc(sizeof(struct in_addr));
	}

	if(isdigit(name[0]))
		addr = inet_addr(name);

	if(addr != INADDR_NONE)
		*(int *)he->h_addr_list[0] = addr;
	else
	{
		hEvent = WSACreateEvent();
		err = XNetDnsLookup(name, hEvent, &pDns);

		WaitForSingleObject( (HANDLE)hEvent, INFINITE);

		if(!pDns || pDns->iStatus != 0)
			return NULL;

		memcpy(he->h_addr_list[0], pDns->aina, sizeof(struct in_addr));

		XNetDnsRelease(pDns);
		WSACloseEvent(hEvent);
	}

	return he;
}