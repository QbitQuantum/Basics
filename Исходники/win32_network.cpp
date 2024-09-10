Socket *CreateClientSocket(const char *host, uint16_t port, int timeoutMS)
{
	wchar_t portwstr[7] = {0};

	{
		char buf[7] = {0};
		int n = StringFormat::snprintf(buf, 6, "%d", port);
		for(int i=0; i < n && i < 6; i++) portwstr[i] = (wchar_t)buf[i];
	}

	addrinfoW hints;
	RDCEraseEl(hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::wstring whost = StringFormat::UTF82Wide(string(host));

	addrinfoW *addrResult = NULL;
	GetAddrInfoW(whost.c_str(), portwstr, &hints, &addrResult);

	for(addrinfoW *ptr = addrResult; ptr != NULL; ptr = ptr->ai_next)
	{
		SOCKET s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_NO_HANDLE_INHERIT);

		if(s == INVALID_SOCKET)
			return NULL;

		u_long enable = 1;
		ioctlsocket(s, FIONBIO, &enable);

		int result = connect(s, ptr->ai_addr, (int)ptr->ai_addrlen);
		if(result == SOCKET_ERROR)
		{
			fd_set set;
			FD_ZERO(&set);

			// macro FD_SET contains the do { } while(0) idiom, which warns
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
			FD_SET(s, &set);
#pragma warning(pop)

			int err = WSAGetLastError();

			if(err == WSAEWOULDBLOCK)
			{
				timeval timeout;
				timeout.tv_sec = (timeoutMS/1000);
				timeout.tv_usec = (timeoutMS%1000)*1000;
				result = select(0, NULL, &set, NULL, &timeout);

				if(result <= 0)
				{
					RDCDEBUG("connect timed out");
					closesocket(s);
					continue;
				}
				else
				{
					RDCDEBUG("connect before timeout");
				}
			}
			else
			{
				RDCDEBUG("problem other than blocking");
				closesocket(s);
				continue;
			}
		}
		else
		{
			RDCDEBUG("connected immediately");
		}

		BOOL nodelay = TRUE;
		setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (const char *)&nodelay, sizeof(nodelay));

		return new Socket((ptrdiff_t)s);
	}

	RDCWARN("Failed to connect to %s:%d", host, port);
	return NULL;
}