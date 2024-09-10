unsigned int __stdcall CxServerSocketTCP::WorkerThread( LPVOID lpParam )
{
	char * pRecvBuffer = NULL;
	ServerThreadContext* pContext = (ServerThreadContext*) lpParam;
	CxServerSocketTCP *pThis = (CxServerSocketTCP *)pContext->pThis;

	XTRACE( _T("Starting thread [%p]0x%x\r\n"), pContext, pContext->hThread );

	if ( !pContext->bListen )
		pThis->OnClientConnected( pContext, pContext->strClientIP, pContext->nClientPort );

	const int nRecvBufferSize = pThis->m_nMaxRecvBufferSize;
	if ( !(pRecvBuffer = (char *)xmalloc(nRecvBufferSize)) ) 
		return 0;

	int nEventIndex;
	WSANETWORKEVENTS hNetworkEvents;
	BOOL bWork = TRUE;
	while ( bWork ) 
	{
		nEventIndex = WSAWaitForMultipleEvents( 2, pContext->hNetEvent, FALSE, 500, FALSE );

		nEventIndex -= WSA_WAIT_EVENT_0;

		for ( int ix=nEventIndex ; ix<2 ; ix++ )
		{
			nEventIndex = WSAWaitForMultipleEvents( 1, &pContext->hNetEvent[ix], TRUE, 0, FALSE );

			if ( (nEventIndex == WSA_WAIT_FAILED ) ) continue;
			else if ( (nEventIndex==WSA_WAIT_TIMEOUT) )
			{
			}
			else
			{
				if ( ix == 1 )
				{
					WSAEnumNetworkEvents( pContext->hSocket, pContext->hNetEvent[1], &hNetworkEvents );
					if ( hNetworkEvents.lNetworkEvents & FD_READ )
					{
						if ( hNetworkEvents.iErrorCode[FD_READ_BIT] != 0 )
						{
							XTRACE( _T("Socket Read Error![%p]\r\n"), pContext );
							break;
						}
						int nRecvBytes = recv( pContext->hSocket, pRecvBuffer, nRecvBufferSize, 0 );

						if ( nRecvBytes > 0 )
						{
							//XTRACE( _T("%d bytes received!\r\n"), nRecvBytes );
							pThis->ProcessBuffer( pContext, pRecvBuffer, nRecvBytes );
						}
						else
						{
							char szBye[3] = { 0, };
							send( pContext->hSocket, szBye, 3, 0 );
							shutdown( pContext->hSocket, SD_BOTH );
							closesocket( pContext->hSocket );
							XTRACE( _T("Closed socket handle [%p]%x\r\n"), pContext, pContext->hSocket );
							
							pContext->hSocket = INVALID_SOCKET;

							if ( pContext->bListen )
								pThis->OnStopServer();
							else
							{
								pThis->OnClientDisconnected( pContext->strClientIP, pContext->nClientPort );
								bWork = FALSE;
							}

						}
					}

					if ( hNetworkEvents.lNetworkEvents & FD_ACCEPT )
					{
						if ( hNetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0 )
						{
							XTRACE( _T("[%p] Accept Error!\r\n"), pContext );
						}

						SOCKADDR_IN addrinClient;
						int nAddrSize = sizeof(SOCKADDR_IN);
						SOCKET hClientSocket = ::accept( pContext->hSocket, reinterpret_cast<struct sockaddr *>(&addrinClient), &nAddrSize );

						if ( hClientSocket == INVALID_SOCKET )
						{
							XTRACE( _T("[%p] accept() failed: %d\r\n"), pContext, WSAGetLastError() );
							bWork = FALSE;
							break;
						}

						int nRet;
						int nMaxSendBufferSize = MAX_SEND_BUF_SIZE;
						int nMaxRecvBufferSize = MAX_RECV_BUF_SIZE;
						nRet = ::setsockopt( hClientSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&nMaxSendBufferSize, sizeof(int) );
						nRet = ::setsockopt( hClientSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&nMaxRecvBufferSize, sizeof(int) );

						int nLen = sizeof(int);
						nRet = ::getsockopt( hClientSocket, SOL_SOCKET, SO_SNDBUF, (char*)&nMaxSendBufferSize, &nLen );
						nLen = sizeof(int);
						nRet = ::getsockopt( hClientSocket, SOL_SOCKET, SO_RCVBUF, (char*)&nMaxRecvBufferSize, &nLen );

						CxString strClientIP;
						int nPort;

						TCHAR szClientAddr[50]={0,};
						DWORD dwSize = sizeof(szClientAddr);
						SOCKADDR* pClientSockAddr = (SOCKADDR*)&addrinClient;
						CxString strClientSockAddr;
						if ( WSAAddressToString( pClientSockAddr, sizeof(SOCKADDR), NULL, szClientAddr, &dwSize) != SOCKET_ERROR )
						{
							strClientSockAddr = szClientAddr;
						}

						int nColonPos = strClientSockAddr.ReverseFind( _T(':') );
						strClientIP = strClientSockAddr.Left( nColonPos );
						strClientSockAddr.Delete( 0, nColonPos+1 );

						nPort = _tcstol(strClientSockAddr, NULL, 10);

						ServerThreadContext* pThreadContext = new ServerThreadContext;

						pThreadContext->hSocket = hClientSocket;
						pThreadContext->hThread = NULL;
						pThreadContext->pThis = pThis;
						pThreadContext->hNetEvent[0] = pThis->m_hCleanupEvent;
						pThreadContext->hNetEvent[1] = WSA_INVALID_EVENT;
						pThreadContext->IoBuffer.Create( pThis->GetIOBufferSize() );
						pThreadContext->IoBuffer.Clear();
						pThreadContext->bListen = FALSE;
						pThreadContext->strClientIP = strClientIP;
						pThreadContext->nClientPort = nPort;
						pThreadContext->dwUserData = 0;

						pThreadContext->hNetEvent[1] = WSACreateEvent();
						if ( WSAEventSelect( pThreadContext->hSocket, pThreadContext->hNetEvent[1], FD_READ|FD_CLOSE ) == SOCKET_ERROR )
						{
							XTRACE( _T("WSAEventSelect() error\r\n") );
							break;
						}
						
						unsigned int nThreadID = 0;
						pThreadContext->hThread = (HANDLE)::_beginthreadex( NULL, 0, WorkerThread, pThreadContext, 0, &nThreadID );
						
						if ( pThreadContext->hThread == NULL )
						{
							delete pThreadContext;
							break;
						}

						CloseHandle( pThreadContext->hThread );
					}

					if ( hNetworkEvents.lNetworkEvents & FD_CLOSE ) // ¿¬°á Á¾·á
					{
						if ( hNetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0 )	
						{
							XTRACE( _T("Abnormal closed...!!!\r\n") );
						}
						else
						{
							WSACloseEvent( pContext->hNetEvent[1] );
							pContext->hNetEvent[1] = WSA_INVALID_EVENT;
						}

						char szBye[3] = { 0, };
						send( pContext->hSocket, szBye, 3, 0 );
						shutdown( pContext->hSocket, SD_BOTH );
						closesocket( pContext->hSocket );
						XTRACE( _T("Closed socket handle [%p]%x\r\n"), pContext, pContext->hSocket );

						pContext->hSocket = INVALID_SOCKET;

						if ( pContext->bListen )
							pThis->OnStopServer();
						else
						{
							pThis->OnClientDisconnected( pContext->strClientIP, pContext->nClientPort );
							bWork = FALSE;
						}
						break;
					}
				}
				else
				{
					bWork = FALSE;
					break;
				}
			}
		}
	}

	if ( pRecvBuffer )
		xfree(pRecvBuffer);

	XTRACE( _T("Exit thread [%p]0x%x\r\n"), pContext, pContext->hThread );

	if ( !pContext->bListen )
	{
		delete pContext;
	}

	_endthreadex(0);

	return 0;
}