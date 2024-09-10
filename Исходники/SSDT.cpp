BOOL GetInterNetURLText(CHAR *lpcInterNetURL,CHAR *lpwzReadData)
{
	HINTERNET hSession;
	HINTERNET hRequest;
	BOOL bResult = FALSE;
	DWORD dwBytesRead;
	CHAR lpwzUserAgent[256];

	memset(lpwzUserAgent,0,sizeof(lpwzUserAgent));
	QueryUserAgent(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings","User Agent",lpwzUserAgent);
	//QueryUserAgent(lpwzUserAgent);
	//MessageBoxA(0,lpwzUserAgent,0,0);
	hSession = InternetOpenA(lpwzUserAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL)
	{
		//MessageBoxA(0,"InternetOpenA",0,0);
		hRequest = InternetOpenUrlA(hSession, lpcInterNetURL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
		if (hRequest != NULL)
		{
			//MessageBoxA(0,"InternetOpenUrlA",0,0);
			if (InternetReadFile(hRequest, lpwzReadData,256, &dwBytesRead))
			{
				//MessageBoxA(0,lpwzReadData,0,0);
				bResult = TRUE;
			}
			InternetCloseHandle(hRequest);
		}
		InternetCloseHandle(hSession);
	}
	return bResult;
}