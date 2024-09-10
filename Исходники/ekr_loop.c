int
main(void)
{
	struct sockaddr_in sin_s, sin_c;
	struct sockaddr_conn sconn;
#ifdef _WIN32
	SOCKET fd_c, fd_s;
#else
	int fd_c, fd_s;
#endif
	struct socket *s_c, *s_s, *s_l;
#ifdef _WIN32
	HANDLE tid_c, tid_s;
#else
	pthread_t tid_c, tid_s;
#endif
	int cur_buf_size, snd_buf_size, rcv_buf_size;
	socklen_t opt_len;
	struct sctp_sndinfo sndinfo;
	char *line;
#ifdef _WIN32
	WSADATA wsaData;
#endif

#ifdef _WIN32
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		printf("WSAStartup failed\n");
		exit (EXIT_FAILURE);
	}
#endif
	usrsctp_init(0, conn_output, debug_printf);
	/* set up a connected UDP socket */
#ifdef _WIN32
	if ((fd_c = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
		printf("socket() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if ((fd_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
		printf("socket() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
#else
	if ((fd_c = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if ((fd_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
#endif
	memset(&sin_c, 0, sizeof(struct sockaddr_in));
	sin_c.sin_family = AF_INET;
#ifdef HAVE_SIN_LEN
	sin_c.sin_len = sizeof(struct sockaddr_in);
#endif
	sin_c.sin_port = htons(9900);
	sin_c.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	memset(&sin_s, 0, sizeof(struct sockaddr_in));
	sin_s.sin_family = AF_INET;
#ifdef HAVE_SIN_LEN
	sin_s.sin_len = sizeof(struct sockaddr_in);
#endif
	sin_s.sin_port = htons(9899);
	sin_s.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
#ifdef _WIN32
	if (bind(fd_c, (struct sockaddr *)&sin_c, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		printf("bind() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if (bind(fd_s, (struct sockaddr *)&sin_s, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		printf("bind() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
#else
	if (bind(fd_c, (struct sockaddr *)&sin_c, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if (bind(fd_s, (struct sockaddr *)&sin_s, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
#endif
#ifdef _WIN32
	if (connect(fd_c, (struct sockaddr *)&sin_s, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		printf("connect() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if (connect(fd_s, (struct sockaddr *)&sin_c, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		printf("connect() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
#else
	if (connect(fd_c, (struct sockaddr *)&sin_s, sizeof(struct sockaddr_in)) < 0) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	if (connect(fd_s, (struct sockaddr *)&sin_c, sizeof(struct sockaddr_in)) < 0) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
#endif
#ifdef _WIN32
	tid_c = CreateThread(NULL, 0, &handle_packets, (void *)&fd_c, 0, NULL);
	tid_s = CreateThread(NULL, 0, &handle_packets, (void *)&fd_s, 0, NULL);
#else
	if (pthread_create(&tid_c, NULL, &handle_packets, (void *)&fd_c)) {
		perror("pthread_create tid_c");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&tid_s, NULL, &handle_packets, (void *)&fd_s)) {
		perror("pthread_create tid_s");
		exit(EXIT_FAILURE);
	};
#endif
#ifdef SCTP_DEBUG
	usrsctp_sysctl_set_sctp_debug_on(SCTP_DEBUG_NONE);
#endif
	usrsctp_sysctl_set_sctp_ecn_enable(0);
	usrsctp_register_address((void *)&fd_c);
	usrsctp_register_address((void *)&fd_s);
	if ((s_c = usrsctp_socket(AF_CONN, SOCK_STREAM, IPPROTO_SCTP, receive_cb, NULL, 0, &fd_c)) == NULL) {
		perror("usrsctp_socket");
		exit(EXIT_FAILURE);
	}
	opt_len = (socklen_t)sizeof(int);
	cur_buf_size = 0;
	if (usrsctp_getsockopt(s_c, SOL_SOCKET, SO_SNDBUF, &cur_buf_size, &opt_len) < 0) {
		perror("usrsctp_getsockopt");
		exit(EXIT_FAILURE);
	}
	printf("Change send socket buffer size from %d ", cur_buf_size);
	snd_buf_size = 1<<20; /* 1 MB */
	if (usrsctp_setsockopt(s_c, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, sizeof(int)) < 0) {
		perror("usrsctp_setsockopt");
		exit(EXIT_FAILURE);
	}
	opt_len = (socklen_t)sizeof(int);
	cur_buf_size = 0;
	if (usrsctp_getsockopt(s_c, SOL_SOCKET, SO_SNDBUF, &cur_buf_size, &opt_len) < 0) {
		perror("usrsctp_getsockopt");
		exit(EXIT_FAILURE);
	}
	printf("to %d.\n", cur_buf_size);
	if ((s_l = usrsctp_socket(AF_CONN, SOCK_STREAM, IPPROTO_SCTP, receive_cb, NULL, 0, &fd_s)) == NULL) {
		perror("usrsctp_socket");
		exit(EXIT_FAILURE);
	}
	opt_len = (socklen_t)sizeof(int);
	cur_buf_size = 0;
	if (usrsctp_getsockopt(s_l, SOL_SOCKET, SO_RCVBUF, &cur_buf_size, &opt_len) < 0) {
		perror("usrsctp_getsockopt");
		exit(EXIT_FAILURE);
	}
	printf("Change receive socket buffer size from %d ", cur_buf_size);
	rcv_buf_size = 1<<16; /* 64 KB */
	if (usrsctp_setsockopt(s_l, SOL_SOCKET, SO_RCVBUF, &rcv_buf_size, sizeof(int)) < 0) {
		perror("usrsctp_setsockopt");
		exit(EXIT_FAILURE);
	}
	opt_len = (socklen_t)sizeof(int);
	cur_buf_size = 0;
	if (usrsctp_getsockopt(s_l, SOL_SOCKET, SO_RCVBUF, &cur_buf_size, &opt_len) < 0) {
		perror("usrsctp_getsockopt");
		exit(EXIT_FAILURE);
	}
	printf("to %d.\n", cur_buf_size);
	/* Bind the client side. */
	memset(&sconn, 0, sizeof(struct sockaddr_conn));
	sconn.sconn_family = AF_CONN;
#ifdef HAVE_SCONN_LEN
	sconn.sconn_len = sizeof(struct sockaddr_conn);
#endif
	sconn.sconn_port = htons(5001);
	sconn.sconn_addr = &fd_c;
	if (usrsctp_bind(s_c, (struct sockaddr *)&sconn, sizeof(struct sockaddr_conn)) < 0) {
		perror("usrsctp_bind");
		exit(EXIT_FAILURE);
	}
	/* Bind the server side. */
	memset(&sconn, 0, sizeof(struct sockaddr_conn));
	sconn.sconn_family = AF_CONN;
#ifdef HAVE_SCONN_LEN
	sconn.sconn_len = sizeof(struct sockaddr_conn);
#endif
	sconn.sconn_port = htons(5001);
	sconn.sconn_addr = &fd_s;
	if (usrsctp_bind(s_l, (struct sockaddr *)&sconn, sizeof(struct sockaddr_conn)) < 0) {
		perror("usrsctp_bind");
		exit(EXIT_FAILURE);
	}
	/* Make server side passive... */
	if (usrsctp_listen(s_l, 1) < 0) {
		perror("usrsctp_listen");
		exit(EXIT_FAILURE);
	}
	/* Initiate the handshake */
	memset(&sconn, 0, sizeof(struct sockaddr_conn));
	sconn.sconn_family = AF_CONN;
#ifdef HAVE_SCONN_LEN
	sconn.sconn_len = sizeof(struct sockaddr_conn);
#endif
	sconn.sconn_port = htons(5001);
	sconn.sconn_addr = &fd_c;
	if (usrsctp_connect(s_c, (struct sockaddr *)&sconn, sizeof(struct sockaddr_conn)) < 0) {
		perror("usrsctp_connect");
		exit(EXIT_FAILURE);
	}
	if ((s_s = usrsctp_accept(s_l, NULL, NULL)) == NULL) {
		perror("usrsctp_accept");
		exit(EXIT_FAILURE);
	}
	usrsctp_close(s_l);
	if ((line = malloc(LINE_LENGTH)) == NULL) {
		exit(EXIT_FAILURE);
	}
	memset(line, 'A', LINE_LENGTH);
	sndinfo.snd_sid = 1;
	sndinfo.snd_flags = 0;
	sndinfo.snd_ppid = htonl(DISCARD_PPID);
	sndinfo.snd_context = 0;
	sndinfo.snd_assoc_id = 0;
	/* Send a 1 MB message */
	if (usrsctp_sendv(s_c, line, LINE_LENGTH, NULL, 0, (void *)&sndinfo,
	                 (socklen_t)sizeof(struct sctp_sndinfo), SCTP_SENDV_SNDINFO, 0) < 0) {
		perror("usrsctp_sendv");
		exit(EXIT_FAILURE);
	}
	free(line);
	usrsctp_shutdown(s_c, SHUT_WR);

	while (usrsctp_finish() != 0) {
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
#ifdef _WIN32
	TerminateThread(tid_c, 0);
	WaitForSingleObject(tid_c, INFINITE);
	TerminateThread(tid_s, 0);
	WaitForSingleObject(tid_s, INFINITE);
	if (closesocket(fd_c) == SOCKET_ERROR) {
		printf("closesocket() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if (closesocket(fd_s) == SOCKET_ERROR) {
		printf("closesocket() failed with error: %ld\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	WSACleanup();
#else
	pthread_cancel(tid_c);
	pthread_join(tid_c, NULL);
	pthread_cancel(tid_s);
	pthread_join(tid_s, NULL);
	if (close(fd_c) < 0) {
		perror("close");
		exit(EXIT_FAILURE);
	}
	if (close(fd_s) < 0) {
		perror("close");
		exit(EXIT_FAILURE);
	}
#endif
	return (0);
}