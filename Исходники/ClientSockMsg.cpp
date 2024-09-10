LPARAM OnClientSockMsg(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
		case FD_CONNECT:
		{
			DWORD dwThreadIDForMsg = 0;

			if (CheckSocketError(lParam))
			{
				dwThreadIDForMsg = 0;

				if (InitThread(ThreadFuncForMsg))
				{
					KillTimer(g_hMainWnd, _ID_TIMER_CONNECTSERVER);
				
					SetTimer(g_hMainWnd, _ID_TIMER_KEEPALIVE, 5000, (TIMERPROC)OnTimerProc);

					InsertLogMsg(IDS_CONNECT_LOGINSERVER);
					SendMessage(g_hStatusBar, SB_SETTEXT, MAKEWORD(1, 0), (LPARAM)_TEXT("Connected"));
				}
			}
			else
			{
				closesocket(g_csock);
				g_csock = INVALID_SOCKET;

				SetTimer(g_hMainWnd, _ID_TIMER_CONNECTSERVER, 10000, (TIMERPROC)OnTimerProc);
			}

			break;
		}
		case FD_CLOSE:
		{
			closesocket(g_csock);
			g_csock = INVALID_SOCKET;

			OnCommand(IDM_STOPSERVICE, 0);

			break;
		}
		case FD_READ:
		{
			int		nSocket = 0;
			char	*pszFirst = NULL, *pszEnd = NULL;

			UINT nRecv = 0;

			ioctlsocket((SOCKET)wParam, FIONREAD, (u_long *)&nRecv);

			if (nRecv)
			{
				char *pszPacket = new char[nRecv + 1];

				nRecv = recv((SOCKET)wParam, pszPacket, nRecv, 0);

				pszPacket[nRecv] = '\0';

				if (!(g_xMsgQueue.PushQ((BYTE *)pszPacket)))
					InsertLogMsg(_TEXT("[INFO] Not enough queue(g_xMsgQueue) buffer."));
			}

			break;
		}
	}

	return 0L;
}