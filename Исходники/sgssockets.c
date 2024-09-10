static int sgs_socket_address( SGS_CTX )
{
	struct sockaddr_storage ss;
	char* buf;
	sgs_SizeVal bufsize;
	sgs_Int af;
	uint16_t port = 0;
	
	SGSFN( "socket_address" );
	if( !sgs_LoadArgs( C, "im|+w", &af, &buf, &bufsize, &port ) )
		return 0;
	
	if( af != AF_INET && af != AF_INET6 )
		STDLIB_WARN( "argument 1 (address family)"
			" must be either AF_INET or AF_INET6" )
	
	memset( &ss, 0, sizeof(ss) );
	
	ss.ss_family = (sa_family_t) af;
	port = htons( port );
	{
#ifdef _WIN32
		INT len = sizeof( ss );
		int res = sockassert( C, WSAStringToAddressA( buf, (int16_t) af,
			NULL, (struct sockaddr*) &ss, &len ) == 0 );
#else
		int res = sockassert( C, inet_pton( (int16_t) af, buf, &ss ) == 1 );
#endif
		if( !res )
			STDLIB_WARN( "failed to generate address from string" )
	}
	
	if( af == AF_INET )
	{
		struct sockaddr_in* sai = (struct sockaddr_in*) &ss;
		sai->sin_port = port;
	}
	else if( af == AF_INET6 )
	{
		struct sockaddr_in6* sai = (struct sockaddr_in6*) &ss;
		sai->sin6_port = port;
	}
	else
		STDLIB_WARN( "INTERNAL ERROR (unexpected AF value)" )
	
	push_sockaddr( C, &ss, sizeof(ss) );
	return 1;
}