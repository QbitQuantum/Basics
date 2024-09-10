void CEventThread::RunThread()
{
	Log(StrF(_T("Start of CEventThread::RunThread() Name: %s"), m_threadName));

	m_threadRunning = true;
	m_threadWasStarted = true;
	HANDLE *pHandleArray = new HANDLE[m_eventMap.size()];

	int indexPos = 0;
	for(EventMapType::iterator it = m_eventMap.begin(); it != m_eventMap.end(); it++)
	{
		pHandleArray[indexPos] = it->first;
		indexPos++;
	}

	SetEvent(m_hEvt);
	ResetEvent(m_hEvt);

	while(m_exitThread == false)
	{
		DWORD event = WaitForMultipleObjects((DWORD)m_eventMap.size(), pHandleArray, FALSE, m_waitTimeout);

		if(event == WAIT_FAILED)
		{
			LPVOID lpMsgBuf = NULL;
			DWORD dwErr = GetLastError();
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
							FORMAT_MESSAGE_FROM_SYSTEM |
							FORMAT_MESSAGE_IGNORE_INSERTS,
							NULL,
							dwErr,
							MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
							(LPTSTR) &lpMsgBuf,
							0,
							NULL);

			ASSERT(!lpMsgBuf);
			LocalFree(lpMsgBuf);
		}
		else if(event == WAIT_TIMEOUT)
		{
			OnTimeOut(m_param);
		}
		else
		{
			HANDLE firedHandle = pHandleArray[event - WAIT_OBJECT_0];
			int eventId = m_eventMap[firedHandle];
			if(eventId == EXIT_EVENT)
			{				
				break;
			}
			else
			{
				Log(StrF(_T("Start of CEventThread::RunThread() - OnEvent %d - Name %s"), eventId, m_threadName));
				OnEvent(eventId, m_param);
				Log(StrF(_T("End of CEventThread::RunThread() - OnEvent %d - Name: %d"), eventId, m_threadName));
			}
		}
	}

	UndoFireEvent(EXIT_EVENT);

	SetEvent(m_hEvt);

	Log(StrF(_T("End of CEventThread::RunThread() Name: %s"), m_threadName));

	m_threadRunning = false;
}