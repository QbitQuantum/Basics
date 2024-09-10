// TODO: To act as construct.
bool 
libsockclient_init(char *Host, int Port) 
{
	WSADATA wsaData;
	struct hostent *pServer;
	struct sockaddr_in pServerAddr;
	int err;

	// TODO: To initial use of WS2_32.DLL by a process.
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) 
	{
#if DEBUG
		printf("DEBUG at %d: WSAStartup error.\n", __LINE__);
#endif
		m_ErrorCode = WSAGetLastError();
		return false;
	}

	// TODO: To create a socket that is bound to a specific transport service 
    // provider, and optionally creates and/or joins a socket group.
	m_SocketHandler = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 
        WSA_FLAG_OVERLAPPED);
	if (m_SocketHandler == INVALID_SOCKET) 
	{
#if DEBUG
		printf("DEBUG at %d: WSASocket error.\n", __LINE__);
#endif
		m_ErrorCode = WSAGetLastError();
		return false;
	}

	// TODO: To retrieve host information corresponding to a host name from a 
    // host database.
	pServer = gethostbyname(Host);
	if (pServer == NULL) 
	{
#if DEBUG
		printf("DEBUG at %d: gethostbyname error.\n", __LINE__);
#endif
		m_ErrorCode = WSAGetLastError();
		libsockclient_cleanup();
		return false;
	}

	// TODO: To establishe a connection to another socket application, exchanges 
    // connect data, and specifies needed quality of service based on the supplied 
    // FLOWSPEC structure.
	ZeroMemory((char *)&pServerAddr, sizeof(pServerAddr));
	pServerAddr.sin_family = AF_INET;
	pServerAddr.sin_port = htons(Port);
	CopyMemory((char *)&pServerAddr.sin_addr.s_addr, (char *)pServer->h_addr, 
		pServer->h_length);
	if (SOCKET_ERROR == WSAConnect(m_SocketHandler, 
		reinterpret_cast<const struct sockaddr *>(&pServerAddr), sizeof(pServerAddr), 
		NULL, NULL, NULL, NULL)) 
	{
#if DEBUG
		printf("DEBUG at %d: WSAConnect error.\n", __LINE__);
#endif
		libsockclient_cleanup();
		m_ErrorCode = WSAGetLastError();
		return false;
	}

	m_Host = Host;
	m_Port = Port;
	return true;
}