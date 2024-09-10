int irc_connect6 (irc_session_t * session,
			const char * server,
			unsigned short port,
			const char * server_password,
			const char * nick,
			const char * username,
			const char * realname)
{
#if defined (ENABLE_IPV6)
	struct sockaddr_in6 saddr;
	struct addrinfo ainfo, *res = NULL;
	char portStr[32];
#if defined (_WIN32)
	int addrlen = sizeof(saddr);
	HMODULE hWsock;
	getaddrinfo_ptr_t getaddrinfo_ptr;
	freeaddrinfo_ptr_t freeaddrinfo_ptr;
	int resolvesuccess = 0;
#endif // _WIN32
	sprintf(portStr, "%u", (unsigned)port);

	// Check and copy all the specified fields
	if ( !server || !nick )
	{
		session->lasterror = LIBIRC_ERR_INVAL;
		return 1;
	}

	if ( session->state != LIBIRC_STATE_INIT )
	{
		session->lasterror = LIBIRC_ERR_STATE;
		return 1;
	}

	if ( username )
		session->username = strdup (username);

	if ( server_password )
		session->server_password = strdup (server_password);

	if ( realname )
		session->realname = strdup (realname);

	session->nick = strdup (nick);
	session->server = strdup (server);

	memset( &saddr, 0, sizeof(saddr) );
	saddr.sin6_family = AF_INET6;
	saddr.sin6_port = htons (port);	

#if defined (_WIN32)
	if ( WSAStringToAddressA( (LPSTR)server, AF_INET6, NULL, (struct sockaddr *)&saddr, &addrlen ) == SOCKET_ERROR )
	{
		hWsock = LoadLibraryA("ws2_32");

		if (hWsock)
		{
			/* Determine functions at runtime, because windows systems < XP do not
			 * support getaddrinfo. */
			getaddrinfo_ptr = (getaddrinfo_ptr_t)GetProcAddress(hWsock, "getaddrinfo");
			freeaddrinfo_ptr = (freeaddrinfo_ptr_t)GetProcAddress(hWsock, "freeaddrinfo");

			if (getaddrinfo_ptr && freeaddrinfo_ptr)
			{
				memset(&ainfo, 0, sizeof(ainfo));
				ainfo.ai_family = AF_INET6;
				ainfo.ai_socktype = SOCK_STREAM;
				ainfo.ai_protocol = 0;

				if ( getaddrinfo_ptr(server, portStr, &ainfo, &res) == 0 && res )
				{
					resolvesuccess = 1;
					memcpy( &saddr, res->ai_addr, res->ai_addrlen );
					freeaddrinfo_ptr( res );
				}
			}
			FreeLibrary(hWsock);
		}
		if (!resolvesuccess)
		{
			session->lasterror = LIBIRC_ERR_RESOLV;
			return 1;
		}
	}
#else
	if ( inet_pton( AF_INET6, server, (void*) &saddr.sin6_addr ) <= 0 )
	{		
		memset( &ainfo, 0, sizeof(ainfo) );
		ainfo.ai_family = AF_INET6;
		ainfo.ai_socktype = SOCK_STREAM;
		ainfo.ai_protocol = 0;

		if ( getaddrinfo( server, portStr, &ainfo, &res ) || !res )
		{
			session->lasterror = LIBIRC_ERR_RESOLV;
			return 1;
		}
		
		memcpy( &saddr, res->ai_addr, res->ai_addrlen );
		freeaddrinfo( res );
	}
#endif // _WIN32
	
	// create the IRC server socket
	if ( socket_create( PF_INET6, SOCK_STREAM, &session->sock)
	|| socket_make_nonblocking (&session->sock) )
	{
		session->lasterror = LIBIRC_ERR_SOCKET;
		return 1;
	}

    // and connect to the IRC server
    if ( socket_connect (&session->sock, (struct sockaddr *) &saddr, sizeof(saddr)) )
    {
    	session->lasterror = LIBIRC_ERR_CONNECT;
		return 1;
    }

    session->state = LIBIRC_STATE_CONNECTING;
    session->motd_received = 0; // reset in case of reconnect
	return 0;
#else
	session->lasterror = LIBIRC_ERR_NOIPV6;
	return 1;
#endif // ENABLE_IPV6
}