void *recv_thread(void *param) {
	CorsSocket *cors = static_cast<CorsSocket *>(param);
	fd_set rfds;
	char rbuff[MAX_LEN];
	int rlen = -1;
	sockaddr_in from;
	int sk = cors->get_sock();
	while (true) {
		FD_ZERO(&rfds);
		FD_SET(sk, &rfds);
		int ret = select(sk + 1, &rfds, NULL, NULL, NULL);
		if (ret < 0) {
			cerr << "select error in recv_thread" << endl;
			break;
		} else {
			rlen = -1;
			cors->recvfrom(rbuff, rlen, from.sin_addr.s_addr, from.sin_port);
		}
	}
	return NULL;
}