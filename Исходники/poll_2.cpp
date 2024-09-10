int __cdecl main()
{
	WSADATA wsd;
	INT nStartup = 0, nErr = 0, ret = 0;
	SOCKET lsock = INVALID_SOCKET, asock = INVALID_SOCKET;
	SOCKADDR_STORAGE    addr = {0};
	WSAPOLLFD           fdarray = {0};
	ULONG               uNonBlockingMode = 1;
	CHAR                buf[MAX_PATH] = {0};
	HANDLE              hThread = NULL;
	DWORD               dwThreadId = 0;
	
	nErr = WSAStartup(WS_VER,&wsd);
	if (nErr) {
		WSASetLastError(nErr);
		ERR("WSAStartup");
		exit(0);
	} else {
		nStartup++;
	}
	
	if (NULL == (hCloseSignal = CreateEvent(NULL, TRUE, FALSE, NULL))) {
		ERR("CreateEvent");
		exit(0);
	}
	
	/*
	if (NULL == (hThread = CreateThread(NULL, 0, ConnectThread, NULL, 0, &dwThreadId))) {
		ERR("CreateThread");
		//exit__leave;
	}
	*/
	
	addr.ss_family = AF_INET;
	INETADDR_SETANY((SOCKADDR*)&addr);
	SS_PORT((SOCKADDR*)&addr) = htons(DEFAULT_PORT);
	
	if (INVALID_SOCKET == (lsock = socket(AF_INET, SOCK_STREAM, 0))) {
		ERR("socket");
		exit(0);
	}
	/*
	if (SOCKET_ERROR == ioctlsocket(lsock, FIONBIO, &uNonBlockingMode)) {
		ERR("FIONBIO");
		exit(0);
	}
	*/
	
	if (SOCKET_ERROR == bind(lsock, (SOCKADDR*)&addr, sizeof (addr))) {
		ERR("bind");
		exit(0);
	}
	
	if (SOCKET_ERROR == listen(lsock, 100)) {
		ERR("listen");
		exit(0);
	}
	
	//Call WSAPoll for readability of listener (accepted)
	
	//fdarray.fd = lsock;
	//fdarray.events = POLLRDNORM | POLLWRNORM;

	/*
	if (SOCKET_ERROR == (ret = WSAPoll(&fdarray, 1, DEFAULT_WAIT))) {
		ERR("WSAPoll");
		exit(0);
	}
	*/

while (1) {
	//if (ret) {
		//if ((fdarray.revents & POLLRDNORM) || (fdarray.revents & POLLWRNORM)) {
		//	printf("Main: Connection established.\n");
			
			if (INVALID_SOCKET == (asock = accept(lsock, NULL, NULL))) {
				ERR("accept");
				//__leave;
			}
			
			/*
			if (SOCKET_ERROR == (ret = recv(asock, buf, sizeof(buf), 0))) {
				ERR("recv");
			} else {
				printf("Main: recvd %d bytes\n",ret);
			}
			*/
		//}
	//}
	
	//Call WSAPoll for writeability of accepted
	
	fdarray.fd = asock;
	fdarray.events = POLLWRNORM;
	
	if (SOCKET_ERROR == (ret = WSAPoll(&fdarray, 1, DEFAULT_WAIT))) {
		ERR("WSAPoll");
		// exit
	}
	
	if (ret) {
		if (fdarray.revents & POLLWRNORM) {
			if (SOCKET_ERROR == (ret = send(asock, TST_MSG, sizeof(TST_MSG), 0))) {
				ERR("send");
				// exit
			} else {
				printf("Main: sent %d bytes\n",ret);
				closesocket(asock);
			}
		}
	}

}

	//SetEvent(hCloseSignal);
	
	//WaitForSingleObject(hThread,DEFAULT_WAIT);
	
	/* clean up before exit */
	
	CloseHandle(hCloseSignal);
	CloseHandle(hThread);
	CLOSESOCK(asock);
	CLOSESOCK(lsock);
	
	if (nStartup) {
		WSACleanup();
	}
	
	return 0;
	
}