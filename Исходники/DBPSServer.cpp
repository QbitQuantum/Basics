DWORD CDBPSServer::StartServer(DWORD dwPort, DWORD dwNumberOfConnection)
{
	/*
		Server have to be give a port for itself from Server Administrator
	*/
	DWORD dwRet = E_RET_SUCCESS;
	dwRet = InitServerSock(dwPort);
	if (dwRet != E_RET_SUCCESS) {
		ErrorLog("Fail to initailize Server Sock");
		return E_RET_FAIL;
	}

	/*
		Create Completion Port for opertation IOCP.
		the variable 0 mean that IOCP set value itself.
	*/
	dwRet = InitIOCompletionPort(0);
	if (dwRet != E_RET_SUCCESS) {
		ErrorLog("Fail to initailize Server Sock");
		return E_RET_FAIL;
	}

	/*
		Make worker threads for operating IOCP
	*/
	dwRet = InitWorkerThread();
	if (dwRet != E_RET_SUCCESS) {
		ErrorLog("Fail to initailize Server Sock");
		return E_RET_FAIL;
	}

	dwRet = InitDBCQueue(dwNumberOfConnection);
	if (dwRet != E_RET_SUCCESS) {
		ErrorLog("Fail to initailize DB Connection Queue");
		return E_RET_FAIL;
	}


	dwRet = InitServerValue(dwPort);
	if (dwRet != E_RET_SUCCESS) {
		ErrorLog("Fail to configure server value");
		return E_RET_FAIL;
	}

	m_bStartServer = TRUE;
	while (m_bStartServer)
	{
		try
		{
			ST_CLIENT_SOCKET stClientSocket;
			dwRet = AcceptServer(stClientSocket);
			if (dwRet != E_RET_SUCCESS) {
				continue;
			}

			dwRet = CompleteReadFromClient(stClientSocket);
			if (dwRet != E_RET_SUCCESS) {
				continue;
			}
		}
		catch (std::exception &e)
		{
			/*
				Abnormally Exception
			*/
			ErrorLog("%s", e.what());
			DestoryDBCQueue(dwNumberOfConnection);
			return dwRet;
		}
	}

	/*
		All Thread is waiting for stopping their operation
	*/
	WaitForMultipleObjects(m_stServerWorkerThreads.dwNumberOfThread, m_stServerWorkerThreads.phWorkerThread, TRUE, INFINITE);
	DestoryDBCQueue(dwNumberOfConnection);
	
	return dwRet;
}