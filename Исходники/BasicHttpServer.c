/*
Name: ListenForClientConnection
Description: This function will have an infinite loop where it will wait forever for client connections. Once client connection is established.
			 It will process it in a fast way or religate the work to a thread and keeps waiting for new connections.
Parameters: - 
ReturnValue: 0 for success else error codes.
*/
int ListenForClientConnection()
{
	int nReturnValue = 0;
	struct addrinfo *structClientAddrInfo = NULL;
	SOCKET scClientSocket = INVALID_SOCKET;
	HANDLE hClientThread = NULL;
	DWORD dwClientThreadId = 0;
	char szMessage[1024] = { '\0' };

	LogMessage(LOG_DEBUG, "Started to listen for client connection");

	if (INVALID_SOCKET == scListenSocket)
	{
		LogMessage(LOG_ERROR, "Invalid listen socket");
		nReturnValue = ERR_INVALIDLISTENSOCKET;
		return nReturnValue;
	}

	LogMessage(LOG_INFO, "listening.........");
	nReturnValue = listen(scListenSocket, SOMAXCONN);
	if (nReturnValue == SOCKET_ERROR)
	{
		//printf_s("BHS:ERROR:listen failed with error %d\n", WSAGetLastError());
		sprintf_s(szMessage, 1024, "listen failed with error %d\n", WSAGetLastError());
		LogMessage(LOG_ERROR, szMessage);
		closesocket(scListenSocket);
		scListenSocket = INVALID_SOCKET;
		WSACleanup();
		nReturnValue = ERR_LISTENFAILURE;
		return nReturnValue;
	}

	LogMessage(LOG_INFO, "Initializing synchronization elements");

	InitializeCriticalSection(&mcriticalThreadSync);
	InitializeConditionVariable(&mcvThreadCount);

	LogMessage(LOG_INFO, "Going for infinite loop of accepts");
	while ((scClientSocket = accept(scListenSocket, NULL, NULL)) != INVALID_SOCKET)
	{

		//printf_s("BHS:INFO:Client connection established: \n");
		LogMessage(LOG_INFO, "Client connection established, Creating a thread to handle the connection");
		//printf_s("BHS:INFO:Creating a thread to handle the connection\n");
		
		hClientThread = CreateThread(NULL, 0, HandleClientRequestThread, scClientSocket, 0x00000004, &dwClientThreadId);

		EnterCriticalSection(&mcriticalThreadSync);


		if (nThread_Count >= nThreadPoolSize)
		{
			LogMessage(LOG_DEBUG, "Active thread count is more than thread pool size");
			SleepConditionVariableCS(&mcvThreadCount, &mcriticalThreadSync, INFINITE);
			LogMessage(LOG_DEBUG, "Got up from sleep(wait), now waking the creating thread to handle client request");
			
		}

		nThread_Count++;
		ResumeThread(hClientThread);

		LeaveCriticalSection(&mcriticalThreadSync);

		LogMessage(LOG_INFO, "Returning to wait for new client connections......");
		//printf_s("BHS:INFO:Returning to wait for new connections......\n");
	}

	if (scClientSocket == INVALID_SOCKET)
	{
		//printf_s("BHS:ERROR:Invalid client socket %d\n", WSAGetLastError());
		sprintf_s(szMessage, 1024, "Invalid client socket %d\n", WSAGetLastError());
		LogMessage(LOG_ERROR, szMessage);
		nReturnValue = ERR_INVALIDCLIENTSOCKET;
	}
	else
	{
		LogMessage(LOG_INFO, "Closing the client socket");
		closesocket(scClientSocket);
		scClientSocket = INVALID_SOCKET;
	}
	
	LogMessage(LOG_INFO, "Closing the listen socket");
	closesocket(scListenSocket);
	scListenSocket = INVALID_SOCKET;
	WSACleanup();

	DeleteCriticalSection(&mcriticalThreadSync);
	
	LogMessage(LOG_DEBUG, "Finished listening for client connection");
	return nReturnValue;
}