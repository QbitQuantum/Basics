DWORD DownloadCurrency(DWORD dwSendTimeOut, wstring& tUrl, string& info)
{
	CUrlCrack url;
	if (!url.Crack(tUrl.c_str()))
		return 1000;

	HINTERNET		m_hInetSession; // 会话句柄
	HINTERNET		m_hInetConnection; // 连接句柄
	HINTERNET		m_hInetFile; //
	
	m_hInetSession = ::InternetOpen(L"Moneyhub4.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (m_hInetSession == NULL)
	{
		return 3000;
	}
	
	DWORD dwTimeOut = 60000;//初始化为5s
	//DWORD dwSendTimeOut = 5000;
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_SEND_TIMEOUT, &dwSendTimeOut, sizeof(DWORD), 0);
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwSendTimeOut, sizeof(DWORD), 0);
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_CONNECT_TIMEOUT, &dwTimeOut, sizeof(DWORD), 0);
	

	m_hInetConnection = ::InternetConnect(m_hInetSession, url.GetHostName(), url.GetPort(), NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if (m_hInetConnection == NULL)
	{
		InternetCloseHandle(m_hInetSession);

		return 3001;
	}

	LPCTSTR ppszAcceptTypes[2];
	ppszAcceptTypes[0] = _T("*/*"); 
	ppszAcceptTypes[1] = NULL;
	
	USES_CONVERSION;
	m_hInetFile = HttpOpenRequestW(m_hInetConnection, _T("GET"), url.GetPath(), NULL, NULL, ppszAcceptTypes, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);
	if (m_hInetFile == NULL)
	{
		InternetCloseHandle(m_hInetConnection);
		InternetCloseHandle(m_hInetSession);
		return 3002;
	}	

	BOOL bSend = ::HttpSendRequestW(m_hInetFile, NULL, 0, NULL, 0);
	if (!bSend)
	{
		int Error = GetLastError();
		InternetCloseHandle(m_hInetConnection);
		InternetCloseHandle(m_hInetFile);
		InternetCloseHandle(m_hInetSession);
		return Error;
	}
	TCHAR szStatusCode[32];
	DWORD dwInfoSize = sizeof(szStatusCode);
	if (!HttpQueryInfo(m_hInetFile, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwInfoSize, NULL))
	{
		InternetCloseHandle(m_hInetConnection);
		InternetCloseHandle(m_hInetFile);
		InternetCloseHandle(m_hInetSession);
		return 3004;
	}
	else
	{
		long nStatusCode = _ttol(szStatusCode);
		if (nStatusCode != HTTP_STATUS_PARTIAL_CONTENT && nStatusCode != HTTP_STATUS_OK)
		{
			InternetCloseHandle(m_hInetConnection);
			InternetCloseHandle(m_hInetFile);
			InternetCloseHandle(m_hInetSession);
			return 3005;
		}
	}

	DWORD dwBytesRead = 0;
	char szReadBuf[1024];
	DWORD dwBytesToRead = sizeof(szReadBuf);
	bool sucess = true;

	do
	{
		memset(szReadBuf, 0 , 1024);
		if (!::InternetReadFile(m_hInetFile, szReadBuf, dwBytesToRead, &dwBytesRead))
		{
			sucess = false;
			break;
		}
		else if (dwBytesRead)
		{
			info += szReadBuf;
		}
	}while (dwBytesRead);

	InternetCloseHandle(m_hInetConnection);
	InternetCloseHandle(m_hInetFile);
	InternetCloseHandle(m_hInetSession);
	if(sucess != true)
		return 3007;
	return 0;
}