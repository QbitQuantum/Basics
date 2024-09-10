DWORD CTcpServerSocketHelper::Start(ITcpServerSocketHelper_Event *pEvent,
									DWORD dwListenPort/*=0*/,BOOL bReadData/*=TRUE*/)
{
	DWORD dwResult = -1;
	DWORD threadID = 0;

	m_pEvent = pEvent;
	m_dwListenPort = dwListenPort;

	if (!CreateTcpSocket(TRUE))
	{
		dwResult = 1;
		goto Exit0;
	}

	BOOL bOpt = TRUE;
	::setsockopt (m_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOpt, sizeof (bOpt));

	if (!Bind())
	{
		dwResult = 2;
		goto Exit0;
	}

	if (!Listen())
	{
		dwResult = 3;
		goto Exit0;
	}

	m_hTerminateAcceptThreadEvent = ::CreateEvent(NULL, TRUE, FALSE,NULL);
	if (!m_hTerminateAcceptThreadEvent)
	{
		dwResult = 4;
		goto Exit0;
	}

	m_hAcceptThreadHandle = (HANDLE)::CreateThread( NULL, 0, 
		(LPTHREAD_START_ROUTINE)_AcceptThreadProc, this, 0, &threadID );
	if (!m_hAcceptThreadHandle)
	{
		dwResult = 5;
		goto Exit0;
	}


	if (bReadData)
	{
		m_hTerminateReadDataThreadEvent = ::CreateEvent(NULL, TRUE, FALSE,NULL);
		if (!m_hTerminateReadDataThreadEvent)
		{
			dwResult = 6;
			goto Exit0;
		}

		m_hReadDataThreadHandle = (HANDLE)::CreateThread( NULL, 0, 
			(LPTHREAD_START_ROUTINE)_ReadDataThreadProc, this, 0, &threadID );
		if (!m_hReadDataThreadHandle)
		{
			goto Exit0;
		}
	}

	dwResult = 0;
Exit0:
	if (0 != dwResult)
	{
		Stop();
	}

	if (dwResult == 0)
	{
		return m_dwListenPort;
	}
	return (DWORD)-1;
}