bool CIOCPServer::Initialize(NOTIFYPROC pNotifyProc, CMainFrame* pFrame, int nMaxConnections, int nPort)
{
	m_pNotifyProc     = pNotifyProc;
	m_pFrame		  =  pFrame;
	m_nMaxConnections = nMaxConnections;

	m_socketListen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_socketListen)
	{
		TRACE(_T("Could not create listen socket %ld\n"),WSAGetLastError());
		return false;
	}

	// Event for handling Network IO
	m_hEvent = WSACreateEvent();

	if (WSA_INVALID_EVENT == m_hEvent)
	{
		TRACE(_T("WSACreateEvent() error %ld\n"),WSAGetLastError());
		closesocket(m_socketListen);
		return false;
	}

	// The listener is ONLY interested in FD_ACCEPT
	// That is when a client connects to or IP/Port
	// Request async notification
	int nRet = WSAEventSelect(m_socketListen,
						  m_hEvent,
						  FD_ACCEPT);

	if (SOCKET_ERROR == nRet)
	{
		TRACE(_T("WSAAsyncSelect() error %ld\n"),WSAGetLastError());
		closesocket(m_socketListen);
		return false;
	}

	SOCKADDR_IN	saServer;		
	// Listen on our designated Port#
	saServer.sin_port = htons(nPort);
	// Fill in the rest of the address structure
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;

	// bind our name to the socket
	nRet = bind(m_socketListen,
				(LPSOCKADDR)&saServer, 
				sizeof(struct sockaddr));
	if (SOCKET_ERROR == nRet)
	{
		TRACE(_T("bind() error %ld\n"),WSAGetLastError());
		closesocket(m_socketListen);
		return false;
	}

	// Set the socket to listen
	nRet = listen(m_socketListen, SOMAXCONN);
	if (nRet == SOCKET_ERROR)
	{
		TRACE(_T("listen() error %ld\n"),WSAGetLastError());
		closesocket(m_socketListen);
		return false;
	}

	UINT	dwThreadId = 0;
	m_hThread = (HANDLE)_beginthreadex(NULL,				// Security
									 0,					// Stack size - use default
									 ListenThreadProc,  // Thread fn entry point
									 (void*) this,	    
									 0,					// Init flag
									 &dwThreadId);	// Thread address

	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		InitializeIOCP();
		m_bInit = true;
		return true;
	}

	return false;
}