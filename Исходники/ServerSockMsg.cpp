DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
	DWORD					dwBytesTransferred = 0;

	CSessionInfo*			pSessionInfo = NULL;
	_LPTCOMPLETIONPORT		lpPerIoData = NULL;

	char					szPacket[DATA_BUFSIZE * 2];
	char					szMsg[32];
	char					*pszPos;

	while (TRUE)
	{
		if ( GetQueuedCompletionStatus( 
										(HANDLE)CompletionPortID, 
										&dwBytesTransferred, 
										(LPDWORD)&pSessionInfo, 										
										(LPOVERLAPPED *)&lpPerIoData, 
										INFINITE) == 0)
		{
			if (g_fTerminated)
				return 0;

			//失败关闭
			if (pSessionInfo)
			{
				szMsg[0] = '%';
				szMsg[1] = 'X';

				char *pszPos = ValToAnsiStr((int)pSessionInfo->sock, &szMsg[2]);

				*pszPos++	= '$';
				*pszPos		= '\0';

				SendExToServer(szMsg); 

				g_xSessionList.RemoveNodeByData(pSessionInfo);

				closesocket(pSessionInfo->sock);
				pSessionInfo->sock = INVALID_SOCKET;

				UpdateStatusBar(FALSE);

				//GlobalFree(pSessionInfo);
				CSessionInfo::ObjPool().reclaimObject(pSessionInfo);
			}

			continue;
		}

		if (g_fTerminated)
			return 0;

		if (dwBytesTransferred == 0)
		{
			szMsg[0] = '%';
			szMsg[1] = 'X';

			char *pszPos = ValToAnsiStr((int)pSessionInfo->sock, &szMsg[2]);

			*pszPos++	= '$';
			*pszPos		= '\0';

			SendExToServer(szMsg); 

			g_xSessionList.RemoveNodeByData(pSessionInfo);

			closesocket(pSessionInfo->sock);
			pSessionInfo->sock = INVALID_SOCKET;

			UpdateStatusBar(FALSE);

			//GlobalFree(pSessionInfo);
			CSessionInfo::ObjPool().reclaimObject(pSessionInfo);
			continue;
		}


		// ORZ:
		pSessionInfo->bufLen += dwBytesTransferred;

		while ( pSessionInfo->HasCompletionPacket() )
		{
			szPacket[0]	= '%';
			szPacket[1]	= 'A';
			pszPos		= ValToAnsiStr( (int) pSessionInfo->sock, &szPacket[2] );
			*pszPos++	= '/';
			pszPos		= pSessionInfo->ExtractPacket( pszPos );
			*pszPos++	= '$';
			*pszPos		= '\0';

			SendExToServer( szPacket );
		}

		// ORZ:
		if ( pSessionInfo->Recv() == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING )
		{
			InsertLogMsg(_TEXT("WSARecv() failed"));
			
			CloseSession(pSessionInfo->sock);
			continue;
		}
	}

	return 0;
}