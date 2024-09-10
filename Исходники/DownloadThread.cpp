int CDownloadThread::TransferDataPost(BOOL bWithFile)
{
	if(!bWithFile) // 不是用文件下载数据
	{
		ATLASSERT(NULL != m_pRead && m_nLength > 0 && NULL != m_pReadLength);
		if (NULL == m_pRead || m_nLength <= 0 || NULL == m_pReadLength)
			return ERR_PARAM;
	}

	CUrlCrack url;
	if (!url.Crack(m_strDownURl.c_str()))
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_URLCRACKERROR,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的url = %s Crack 异常！", m_strDownURl.c_str()));
		return ERR_URLCRACKERROR;
	}

	NEED_STOP;

	m_hInetSession = ::InternetOpen(MONEYHUB_USERAGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (m_hInetSession == NULL)
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTOPEN,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的InternetOpen异常！LastErrCode = %d", GetLastError()));
		//OutputDebugString(strErr);
		return ERR_INTOPEN;
	}

	NEED_STOP;
	DWORD dwTimeOut = 60000;
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, &dwTimeOut, sizeof(DWORD), 0);
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_CONTROL_SEND_TIMEOUT, &dwTimeOut, sizeof(DWORD), 0);
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_SEND_TIMEOUT, &dwTimeOut, sizeof(DWORD), 0);
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwTimeOut, sizeof(DWORD), 0);
	InternetSetOptionEx(m_hInetSession, INTERNET_OPTION_CONNECT_TIMEOUT, &dwTimeOut, sizeof(DWORD), 0);

	m_hInetConnection = ::InternetConnect(m_hInetSession, url.GetHostName(), url.GetPort(), NULL, NULL, INTERNET_SERVICE_HTTP, 0, (DWORD)this);
	if (m_hInetConnection == NULL)
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTCONNECT,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的InternetConnect异常！LastErrCode = %d", GetLastError()));
		//OutputDebugString(strErr);
		CloseHandles();
		return ERR_INTCONNECT;
	}

	LPCTSTR ppszAcceptTypes[2];
	ppszAcceptTypes[0] = _T("*/*"); 
	ppszAcceptTypes[1] = NULL;

	DWORD dwFlags = 0;
	if(INTERNET_DEFAULT_HTTPS_PORT == url.GetPort())
	{
		dwFlags = INTERNET_FLAG_SECURE;
		
	}
	else if(INTERNET_DEFAULT_HTTP_PORT == url.GetPort())
	{
		dwFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION ;
	}

	m_hInetFile = HttpOpenRequest(m_hInetConnection, _T("POST"), url.GetPath(), NULL, NULL, ppszAcceptTypes, dwFlags, (DWORD)this);
	if (m_hInetFile == NULL)
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTOPENREQ,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的HttpOpenRequest异常！LastErrCode = %d", GetLastError()));
		
		CloseHandles();
		return ERR_INTOPENREQ;
	}

	if(INTERNET_DEFAULT_HTTPS_PORT == url.GetPort())
	{
		DWORD dwOptionFlags;
		DWORD dwBuffLen = sizeof(dwOptionFlags);

		InternetQueryOption (m_hInetFile, INTERNET_OPTION_SECURITY_FLAGS,
			(LPVOID)&dwOptionFlags, &dwBuffLen);

		dwOptionFlags |= (SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_CN_INVALID);
		InternetSetOption (m_hInetFile, INTERNET_OPTION_SECURITY_FLAGS,
			&dwOptionFlags, sizeof (dwOptionFlags) );

	}

	NEED_STOP;
	
	HttpAddRequestHeaders(m_hInetFile, _T("Content-Type: application/x-www-form-urlencoded\r\n"), -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	HttpAddRequestHeaders(m_hInetFile, _T("User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET CLR 1.1.4322; .NET4.0C; .NET4.0E)\r\n"), -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE); 
	HttpAddRequestHeaders(m_hInetFile, _T("Accept-Language: zh-CN"), -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE); 

	TCHAR szHeaders[1024];
	
	_stprintf_s(szHeaders, _countof(szHeaders), _T("Moneyhubuid: %s\r\n"), m_strHWID.c_str());
	HttpAddRequestHeaders(m_hInetFile, szHeaders, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE); 

	BOOL bSend = ::HttpSendRequest(m_hInetFile, NULL, 0, (LPVOID)m_strSendData.c_str (), m_dwPostDataLength);
	if (!bSend)
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTSENDREQ,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的HttpSendRequest异常！LastErrCode = %d", GetLastError()));
		//OutputDebugString(strErr);
		CloseHandles();
		return ERR_INTSENDREQ;
	}

	NEED_STOP;
	
	TCHAR szStatusCode[32];
	DWORD dwInfoSize = sizeof(szStatusCode);
	if (!HttpQueryInfo(m_hInetFile, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwInfoSize, NULL))
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTQUREYINFO,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的HttpQueryInfo异常！LastErrCode = %d", GetLastError()));
		//OutputDebugString(strErr);
		CloseHandles();
		return ERR_INTQUREYINFO;
	}
	else
	{
		long nStatusCode = _ttol(szStatusCode);
		if (nStatusCode != HTTP_STATUS_OK)
		{
			CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTFILENOTFOUND,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的HttpQueryInfo异常！LastErrCode = %d", GetLastError()));
			//OutputDebugString(strErr);
			
			CloseHandles();
			return ERR_INTFILENOTFOUND;
		}
	}

	NEED_STOP;
	
	if (bWithFile)
	{
		m_hSaveFile = CreateFile(m_strSaveFile.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (m_hSaveFile == INVALID_HANDLE_VALUE)
		{
			CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_CREATEFILE,
				CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的CreateFile异常！LastErrCode = %d", GetLastError()));
			//OutputDebugString(strErr);
			CloseHandles();
			return ERR_CREATEFILE;
		}
	}
	
	NEED_STOP;

	LPBYTE lpszData = NULL;
	DWORD dwSize = 0;
	
	while (true)   
	{   
		NEED_STOP;

		if (!InternetQueryDataAvailable(m_hInetFile, &dwSize, 0, 0))
		{
			CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTQUERYDATAAVAILABLE,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的InternetQueryDataAvailable异常！LastErrCode = %d", GetLastError()));
			//OutputDebugString(strErr);
			// ERR_INTQUERYDATAAVAILABLE
			break;
		}

		
		lpszData = new BYTE[dwSize];
		

		DWORD dwDownloaded = 0;

		if (!InternetReadFile(m_hInetFile, (LPVOID)lpszData, dwSize, &dwDownloaded))   
		{   
			CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_INTREADFILE,
			CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的InternetReadFile异常！LastErrCode = %d", GetLastError()));
			//OutputDebugString(strErr);
			delete []lpszData;
			CloseHandles();
			return ERR_INTREADFILE;  
		}   
		else   
		{   
			if (bWithFile) // 用文件
			{
				DWORD dwBytesWritten = 0;
				if (!WriteFile(m_hSaveFile, lpszData, dwDownloaded, &dwBytesWritten, NULL))
				{
					CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_WRITEFILE,
						CRecordProgram::GetInstance()->GetRecordInfo(L"TransferDataPost的WriteFile异常！LastErrCode = %d", GetLastError()));
					delete []lpszData;
					CloseHandles();
					return ERR_WRITEFILE;
				}
			}
			else
			{
				if (m_nLength < (*m_pReadLength) + dwDownloaded)
				{
					delete []lpszData;
					CloseHandles();
					return ERR_WRITEFILE;	
				}

				memcpy(m_pRead + (*m_pReadLength), lpszData, dwDownloaded);
				*m_pReadLength += dwDownloaded;
			}

			delete []lpszData;   

			if (dwDownloaded == 0)   
				break;   
		}   
	}

	CloseHandles();
	
	return ERR_SUCCESS;
}