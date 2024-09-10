BOOL CMyUtility::QueryMasterModifyTime( LPCTSTR strMasterFile, SYSTEMTIME *lpSysTime )
{

	// Clear output buffer
	SecureZeroMemory(lpSysTime, sizeof(SYSTEMTIME));

	DeleteUrlCacheEntry(strMasterFile);

	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) 
		return FALSE;

	// Open the resource from server
	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, strMasterFile, NULL, 0, 0, 0);
	if (!hInternetFile)
	{
		InternetCloseHandle(hInternetSession);
		return FALSE;
	}

	// Query last modify date and time
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_LAST_MODIFIED | HTTP_QUERY_FLAG_SYSTEMTIME, lpSysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetFile);
		InternetCloseHandle(hInternetSession);
		return FALSE;
	}

	// Clean up...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);
	return TRUE;

}