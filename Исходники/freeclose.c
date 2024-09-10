static int
init_fake_server(int ip_port)
{
	struct sockaddr_in sin;
	TDS_SYS_SOCKET s;

	memset(&sin, 0, sizeof(sin));
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sin.sin_port = htons((short) ip_port);
	sin.sin_family = AF_INET;

	if (TDS_IS_SOCKET_INVALID(s = socket(AF_INET, SOCK_STREAM, 0))) {
		perror("socket");
		exit(1);
	}
	if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("bind");
		CLOSESOCKET(s);
		return 1;
	}
	if (listen(s, 5) < 0) {
		perror("listen");
		CLOSESOCKET(s);
		return 1;
	}
	if (tds_thread_create(&fake_thread, fake_thread_proc, int2ptr(s)) != 0) {
		perror("tds_thread_create");
		exit(1);
	}
	return 0;
}