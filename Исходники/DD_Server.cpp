unsigned int WINAPI ClientHandlingThread( LPVOID lpParam )
{
	LThreadType = THREAD_CLIENT;

	PendingAcceptList* pAcceptList = (PendingAcceptList*)lpParam;

	/// Timer
	HANDLE hTimer = CreateWaitableTimer( NULL, FALSE, NULL );
	if ( hTimer == NULL )
		return -1;

	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -10000000; ///< 1초 후부터 동작
	if ( !SetWaitableTimer( hTimer, &liDueTime, 100, TimerProc, NULL, TRUE ) )
		return -1;

	while ( true )
	{
		SOCKET acceptSock = NULL;

		/// 새로 접속한 클라이언트 처리
		if ( pAcceptList->Consume( acceptSock, false ) )
		{
			/// 소켓 정보 구조체 할당과 초기화
			ClientSession* client = GClientManager->CreateClient( acceptSock );

			SOCKADDR_IN clientaddr;
			int addrlen = sizeof( clientaddr );
			getpeername( acceptSock, (SOCKADDR*)&clientaddr, &addrlen );

			// 클라 접속 처리
			if ( false == client->OnConnect( &clientaddr ) )
			{
				client->Disconnect();
			}

			continue; ///< 다시 대기로
		}

		/// 최종적으로 클라이언트들에 쌓인 send 요청 처리
		GClientManager->FlushClientSend();

		/// APC Queue에 쌓인 작업들 처리
		SleepEx( INFINITE, TRUE );
	}

	CloseHandle( hTimer );
	return 0;
}