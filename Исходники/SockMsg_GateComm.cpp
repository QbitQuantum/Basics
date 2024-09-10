DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
	DWORD				dwBytesTransferred;
	CGateInfo*			pGateInfo;
	LPOVERLAPPEDEX		lpOverlapped;
	_LPTMSGHEADER		pMsgHeader;
	char				completionPacket[DATA_BUFSIZE];

	while (TRUE)
	{
		GetQueuedCompletionStatus((HANDLE)CompletionPortID, &dwBytesTransferred, (LPDWORD)&pGateInfo, (LPOVERLAPPED *)&lpOverlapped, INFINITE);
		
		if (g_fTerminated) return 0L;

		if (dwBytesTransferred == 0)
		{
			if (g_xUserInfoList.GetCount())
			{
				PLISTNODE pListNode = g_xUserInfoList.GetHead();

				while (pListNode)
				{
					CUserInfo *pUserInfo = g_xUserInfoList.GetData(pListNode);

					if (pUserInfo->m_pGateInfo == pGateInfo)
					{
						pUserInfo->Lock();
						pUserInfo->m_bEmpty = true;
						pUserInfo->Unlock();
						
						// °íÃÄ¾ß µÊ
						if (pUserInfo->m_pxPlayerObject)
							pUserInfo->m_pxPlayerObject->m_pMap->RemoveObject(pUserInfo->m_pxPlayerObject->m_nCurrX,
																				pUserInfo->m_pxPlayerObject->m_nCurrY,
																				OS_MOVINGOBJECT,
																				pUserInfo->m_pxPlayerObject);
						
						pListNode = g_xUserInfoList.RemoveNode(pListNode);

						UpdateStatusBarUsers(FALSE);
					}
					else
						pListNode = g_xUserInfoList.GetNext(pListNode);
				}
			}

			closesocket(pGateInfo->m_sock);
			g_xGateList.RemoveNodeByData(pGateInfo);

			if (pGateInfo) delete pGateInfo;
			
			continue;
		}

		if (lpOverlapped->nOvFlag == OVERLAPPED_RECV)
		{
			static DWORD nLastTick = GetTickCount();
			static DWORD nBytes = 0;

			nBytes += dwBytesTransferred;

			if ( GetTickCount() - nLastTick >= 1000)
			{
				TCHAR buf[256];
				wsprintf( buf, _T("R: %d bytes/sec"), nBytes );

				nLastTick = GetTickCount();
				nBytes = 0;

				SendMessage(g_hStatusBar, SB_SETTEXT, MAKEWORD(3, 0), (LPARAM)buf);
			}	

			pGateInfo->OverlappedEx[0].bufLen += dwBytesTransferred;

			while ( pGateInfo->HasCompletionPacket() )
			{
				*(pGateInfo->ExtractPacket( completionPacket )) = '\0';

				pMsgHeader = (_LPTMSGHEADER) completionPacket;

				if ( pMsgHeader->nCode != 0xAA55AA55 )
					continue;

				switch ( pMsgHeader->wIdent )
				{
					case GM_OPEN:
					{
						pGateInfo->OpenNewUser( completionPacket );
						break;
					}
					case GM_CLOSE:
					{
						CUserInfo *pUserInfo = &g_xUserInfoArr[ pMsgHeader->wUserListIndex ];

						if (pUserInfo)
						{
							pUserInfo->m_btCurrentMode = USERMODE_LOGOFF;
							g_xLoginOutUserInfo.AddNewNode(pUserInfo);
						}

						break;
					}
					case GM_CHECKCLIENT:
					{
						pGateInfo->SendGateCheck();
						break;
					}
					case GM_RECEIVE_OK:
					{
						break;
					}
					case GM_DATA:
					{
						CUserInfo *pUserInfo = &g_xUserInfoArr[ pMsgHeader->wUserListIndex ];

						if ( !pUserInfo->IsEmpty() )
						{
							if ( pUserInfo->m_btCurrentMode == USERMODE_PLAYGAME)
							{
								if ( pMsgHeader->nSocket == pUserInfo->m_sock )
									pUserInfo->ProcessUserMessage(completionPacket + sizeof( _TMSGHEADER ) );
							}
							else
							{
								pUserInfo->Lock();
								pUserInfo->DoClientCertification( completionPacket + sizeof( _TMSGHEADER ) + sizeof(_TDEFAULTMESSAGE) );
								pUserInfo->Unlock();
							}
						}

						break;
					}
				} // switch
			} // while
	
			if ( pGateInfo->Recv() == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING )
				InsertLogMsg( _T("WSARecv() failed") );
		} // if (OVERLAPPED_RECV)
		else if (lpOverlapped->nOvFlag == OVERLAPPED_SEND)
		{
			static DWORD nLastTick = GetTickCount();
			static DWORD nBytes = 0;

			nBytes += dwBytesTransferred;

			if ( GetTickCount() - nLastTick >= 1000)
			{
				TCHAR buf[256];
				wsprintf( buf, _T("S: %d bytes/sec"), nBytes );

				nLastTick = GetTickCount();
				nBytes = 0;

				SendMessage(g_hStatusBar, SB_SETTEXT, MAKEWORD(4, 0), (LPARAM)buf);
			}	
/*			fprintf( fp, "sended\r\n" );

			pGateInfo->m_fDoSending = FALSE;
			
			if ( pGateInfo->Send( NULL ) == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING )
				InsertLogMsg( _T("WSASend() failed") );	*/
		}
	}

	return 0;
}