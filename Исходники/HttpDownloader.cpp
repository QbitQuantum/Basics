HRESULT CHttpDownloader::ConnectToServer(_bstr_t &strBuffer)
{
	BOOL bResult;
	DWORD dwStatus;
	DWORD nTimeoutCounter;
	_bstr_t strMethod;
	_bstr_t strUrl = m_request.url;

	LPCTSTR szProxyName = NULL;
	if(m_ProxyType == INTERNET_OPEN_TYPE_PROXY)
		szProxyName = m_ProxyName;
	
//// InternetOpen \\\\	
	if(!m_hInternet)
		m_hInternet = InternetOpen(_T("McHttpDownloader"), m_ProxyType, szProxyName, NULL, INTERNET_FLAG_ASYNC);
	if(!m_hInternet)
	{
		strBuffer = _T("InternetOpen failed");
		return E_FAIL;
	}

	
	InternetSetStatusCallback(m_hInternet, (INTERNET_STATUS_CALLBACK)CallbackFunc);
//// InternetOpen ////	
	
	if(m_longAbort > 0)
		return E_ABORT;

//// InternetConnect \\\\	
	if(!m_hConnect)
	{
		m_hConnect = InternetConnect(m_hInternet, m_request.server, (short)m_request.port, NULL, NULL, INTERNET_SERVICE_HTTP, NULL, (DWORD)&m_context);
	}
	if(m_hConnect == NULL)
	{
		strBuffer = _T("InternetConnect failed");
		return INET_E_CANNOT_CONNECT;
	}
//// InternetConnect ////	
	
	nTimeoutCounter = 0;

NewConnect:

	strMethod = _T("GET");
	strBuffer = _T("");

//// OpenRequest \\\\	
	if(m_hRequest)
	{
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
	}
	
	if(m_longAbort > 0)
		return E_ABORT;

	DWORD dwFlags = 
		INTERNET_FLAG_KEEP_CONNECTION	|
		INTERNET_FLAG_NO_CACHE_WRITE	|
		INTERNET_FLAG_RELOAD			|
		INTERNET_FLAG_PRAGMA_NOCACHE	|
		INTERNET_FLAG_NO_UI			|
		INTERNET_FLAG_NO_COOKIES		|
		INTERNET_FLAG_IGNORE_CERT_CN_INVALID  |
		INTERNET_FLAG_NO_AUTO_REDIRECT  | 
		INTERNET_FLAG_HYPERLINK |
		(m_request.bUseSSL ?
							(INTERNET_FLAG_SECURE/*|
							INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS|
							INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP*/)
							:
							0);
		
	m_context.op = HTTP_DOWNLOADER_OP_OPEN_REQUEST;
	m_hRequest = HttpOpenRequest(m_hConnect, strMethod, strUrl, _T("HTTP/1.1"), NULL, NULL, dwFlags, (DWORD)&m_context);
	if(m_hRequest == NULL)
	{
		strBuffer = _T("HttpOpenRequest failed");
		return E_FAIL;
	}

	if(m_ProxyType == INTERNET_OPEN_TYPE_PROXY)
	{
		if(GetOptionInt(IDS_NETOPTIONS,IDS_USEFIREWALL,0))
		{
			CString fireWallUser =  GetOptionString(IDS_NETOPTIONS, IDS_FIREWALLUSER, _T(""));
			CString fireWallPass = GetOptionString(IDS_NETOPTIONS, IDS_FIREWALLPASS, _T(""));

			//////////////////////////////////////////////////////////////////////////

			int HeaderLen = ATL::ProxyAuthorizationStringGetRequiredLength(fireWallUser, fireWallPass);
			LPTSTR strHeader = new TCHAR[HeaderLen+1];
			ZeroMemory(strHeader,HeaderLen+1);

			HRESULT hr = ATL::ProxyAuthorizationString(fireWallUser, fireWallPass, strHeader, &HeaderLen);

			ASSERT(hr==S_OK);

			HttpAddRequestHeaders(m_hRequest, strHeader, HeaderLen, HTTP_ADDREQ_FLAG_ADD );

			delete []strHeader;
			//////////////////////////////////////////////////////////////////////////
		}
	}
	
//// OpenRequest ////	
	
NewRequest:

	if(m_longAbort > 0)
		return E_ABORT;

	m_context.op = HTTP_DOWNLOADER_OP_SEND_REQUEST;
	bResult = HttpSendRequest(m_hRequest, NULL , 0, (LPVOID)(BYTE*)(LPCTSTR)strBuffer, lstrlen(strBuffer));
	if(!bResult && 997 == GetLastError())		// Overlapped I/O operation is in progress.
		bResult = WaitForComplete(m_dwTimeout); // Resolve host name, connect, send request, receive response.
	if(!bResult)
	{
		DWORD dwErrCode = GetLastError();
//		ATLTRACE("Send Request error = %d \r\n",dwErrCode);
		
		if(dwErrCode == 6)		// The handle is invalid.
			goto NewConnect;
		
		if(dwErrCode == ERROR_INTERNET_TIMEOUT)	// timeout
		{
			if(++nTimeoutCounter < m_dwConnectRetryCount)
				goto NewConnect;
			else
			{
				strBuffer = _T("Timeout");
				return E_FAIL;//INET_E_CONNECTION_TIMEOUT;
			}
		}

		strBuffer = _T("SendRequest failed");
		return E_FAIL;
	}
	
	dwStatus = GetHttpStatus();

	if(dwStatus == 401 || dwStatus == 407) // Denied or Proxy asks password
	{
		if(ERROR_INTERNET_FORCE_RETRY == 
		   InternetErrorDlg(GetDesktopWindow(), m_hRequest,
				ERROR_INTERNET_INCORRECT_PASSWORD,
				FLAGS_ERROR_UI_FILTER_FOR_ERRORS | 
				FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS |
				FLAGS_ERROR_UI_FLAGS_GENERATE_DATA,
				NULL))
			{
				goto NewRequest;
			}
					
	}

	if(dwStatus != 200) // Not OK
	{		
		strBuffer = _T("SendRequest returned with error");
		return INET_E_CANNOT_CONNECT;
	} 

	return S_OK;
}