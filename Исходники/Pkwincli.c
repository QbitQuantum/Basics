void 
main( int argc, char **argv )
{
    SOCKET	sock;
    int		arg;
    char	*host = DEFAULT_HOST;
    u_short	port = (u_short)DEFAULT_PORT;

    for( arg = 1; arg < argc; arg++ )
    {
	if ( argv[ arg ][0] != '-' )
	{
	    fprintf( stderr, "Invalid command line argument: %s\n", argv[ arg ] );
	    exit(1);
	}

	switch( argv[ arg ][1] )
	{
	case 'h':
	    printf( "-t <host>\tTarget host name (default 'localhost')\n" );
	    printf( "-p <port>\tTarget port number (default 16903)\n" );
	    printf( "-e\t\tAES Mode ECB\n" );
	    printf( "-v\t\tVerbose\n" );
	    exit(0);

	case 't' :  host = argv[ ++arg ];		break;
	case 'p' :  port = atoi( argv[ ++arg ] );	break;
	case 'e' :  sessKeyMode = CRYPT_MODE_ECB;	break;
	case 'v' :  verbose = TRUE;			break;

	default:
	    fprintf( stderr, "Invalid command line flag: %s\n", argv[ arg ] );
	    exit(1);
	}
    }

    if ( ! initCrypt() )  exit(1);
    sock = tcpConnect( host, port );
    if ( ! initSession( sock ) )  exit(1);
    if ( ! clientRequest( sock, host, port ) )  exit(1);
    shutdown( sock, 2 );
    closesocket( sock );

    if ( WSACleanup() == SOCKET_ERROR )
	fprintf( stderr, "Problem with socket cleanup\n" );

    termCrypt();

    exit(0);
}