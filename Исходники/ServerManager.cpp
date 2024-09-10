//클라이언트의ㅡaccept를 담당할 쓰레드
UINT AcceptThread( LPVOID lParam ){

	SERVER_INFO* serverInfo = (SERVER_INFO*)lParam;

	OVERLAPPED ov;

	while(TRUE)
	{
		//SOCKET clientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//이렇게 프로토콜만 결정된상태
		SOCKET clientSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		char temp[1024];
		DWORD dwRecv;	//이건사실안나온다. 억셉트ex는 비동기함수라 바로 밑으로 빠져나간다. 그래서 dwRecv에 값이 들어갈수가없다. 형식적인거.

		memset(&ov, 0, sizeof(ov));
		AcceptEx(*serverInfo->hServSock, clientSocket, temp, 0, sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &dwRecv, &ov);
		//첫번째 listensocket, 서버소켓만들고바인드하고리슨까지한거,그다음은 acceptsocket			

		//그럼 이제 시스템이 내부적으로 클라이언트가 connect할때까지 기다린다.
		//우리는 클라이언트가 커넥트하면 clientSocket가지고 링크드리스트에 집어넣고 이런작업해야한다.
		//근데 얘는 언제끝날지 모른다. 그래서
		WaitForSingleObject((HANDLE)*serverInfo->hServSock, INFINITE);	//이렇게 클라이언트가 connect할때까지 기다리는거다.

		//SOCKADDR_IN의 더블포인터가 필요하다.
		SOCKADDR_IN * pLocal;
		SOCKADDR_IN * pAddr;
		int iLocalLen = sizeof(SOCKADDR_IN);
		int iRemoteLen = sizeof(SOCKADDR_IN);
		GetAcceptExSockaddrs(temp, 0, sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, (sockaddr **)&pLocal,
			&iLocalLen, (sockaddr **)&pAddr, &iRemoteLen);	//이 temp에 정보가 다 들어있다.

		CreateIoCompletionPort((HANDLE)clientSocket, *serverInfo->hComPort, (DWORD)clientSocket, 0);
		//세번째 파라미터가 RecvFunc에 dwCompKey로 간다.
		//이렇게 하면 소켓이 아까 만든 껍데기에 등록이 된다. 처음에 한명이 접근해서 하나가 등록이 된다.

		EnterCriticalSection(&myCS2);
		//client 등록
		serverInfo->mCToonVasServerDlg->AddClient(clientSocket, *pAddr);
		
		LeaveCriticalSection(&myCS2);

	}
	return 0;
}