BOOL CMulticastSocket::CreateReceivingSocket(LPCTSTR strGroupIP, UINT nGroupPort)
{
	/* Create socket for receiving packets from multicast group */
	if(!Create(nGroupPort, SOCK_DGRAM, FD_READ))
		return FALSE;

	BOOL bMultipleApps = TRUE;		/* allow reuse of local port if needed */
	SetSockOpt(SO_REUSEADDR, (void*)&bMultipleApps, sizeof(BOOL), SOL_SOCKET);

	/* Fill m_saHostGroup_in for sending datagrams */
	memset(&m_saHostGroup, 0, sizeof(m_saHostGroup));
	m_saHostGroup.sin_family = AF_INET;
	m_saHostGroup.sin_addr.s_addr = inet_addr(strGroupIP);
	m_saHostGroup.sin_port = htons((USHORT)nGroupPort);

	/* Join the multicast group */
	m_mrMReq.imr_multiaddr.s_addr = inet_addr(strGroupIP);	/* group addr */ 
	m_mrMReq.imr_interface.s_addr = htons(INADDR_ANY);		/* use default */ 
	if(setsockopt(m_hSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char FAR *)&m_mrMReq, sizeof(m_mrMReq)) < 0)
		return FALSE;

	return TRUE;
}