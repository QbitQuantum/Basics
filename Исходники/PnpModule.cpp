DWORD WINAPI 
PnpModuleThreadProc(
					LPVOID lpParameter   // thread data
					)
{
	int						iResult;
	CPnpModule				*pRC;
	WSAOVERLAPPED			overlapped;
	WSABUF					buffer[1];
	DWORD					dwFlag;
	DWORD					dwRecvDataLen;
	SOCKADDR_LPX			PeerAddr;
	INT						iFromLen;
	BOOL					bFinish;
	HANDLE					hEvents[2];
	PNP_MESSAGE				message;

	DebugPrint(2, (TEXT("[NetdiskTest]PnpModuleThread: PnpModule Thread Started.\n")));

	pRC = (CPnpModule *) lpParameter;

	// Server Stop Event.
	hEvents[0] = hServerStopEvent;

	// Overlapped event
	//
	hEvents[1] = WSACreateEvent();
	memset(&overlapped, 0, sizeof(WSAOVERLAPPED));
	overlapped.hEvent = hEvents[1];

	buffer[0].len = sizeof(message);
	buffer[0].buf = (PCHAR)&message;
	 
	
	bFinish = FALSE;

	do {
		DWORD	dwResult;

		// Flag
		dwFlag = 0;
	
		WSAResetEvent(hEvents[1]);

		iFromLen = sizeof(PeerAddr);

		iResult = WSARecvFrom(
			pRC->ListenSocket,
			buffer,
			1,
			&dwRecvDataLen,
			&dwFlag,
			(struct sockaddr *)&PeerAddr,
			&iFromLen,
			&overlapped,
			NULL
			);
		if(iResult != SOCKET_ERROR) {
			DebugPrint(4, ("[NetDiskTest]PnpModuleThreadProc: no Error when Recv.\n"));
			continue;
		}

		if((iResult = WSAGetLastError()) != WSA_IO_PENDING) {
			DebugPrint(1, ("[NetDiskTest]PnpModuleThreadProc: Error when Recv. %d\n", iResult));

			bFinish = TRUE;

			continue;
		}

		// Wait
		dwResult = WaitForMultipleObjects(
			2,
			hEvents,
			FALSE,
			3000 //INFINITE
			);
		switch(dwResult) {
		case WAIT_TIMEOUT:
			TRACE("\nWAIT_TIMEOUT\n");
			SetEvent(hUpdateEvent);
			break;
		case WAIT_OBJECT_0:
			{
				TRACE("\nWAIT_OBJECT_0\n");
				bFinish = TRUE;
				DebugPrint(1, ("[NetDiskTest]PnpModuleThreadProc: Recv Stop Event.\n"));
			}
			break;
		case WAIT_OBJECT_0 + 1:
			{
				TRACE("\nWAIT_OBJECT_0+1\n");
				BOOL		bResult;

				bResult = WSAGetOverlappedResult(
					pRC->ListenSocket,
					&overlapped,
					&dwRecvDataLen,
					TRUE,
					&dwFlag
					);

				// Check Size.
				if(dwRecvDataLen != sizeof(message)) {
					DebugPrint(1, ("[NetDiskTest]PnpModuleThreadProc: Recv Packet size = %d. Ignore...\n", dwRecvDataLen));
					break;
				}

				// Is Valid?
				if (message.ucType != 0 || 
					(
						message.ucVersion != 0 &&
						message.ucVersion != 1 &&
						message.ucVersion != 2
					)
				)
				{
					DebugPrint(1, ("[NetDiskTest]PnpModuleThreadProc: Bad Packet 0x%x. 0x%x. Ignore...\n", message.ucType, message.ucVersion));
					break;
				}
				
			}
//			DebugPrint(4, ("[NetDiskTest]PnpModuleThreadProc: %.2X%.2X%.2X\n",
//				PeerAddr.LpxAddress.Node[0], PeerAddr.LpxAddress.Node[1], PeerAddr.LpxAddress.Node[2]));
			memcpy((void *) ucCurrentNetdisk, (void *) PeerAddr.LpxAddress.Node, 6);
			ucVersion = message.ucVersion;
			bNewNetdiskArrived = TRUE;
			SetEvent(hUpdateEvent);
			break;

		default:
			break;
		}

	} while(bFinish != TRUE);

	CloseHandle(hEvents[1]);

	ExitThread(0);

	return 0;
}