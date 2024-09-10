RNS2BindResult RNS2_Berkley::BindSharedIPV4And6( RNS2_BerkleyBindParameters *bindParameters, const char *file, unsigned int line ) {
	
	(void) file;
	(void) line;
	(void) bindParameters;

#if RAKNET_SUPPORT_IPV6==1

	int ret=0;
	struct addrinfo hints;
	struct addrinfo *servinfo=0, *aip;  // will point to the results
	PrepareAddrInfoHints2(&hints);
	hints.ai_family=bindParameters->addressFamily;
	char portStr[32];
	Itoa(bindParameters->port,portStr,10);

	// On Ubuntu, "" returns "No address associated with hostname" while 0 works.
	if (bindParameters->hostAddress && 
		(_stricmp(bindParameters->hostAddress,"UNASSIGNED_SYSTEM_ADDRESS")==0 || bindParameters->hostAddress[0]==0))
	{
		getaddrinfo(0, portStr, &hints, &servinfo);
	}
	else
	{
		getaddrinfo(bindParameters->hostAddress, portStr, &hints, &servinfo);
	}

	// Try all returned addresses until one works
	for (aip = servinfo; aip != NULL; aip = aip->ai_next)
	{
		// Open socket. The address type depends on what
		// getaddrinfo() gave us.
		rns2Socket = socket__(aip->ai_family, aip->ai_socktype, aip->ai_protocol);

		if (rns2Socket == -1)
			return BR_FAILED_TO_BIND_SOCKET;

		ret = bind__(rns2Socket, aip->ai_addr, (int) aip->ai_addrlen );
		if (ret>=0)
		{
			// Is this valid?
			memcpy(&boundAddress.address.addr6, aip->ai_addr, sizeof(boundAddress.address.addr6));

			freeaddrinfo(servinfo); // free the linked-list

			SetSocketOptions();
			SetNonBlockingSocket(bindParameters->nonBlockingSocket);
			SetBroadcastSocket(bindParameters->setBroadcast);

			GetSystemAddressIPV4And6( rns2Socket, &boundAddress );
			
			return BR_SUCCESS;
		}
		else
		{
			closesocket__(rns2Socket);
		}
	}
	
	return BR_FAILED_TO_BIND_SOCKET;

#else
return BR_REQUIRES_RAKNET_SUPPORT_IPV6_DEFINE;
#endif
}