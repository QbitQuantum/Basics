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
	char portStr[32], *p;
#if defined (_WIN32)
	int addrlen = sizeof(saddr);
	HMODULE hWsock;
	getaddrinfo_ptr_t getaddrinfo_ptr;
	freeaddrinfo_ptr_t freeaddrinfo_ptr;
	int resolvesuccess = 0;
#endif

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

	// Free the strings if defined; may be the case when the session is reused after the connection fails
	free_ircsession_strings( session );

	// Handle the server # prefix (SSL)
	if ( server[0] == SSL_PREFIX )
	{
#if defined (ENABLE_SSL)
		server++;
		session->flags |= SESSIONFL_SSL_CONNECTION;
#else
		session->lasterror = LIBIRC_ERR_SSL_NOT_SUPPORTED;
		return 1;
#endif
	}

	if ( username )
		session->username = strdup (username);

	if ( server_password )
		session->server_password = strdup (server_password);

	if ( realname )
		session->realname = strdup (realname);

	session->nick = strdup (nick);
	session->server = strdup (server);

	// If port number is zero and server contains the port, parse it
	if ( port == 0 && (p = strchr( session->server, ':' )) != 0 )
	{
		// Terminate the string and parse the port number
		*p++ = '\0';
		port = atoi( p );
	}

	memset( &saddr, 0, sizeof(saddr) );
	saddr.sin6_family = AF_INET6;
	saddr.sin6_port = htons (port);

	sprintf( portStr, "%u", (unsigned)port );

#if defined (_WIN32)
	if ( WSAStringToAddressA( (LPSTR)session->server, AF_INET6, NULL, (struct sockaddr *)&saddr, &addrlen ) == SOCKET_ERROR )
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

				if ( getaddrinfo_ptr(session->server, portStr, &ainfo, &res) == 0 && res )
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
	if ( inet_pton( AF_INET6, session->server, (void*) &saddr.sin6_addr ) <= 0 )
	{
		memset( &ainfo, 0, sizeof(ainfo) );
		ainfo.ai_family = AF_INET6;
		ainfo.ai_socktype = SOCK_STREAM;
		ainfo.ai_protocol = 0;

		if ( getaddrinfo( session->server, portStr, &ainfo, &res ) || !res )
		{
			session->lasterror = LIBIRC_ERR_RESOLV;
			return 1;
		}

		memcpy( &saddr, res->ai_addr, res->ai_addrlen );
		freeaddrinfo( res );
	}
#endif

	// create the IRC server socket
	if ( socket_create( PF_INET6, SOCK_STREAM, &session->sock)
	|| socket_make_nonblocking (&session->sock) )
	{
		session->lasterror = LIBIRC_ERR_SOCKET;
		return 1;
	}

#if defined (ENABLE_SSL)
	// Init the SSL stuff
	if ( session->flags & SESSIONFL_SSL_CONNECTION )
	{
		int rc = ssl_init( session );

		if ( rc != 0 )
			return rc;
	}
#endif

    // and connect to the IRC server
    if ( socket_connect (&session->sock, (struct sockaddr *) &saddr, sizeof(saddr)) )
    {
    	session->lasterror = LIBIRC_ERR_CONNECT;
		return 1;
    }

    session->state = LIBIRC_STATE_CONNECTING;
    session->flags = 0; // reset in case of reconnect
	return 0;
#else
	session->lasterror = LIBIRC_ERR_NOIPV6;
	return 1;
#endif
}