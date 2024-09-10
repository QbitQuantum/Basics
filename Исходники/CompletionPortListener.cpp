int CompletionPortListener::Start()
{
	if ((Ret = WSAStartup((2, 2), &wsaData)) != 0)
	{
		printf("WSAStartup() failed with error %d\n", Ret);
		return 1;
	}
	else
		printf("WSAStartup() is OK!\n");

	// Setup an I/O completion port
	if ((CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		printf("CreateIoCompletionPort() failed with error %d\n", GetLastError());
		return 1;
	}
	else
		printf("CreateIoCompletionPort() is damn OK!\n");

	// Determine how many processors are on the system
	GetSystemInfo(&SystemInfo);
	// Create worker threads based on the number of processors available on the
	// system. Create two worker threads for each processor
	for (i = 0; i < (int)SystemInfo.dwNumberOfProcessors * 2; i++)
	{
		// Create a server worker thread and pass the completion port to the thread
		if ((ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, this, 0, &ThreadID)) == NULL)
		{
			printf("CreateThread() failed with error %d\n", GetLastError());
			return 1;
		}
		else
			printf("CreateThread() is OK!\n");
		// Close the thread handle
		CloseHandle(ThreadHandle);
	}

	// Create a listening socket
	if ((Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("WSASocket() is OK!\n");

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(DEFAULT_PORT_INT);

	if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("bind() is fine!\n");

	// Prepare socket for listening
	if (listen(Listen, 5) == SOCKET_ERROR)
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("listen() is working...\n");

	completionPortStackListener.Start();

	// Accept connections and assign to the completion port
	while (TRUE)
	{
		if ((Accept = WSAAccept(Listen, NULL, NULL, NULL, 0)) == SOCKET_ERROR)
		{
			printf("WSAAccept() failed with error %d\n", WSAGetLastError());
			return 1;
		}
		else
			printf("WSAAccept() looks fine!\n");

		// Create a socket information structure to associate with the socket
		if ((PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA))) == NULL)
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
		else
			printf("GlobalAlloc() for LPPER_HANDLE_DATA is OK!\n");

		// Associate the accepted socket with the original completion port
		printf("Socket number %d got connected...\n", Accept);
		PerHandleData->Socket = Accept;

		if (CreateIoCompletionPort((HANDLE)Accept, CompletionPort, (DWORD)PerHandleData, 0) == NULL)
		{
			printf("CreateIoCompletionPort() failed with error %d\n", GetLastError());
			return 1;
		}
		else
			printf("CreateIoCompletionPort() is OK!\n");

		// Create per I/O socket information structure to associate with the WSARecv call below
		if ((PerIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_OPERATION_DATA))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			return 1;
		}
		else
			printf("GlobalAlloc() for LPPER_IO_OPERATION_DATA is OK!\n");

		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		PerIoData->BytesSEND = 0;
		PerIoData->BytesRECV = 0;
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;

		Flags = 0;
		if (WSARecv(Accept, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags, &(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				printf("WSARecv() failed with error %d\n", WSAGetLastError());
				return 1;
			}
		}
		else
			printf("WSARecv() is OK!\n");

	}

}