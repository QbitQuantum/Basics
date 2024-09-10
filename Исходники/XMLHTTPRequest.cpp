UINT APIENTRY CXMLHttpRequest::SendThread(void *pParm)
{
	ATLTRACE(_T("CXMLHttpRequest::SendThread\n"));

	CXMLHttpRequest *pCtx = reinterpret_cast<CXMLHttpRequest *> (pParm);
	if (NULL == pCtx)
		return 0;

	HINTERNET hOpen    = NULL;
	HINTERNET hConnect = NULL; 
	HINTERNET hRequest = NULL; 

	hOpen = InternetOpen(_T("XMLHTTP/1.0"),INTERNET_OPEN_TYPE_PRECONFIG,
										NULL,NULL,0);
	if (NULL == hOpen) {
		DWORD res = GetLastError();
		pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
		pCtx->m_bSuccess = false;
	}

	if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
		if (INTERNET_INVALID_STATUS_CALLBACK == InternetSetStatusCallback(hOpen,
				CXMLHttpRequest::InternetStatusCallback)) {
			pCtx->m_Error = _T("Invalid Internet Status Callback function.");
			pCtx->m_bSuccess = false;
		}
	}

	bool bPromptForAuthentication = true;
	if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
		LPTSTR lpszUserName = NULL;
		LPTSTR lpszPassword = NULL;
		if (pCtx->m_User.length() > 0) {
			bPromptForAuthentication = false;
			lpszUserName = pCtx->m_User; 
			if (pCtx->m_Password.length() > 0) 
				lpszPassword = pCtx->m_Password;
		}    
		hConnect = InternetConnect(hOpen,pCtx->m_HostName,pCtx->m_Port,lpszUserName,lpszPassword,
										INTERNET_SERVICE_HTTP,0,reinterpret_cast<DWORD> (pCtx));
		if (NULL == hConnect) {
			DWORD res = GetLastError();
			pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
			pCtx->m_bSuccess = false;
		}
	}

	if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
		DWORD dwFlags = (443 == pCtx->m_Port) ? INTERNET_FLAG_SECURE : 0;
		dwFlags |= INTERNET_FLAG_NO_CACHE_WRITE;
		hRequest = HttpOpenRequest(hConnect,pCtx->m_Method,
						pCtx->m_URLPath,NULL,NULL,NULL,
						dwFlags,reinterpret_cast<DWORD> (pCtx));
		if (NULL == hRequest) {
			DWORD res = GetLastError();
			pCtx->m_bSuccess = false;
			pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
		}
	}

	BOOL rc = TRUE;

	if (!pCtx->m_bAbort && pCtx->m_bSuccess && pCtx->m_RequestHeaderMap.GetSize() > 0) {
		_bstr_t requestHeaders;
		for (int i = 0 ; i < pCtx->m_RequestHeaderMap.GetSize(); ++i) {
			requestHeaders += pCtx->m_RequestHeaderMap.GetKeyAt(i);
			requestHeaders += _T(": ");
			requestHeaders += pCtx->m_RequestHeaderMap.GetValueAt(i);
			requestHeaders += _T("\r\n");
		}
		rc = HttpAddRequestHeaders(hRequest,requestHeaders,-1,HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
		if (!rc) {	
			DWORD res = GetLastError();
			pCtx->m_bSuccess = false;
			pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
		}
	}
	
	DWORD dwLen = 0;
	DWORD dwError = ERROR_SUCCESS; 
	do {
		if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
			rc = HttpSendRequest(hRequest,NULL,0,pCtx->m_pBody,pCtx->m_lBodyLength);
			if (!rc) {	
				DWORD res = GetLastError();
				pCtx->m_bSuccess = false;
				pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
				break;
			}
		}
		if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
			dwLen = sizeof(DWORD);
			rc = HttpQueryInfo(hRequest,
							   HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
							   &pCtx->m_dwStatus,&dwLen,NULL);
			if (!rc) {
				DWORD res = GetLastError();
				pCtx->m_bSuccess = false;
				pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
				break;
			}
		}
		if (!pCtx->m_bAbort && pCtx->m_bSuccess &&
			bPromptForAuthentication &&
			(HTTP_STATUS_PROXY_AUTH_REQ == pCtx->m_dwStatus ||
			 HTTP_STATUS_DENIED		    == pCtx->m_dwStatus)) 
   			dwError = InternetErrorDlg(pCtx->m_HwndParent,
									   hRequest,
									   ERROR_INTERNET_INCORRECT_PASSWORD,
									   FLAGS_ERROR_UI_FILTER_FOR_ERRORS	   |
									   FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS |
									   FLAGS_ERROR_UI_FLAGS_GENERATE_DATA,				
									   NULL);
		else
			break;
	
	} while (ERROR_INTERNET_FORCE_RETRY == dwError &&
			 !pCtx->m_bAbort && pCtx->m_bSuccess); 		
	
	if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
		dwLen = 1024;
		TCHAR *pBuff = new TCHAR[dwLen];
		rc = HttpQueryInfo(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF,pBuff,&dwLen,NULL);
		if (!rc) {
			DWORD res = GetLastError();
			if (ERROR_INSUFFICIENT_BUFFER == res) {
				delete [] pBuff;
				pBuff = new TCHAR[dwLen];
				rc = HttpQueryInfo(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF,pBuff,&dwLen,NULL);
				if (!rc) {
					res = GetLastError();
					pCtx->m_bSuccess = false;
					pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
				}
			}
			else {
				pCtx->m_bSuccess = false;
				pCtx->m_Error = CXMLHttpRequest::GetErrorMsg(res);
			}
		}
		if (rc)
			 pCtx->m_ResponseHeaders = pBuff;

		delete [] pBuff;
	}

	if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
		dwLen = 1024;
		TCHAR *pBuff = new TCHAR[dwLen];
		rc = HttpQueryInfo(hRequest,HTTP_QUERY_STATUS_TEXT,pBuff,&dwLen,NULL);
		if (!rc) {
			DWORD res = GetLastError();
			if (ERROR_INSUFFICIENT_BUFFER == res) {
				delete [] pBuff;
				pBuff = new TCHAR[dwLen];
				rc = HttpQueryInfo(hRequest,HTTP_QUERY_STATUS_TEXT,pBuff,&dwLen,NULL);
				if (!rc) 
					_tcscpy(pBuff,_T("Unknown"));
			}
			else 
				_tcscpy(pBuff,_T("Unknown"));
		}
		pCtx->m_StatusText = pBuff; 
		delete [] pBuff;
	
		if (HTTP_STATUS_OK != pCtx->m_dwStatus) {
			TCHAR errBuff[MAX_PATH] = _T("");
			wsprintf(errBuff,_T("HTTP Status Code: %d, Reason: "),pCtx->m_dwStatus);
			pCtx->m_Error = errBuff;
			pCtx->m_Error += pCtx->m_StatusText;
			pCtx->m_bSuccess = false;
		}
	}

	if (!pCtx->m_bAbort && pCtx->m_bSuccess) {
		PBYTE buffer[255];
		DWORD dwRead = 0;
		delete [] pCtx->m_pResponseBody;
		pCtx->m_pResponseBody = NULL;
		pCtx->m_lResponseBodyLength = 0;
		while (rc = InternetReadFile(hRequest,buffer,255,&dwRead)) {
			if (!rc || pCtx->m_bAbort || 0 == dwRead) 
				break;
					
			PBYTE tmp = new BYTE[pCtx->m_lResponseBodyLength + dwRead];
			if (pCtx->m_pResponseBody) {
				memcpy(tmp,pCtx->m_pResponseBody,pCtx->m_lResponseBodyLength);
				delete [] pCtx->m_pResponseBody;
			}

			memcpy(tmp+pCtx->m_lResponseBodyLength,buffer,dwRead);
			pCtx->m_pResponseBody = tmp;
			pCtx->m_lResponseBodyLength += dwRead;
		}
		if (!rc) {
			DWORD res = GetLastError();
			pCtx->m_Error = _T("Error reading response: ") + CXMLHttpRequest::GetErrorMsg(res);
			pCtx->m_bSuccess = false;
		}
	}

	if (hRequest != NULL)
		InternetCloseHandle(hRequest);
	
	if (hConnect != NULL) 
		InternetCloseHandle(hConnect);

	if (hOpen)
		InternetCloseHandle(hOpen);
	
	if (!pCtx->m_bAbort && pCtx->m_bAsync)
		::PostMessage(pCtx->m_hWnd,MSG_READY_STATE_CHANGE,4,0); 
  
	return 0;
}