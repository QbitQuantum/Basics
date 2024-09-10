int main(int argc, char* argv[]) {
	while (!initSock());
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockServer == INVALID_SOCKET) {
		clearSock(sockServer);
		return -1;
	}
	sockaddr_in serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);


	if (bind(sockServer, (sockaddr*)&serverAddr, sizeof(sockaddr))) {
		clearSock(sockServer);
		return -1;
	}

	WSAEVENT listenEvent = WSACreateEvent();
	long eventType = FD_ACCEPT | FD_CLOSE;
	WSAEventSelect(sockServer, listenEvent, eventType);
	printf("******************************************************************************\n");
	printf("**********welcome to use the high-big-up server built by lancelot************");
	printf("********************************************************************************\n");
	printf("\nwaiting...\n");
	if (listen(sockServer, SOMAXCONN) == SOCKET_ERROR) {
		clearSock(sockServer);
		printf("\n                               bye-bye \n");
		return -1;
	}
	arrSocket[g_total] = sockServer;
	arrEvent[g_total++] = listenEvent;

	char buf[1024] = { 0 };
	SOCKET sockClient = INVALID_SOCKET;
	WSANETWORKEVENTS netWorkEvent = { 0 };
	long clientEventType = FD_CLOSE | FD_READ | FD_WRITE;
	while (true) {
		g_index = WSAWaitForMultipleEvents(g_total, arrEvent, false, 100, false);
		if (g_index == WSA_WAIT_TIMEOUT)
			continue;
		WSAEnumNetworkEvents(arrSocket[g_index - WSA_WAIT_EVENT_0], arrEvent[g_index - WSA_WAIT_EVENT_0], &netWorkEvent);
		if(!eventFunc(netWorkEvent, sockClient, buf, clientEventType))
			continue;
		printf("get a message!\n");
	}

	if (sockServer != INVALID_SOCKET)
		closesocket(sockServer);
	WSACleanup();
	return 0;
}