DWORD WINAPI CEgTcpDriver::Start(IEgTcpDriverEvents * pEvents, 
								 const COINIT ThreadingModel,
								 const unsigned short usServerPort)
{
	if (pEvents == NULL)
		return ERROR_INVALID_PARAMETER;

	CAutoLock lock(&m_InitLock);

	if (m_bInited)
		return ERROR_ALREADY_INITIALIZED;

	m_ThreadingModel = ThreadingModel;

	m_pEvents = pEvents;

	m_usServerPort = usServerPort;

	for(int i = 0; i < WSATOTAL_EVENTS; i++)
	{
		m_hWsaEvents[i] = WSACreateEvent();
		if (WSA_INVALID_EVENT == m_hWsaEvents[i])
			return WSAGetLastError();
	}

	m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (NULL == m_hIocp) 
		return GetLastError();

	SYSTEM_INFO	systemInfo;
    GetSystemInfo(&systemInfo);
    m_dwThreadCount = 1/*systemInfo.dwNumberOfProcessors * 2*/;


	// Create worker threads to service the overlapped I/O requests.  The decision
    // to create 1 worker threads per CPU in the system is a heuristic.  Also,
    // note that thread handles are closed right away, because we will not need them
    // and the worker threads will continue to execute.
    unsigned long  hThread;
    UINT   dwThreadId;

	for (DWORD dwCPU=0; dwCPU < m_dwThreadCount; dwCPU++) 
    {
		hThread = _beginthreadex(NULL, 0, WorkerThread, this, 0, &dwThreadId);
		if (hThread == -1) 
			return GetLastError();

		m_hThreads.push_back((HANDLE)hThread);
	}

	hThread = _beginthreadex(NULL, 0, WsaEventThread, this, 0, &dwThreadId);

	if (hThread == -1) 
			return GetLastError();

	m_hWSAEventThread = (HANDLE)hThread;

	if (m_usServerPort != CLIENT_ONLY)
	{
		DWORD dwErr = CreateListenSocket();
		if (dwErr != 0)
			return dwErr;

		dwErr = CreateAcceptSocket(TRUE);
		if (dwErr != 0)
			return dwErr;
	}
           
	m_bInited = TRUE;

	return 0;
}