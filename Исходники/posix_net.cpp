/*
====================
IPSocket
====================
*/
static int IPSocket( const char *net_interface, int port, netadr_t *bound_to = NULL )
{
    int newsocket;
    struct sockaddr_in address;
    int i = 1;

    if ( net_interface )
    {
        common->Printf( "Opening IP socket: %s:%i\n", net_interface, port );
    }
    else
    {
        common->Printf( "Opening IP socket: localhost:%i\n", port );
    }

    if ( ( newsocket = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP ) ) == -1 )
    {
        common->Printf( "ERROR: IPSocket: socket: %s", strerror( errno ) );
        return 0;
    }
    // make it non-blocking
    int on = 1;
    if ( ioctl( newsocket, FIONBIO, &on ) == -1 )
    {
        common->Printf( "ERROR: IPSocket: ioctl FIONBIO:%s\n",
                        strerror( errno ) );
        return 0;
    }
    // make it broadcast capable
    if ( setsockopt( newsocket, SOL_SOCKET, SO_BROADCAST, (char *) &i, sizeof(i) ) == -1 )
    {
        common->Printf( "ERROR: IPSocket: setsockopt SO_BROADCAST:%s\n", strerror( errno ) );
        return 0;
    }

    if ( !net_interface || !net_interface[ 0 ]
            || !idStr::Icmp( net_interface, "localhost" ) )
    {
        address.sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        StringToSockaddr( net_interface, &address, true );
    }

    if ( port == PORT_ANY )
    {
        address.sin_port = 0;
    }
    else
    {
        address.sin_port = htons((short) port);
    }

    address.sin_family = AF_INET;

    if ( bind( newsocket, (const struct sockaddr *)&address, sizeof( address ) ) == -1 )
    {
        common->Printf( "ERROR: IPSocket: bind: %s\n", strerror( errno ) );
        close( newsocket );
        return 0;
    }

    if ( bound_to )
    {
        unsigned int len = sizeof( address );
        if ( (unsigned int)(getsockname( newsocket, (struct sockaddr *)&address, (socklen_t*)&len )) == -1 )
        {
            common->Printf( "ERROR: IPSocket: getsockname: %s\n", strerror( errno ) );
            close( newsocket );
            return 0;
        }
        SockadrToNetadr( &address, bound_to );
    }

    return newsocket;
}