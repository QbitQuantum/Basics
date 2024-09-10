//--------------------------------------------------------------------------------
bool CSmallSocket::GetPeerName(CString& rSocketAddress, UINT& rSocketPort)
	{
	if(m_hSocket == INVALID_SOCKET)
		return false;

	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);

	bool bResult = GetPeerName((SOCKADDR*)&sockAddr, &nSockAddrLen);
	if(bResult)
		{
		rSocketPort = ntohs(sockAddr.sin_port);
		rSocketAddress = inet_ntoa(sockAddr.sin_addr);
		}

	return bResult;
	}