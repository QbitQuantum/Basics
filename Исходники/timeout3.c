/* accept a socket and read data as much as you can */
static TDS_THREAD_PROC_DECLARE(fake_thread_proc, arg)
{
	TDS_SYS_SOCKET s = ptr2int(arg), sock;
	socklen_t len;
	char buf[128];
	struct sockaddr_in sin;
	struct pollfd fd;

	memset(&sin, 0, sizeof(sin));
	len = sizeof(sin);

	fd.fd = s;
	fd.events = POLLIN;
	fd.revents = 0;
	if (poll(&fd, 1, 30000) <= 0) {
		perror("poll");
		exit(1);
	}

	if (TDS_IS_SOCKET_INVALID(sock = tds_accept(s, (struct sockaddr *) &sin, &len))) {
		perror("accept");
		exit(1);
	}
	tds_mutex_lock(&mtx);
	fake_sock = sock;
	tds_mutex_unlock(&mtx);
	CLOSESOCKET(s);

	for (;;) {
		int len;

		fd.fd = sock;
		fd.events = POLLIN;
		fd.revents = 0;
		if (poll(&fd, 1, 30000) <= 0) {
			perror("poll");
			exit(1);
		}

		/* just read and discard */
		len = READSOCKET(sock, buf, sizeof(buf));
		if (len == 0)
			break;
		if (len < 0 && sock_errno != TDSSOCK_EINPROGRESS)
			break;
	}
	return NULL;
}