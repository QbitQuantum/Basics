/*
========================
NET_IPSocket
========================
*/
int NET_IPSocket( const char* bind_ip, int port, netadr_t* bound_to )
{
	SOCKET				newsocket;
	sockaddr_in			address;
	
	if( port != PORT_ANY )
	{
		if( bind_ip )
		{
			idLib::Printf( "Opening IP socket: %s:%i\n", bind_ip, port );
		}
		else
		{
			idLib::Printf( "Opening IP socket: localhost:%i\n", port );
		}
	}
	
	if( ( newsocket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ) ) == INVALID_SOCKET )
	{
		idLib::Printf( "WARNING: UDP_OpenSocket: socket: %s\n", NET_ErrorString() );
		return 0;
	}
	
	// make it non-blocking
#ifdef _WIN32 // which has no fcntl()
	unsigned long	_true = 1;
	if( ioctlsocket( newsocket, FIONBIO, &_true ) == SOCKET_ERROR )
	{
		idLib::Printf( "WARNING: UDP_OpenSocket: ioctl FIONBIO: %s\n", NET_ErrorString() );
		closesocket( newsocket );
		return 0;
	}
#else
	int flags = fcntl( newsocket, F_GETFL, 0 );
	if( flags < 0 )
	{
		idLib::Printf( "WARNING: UDP_OpenSocket: fcntl F_GETFL: %s\n", NET_ErrorString() );
		closesocket( newsocket );
		return 0;
	}
	flags |= O_NONBLOCK;
	if( fcntl( newsocket, F_SETFL, flags ) < 0 )
	{
		idLib::Printf( "WARNING: UDP_OpenSocket: fcntl F_SETFL with O_NONBLOCK: %s\n", NET_ErrorString() );
		closesocket( newsocket );
		return 0;
	}
#endif
	
	// make it broadcast capable
	int i = 1;
	if( setsockopt( newsocket, SOL_SOCKET, SO_BROADCAST, ( char* )&i, sizeof( i ) ) == SOCKET_ERROR )
	{
		idLib::Printf( "WARNING: UDP_OpenSocket: setsockopt SO_BROADCAST: %s\n", NET_ErrorString() );
		closesocket( newsocket );
		return 0;
	}
	
	if( !bind_ip || !bind_ip[0] || !idStr::Icmp( bind_ip, "localhost" ) )
	{
		address.sin_addr.s_addr = INADDR_ANY;
	}
	else
	{
		Net_StringToSockaddr( bind_ip, &address, true );
	}
	
	if( port == PORT_ANY )
	{
		address.sin_port = 0;
	}
	else
	{
		address.sin_port = htons( ( short )port );
	}
	
	address.sin_family = AF_INET;
	
	if( bind( newsocket, ( const sockaddr* )&address, sizeof( address ) ) == SOCKET_ERROR )
	{
		idLib::Printf( "WARNING: UDP_OpenSocket: bind: %s\n", NET_ErrorString() );
		closesocket( newsocket );
		return 0;
	}
	
	// if the port was PORT_ANY, we need to query again to know the real port we got bound to
	// ( this used to be in idUDP::InitForPort )
	if( bound_to )
	{
		socklen_t len = sizeof( address );
		if( getsockname( newsocket, ( struct sockaddr* )&address, &len ) == SOCKET_ERROR )
		{
			common->Printf( "ERROR: IPSocket: getsockname: %s\n", NET_ErrorString() );
			closesocket( newsocket );
			return 0;
		}
		Net_SockadrToNetadr( &address, bound_to );
	}
	
	return newsocket;
}