BOOL Server(void) {
	DWORD		Ret;
	SOCKET		ListenSocket;
	struct		sockaddr_in InetAddr;
	WSADATA		wsaData;
	LPSTR		psBuff;

	WORD wVersionRequested = MAKEWORD(2,2);

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	if ((Ret = WSAStartup(wVersionRequested, &wsaData)) != 0) {
		wsprintf(psBuff, (LPCTSTR)"WSAStartup failed with error %d", Ret);
		AppendLog(psBuff);
		return FALSE;
	}

	if ((ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 	{
		wsprintf(psBuff, (LPCTSTR)"socket() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}

	WSAAsyncSelect(ListenSocket, ghWndMain, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

	wsprintf(psBuff, (LPCTSTR)"WM_SOCKET = %d", WM_SOCKET);
	AppendLog(psBuff);

	memset((char *)&InetAddr, 0, sizeof(struct sockaddr_in));
	InetAddr.sin_family = AF_INET;
	InetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InetAddr.sin_port = htons(PORT);

	if (bind(ListenSocket, (struct sockaddr *)&InetAddr, sizeof(InetAddr)) == SOCKET_ERROR) {
		wsprintf(psBuff, (LPCTSTR)"bind() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}

	if (listen(ListenSocket, 5)) {
		wsprintf(psBuff, (LPCTSTR)"listen() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}
	else {
		return TRUE;
	}
}