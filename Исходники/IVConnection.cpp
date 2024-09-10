void CIVConnection::GetHTTPData(LPCTSTR szQuery, CString &rstr)
{
	TRACE (_T("HTTP Request: %s\n"), szQuery);

	DWORD dwServiceType = 0;
	CString strServer;
	CString strObject;		
	INTERNET_PORT nPort=0;
	bool    bFirst = false;
	
	HINTERNET hFile = NULL;

	bool bFailed = false;
	
	try
	{
		while(1)
		{
			if(!m_strHeader.GetLength())
				hFile = ::InternetOpenUrl (m_hSession, szQuery, NULL, 0,  INTERNET_FLAG_DONT_CACHE, 0 );
			else
				hFile = ::InternetOpenUrl (m_hSession, szQuery, (LPCSTR)m_strHeader, m_strHeader.GetLength(),  INTERNET_FLAG_DONT_CACHE, 0 );

			if (! hFile)
				AfxThrowInternetException(0);

			rstr.Empty();

			const int nSizeBuffer = 1024;
			BYTE pBuffer [nSizeBuffer];
			DWORD dwTotalRead = 0;

			while (true)
			{
				DWORD dwRead = 0;
				BOOL bResult = ::InternetReadFile (hFile, pBuffer, nSizeBuffer, &dwRead);
				if (! bResult)
					AfxThrowInternetException(0);
				
				if (dwRead ==0)
					break;

				DWORD dwOldTotal = dwTotalRead;
				dwTotalRead += dwRead;		

				LPTSTR szTarget = rstr.GetBuffer(dwTotalRead);
				szTarget += dwOldTotal;
	#ifndef _UNICODE				
				memcpy (szTarget, pBuffer, dwRead);
	#else
				MultiByteToWideChar (CP_ACP, 0, (LPCSTR) pBuffer, dwRead, szTarget, dwRead);			
	#endif //_UNICODE
				rstr.ReleaseBuffer(dwTotalRead);
			}

			if ( CheckErrorMessage(rstr) ) 
				bFailed = true;
			else
			{
				DWORD dwStatus = QueryInfoStatusCode(hFile);
				if(HTTP_STATUS_PROXY_AUTH_REQ == dwStatus && !bFirst && m_opts.m_iProxyAuth)
				{
					bFirst = true;

					CString strIn;
					CString strOut;
					unsigned nLen = 0;
					
					strIn.Format(_T("%s:%s"), (LPCTSTR)m_opts.m_strProxyLogin, (LPCTSTR)m_opts.m_strProxyPassword);
					encode64((LPCSTR)strIn, strIn.GetLength(), strOut.GetBufferSetLength(200), 190, &nLen);
					strOut.ReleaseBuffer();
					m_strHeader.Format(_T("Proxy-Authorization: Basic %s\r\n"),(LPCTSTR)strOut);
					InternetCloseHandle(hFile);
					continue;

				}
				if(!m_opts.m_iProxyAuth)
					m_strHeader = _T("");

				if ( HttpError (hFile, dwStatus) )
					bFailed = true;
			}
			break;
		}
	}
	catch (CInternetException * e )
	{
		bFailed = true;
		
		if ( e->m_dwError  != ERROR_INTERNET_OPERATION_CANCELLED  &&
			e->m_dwError  != ERROR_INVALID_HANDLE )
		{
			TCHAR szError [512] = _T("") ;
			e->GetErrorMessage(szError, sizeof (szError) / sizeof (TCHAR) );
			SetError (GetCommonIVError(szError));
		}
		else
			TRACE (_T("CIVConnection - canceled\n"));

		e->Delete();
	}

	TRACE (_T("End of HTTP request\n"));

	if (hFile)
		::InternetCloseHandle (hFile);

	if (bFailed)
		AfxThrowUserException();
}