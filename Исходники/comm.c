/* Initialize a dac_conn_t and connect to the DAC.
 *
 * On success, return 0.
 */
int dac_connect(dac_t *d, const char *host, const char *port) {
	dac_conn_t *conn = &d->conn;
	ZeroMemory(conn, sizeof(d->conn));

	// Look up the server address
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	trace(d, "Calling getaddrinfo: \"%s\", \"%s\"\n", host, port);

	int res = getaddrinfo(host, port, &hints, &result);
	if (res != 0) {
		trace(d, "getaddrinfo failed: %d\n", res);
		return -1;
	}

	// Create a SOCKET
	ptr = result;
	conn->sock = socket(ptr->ai_family, ptr->ai_socktype, 
		ptr->ai_protocol);

	if (conn->sock == INVALID_SOCKET) {
		log_socket_error(d, "socket");
		freeaddrinfo(result);
		return -1;
	}

	unsigned long nonblocking = 1;
	ioctlsocket(conn->sock, FIONBIO, &nonblocking);

	memset(&conn->udp_target, 0, sizeof(conn->udp_target));
	conn->udp_target.sin_family = AF_INET;
	conn->udp_target.sin_addr.s_addr = ((struct sockaddr_in *)(ptr->ai_addr))->sin_addr.s_addr;
	conn->udp_target.sin_port = htons(60000);

	// Connect to host. Because the socket is nonblocking, this
	// will always return WSAEWOULDBLOCK.
	connect(conn->sock, ptr->ai_addr, (int)ptr->ai_addrlen);
	freeaddrinfo(result);

	if (WSAGetLastError() != WSAEWOULDBLOCK) {
		log_socket_error(d, "connect");
		closesocket(conn->sock);
		conn->sock = INVALID_SOCKET;
		return -1;
	}

	// Wait for connection.
	fd_set set;
	FD_ZERO(&set);
	FD_SET(conn->sock, &set);
	struct timeval time;
	time.tv_sec = 0;
	time.tv_usec = DEFAULT_TIMEOUT;
	res = select(0, &set, &set, &set, &time);

	if (res == SOCKET_ERROR) {
		log_socket_error(d, "select");
		closesocket(conn->sock);
		conn->sock = INVALID_SOCKET;
		return -1;
	} else if (res == 0) {
		trace(d, "Connection to %s timed out.\n", host);
		closesocket(conn->sock);
		conn->sock = INVALID_SOCKET;
		return -1;
	}

	// See if we have *actually* connected
	int error;
	int len = sizeof(error);
	if (getsockopt(conn->sock, SOL_SOCKET, SO_ERROR, (char *)&error, &len) ==
			SOCKET_ERROR) {
		log_socket_error(d, "getsockopt");
		closesocket(conn->sock);
		conn->sock = INVALID_SOCKET;
		return -1;
	}

	if (error) {
		WSASetLastError(error);
		log_socket_error(d, "connect");
		closesocket(conn->sock);
		conn->sock = INVALID_SOCKET;
		return -1;
	}

	BOOL ndelay = 1;
	res = setsockopt(conn->sock, IPPROTO_TCP, TCP_NODELAY,
		(char *)&ndelay, sizeof(ndelay));
	if (res == SOCKET_ERROR) {
		log_socket_error(d, "setsockopt TCP_NODELAY");
		closesocket(conn->sock);
		conn->sock = INVALID_SOCKET;
		return -1;
	}

	trace(d, "Connected.\n");

	// Create socket for OSC
	conn->udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (conn->udp_sock == INVALID_SOCKET) {
		log_socket_error(d, "socket(AF_INET, SOCK_DRGAM)");
	} else {
		res = connect(conn->udp_sock, (struct sockaddr *)&conn->udp_target, sizeof(conn->udp_target));
		if (res == SOCKET_ERROR) {
			log_socket_error(d, "connect(udp_sock)");
		}
	}

	nonblocking = 1;
	ioctlsocket(conn->udp_sock, FIONBIO, &nonblocking);

	// After we connect, the host will send an initial status response. 
	dac_read_resp(d, DEFAULT_TIMEOUT);
	dac_dump_resp(d);

	char c = 'p';
	dac_sendall(d, &c, 1);
	dac_read_resp(d, DEFAULT_TIMEOUT);
	dac_dump_resp(d);

	if (d->sw_revision >= 2) {
		c = 'v';
		dac_sendall(d, &c, 1);
		res = dac_read_bytes(d, d->version, sizeof(d->version));
		if (res < 0)
			return res;

		trace(d, "DAC version: %.*s\n", sizeof(d->version), d->version);
	} else {
		memset(d->version, 0, sizeof(d->version));
		trace(d, "DAC version old!\n");
	}

	return 0;
}