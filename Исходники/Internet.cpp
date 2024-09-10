int CInternet::URLPost(const TCHAR *lpszServer, const char *lpszDest)
{
	int bReturn = 0;
//	HINTERNET  hConnect = NULL, hRequest = NULL;
	
	TCHAR szErrMsg[512];
  	char *lpBufferA=NULL;

	LPTSTR AcceptTypes[10] = {TEXT("*/*"), NULL}; 

    DWORD dwRequestFlag = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;

	if(strstr(lpszServer,"https://")!=NULL) //check if it is a HTTPS server
		dwRequestFlag = INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID | INTERNET_FLAG_IGNORE_CERT_CN_INVALID;

	TCHAR szHeaders[] = _T("Content-Type: application/x-www-form-urlencoded"); //content type for post...
	
	TCHAR *HostName = _tcsdup(uc.lpszHostName);
	HostName[uc.dwHostNameLength] = '\0';
	TCHAR *FileName = _tcsdup(uc.lpszUrlPath);
	FileName[uc.dwUrlPathLength] = '\0';
	HINTERNET hCO = InternetConnect(m_hOpen, HostName, uc.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, INTERNET_FLAG_NO_CACHE_WRITE, 0);
	HINTERNET hIS = HttpOpenRequest(hCO, _T("POST"), FileName, NULL, NULL, (LPCTSTR*)AcceptTypes, dwRequestFlag, 0);

again:
	HINTERNET hOU = InternetOpenUrl (m_hOpen, lpszServer, NULL, 0,dwRequestFlag, 0);
	//DWORD dwLength = GetFileLength(hOU);
	if (!HttpSendRequest(hIS, szHeaders, _tcslen(szHeaders), (TCHAR*)&uc.lpszUrlPath[1], _tcslen(&uc.lpszUrlPath[1])))
	{
		DWORD LastError = GetLastError();
		if(LastError == ERROR_INTERNET_INVALID_CA)
		{
			DWORD dwFlags;
			DWORD dwBuffLen = sizeof(dwFlags);

			InternetQueryOption (hIS, INTERNET_OPTION_SECURITY_FLAGS,
			(LPVOID)&dwFlags, &dwBuffLen);

			dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
			InternetSetOption (hIS, INTERNET_OPTION_SECURITY_FLAGS,
			&dwFlags, sizeof (dwFlags) );
			goto again;

		}
	}
	
	FILE *stream = NULL;
	errno_t err = _set_fmode(_O_BINARY);
	if (err == EINVAL)
	{ 
	  OutputDebugString("Invalid mode.\n");
	  return 5;
	}
	
	DWORD dynamicByte = 32000;
	DWORD downloadBytes = 0;
	DWORD dwSize = 0; 
	DWORD availableSize=0;
	do
	{
		lpBufferA = new CHAR [dynamicByte];
		InternetQueryDataAvailable(hIS,&availableSize,0,0);
		sprintf_s(szErrMsg,sizeof(szErrMsg),"Downloaded %d of %d KBytes\n",downloadBytes/1000,availableSize/1000);
		OutputDebugString(szErrMsg);	
	
		if (!InternetReadFile (hIS, (LPVOID)lpBufferA, dynamicByte, &dwSize))
		{
			_stprintf_s(szErrMsg, TEXT("%s: %x\n"), TEXT("InternetReadFile Error"),GetLastError());
			OutputDebugString(szErrMsg);
			delete[] lpBufferA;
			goto exit;
		}

		if (dwSize != 0)    
		{	
			downloadBytes+=dwSize;
			if((stream==NULL) && (bReturn==0))
		   		fopen_s(&stream, lpszDest, "w+" );

			if(stream!=NULL)
				 fwrite( lpBufferA, sizeof( CHAR ), dwSize, stream );		
		}    
		if(lpBufferA)
			delete[] lpBufferA; 
		dynamicByte+=1024;
		if(dynamicByte>128000)
			dynamicByte = 128000;

	} while (dwSize);

	if(stream!=NULL)
		fclose(stream);

  goto exitWithNoErr;
exit:
	bReturn = 1;
exitWithNoErr:
	free(HostName);
	free(FileName);

	if (hIS)
	{
		if (!InternetCloseHandle (hIS))
		{
			_stprintf_s(szErrMsg, TEXT("%s: %x"), TEXT("CloseHandle Error"), GetLastError());
			OutputDebugString(szErrMsg);
		}
	}
	if (hCO)
	{
		if (!InternetCloseHandle (hCO))
		{
			_stprintf_s(szErrMsg, TEXT("%s: %x"), TEXT("ConnectOpen close Error"), GetLastError());
			OutputDebugString(szErrMsg);
		}
	}
    _stprintf_s(szErrMsg, TEXT("Return %d"), bReturn);
	OutputDebugString(szErrMsg);
	return bReturn;
}