int socketpair(int domain, int type, int protocol, int socket_vector[2])
{
	if (domain != AF_UNIX || !(type & SOCK_STREAM) || protocol != PF_UNSPEC)
		return -1;

	socket_vector[0] = -1;
	socket_vector[1] = -1;

	int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listener == -1) {
		return -1;
	}

	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_LOOPBACK),
		.sin_port = 0,
	};

	int yes = 1, e;
	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR,
			(void *)&yes, sizeof yes) == -1)
		goto err;

	if (bind(listener, (struct sockaddr *)&addr, sizeof addr) != 0)
		goto err;

	memset(&addr, 0, sizeof addr);
	socklen_t addrlen = sizeof addr;
	if (getsockname(listener, (struct sockaddr *)&addr, &addrlen) != 0)
		goto err;

	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr.sin_family = AF_INET;

	if (listen(listener, 1) != 0)
		goto err;

	socket_vector[0] = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);
	if (socket_vector[0] == -1)
		goto err;

	if (connect(socket_vector[0], (struct sockaddr *)&addr, sizeof addr) != 0)
		goto err;

	socket_vector[1] = accept(listener, NULL, NULL);
	if (socket_vector[1] == -1)
		goto err;

	closesocket(listener);
	return 0;

err:
	e = WSAGetLastError();
	closesocket(listener);
	closesocket(socket_vector[0]);
	closesocket(socket_vector[1]);
	WSASetLastError(e);
	socket_vector[0] = -1;
	socket_vector[1] = -1;
	return -1;
}

int pipe(int fildes[2])
{
	return socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, PF_UNSPEC, fildes);
}

#else

static int setfd(int fd, int flag)
{
	int flags = fcntl(fd, F_GETFD);
	flags |= flag;
	return fcntl(fd, F_SETFD, flags);
}