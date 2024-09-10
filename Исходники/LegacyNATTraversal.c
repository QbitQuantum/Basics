static int
inet_pton( int family, const char * addr, void * dst )
	{
	struct sockaddr_storage ss;
	int sslen = sizeof( ss );

	ZeroMemory( &ss, sizeof( ss ) );
	ss.ss_family = family;

	if ( WSAStringToAddressA( addr, family, NULL, ( struct sockaddr* ) &ss, &sslen ) == 0 )
		{
		if ( family == AF_INET ) { memcpy( dst, &( ( struct sockaddr_in* ) &ss)->sin_addr, sizeof( IN_ADDR ) ); return 1; }
		else if ( family == AF_INET6 ) { memcpy( dst, &( ( struct sockaddr_in6* ) &ss)->sin6_addr, sizeof( IN6_ADDR ) ); return 1; }
		else return 0;
		}
	else return 0;
	}