DWORD IOCPNet::WSAAcceptProcess()
{
	IOCPNet* pThis = this;

	while (true)
	{
		HANDLE_Data* hAccept = NULL;
		SOCKADDR_IN clientAddr;
		int len = sizeof(clientAddr);

		int acceptSocket = WSAAccept(pThis->m_ServerSocket, (sockaddr*)&clientAddr, &len, NULL, NULL);

		if (!m_bRun)
		{
			return 0;
		}

		if(acceptSocket == INVALID_SOCKET)
		{
			printf("create socket fail %d \n", WSAGetLastError());
			/*return -1;*/
			continue;
		}

		if (m_nConnectNum >= MAX_CONNECT_NUM)
		{
			closesocket(acceptSocket);
			printf("server has already connect full cur = %d  max = %d \n", m_nConnectNum, MAX_CONNECT_NUM);
			continue;
		}

		hAccept = new HANDLE_Data;

		if (!hAccept)
		{
			closesocket(acceptSocket);
			printf("new HANDLE_Data fail \n");
			return -1;
		}

		hAccept->acceptSocket = acceptSocket;
		memcpy(&hAccept->ClientAddr, &clientAddr, sizeof(SOCKADDR_IN));

		pThis->m_mapClientSocket.insert(make_pair(hAccept->acceptSocket, hAccept));
		printf("socket[%d] port[%d] ip[%s] connect \n", (int)hAccept->acceptSocket, hAccept->ClientAddr.sin_port, inet_ntoa(hAccept->ClientAddr.sin_addr));

		HANDLE h = CreateIoCompletionPort((HANDLE)hAccept->acceptSocket, pThis->m_CompletePort, (DWORD)hAccept, 0);

		if (h == NULL)
		{
			closesocket(hAccept->acceptSocket);
			pThis->ClearClientSocket(hAccept->acceptSocket);
			printf("CreateIoCompletionPort fail %d \n", WSAGetLastError());
			continue;
		}
		
		IOData* data = new IOData;
		if (!data)
		{
			return -1;
		}

		ZeroMemory(&data->overLapped, sizeof(data->overLapped));
		data->wsaBuff.len = DataBuffSize;
		data->wsaBuff.buf = data->szBuffer;
		data->OpType = IO_TYPE_READ;

		DWORD RecvBytes;  
		DWORD Flags = 0;  

		int nError = NO_ERROR;
		nError = WSARecv(hAccept->acceptSocket, &data->wsaBuff, 1, &RecvBytes, &Flags, &data->overLapped, NULL);

		if (nError == SOCKET_ERROR)
		{
			int nError = WSAGetLastError();

			if (nError != WSA_IO_PENDING )
			{
				printf("PostIoMessage error socket=%d type=%d error=%d \n", hAccept->acceptSocket, IO_TYPE_READ, nError);
			}	
		}
	}

	return 0;
}