BOOL CSocket::PumpMessages(UINT uStopFlag)
{
	// The same socket better not be blocking in more than one place.
	ASSERT(m_pbBlocking == NULL);

	AFX_THREAD_STATE* pThreadState = AfxGetThreadState();

	ASSERT(pThreadState->m_hSocketWindow != NULL);

	BOOL bBlocking = TRUE;
	m_pbBlocking = &bBlocking;
	CWinThread* pThread = AfxGetThread();

	UINT nTimerID = ::SetTimer(NULL, 0xff00, m_nTimeOut, NULL);

	if (nTimerID == 0)
		AfxThrowResourceException();

	while (bBlocking)
	{
		TRY
		{
			MSG msg;
			if (::PeekMessage(&msg, pThreadState->m_hSocketWindow,
				WM_SOCKET_NOTIFY, WM_SOCKET_DEAD, PM_REMOVE))
			{
				if (msg.message == WM_SOCKET_NOTIFY && (SOCKET)msg.wParam == m_hSocket)
				{
					if (WSAGETSELECTEVENT(msg.lParam) == FD_CLOSE)
					{
						break;
					}
					if (WSAGETSELECTEVENT(msg.lParam) == uStopFlag)
					{
						if (uStopFlag == FD_CONNECT)
							m_nConnectError = WSAGETSELECTERROR(msg.lParam);
						break;
					}
				}
				if (msg.wParam != 0 || msg.lParam != 0)
					CSocket::AuxQueueAdd(msg.message, msg.wParam, msg.lParam);
			}
			else if (::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE))
			{
				if (msg.wParam == nTimerID)
				{
					::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_REMOVE);
					break;
				}
			}
			else if (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) &&
				OnMessagePending())
			{
				// allow user-interface updates
				pThread->OnIdle(-1);
			}
			else
			{
				// no work to do -- allow CPU to sleep
				WaitMessage();
			}
		}
		CATCH_ALL(e)
		{
			TRACE0("Error: caught exception in PumpMessage - continuing.\n");
			DELETE_EXCEPTION(e);
		}
		END_CATCH_ALL
	}

	::KillTimer(NULL, nTimerID);

	if (!bBlocking)
	{
		WSASetLastError(WSAEINTR);
		return FALSE;
	}
	m_pbBlocking = NULL;

	::PostMessage(pThreadState->m_hSocketWindow,WM_SOCKET_NOTIFY,0,0);

 	return TRUE;
}