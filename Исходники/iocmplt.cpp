void main(void)
{
    SOCKADDR_IN InternetAddr;
    SOCKET Listen;
    SOCKET Accept;
    HANDLE CompletionPort;
    SYSTEM_INFO SystemInfo;
    LPPER_HANDLE_DATA PerHandleData;
    LPPER_IO_OPERATION_DATA PerIoData;
    int i;
    DWORD RecvBytes;
    DWORD Flags;
    DWORD ThreadID;
    WSADATA wsaData;
    DWORD Ret;

    if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
    {
        printf("WSAStartup failed with error %d\n", Ret);
        return;
    }

    // Setup an I/O completion port.

    if ((CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
    {
        printf( "CreateIoCompletionPort failed with error: %d\n", GetLastError());
        return;
    }

    // Determine how many processors are on the system.

    GetSystemInfo(&SystemInfo);

    // Create worker threads based on the number of processors available on the
    // system. Create two worker threads for each processor.

    for(i = 0; i < SystemInfo.dwNumberOfProcessors * 2; i++)
    {
        HANDLE ThreadHandle;

        // Create a server worker thread and pass the completion port to the thread.

        if ((ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, CompletionPort,
                                         0, &ThreadID)) == NULL)
        {
            printf("CreateThread() failed with error %d\n", GetLastError());
            return;
        }

        // Close the thread handle
        CloseHandle(ThreadHandle);
    }

    // Create a listening socket

    if ((Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
                            WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
        printf("WSASocket() failed with error %d\n", WSAGetLastError());
        return;
    }

    InternetAddr.sin_family = AF_INET;
    InternetAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    InternetAddr.sin_port = htons(PORT);


    if (bind(Listen, (PSOCKADDR) &InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
    {
        printf("bind() failed with error %d\n", WSAGetLastError());
        return;
    }

    // Prepare socket for listening

    if (listen(Listen, 5) == SOCKET_ERROR)
    {
        printf("listen() failed with error %d\n", WSAGetLastError());
        return;
    }

    // Accept connections and assign to the completion port.
    sockaddr_in client;
    int len=sizeof(client);
    while(TRUE)
    {
        ZeroMemory(&client,sizeof(sockaddr_in));
        if ((Accept = WSAAccept(Listen, PSOCKADDR(&client), &len, NULL, 0)) == SOCKET_ERROR)
        {
            printf("WSAAccept() failed with error %d\n", WSAGetLastError());
            return;
        }

        // Create a socket information structure to associate with the socket
        if ((PerHandleData = (LPPER_HANDLE_DATA) GlobalAlloc(GPTR,
                             sizeof(PER_HANDLE_DATA))) == NULL)
        {
            printf("GlobalAlloc() failed with error %d\n", GetLastError());
            return;
        }

        // Associate the accepted socket with the original completion port.

        PerHandleData->Socket = Accept;

        if (CreateIoCompletionPort((HANDLE) Accept, CompletionPort, (DWORD) PerHandleData,
                                   0) == NULL)
        {
            printf("CreateIoCompletionPort failed with error %d\n", GetLastError());
            return;
        }

        // Create per I/O socket information structure to associate with the
        // WSARecv call below.

        if ((PerIoData = (LPPER_IO_OPERATION_DATA) GlobalAlloc(GPTR,          sizeof(PER_IO_OPERATION_DATA))) == NULL)
        {
            printf("GlobalAlloc() failed with error %d\n", GetLastError());
            return;
        }

        ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
        strncpy(PerIoData->ip,inet_ntoa(client.sin_addr),20);
        PerIoData->port=ntohs(client.sin_port);
        PerIoData->BytesSEND = 0;
        PerIoData->BytesRECV = 0;
        PerIoData->DataBuf.len = DATA_BUFSIZE;
        PerIoData->DataBuf.buf = PerIoData->Buffer;

        printf("[%s:%u] has established!!\n",PerIoData->ip,PerIoData->port);

        Flags = 0;
        if (WSARecv(Accept, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
                    &(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
        {
            if (WSAGetLastError() != ERROR_IO_PENDING)
            {
                printf("WSARecv() failed with error %d\n", WSAGetLastError());
                return;
            }
        }
    }
}