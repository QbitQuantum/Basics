BOOL CAsyncSocketExLayer::ConnectNext(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	ASSERT(GetLayerState()==unconnected);
	ASSERT(m_pOwnerSocket);
	BOOL res = FALSE;
	if (m_pNextLayer)
		res = m_pNextLayer->Connect(lpszHostAddress, nHostPort);
	else if (m_nFamily == AF_INET)
	{
		USES_CONVERSION;

		ASSERT(lpszHostAddress != NULL);

		SOCKADDR_IN sockAddr;
		memset(&sockAddr,0,sizeof(sockAddr));

		LPSTR lpszAscii = T2A((LPTSTR)lpszHostAddress);
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);

		if (sockAddr.sin_addr.s_addr == INADDR_NONE)
		{
			LPHOSTENT lphost;
			lphost = gethostbyname(lpszAscii);
			if (lphost != NULL)
				sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
			else
			{
				WSASetLastError(WSAEINVAL);
				res = FALSE;
			}
		}

		sockAddr.sin_port = htons((u_short)nHostPort);

		res = (SOCKET_ERROR != connect(m_pOwnerSocket->GetSocketHandle(), (SOCKADDR*)&sockAddr, sizeof(sockAddr)) );
	}
	else if (m_nFamily == AF_INET6 || m_nFamily == AF_UNSPEC)
	{
		if (!m_pOwnerSocket->p_getaddrinfo)
		{
			WSASetLastError(WSAEPROTONOSUPPORT);
			return FALSE;
		}
		USES_CONVERSION;

		ASSERT(lpszHostAddress != NULL);

		addrinfo hints, *res0, *res1;
		SOCKET hSocket;
		int error;
		char port[10];

		m_pOwnerSocket->p_freeaddrinfo(m_addrInfo);
		m_nextAddr = 0;
		m_addrInfo = 0;

		memset(&hints, 0, sizeof(addrinfo));
		hints.ai_family = m_nFamily;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = 0;
		_snprintf(port, 9, "%lu", nHostPort);
		error = m_pOwnerSocket->p_getaddrinfo(T2CA(lpszHostAddress), port, &hints, &res0);
		if (error)
			return FALSE;

		for (res1 = res0; res1; res1 = res1->ai_next)
		{
			if (m_nFamily == AF_UNSPEC)
				hSocket = socket(res1->ai_family, res1->ai_socktype, res1->ai_protocol);
			else
				hSocket = m_pOwnerSocket->GetSocketHandle();

			if (INVALID_SOCKET == hSocket)
			{
				res = FALSE;
				continue;
			}

			if (m_nFamily == AF_UNSPEC)
			{
				m_pOwnerSocket->m_SocketData.hSocket = hSocket;
				m_pOwnerSocket->AttachHandle(hSocket);
				if (!m_pOwnerSocket->AsyncSelect(m_lEvent))
				{
					m_pOwnerSocket->Close();
					res = FALSE;
					continue ;
				}
				if (m_pOwnerSocket->m_pFirstLayer)
				{
					if (WSAAsyncSelect(m_pOwnerSocket->m_SocketData.hSocket, m_pOwnerSocket->GetHelperWindowHandle(), m_pOwnerSocket->m_SocketData.nSocketIndex+WM_SOCKETEX_NOTIFY, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE) )
					{
						m_pOwnerSocket->Close();
						res = FALSE;
						continue;
					}
				}
				if (m_pOwnerSocket->m_pendingCallbacks.size())
					PostMessage(m_pOwnerSocket->GetHelperWindowHandle(), WM_USER + 2, (WPARAM)m_pOwnerSocket->m_SocketData.nSocketIndex, 0);
			}

			if (m_nFamily == AF_UNSPEC)
			{
				m_pOwnerSocket->m_SocketData.nFamily = m_nFamily = res1->ai_family;
				if (!m_pOwnerSocket->Bind(m_nSocketPort, m_lpszSocketAddress))
				{
					m_pOwnerSocket->m_SocketData.nFamily = m_nFamily = AF_UNSPEC;
					Close();
					continue;
				}
			}

			if (!( res = ( SOCKET_ERROR != connect(m_pOwnerSocket->GetSocketHandle(), res1->ai_addr, res1->ai_addrlen) ) )
				&& WSAGetLastError() != WSAEWOULDBLOCK)
			{
				if (hints.ai_family == AF_UNSPEC)
				{
					m_nFamily = AF_UNSPEC;
					Close();
				}
				continue ;
			}

			m_nFamily = res1->ai_family;
			m_pOwnerSocket->m_SocketData.nFamily = res1->ai_family;
			res = TRUE;
			break;
		}

		if (res1)
			res1 = res0->ai_next;

		if (res1)
		{
			m_addrInfo = res0;
			m_nextAddr = res1;
		}
		else
			m_pOwnerSocket->p_freeaddrinfo(res0);

		if (INVALID_SOCKET == m_pOwnerSocket->GetSocketHandle())
			res = FALSE ;
	}

	if (res || WSAGetLastError() == WSAEWOULDBLOCK)
	{
		SetLayerState(connecting);
	}
	return res;
}