DWORD WINAPI IocpServerWorker(LPVOID p)
{
	SYSTEM_INFO SystemInfo;
	DWORD ThreadID;
	SOCKET Accept;
	int nRet;
	int ClientIndex;
	SOCKADDR_IN cAddr;
	IN_ADDR		cInAddr;
	int			cAddrlen = sizeof( cAddr );
	LPPER_SOCKET_CONTEXT lpPerSocketContext = NULL; 
	DWORD RecvBytes;
	DWORD Flags=0;
	
	InitializeCriticalSection(&criti);
	GetSystemInfo(&SystemInfo);

	g_dwThreadCount = SystemInfo.dwNumberOfProcessors * 2;
	//MyFix 3
	if ( g_dwThreadCount > 16 )
    {
       g_dwThreadCount = 16;
       LogAdd(" **** Worker Thread Max Count Fix 16ea ****");
    }
	//ms_exc.registration.TryLevel = 0;
	
	__try
	{

		g_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if ( g_CompletionPort == NULL)
		{
			LogAdd("CreateIoCompletionPort failed with error: %d", GetLastError());
			__leave;
		}
		
		for(DWORD dwCPU = 0; dwCPU < g_dwThreadCount; dwCPU++)
		{
			HANDLE ThreadHandle;
			// Create a server worker thread and pass the completion port to the thread.
			
			ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, g_CompletionPort, 0, &ThreadID);
			if ( ThreadHandle == NULL)
			{
				LogAdd("CreateThread() failed with error %d", GetLastError());
				__leave;
			}
			g_ThreadHandles[dwCPU] = ThreadHandle;
			CloseHandle(ThreadHandle);

		}

		if (!CreateListenSocket() )
			__leave;

		
		while(TRUE)		
		{
			Accept = WSAAccept(g_Listen, (LPSOCKADDR)&cAddr, &cAddrlen, NULL, 0);
			if (Accept==SOCKET_ERROR)
			{
				EnterCriticalSection(&criti);
				LogAdd("WSAAccept() failed with error %d", WSAGetLastError());
				LeaveCriticalSection(&criti);
				continue;
			}
			EnterCriticalSection(&criti);

			memcpy( &cInAddr, &cAddr.sin_addr.s_addr, 4 );

			ClientIndex = gObjAddSearch(Accept, inet_ntoa(cInAddr) );
			
			if ( ClientIndex == -1 )
			{
				LogAddL("error-L2 : ClientIndex = -1");
				closesocket(Accept);
				LeaveCriticalSection(&criti);
				continue;
			}

			if (UpdateCompletionPort(Accept, ClientIndex, 1) == 0 )
			{
				LogAddL("error-L1 : %d %d CreateIoCompletionPort failed with error %d", Accept, ClientIndex, GetLastError() );
				closesocket(Accept);
				LeaveCriticalSection(&criti);
				continue;
			}

			if (gObjAdd(Accept, inet_ntoa(cInAddr), ClientIndex) == -1 )
			{
				LogAddL("error-L1 : %d %d gObjAdd() failed with error %d", Accept, ClientIndex, GetLastError() );
				LeaveCriticalSection(&criti);
				closesocket(Accept);
				continue;
			}
			bool bCryptoOpenCS = g_CryptoSessionCS.Open(ClientIndex);
            bool bCryptoOpenSC = g_CryptoSessionSC.Open(ClientIndex);
            if ( !bCryptoOpenCS || !bCryptoOpenSC )
			{
				g_CryptoSessionCS.Close(ClientIndex);
                g_CryptoSessionSC.Close(ClientIndex);
                LogAddL("error-L1 : %d %d Open Set Crypto Open failed with error", Accept, ClientIndex);
                LeaveCriticalSection(&criti);
                closesocket(Accept);
                continue;
			}
			memset(&gObj[ClientIndex].PerSocketContext->IOContext[0].Overlapped, 0, sizeof(OVERLAPPED));
			memset(&gObj[ClientIndex].PerSocketContext->IOContext[1].Overlapped, 0, sizeof(OVERLAPPED));
			gObj[ClientIndex].PerSocketContext->IOContext[0].wsabuf.buf = gObj[ClientIndex].PerSocketContext->IOContext[0].Buffer;
			gObj[ClientIndex].PerSocketContext->IOContext[0].wsabuf.len = MAX_IO_BUFFER_SIZE;
			gObj[ClientIndex].PerSocketContext->IOContext[0].nTotalBytes = 0;
			gObj[ClientIndex].PerSocketContext->IOContext[0].nSentBytes = 0;
			gObj[ClientIndex].PerSocketContext->IOContext[0].nWaitIO    = 0;
			gObj[ClientIndex].PerSocketContext->IOContext[0].nSecondOfs = 0;
			gObj[ClientIndex].PerSocketContext->IOContext[0].IOOperation = RECV_IO;
			
			gObj[ClientIndex].PerSocketContext->IOContext[1].wsabuf.buf = gObj[ClientIndex].PerSocketContext->IOContext[0].Buffer;
			gObj[ClientIndex].PerSocketContext->IOContext[1].wsabuf.len = MAX_IO_BUFFER_SIZE;
			gObj[ClientIndex].PerSocketContext->IOContext[1].nTotalBytes= 0;
			gObj[ClientIndex].PerSocketContext->IOContext[1].nSentBytes = 0;
			gObj[ClientIndex].PerSocketContext->IOContext[1].nWaitIO    = 0;
			gObj[ClientIndex].PerSocketContext->IOContext[1].nSecondOfs = 0;
			gObj[ClientIndex].PerSocketContext->IOContext[1].IOOperation = SEND_IO;
			gObj[ClientIndex].PerSocketContext->m_socket = Accept;
			gObj[ClientIndex].PerSocketContext->nIndex   = ClientIndex;

			nRet = WSARecv(Accept, &(gObj[ClientIndex].PerSocketContext->IOContext[0].wsabuf), 1, &RecvBytes, &Flags,
				&(gObj[ClientIndex].PerSocketContext->IOContext[0].Overlapped), NULL);

			if( nRet == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING )
			{
				LogAdd("error-L1 : WSARecv() failed with error %d", WSAGetLastError());
				gObj[ClientIndex].PerSocketContext->IOContext[0].nWaitIO = 4;
				CloseClient(gObj[ClientIndex].PerSocketContext, FALSE);
				LeaveCriticalSection(&criti);
				continue;
			}

			gObj[ClientIndex].PerSocketContext->IOContext[0].nWaitIO = 1;
			gObj[ClientIndex].PerSocketContext->dwIOCount++;

			LeaveCriticalSection(&criti);
			SCPJoinResultSend(ClientIndex, 1);

		}
	}
	__finally  
	{		
		if( g_CompletionPort )
		{
			for (DWORD i = 0; i < g_dwThreadCount; i++) 
					PostQueuedCompletionStatus(g_CompletionPort, 0, 0, NULL); 
		}
		if( g_CompletionPort )
		{
			CloseHandle(g_CompletionPort);
			g_CompletionPort = NULL;
		}
		if (g_Listen != INVALID_SOCKET)  
		{ 
            closesocket(g_Listen);  
            g_Listen = INVALID_SOCKET; 
		} 
	}
	return TRUE;
}