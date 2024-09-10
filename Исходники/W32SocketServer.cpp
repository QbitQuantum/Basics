unsigned WINAPI CW32SocketServer::thrdClientServer(LPVOID pParam)
{
	CSocketPool* pPool = (CSocketPool*) pParam;
	CW32SocketServer* pThis = pPool->GetOwner();
	DWORD dwWaitResult = 0;
	int nIndex = 0;
	HANDLE arrHandles[WSA_MAXIMUM_WAIT_EVENTS];
	stClientSocket* arrSockets[WSA_MAXIMUM_WAIT_EVENTS];
	stClientSocket* pSocket = NULL;
	WSANETWORKEVENTS events;

	while ( pThis->m_bRun && pPool->GetSocketCount() )
	{
		// create the handle array
		ZeroMemory(arrHandles, sizeof(arrHandles));
		ZeroMemory(arrSockets, sizeof(arrSockets));
		nIndex = 0;
		for ( int i = 0; i < WSA_MAXIMUM_WAIT_EVENTS; i++ )
		{
			if ( (pSocket = pPool->GetSocket(i)) && !pSocket->bAvailable )
			{
				arrSockets[nIndex] = pSocket;
				arrHandles[nIndex++] = pSocket->hEvent;
			}
		}

		// wait for an event to occur
		dwWaitResult = WSAWaitForMultipleEvents( (DWORD)nIndex, arrHandles, FALSE, 1000, FALSE );
		if ( dwWaitResult != WSA_WAIT_FAILED && (dwWaitResult >= WSA_WAIT_EVENT_0) && (dwWaitResult <= (WSA_WAIT_EVENT_0 + nIndex -1)) )
		{
			nIndex = dwWaitResult - WSA_WAIT_EVENT_0;
			if ( (pSocket = arrSockets[nIndex]) )
			{
				WSAEnumNetworkEvents( pSocket->s, pSocket->hEvent, &events );
				if ( events.lNetworkEvents & FD_READ )
				{
					// data has arrived
					pThis->OnDataReceived(pSocket);
				}
				if ( events.lNetworkEvents & FD_WRITE )
				{
					// data sent
				}
				if ( events.lNetworkEvents & FD_CLOSE )
				{
					// socket closed
					pThis->OnClientSocketClosed(pSocket, (DWORD)events.iErrorCode[FD_CLOSE_BIT]);
				}				
			}
		}
	}

	delete pPool;

	return 0;
}