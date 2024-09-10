DWORD WINAPI WorkerThread(LPVOID CompletionPortID)
{

	HANDLE                  CompletionPort=(HANDLE)CompletionPortID;
	DWORD                   dwBytesTransferred;
	SOCKET                  sClient;
	LPPER_IO_OPERATION_DATA lpPerIOData = NULL;

	while (TRUE)
	{

		GetQueuedCompletionStatus(
			CompletionPort,
			&dwBytesTransferred,
			 (ULONG_PTR *)&sClient,
			(LPOVERLAPPED *)&lpPerIOData,
			INFINITE
		);

		if (dwBytesTransferred == 0xFFFFFFFF)
		{
			return 0;
		}

		if (lpPerIOData->OperationType == RECV_POSTED)
		{
			if (dwBytesTransferred == 0)
			{
				// Connection was closed by client
				printf("client close\r\n");
				closesocket(sClient);
				HeapFree(GetProcessHeap(), 0, lpPerIOData);
			}
			else
			{
				printf("%s\r\n",lpPerIOData->szMessage);

			lpPerIOData->szMessage[dwBytesTransferred] = '\0';
			send(sClient, lpPerIOData->szMessage, dwBytesTransferred, 0);

			// Launch another asynchronous operation for sClient
			memset(lpPerIOData, 0, sizeof(PER_IO_OPERATION_DATA));

			lpPerIOData->Buffer.len = MSGSIZE;
			lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
			lpPerIOData->OperationType = RECV_POSTED;

			WSARecv(
				sClient,
				&lpPerIOData->Buffer,
				1,
				&lpPerIOData->NumberOfBytesRecvd,
				&lpPerIOData->Flags,
				&lpPerIOData->overlap,
				NULL
			);

			}

		}

	}

	return 0;

}