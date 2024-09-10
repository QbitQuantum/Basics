int __cdecl main()
{
	// [+] socket setup
	// borrowed from MSDN - https://msdn.microsoft.com/en-us/library/windows/desktop/ms738545%28v=vs.85%29.aspx

	// Initialize Winsock
	WSADATA wsaData = { 0 };
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		printf("WSAStartup failed: %d\n", result);
		return -1;
	}

	struct addrinfo hints = { 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	struct addrinfo *ainfo;
	result = getaddrinfo(LHOST, LPORT, &hints, &ainfo);
	if (result != 0) {
		printf("getaddrinfo failed: %d\n", result);
		WSACleanup();
		return -1;
	}

	// Create a SOCKET for the server to listen for client connections
	SOCKET listenSocket;
	if ((listenSocket = socket(ainfo->ai_family, ainfo->ai_socktype, ainfo->ai_protocol)) == INVALID_SOCKET) {
		printf("socket() failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(ainfo);
		WSACleanup();
		return -1;
	}

	// Setup the TCP listening socket
	if ((bind(listenSocket, ainfo->ai_addr, (int)ainfo->ai_addrlen)) == SOCKET_ERROR) {
		printf("bind() failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(ainfo);
		closesocket(listenSocket);
		WSACleanup();
		return -1;
	}
	freeaddrinfo(ainfo);

	// Listen on the socket
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("listen() failed with error: %ld\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return -1;
	}

	printf("[+] Listening for connections.\n");
	
	// [+] handle connections
	// borrowed from http://stackoverflow.com/a/15185627
	while (1) {
		// Accept a connection
		SOCKET clientSocket;
		if ((clientSocket = accept(listenSocket, NULL, NULL)) == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			continue;
		}
		printf("Received connection from remote host.\n");

		// Create thread to handle connection
		_beginthread(&handleConnection, 0, (void*)clientSocket);
		printf("Connection handed off to handler thread.\n");
	}
}