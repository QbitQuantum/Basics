//#else
void CSinaSvr::PostWeibo(LPCTSTR lpContent)
{
	BOOL bResults= FALSE;
HINTERNET  hSession = NULL,hConnect = NULL,	hRequest = NULL;
	TCHAR szServer[1024] = _T("weibo.com");
	TCHAR szParam[1024]  = _T("aj/mblog/add");
	TCHAR szHeader[1024] = {0};
	TCHAR szCookie[1024] = {0};
	_stprintf(szHeader,_T("Accept: */*\r\nContent-Type: application/x-www-form-urlencoded\r\nReferer: http://weibo.com/%s\r\nx-requested-with: XMLHttpRequest\r\n"),m_szCurUID);
	_stprintf(szCookie,_T("Cookie: %s\r\n"),m_strCookie.GetBuffer());
	WCHAR szwPost[1024]={0};
	_stprintf(szwPost,_T("_t=0&pic_id=&text=%s"),lpContent);

	char szPost[1024]= {0};
	WideCharToMultiByte(CP_UTF8, 0, szwPost, -1, szPost, MAX_PATH, NULL, NULL);

	PBYTE pBuf = new BYTE[1024*1024];

	hSession = WinHttpOpen(0,  
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME, 
		WINHTTP_NO_PROXY_BYPASS, 0 );
	
	if(hSession)
		WinHttpSetTimeouts( hSession, 600000, 600000, 600000, 600000);

	if( hSession )
		hConnect = WinHttpConnect( hSession,szServer,80, 0 );

	if (hConnect)
        hRequest = WinHttpOpenRequest( hConnect, L"POST", szParam, 
		NULL, WINHTTP_NO_REFERER, 
		WINHTTP_DEFAULT_ACCEPT_TYPES, 
		0);
	int nLen = strlen(szPost);
	WinHttpAddRequestHeaders( hRequest, 
		szCookie, 
		-1, 
		WINHTTP_ADDREQ_FLAG_ADD);
	// Send a Request.
    if (hRequest) 
		bResults = WinHttpSendRequest( hRequest, szHeader,-1, szPost, nLen,nLen,0);

	DWORD dwLen;
	GetHttpResponse(pBuf,dwLen,hRequest);

	if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
	
	delete []pBuf;
	PostWeibo1(lpContent);
}