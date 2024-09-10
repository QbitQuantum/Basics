//--    main()              ///{{{1///////////////////////////////////////////
int main( int argc, char* argv[] )
{
	int serverPort = kServerPort;

	// did the user specify a port?
	if( 2 == argc )
	{
		serverPort = atoi(argv[1]);
	}

#	if VERBOSE
	printf( "Attempting to bind to port %d\n", serverPort );
#	endif

	// set up listening socket - see setup_server_socket() for details.
	int listenfd = setup_server_socket( serverPort );

	if( -1 == listenfd )
		return 1;

	// loop forever
	while( 1 )
	{
		sockaddr_in clientAddr;
		socklen_t addrSize = sizeof(clientAddr);

		// accept a single incoming connection
		int clientfd = accept( listenfd, (sockaddr*)&clientAddr, &addrSize );
		printf("Accepted a new client.. \n");

		if( -1 == clientfd )
		{
			perror( "accept() failed" );
			continue; // attempt to accept a different client.
		}

#			if VERBOSE
		// print some information about the new client
		char buff[128];
		printf( "Connection from %s:%d -> socket %d\n",
			inet_ntop( AF_INET, &clientAddr.sin_addr, buff, sizeof(buff) ),
			ntohs(clientAddr.sin_port),
			clientfd
		);
		fflush( stdout );
#			endif

#			if NONBLOCKING
		// enable non-blocking sends and receives on this socket
		if( !set_socket_nonblocking( clientfd ) )
			continue;
#			endif

		// initialize connection data
		ConnectionData connData;
		memset( &connData, 0, sizeof(connData) );

		connData.sock = clientfd;
		connData.state = eConnStateReceiving;

		// Repeatedly receive and re-send data from the connection. When
		// the connection closes, process_client_*() will return false, no
		// further processing is done.
		bool processFurther = true;
		while( processFurther )
		{
			while( processFurther && connData.state == eConnStateReceiving )
				processFurther = process_client_recv( connData );

			while( processFurther && connData.state == eConnStateSending )
				processFurther = process_client_send( connData );
		}

		// done - close connection
		close( connData.sock );
	}

	// The program will never reach this part, but for demonstration purposes,
	// we'll clean up the server resources here and then exit nicely.
	close( listenfd );

	return 0;
}