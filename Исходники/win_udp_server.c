int main() {

	SOCKET wsocket;
	
	struct sockaddr_in server;
	struct sockaddr_in secondary_input;

	int slen;
	int recv_len;

	char _buffer[BUFLEN];
	WSADATA wsa;

	slen = sizeof(secondary_input);

	// initialize socket
	printf("%s\n", "Initializing dear system sequence...");

	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("%s%s\n", "ERR", "winsock failure initializing. Rejecting telemetry.");
		return WSAGetLastError();
	}

	printf("%s", "Winsock initialized...\n");

	// create socket
	if(wsocket = socket(AF_INET, SOCK_DGRAM, 0) == INVALID_SOCKET) {
		printf("%s%s\n", "ERR", "winsock failure spawning. Rejecting telemetry.");
		return WSAGetLastError();
	}

	printf("%s", "Winsock spawned. Binding...");

	// set struct properties
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	// bind socket
	if(bind(wsocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("%s%s\n", "ERR", "winsock failure binding. Rejecting telemetry.");
		return WSAGetLastError();
	}

	printf("%s", "winsock ready. Listening for telemetry...\n");

	while(1) {

		fflush(stdout);
		memset(_buffer, '\0', BUFLEN);

		// receive data
		if((recv_len = recvfrom(wsocket, _buffer, BUFLEN, 0, (struct sockaddr *)&secondary_input, &slen)) == SOCKET_ERROR) {
			printf("%s\n", "winsock failure receiving telemetry. Flushing...");
			return WSAGetLastError();
		}

		// print data
		printf("%s\n", _buffer);

	}

	closesocket(wsocket);
	WSACleanup();

	return 0;
}