void main()
{
	WSADATA wsa; // 버전정보   

	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) //DLL 로딩 
	{
		puts("WSAStartup Error !! "); return ;
	}
	//1) 핸드폰 단말기 구입 -->  SOCKET : 통신을 하기위한 매개체 !! 
	SOCKET ServerSocket;  
	//2) 소켓 생성 !!		   // TCP/UDP   TCP   
	ServerSocket = socket( AF_INET  , SOCK_STREAM, 0);  

	if( ServerSocket == INVALID_SOCKET)
	{
		puts("socket() error!!");	return ; 
	}
	//3) Usim 
	SOCKADDR_IN ServerAddr; 
	ServerAddr.sin_family		  = AF_INET;		    // TCP/UDP 
	ServerAddr.sin_port		  = htons(20000);	// 포트번호 
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	// 4) socket + sockaddr  ==   핸드폰 + Usim 	
	int ret =	bind( ServerSocket, // 소켓 
		(SOCKADDR*)&ServerAddr, //주소 구조체 
		sizeof(ServerAddr));		    // 주소의 크기 

	if( ret == SOCKET_ERROR) 
	{
		puts("bind() error !! "); return ; 
	}
	// 4) 통화 대기 !! 
	ret = 	  listen( ServerSocket,  // 기다릴 소켓 
		SOMAXCONN);	// 가능한 최대값 

	if( ret == SOCKET_ERROR ) 
	{
		puts("listen() error !!"); return ; 
	}
	// 1) 소켓과 이벤트를 연결하고 배열에 저장 
		
	HANDLE hEvent = WSACreateEvent(); //이벤트 객체 생성 !
	// 2) 연결 !! 
	WSAEventSelect( ServerSocket,  // 이벤트를 처리할 소켓 
						  hEvent,			 // 신호를 보내줄 이벤트 
						  FD_ACCEPT|FD_CLOSE); 

	SockList[SockCnt] = ServerSocket; 
	EventList[SockCnt] = hEvent;
	SockCnt++; 

	int index = 0; 
	WSANETWORKEVENTS ne;  
	while(1) 
	{	
		// 소켓에서 네트워크 이벤트 발생하면 Event객체가 시그날 되기를 기다린다!!
		index = WSAWaitForMultipleEvents( SockCnt,  // 시그날을 기다리는 이벤트 수 
										  EventList,  // 이벤트 배열 
										  FALSE, // 1개만 시그날이 돼도 리턴 !! 
										  WSA_INFINITE, 
										  FALSE); 
		index -= WSA_WAIT_EVENT_0; 
	
		// 1) networkevent 구조체에 이벤트 내용을 가져온다 !! 
		// 2) EventList[index] 이벤트를 넌시그날로 변경 
		WSAEnumNetworkEvents( SockList[index], // 이벤트가 발생한 소켓 
										EventList[index], // 시그널 된 이벤트 
										&ne); // out put 

		if( ne.lNetworkEvents & FD_ACCEPT) 
		{
			
			if(ne.iErrorCode[FD_ACCEPT_BIT] != 0) 
			{			
				puts("accept error"); 
				return;
			}
			SOCKADDR_IN ClientAddr; 
			int len = sizeof(ClientAddr); 
			SOCKET ClientSocket;

			ClientSocket = accept( SockList[index] , // 대기하는 소켓 
										 (SOCKADDR*)&ClientAddr, // 클라이언트의 주소를 가져올 구조체
										 &len); 

			if ( ClientSocket == INVALID_SOCKET) 
			{
				puts("accept error "); return ;
			}	
			printf("[ %s ] : %d 님 접속\n" ,   inet_ntoa( ClientAddr.sin_addr),
			ntohs( ClientAddr.sin_port )  ); 
			// 접속자 소켓과 연결될 이벤트 생성 !! 
			WSAEVENT hClientEvent = WSACreateEvent(); 
			// socket + event 
			WSAEventSelect( ClientSocket, hClientEvent, FD_READ|FD_WRITE|FD_CLOSE); 
				
			SockList[SockCnt] = ClientSocket; 
			EventList[SockCnt] = hClientEvent; 
			SockCnt++; 
		}
		
		if( ne.lNetworkEvents & FD_READ || ne.lNetworkEvents & FD_WRITE) 
		{
			if( ne.lNetworkEvents & FD_READ && 
								ne.iErrorCode[FD_READ_BIT] != 0 ) 
			{			
				puts("FD_READ_BIT"); 
				return;
			}
			if( ne.lNetworkEvents & FD_WRITE && ne.iErrorCode[FD_WRITE_BIT] != 0) 
			{			
				puts("FD_WRITE_BIT"); 
				return;
			}
			char buf[BUF_SIZE] = {0};	
			
			recv( SockList[index], buf , BUF_SIZE, 0); 
			SOCKADDR_IN SenderAddr; 
			int len = sizeof(SenderAddr);

			getpeername( SockList[index], (SOCKADDR*)&SenderAddr, &len); 

			printf("[ %s ] %s\n",  inet_ntoa( SenderAddr.sin_addr) ,buf );	
			
			for( int i = 1; i< SockCnt; i++) 
			{
				if( i != index) 
				send( SockList[i], buf, BUF_SIZE, 0);
			}
		}
		if( ne.lNetworkEvents & FD_CLOSE) 
		{
			if(ne.iErrorCode[FD_CLOSE_BIT] != 0) 
			{			
				puts("FD_CLOSE_BIT"); 
				return;
			}
			RemoveSocket( index );
		
		}

	}
	/*
	
	// 화면에 접속한 클라이언트의 IP를 출력 !! 


	*/
	WSACleanup(); // DLL 정리 

}