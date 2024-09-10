// Use the socket in the CHandshakes object to listen for remote computers who want to connect to us
// Returns true if we're listening, false if it didn't work
BOOL CHandshakes::Listen()
{
	if ( IsValid() )
		return TRUE;

	// Make sure only one thread can execute the code of this method at a time
	CSingleLock pLock( &m_pSection, TRUE ); // When the method exits, local pLock will be destructed, and the lock released

	m_hSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( ! IsValid() )	// Now, make sure it has been created
	{
		theApp.Message( MSG_ERROR, _T("Failed to create TCP socket. (1st Try)") );
		// Second attempt
		m_hSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
		if ( ! IsValid() )
		{
			theApp.Message( MSG_ERROR, _T("Failed to create TCP socket. (2nd Try)") );
			return FALSE;
		}
	}

	// Disables the Nagle algorithm for send coalescing
	VERIFY( setsockopt( m_hSocket, IPPROTO_TCP, TCP_NODELAY, "\x01", 1) == 0 );

	// Get our computer's Internet IP address and port number from the network object
	SOCKADDR_IN saHost = Network.m_pHost; // This is the address of our computer as visible to remote computers on the Internet

	// If the program connection settings disallow binding, zero the 4 bytes of the IP address
	if ( ! Settings.Connection.InBind ) 
		saHost.sin_addr.s_addr = INADDR_ANY; // s_addr is the IP address formatted as a single u_long
	else
	{
		// Set the exclusive address option
		VERIFY( setsockopt( m_hSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, "\x01", 1 ) == 0 );
	}

	// First attempt to bind socket
	if ( bind( m_hSocket, (SOCKADDR*)&saHost, sizeof( saHost ) ) != 0 )
	{
		theApp.Message( MSG_ERROR, IDS_NETWORK_CANT_LISTEN, (LPCTSTR)CString( inet_ntoa( saHost.sin_addr ) ), htons( saHost.sin_port ) );

		if ( saHost.sin_addr.s_addr == INADDR_ANY )
			return FALSE;

		// Second attempt to bind socket
		saHost.sin_addr.s_addr = INADDR_ANY;
		if ( bind( m_hSocket, (SOCKADDR*)&saHost, sizeof( saHost ) ) != 0 )
		{
			theApp.Message( MSG_ERROR, IDS_NETWORK_CANT_LISTEN, (LPCTSTR)CString( inet_ntoa( saHost.sin_addr ) ), htons( saHost.sin_port ) );
			return FALSE;
		}
	}

	// Report that we are now listening on our IP address
	theApp.Message( MSG_INFO, IDS_NETWORK_LISTENING_TCP, (LPCTSTR)CString( inet_ntoa( saHost.sin_addr ) ), htons( saHost.sin_port ) );

	// Set it up so that when a remote computer connects to us, the m_pWakeup event is fired
	WSAEventSelect(		// Specify an event object to associate with the specified set of FD_XXX network events
		m_hSocket,		// Our listening socket
		GetWakeupEvent(),		// Our event, a CEvent object member variable
		FD_ACCEPT );	// The network event to trigger this is us accepting a remote computer's connection

	// Have the socket wait, listening for remote computer on the Internet to connect to it
	listen(			// Place a socket in a state in which it is listening for an incoming connection
		m_hSocket,	// Our socket
		256 );		// Maximum length of the queue of pending connections, let 256 computers try to call us at once (do)

	Network.AcquireLocalAddress( m_hSocket );

	// Create a new thread to run the ThreadStart method, passing it a pointer to this C
	return BeginThread( "Handshakes" );
}