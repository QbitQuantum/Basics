BOOL CwsGameServer::CreateServer(LPSTR ip_addr, WORD port, DWORD WinServerMsg, DWORD WinClientMsg)
{
	sockaddr_in addr;
	int nResult;
	
	if (this->m_hWnd == 0 )
	{
		MsgBox("windows handle error");
		return 0;
	}

	memset(&addr, 0, sizeof(addr) );

	addr.sin_family=AF_INET; // INET
	addr.sin_addr.S_un.S_addr=htonl(0);
	addr.sin_port=htons(port);

	nResult=bind(this->m_socket, (sockaddr*)&addr, 16);

	if ( nResult == -1 )
	{
		LogAdd("Server bind error %d", WSAGetLastError() );
		closesocket(this->m_socket);
		return 0;
	}

	nResult=listen(this->m_socket , 4);

	if (nResult == -1)
	{
		closesocket(this->m_socket );
		LogAdd("Server listen error %d", WSAGetLastError() );
		return 0;
	}

	nResult=WSAAsyncSelect( this->m_socket , this->m_hWnd , WinServerMsg, FD_ACCEPT);

	if (nResult == -1)
	{
		closesocket(this->m_socket);
		LogAdd("Server WSAAsyncSelect error %d", WSAGetLastError());
		return 0;
	}

	this->m_WinClientMsg  =WinClientMsg;
	return 1;
}