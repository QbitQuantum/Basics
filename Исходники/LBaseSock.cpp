/*========================================================================================
	FUNCTION: LBaseSock::Listen()
	DESCRIPT: Listen connections for the server socket.
	RETURN	:
		EWS_NO_ERR: Success!
		Others	  : System error code
	ARGUMENT:
		szAddr	   : (i)IP address
		nPort	   : (i)Port #
		nMaxConnect: (i)Max. # of connections accepted (Default = 1)
	UPDATE	: 2004/07/01, In-hyeok Paek; First work!
========================================================================================*/
int LBaseSock::Listen( char *szAddr, int nPort, int nMaxConnect )
{
	SOCKADDR_IN		SockAddr;	//	Socket address structure
	BOOL	bOpt = true;
	DWORD	dwResult;	//	Function result
	int		nResult;	//	Function result

	//	Get the socket descriptor.
	if( (m_Sock = socket( AF_INET, SOCK_STREAM, 0 )) == INVALID_SOCKET ) {
		return (m_nLastErr = WSAGetLastError());
	}

	//	Set the socket option.
	setsockopt( m_Sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&bOpt, sizeof( bOpt ) );

	//	Bind socket.
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons( (u_short)nPort );
	if( szAddr == NULL ) { SockAddr.sin_addr.s_addr = htonl( INADDR_ANY ); }
	else {
		dwResult = inet_addr( szAddr );
		if( dwResult == INADDR_NONE ) { return (m_nLastErr = WSAGetLastError()); }
		SockAddr.sin_addr.s_addr = dwResult;
	}
	if( bind( m_Sock, (LPSOCKADDR)&SockAddr, sizeof( SOCKADDR ) ) == SOCKET_ERROR ) {
		return (m_nLastErr = WSAGetLastError());
	}

	//	Select the socket event.
	nResult = WSAAsyncSelect( m_Sock, m_hWnd, WM_SOCK_SOCKET,
							  FD_ACCEPT | FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE );
	if( nResult == SOCKET_ERROR ) { return (m_nLastErr = WSAGetLastError()); }

	//	Listen connections.
	if( listen( m_Sock, nMaxConnect ) == SOCKET_ERROR ) {
		m_nLastErr = WSAGetLastError();
		closesocket( m_Sock );
		m_Sock = INVALID_SOCKET;
		return m_nLastErr;
	}
	m_fListenSocket = true;

	return EWS_NO_ERR;
}