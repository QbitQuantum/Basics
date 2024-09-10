void SocTransport::Poll()
{
	if (!IsOpen())
		return;

	// Users of Transport::AsyncConnect rely on it not completing the connection
	// immediately so they have an opportunity to hook the OnConnectComplete
	// callback.

	if (m_pconAsyncConnect != NULL) {
		if (m_fAsyncConnectLoopback)
			((LoopbackConnection *)m_pconAsyncConnect)->Connect();
		IConnectionCallback *pccb = m_pconAsyncConnect->GetCallback();
		if (pccb != NULL) {
			pccb->OnConnectComplete(m_pconAsyncConnect);
		}
		m_pconAsyncConnect = NULL;
	}

	// While a game is being advertised the server accepts client connections

	if (m_socAcceptListen != INVALID_SOCKET) {

		// Test if any client connection requests are pending

		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(m_socAcceptListen, &fds);
		TIMEVAL tvTimeout;
		tvTimeout.tv_sec = 0;
		tvTimeout.tv_usec = 0;
		int nSelected = select(((int)m_socAcceptListen) + 1, &fds, NULL, NULL, &tvTimeout);
		if (nSelected == SOCKET_ERROR) {
#ifdef DEBUG
			HostMessageBox(TEXT("select err: %s"), PszFromSocError());
#endif
			if (m_ptcb != NULL)
				m_ptcb->OnTransportError(ktraeAdvertiseGameFailed);
			return;
		}

		// Accept a client connection and produce a new socket for communicating with that client

		if (nSelected == 1) {
			NetAddress nad;
			memset(&nad, 0, sizeof(nad));
#ifdef IPHONE
            socklen_t cbAddr = sizeof(nad);
#else
			int cbAddr = sizeof(nad);
#endif
			SOCKET socConn = accept(m_socAcceptListen, (sockaddr *)&nad, &cbAddr);
			if (socConn == INVALID_SOCKET) {
				// This error is seen on a Tungsten C hosting a game when a ux50 
				// times out while trying to connect. The best thing to do is just
				// ignore the connection attempt. Hopefully it will try again and
				// get it right this time

				if (WSAGetLastError() == 0)
					return;
#ifdef DEBUG
				HostMessageBox(TEXT("accept err: %s"), PszFromSocError());
#endif
				return;
			}
//			HostMessageBox("cbAddr = %d, sizeof(sockaddr_in) = %d", cbAddr, sizeof(sockaddr_in));
//			Assert(cbAddr == sizeof(sockaddr_in));

			Connection *pcon = new SocConnection(socConn);
			Assert(pcon != NULL, "out of memory!");
			if (pcon == NULL) {
				closesocket(socConn);
				return;
			}
			AddConnection(pcon);

			if (m_ptcb != NULL) {
				if (!m_ptcb->OnClientConnect(pcon))
					delete pcon;
			}
		}
	}

	Transport::Poll();
}