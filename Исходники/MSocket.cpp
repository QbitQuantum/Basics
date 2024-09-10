UINT CMSocket::ThreadReadProc(LPVOID pParam)
{
	CMSocket* pSocket = (CMSocket*) pParam;
	DWORD dwRecvd = SOCKET_BUFFER_SIZE;
	int ir, iCurrentBuffer = 0;
	CMSocket::SocketData* pData;

	ResetEvent(pSocket->m_hSocketThreadComplete);
	pSocket->m_iWriteOffset = 0;
	pSocket->m_hSocketEvent = WSACreateEvent();
	if (SOCKET_ERROR != WSAEventSelect(pSocket->m_socket,pSocket->m_hSocketEvent,FD_READ | FD_CLOSE))
	{
		WSANETWORKEVENTS wne;
		while (!pSocket->m_bDone)
		{
			dwRecvd = SOCKET_BUFFER_SIZE;
			WaitForSingleObject(pSocket->m_hSocketEvent,INFINITE);
			WSAEnumNetworkEvents(pSocket->m_socket,pSocket->m_hSocketEvent,&wne);
			switch(wne.lNetworkEvents)
			{
			case FD_READ:
				if (0 == wne.iErrorCode[FD_READ_BIT])
				{
					pData = new CMSocket::SocketData();
					ir = pSocket->Receive(pData->Buffer,SOCKET_BUFFER_SIZE);
					if (SOCKET_ERROR == ir)
					{
						int er = WSAGetLastError();
						delete pData;
						ASSERT(0);
					}
					else
					{
						EnterCriticalSection(&pSocket->m_csIO);
						pData->iBufferSize = ir;
						pSocket->m_deqSocketData.push_back(pData);
						LeaveCriticalSection(&pSocket->m_csIO);
					}
				}
				break;
			case FD_CLOSE:
				pSocket->m_bDone = true;
				break;
			default:
				break;
			}
		}
	}
	SetEvent(pSocket->m_hSocketThreadComplete);
	return 0;
}