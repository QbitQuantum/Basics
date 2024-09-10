static BOOL freerdp_listener_open(freerdp_listener* instance, const char* bind_address, UINT16 port)
{
	int status;
	int sockfd;
	char addr[64];
	void* sin_addr;
	int option_value;
	char servname[16];
	struct addrinfo* ai;
	struct addrinfo* res;
	struct addrinfo hints = { 0 };
	rdpListener* listener = (rdpListener*) instance->listener;
#ifdef _WIN32
	u_long arg;
#endif

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (!bind_address)
		hints.ai_flags = AI_PASSIVE;

	sprintf_s(servname, sizeof(servname), "%d", port);
	status = getaddrinfo(bind_address, servname, &hints, &res);

	if (status != 0)
	{
#ifdef _WIN32
		WLog_ERR("getaddrinfo error: %s", gai_strerrorA(status));
#else
		WLog_ERR(TAG, "getaddrinfo");
#endif
		return FALSE;
	}

	for (ai = res; ai && (listener->num_sockfds < 5); ai = ai->ai_next)
	{
		if ((ai->ai_family != AF_INET) && (ai->ai_family != AF_INET6))
			continue;

		if (listener->num_sockfds == MAX_LISTENER_HANDLES)
		{
			WLog_ERR(TAG, "too many listening sockets");
			continue;
		}

		sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);

		if (sockfd == -1)
		{
			WLog_ERR(TAG, "socket");
			continue;
		}

		if (ai->ai_family == AF_INET)
			sin_addr = &(((struct sockaddr_in*) ai->ai_addr)->sin_addr);
		else
			sin_addr = &(((struct sockaddr_in6*) ai->ai_addr)->sin6_addr);

		inet_ntop(ai->ai_family, sin_addr, addr, sizeof(addr));

		option_value = 1;

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*) &option_value, sizeof(option_value)) == -1)
			WLog_ERR(TAG, "setsockopt");

#ifndef _WIN32
		fcntl(sockfd, F_SETFL, O_NONBLOCK);
#else
		arg = 1;
		ioctlsocket(sockfd, FIONBIO, &arg);
#endif

		status = _bind((SOCKET) sockfd, ai->ai_addr, ai->ai_addrlen);

		if (status != 0)
		{
			closesocket((SOCKET) sockfd);
			continue;
		}

		status = _listen((SOCKET) sockfd, 10);

		if (status != 0)
		{
			WLog_ERR(TAG, "listen");
			closesocket((SOCKET) sockfd);
			continue;
		}

		/* FIXME: these file descriptors do not work on Windows */

		listener->sockfds[listener->num_sockfds] = sockfd;
		listener->events[listener->num_sockfds] = WSACreateEvent();
		if (!listener->events[listener->num_sockfds])
		{
			listener->num_sockfds = 0;
			break;
		}
		WSAEventSelect(sockfd, listener->events[listener->num_sockfds], FD_READ | FD_ACCEPT | FD_CLOSE);
		listener->num_sockfds++;

		WLog_INFO(TAG, "Listening on %s:%s", addr, servname);
	}

	freeaddrinfo(res);

	return (listener->num_sockfds > 0 ? TRUE : FALSE);
}