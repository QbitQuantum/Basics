void ConnectSKKServer()
{
	ADDRINFOW *paiwResult;
	ADDRINFOW *paiw;
	u_long mode;
	timeval tv;
	fd_set fdw, fde;

	ADDRINFOW aiwHints = {};
	aiwHints.ai_family = AF_UNSPEC;
	aiwHints.ai_socktype = SOCK_STREAM;
	aiwHints.ai_protocol = IPPROTO_TCP;

	if(GetAddrInfoW(host, port, &aiwHints, &paiwResult) != 0)
	{
		return;
	}

	for(paiw = paiwResult; paiw != nullptr; paiw = paiw->ai_next)
	{
		sock = socket(paiw->ai_family, paiw->ai_socktype, paiw->ai_protocol);
		if(sock == INVALID_SOCKET)
		{
			continue;
		}

		if(setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
		{
			closesocket(sock);
			sock = INVALID_SOCKET;
			continue;
		}
		if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
		{
			closesocket(sock);
			sock = INVALID_SOCKET;
			continue;
		}

		mode = 1;
		ioctlsocket(sock, FIONBIO, &mode);

		if(connect(sock, paiw->ai_addr, (int)paiw->ai_addrlen) == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				sock = INVALID_SOCKET;
				continue;
			}
		}

		mode = 0;
		ioctlsocket(sock, FIONBIO, &mode);

		tv.tv_sec = timeout / 1000;
		tv.tv_usec = (timeout % 1000) * 1000;

		FD_ZERO(&fdw);
		FD_ZERO(&fde);
		FD_SET(sock, &fdw);
		FD_SET(sock, &fde);

		select(0, nullptr, &fdw, &fde, &tv);
		if(FD_ISSET(sock, &fdw))
		{
			break;
		}

		DisconnectSKKServer();
	}

	FreeAddrInfoW(paiwResult);
}