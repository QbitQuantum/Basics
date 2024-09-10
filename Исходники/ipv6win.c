static int net_socket_close(SOCKET fd) {
	struct linger l;
	int ret;
	int len = sizeof (l);
	if (getsockopt(fd, SOL_SOCKET, SO_LINGER, (char *)&l, &len) == 0) {
		if (l.l_onoff == 0) {
			WSASendDisconnect(fd, NULL);
		}
	}
	ret = closesocket (fd);
	return ret;
}