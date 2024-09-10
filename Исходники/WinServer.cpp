VOID AcceptThread(LPVOID)
{
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_DATA PerIoData;
	SOCKET clientSock;
	DWORD Flags,RecvBytes;
	while(1)
	{
		clientSock = accept(hSocket,NULL, NULL);
		if(clientSock == INVALID_SOCKET)
		{
			cout << "Error!! accept()" << endl;
			return ;
		}


		PerHandleData = (LPPER_HANDLE_DATA)new(PER_HANDLE_DATA);
		g_sockArr[g_clientNum++] = PerHandleData->hSocket = clientSock;

		CreateIoCompletionPort((HANDLE)clientSock, CompletionPort, 
			(DWORD)PerHandleData,0);

		PerIoData = (LPPER_IO_DATA) new PER_IO_DATA;
		ZeroMemory(&(PerIoData->overlapped), sizeof(OVERLAPPED));
		PerIoData->wsaBuf.len = sizeof(DATA);
		PerIoData->wsaBuf.buf = (char*)&PerIoData->data;
		Flags = 0;

		if(WSARecv(clientSock, &(PerIoData->wsaBuf), 1, &RecvBytes,
			&Flags, &(PerIoData->overlapped), NULL) == SOCKET_ERROR)
		{
			if(WSAGetLastError( ) != ERROR_IO_PENDING)
			{
				cout << "Error!! WSARecv()" << endl;
				return ;
			}
		}
	}
}