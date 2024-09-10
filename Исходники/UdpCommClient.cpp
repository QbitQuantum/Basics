BOOL 
CUdpCommClient::Init()
{
	//
	if (FALSE == CThreadClient::Init())
	{
		return FALSE;
	}

	//
	if (FALSE == m_bSockLibFlag)
	{
		return FALSE;
	}

	//
	m_tTimeout = time(NULL);

	//
	if (NULL == m_hQuit)
	{
		m_nErrorCode = GetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
		return FALSE;
	}

	//
	if (NULL == m_hWrEvent)
	{
		m_nErrorCode = GetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
		return FALSE;
	}

	//
	// 일단 UDP로 
	//
	m_dSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_dSock)
	{
		m_nErrorCode = WSAGetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
		return FALSE;
	}

	//
	if (FALSE == UdpFixBind())
	{
		return FALSE;
	}


	//... SOO SOCKET BUFF SIZING : 
//  	m_ulRcvBuff = 1024 * 1024 * 1000;
//  	m_ulSndBuff = 1024 * 1024 * 1000;

	//
	if (SOCKET_ERROR == setsockopt(m_dSock, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char*>(&m_ulRcvBuff), sizeof(m_ulRcvBuff)))
	{
		m_nErrorCode = WSAGetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
	}
	
	//
	if (SOCKET_ERROR == setsockopt(m_dSock, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<const char*>(&m_ulSndBuff), sizeof(m_ulSndBuff)))
	{
		m_nErrorCode = WSAGetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
	}
	
	//
	int nLenVariable = sizeof(m_ulMaxSndPktLen);
	if (SOCKET_ERROR == getsockopt(m_dSock, SOL_SOCKET, SO_MAX_MSG_SIZE, reinterpret_cast<char*>(&m_ulMaxSndPktLen), &nLenVariable))
	{
		m_nErrorCode = WSAGetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
		return FALSE;
	}

	//
	if (FALSE == m_cRecvChunk.Ext(m_ulMaxRcvPktLen + 1))
	{
		m_nErrorCode = WSAGetLastError();
		HandleError(OCFCLIENT_ERROR_USERDEF, OCFCLIENT_ERROR_USERDEF_CATEGORY_MEMORY, 0xFF, 0, NULL);
		return FALSE;
	}

	//
	m_hSockEvent = WSACreateEvent();
	if (WSA_INVALID_EVENT == m_hSockEvent)
	{
		m_nErrorCode = WSAGetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
		return FALSE;
	}

	//
	// Only For UDP
	//
	if (WSAEventSelect(m_dSock, m_hSockEvent, FD_READ | FD_WRITE) == SOCKET_ERROR)
	{
		m_nErrorCode = WSAGetLastError();
		HandleError(OCFCLIENT_ERROR_WINSOCK, m_nErrorCode, 0xFF, 0, NULL);
		return FALSE;
	}

	//
	m_bConnectFlag = TRUE;
	m_bWouldBlock = FALSE;

	return TRUE;
}