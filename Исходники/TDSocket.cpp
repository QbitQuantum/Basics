//------------------------------------------------------------------------------
//
// ConnectTCP() -
//
//------------------------------------------------------------------------------
bool TDSocket::ConnectTCP(const char *pAddr, i16 nPort)
{
	bool           bRetVal = false;
	struct in_addr stIpAddress;

	//------------------------------------------------------------------
	// Preconnection setup that must be preformed					 
	//------------------------------------------------------------------
	memset(&m_stServerSockaddr, 0, sizeof(m_stServerSockaddr));
	m_stServerSockaddr.sin_family = AF_INET;

	hostent * pHE = NULL;
	if ((pHE = GETHOSTBYNAME(pAddr)) == NULL)
	{
#ifdef WIN32
		TranslateSocketError();
#else
		if (h_errno == HOST_NOT_FOUND)
		{
			SetSocketError(SocketInvalidAddress);
		}
#endif
		return bRetVal;
	}

	memcpy(&stIpAddress, pHE->h_addr_list[0], pHE->h_length);
	m_stServerSockaddr.sin_addr.s_addr = stIpAddress.s_addr;

	if ((i32)m_stServerSockaddr.sin_addr.s_addr == TDSocket::SocketError)
	{
		TranslateSocketError();
		return bRetVal;
	}

	m_stServerSockaddr.sin_port = htons(nPort);

	//------------------------------------------------------------------
	// Connect to address "xxx.xxx.xxx.xxx"	(IPv4) address only.  
	// 
	//------------------------------------------------------------------

	if (connect(m_socket, (struct sockaddr*)&m_stServerSockaddr, sizeof(m_stServerSockaddr)) ==
		TDSocket::SocketError)
	{
		//--------------------------------------------------------------
		// Get error value this might be a non-blocking socket so we 
		// must first check.
		//--------------------------------------------------------------
		TranslateSocketError();

		//--------------------------------------------------------------
		// If the socket is non-blocking and the current socket error
		// is SocketEinprogress or SocketEwouldblock then poll connection 
		// with select for designated timeout period.
		// Linux returns EINPROGRESS and Windows returns WSAEWOULDBLOCK.
		//--------------------------------------------------------------
		if ((IsNonblocking()) &&
			((GetSocketError() == TDSocket::SocketEwouldblock) ||
			(GetSocketError() == TDSocket::SocketEinprogress)))
		{
			bRetVal = Select(GetConnectTimeoutSec(), GetConnectTimeoutUSec());
		}
	}
	else
	{
		TranslateSocketError();
		bRetVal = true;
	}


	return bRetVal;
}