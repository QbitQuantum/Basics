NetSocket* TCPNetworkEngine::connect(const char* uri)
{
	if(strncmp(uri, "yc://", 5) == 0)
	{
		const char* host = uri + 5;

		TCPNetSocket* s = new TCPNetSocket();
		s->socket = socket(PF_INET, SOCK_STREAM, 0);

		xerror(s->socket != SOCKET_ERROR, "Could not create a socket.");

		struct hostent* hostaddr = gethostbyname(host);
		xwarn(hostaddr->h_addr_list, "Could not retreive address for host %s", host);
		if(!hostaddr->h_addr_list)
			return NULL;

		struct sockaddr_in saddr;
		bzero(&saddr, sizeof(saddr));
		saddr.sin_family = hostaddr->h_addrtype;
		saddr.sin_port = htons(port);
#ifndef WIN32
		inet_pton(hostaddr->h_addrtype, hostaddr->h_addr_list[0], &saddr.sin_addr);
#else
		struct sockaddr_storage ss;
		int sslen = sizeof(ss);
		WSAStringToAddressA(hostaddr->h_addr_list[0], hostaddr->h_addrtype, NULL, (struct sockaddr*)&ss, &sslen);
		saddr.sin_addr = ((struct sockaddr_in *)&ss)->sin_addr;
#endif

		if(::connect(s->socket, (struct sockaddr *)&saddr, sizeof(saddr) ) == SOCKET_ERROR)
		{
			xwarn(false, "Could not connect to %s", host);
			return NULL;
		}

#ifdef WIN32
		ULONG on=1;
		ioctlsocket(s->socket, FIONBIO, &on);
#else
		fcntl(s->socket, F_SETFL, O_NONBLOCK);
#endif

		return s;
	} else {
		xwarn(false, "Unknown protocol : %s", uri);
		return NULL;
	}
}