// adzm 2010-08
VBool
VSocket::SetDefaultSocketOptions()
{
	VBool result = VTrue;

	const int one = 1;

	if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&one, sizeof(one)))
	{
		result = VFalse;
	}

	int defaultSocketKeepAliveTimeout = m_defaultSocketKeepAliveTimeout;
	if (defaultSocketKeepAliveTimeout > 0) {
		if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (const char *)&one, sizeof(one))) {
			result = VFalse;
		} else {
			DWORD bytes_returned = 0;
			tcp_keepalive keepalive_requested;
			tcp_keepalive keepalive_returned;
			ZeroMemory(&keepalive_requested, sizeof(keepalive_requested));
			ZeroMemory(&keepalive_returned, sizeof(keepalive_returned));

			keepalive_requested.onoff = 1;
			keepalive_requested.keepalivetime = defaultSocketKeepAliveTimeout;
			keepalive_requested.keepaliveinterval = 1000;
			// 10 probes always used by default in Vista+; not changeable. 

			if (0 != WSAIoctl(sock, SIO_KEEPALIVE_VALS, 
					&keepalive_requested, sizeof(keepalive_requested), 
					&keepalive_returned, sizeof(keepalive_returned), 
					&bytes_returned, NULL, NULL))
			{
				result = VFalse;
			}
		}
	}

	assert(result);

	{
	sockaddr_in skaddr={0};
	int	iSockSize=sizeof(sockaddr_in); 		
	//initialise socket row value
	getsockname(sock,(sockaddr*)&skaddr,&iSockSize);
	m_SocketInfo.dwState =MIB_TCP_STATE_ESTAB;
	m_SocketInfo.dwLocalAddr=skaddr.sin_addr.S_un.S_addr;
	m_SocketInfo.dwLocalPort=skaddr.sin_port;
	getpeername(sock,(sockaddr*)&skaddr,&iSockSize);
	m_SocketInfo.dwRemoteAddr=skaddr.sin_addr.S_un.S_addr;
	m_SocketInfo.dwRemotePort=skaddr.sin_port;

	PUCHAR rw = NULL;
	TCP_ESTATS_SND_CONG_RW_v0	  enableInfo={0};
	ULONG iRet, lSize = 0;
	//enable tcp stats 
	rw = (PUCHAR) & enableInfo;
	enableInfo.EnableCollection=TRUE;
	lSize = sizeof (TCP_ESTATS_SND_CONG_RW_v0); 
	if (s_pSetPerTcpConnectionEStats)
	{
	iRet = s_pSetPerTcpConnectionEStats((PMIB_TCPROW) &m_SocketInfo, TcpConnectionEstatsSndCong, rw, 0, lSize, 0);
	CanUseFlow=false;
	if (iRet==ERROR_SUCCESS) CanUseFlow=true;
	}
	else CanUseFlow=true;
  } 

	return result;
}