bool TCPConnection::ConnectIP(uint32 in_ip, uint16 in_port, char* errbuf) {
	if (errbuf)
		errbuf[0] = 0;
	if (ConnectionType != Outgoing) {
		// If this code runs, we got serious problems
		// Crash and burn.
		return false;
	}
	MState.lock();
	if (ConnectReady()) {
		pState = TCPS_Connecting;
	} else {
		MState.unlock();
		SetAsyncConnect(false);
		return false;
	}
	MState.unlock();
	if (!pRunLoop) {
		pRunLoop = true;
#ifdef _WINDOWS
		_beginthread(TCPConnectionLoop, 0, this);
#else
		pthread_t thread;
		pthread_create(&thread, nullptr, TCPConnectionLoop, this);
#endif
	}

	connection_socket = INVALID_SOCKET;
	struct sockaddr_in	server_sin;
	//struct in_addr	in;

	if ((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET || connection_socket == 0) {
#ifdef _WINDOWS
		if (errbuf)
			snprintf(errbuf, TCPConnection_ErrorBufferSize, "TCPConnection::Connect(): Allocating socket failed. Error: %i", WSAGetLastError());
#else
		if (errbuf)
			snprintf(errbuf, TCPConnection_ErrorBufferSize, "TCPConnection::Connect(): Allocating socket failed. Error: %s", strerror(errno));
#endif
		SetState(TCPS_Ready);
		SetAsyncConnect(false);
		return false;
	}
	server_sin.sin_family = AF_INET;
	server_sin.sin_addr.s_addr = in_ip;
	server_sin.sin_port = htons(in_port);

	// Establish a connection to the server socket.
#ifdef _WINDOWS
	if (connect(connection_socket, (PSOCKADDR) &server_sin, sizeof (server_sin)) == SOCKET_ERROR) {
		if (errbuf)
			snprintf(errbuf, TCPConnection_ErrorBufferSize, "TCPConnection::Connect(): connect() failed. Error: %i", WSAGetLastError());
		closesocket(connection_socket);
		connection_socket = 0;
		SetState(TCPS_Ready);
		SetAsyncConnect(false);
		return false;
	}
#else
	if (connect(connection_socket, (struct sockaddr *) &server_sin, sizeof (server_sin)) == SOCKET_ERROR) {
		if (errbuf)
			snprintf(errbuf, TCPConnection_ErrorBufferSize, "TCPConnection::Connect(): connect() failed. Error: %s", strerror(errno));
		close(connection_socket);
		connection_socket = 0;
		SetState(TCPS_Ready);
		SetAsyncConnect(false);
		return false;
	}
#endif
	int bufsize = 64 * 1024; // 64kbyte recieve buffer, up from default of 8k
	setsockopt(connection_socket, SOL_SOCKET, SO_RCVBUF, (char*) &bufsize, sizeof(bufsize));
#ifdef _WINDOWS
	unsigned long nonblocking = 1;
	ioctlsocket(connection_socket, FIONBIO, &nonblocking);
#else
	fcntl(connection_socket, F_SETFL, O_NONBLOCK);
#endif

	SetEcho(false);
	ClearBuffers();

	rIP = in_ip;
	rPort = in_port;
	SetState(TCPS_Connected);
	SetAsyncConnect(false);
	return true;
}