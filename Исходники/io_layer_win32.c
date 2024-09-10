static char *IoLayer_Post(IOLAYER *hPIO, char *pszURL, char *pszPostFields, unsigned int cbPostFields, unsigned int *pdwLength)
{
	IOLAYER_INST *hIO = (IOLAYER_INST*)hPIO;
	URL_COMPONENTS urlInfo = {0};
	HINTERNET hUrl;
	DWORD dwFlags = 0, cbFlags = sizeof(dwFlags), dwRemaining = 0;
	char szHostName[INTERNET_MAX_HOST_NAME_LENGTH],
		szURLPath[INTERNET_MAX_URL_LENGTH], *p;

//OutputDebugString(pszPostFields);
	urlInfo.dwStructSize = sizeof (URL_COMPONENTS);
	urlInfo.lpszHostName = szHostName;
	urlInfo.dwHostNameLength = sizeof(szHostName);
	urlInfo.lpszUrlPath = szURLPath;
	urlInfo.dwUrlPathLength = sizeof(szURLPath);
	if (!InternetCrackUrl(pszURL, strlen(pszURL), 0, &urlInfo)) return NULL;
	/*
	if (!pszPostFields)
	{
		if (pszPostFields=strchr (pszURL, '?'))
			cbPostFields = strlen(pszPostFields);
	}
	*/

	if (!(hUrl = InternetConnect (hIO->hInet, szHostName, 
		INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0)))
	{
		FetchLastError (hIO);
		return NULL;
	}
	
	hIO->hRequest = HttpOpenRequest (hUrl, pszPostFields?"POST":"GET", szURLPath, NULL, NULL, NULL, 
		INET_FLAGS, 0);
	if (!hIO->hRequest)
	{
		FetchLastError (hIO);
		InternetCloseHandle (hUrl);
		return NULL;
	}
	
	InternetQueryOption (hIO->hRequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)&dwFlags, &cbFlags); 
	dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
	InternetSetOption (hIO->hRequest, INTERNET_OPTION_SECURITY_FLAGS, &dwFlags, sizeof (dwFlags));

	/*
	{
		char szCookies[4096];
		DWORD cbCookies, dwIndex=0;

		OutputDebugString ("Sending headers:\n");
		do
		{
			cbCookies=sizeof(szCookies);
			HttpQueryInfo (hIO->hRequest, HTTP_QUERY_FLAG_REQUEST_HEADERS|HTTP_QUERY_RAW_HEADERS_CRLF, szCookies, &cbCookies, &dwIndex);
			OutputDebugString (szCookies);
		} while (GetLastError() == ERROR_SUCCESS);
	}
	*/

	if (!(HttpSendRequest (hIO->hRequest, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
		"X-Requested-With: XMLHttpRequest", -1,
		pszPostFields, cbPostFields)))
	{
		FetchLastError (hIO);
		InternetCloseHandle (hIO->hRequest);
		hIO->hRequest = NULL;
		InternetCloseHandle (hUrl);
		return NULL;
	}

	/*
	{
		char szCookies[4096];
		DWORD cbCookies, dwIndex=0;

		OutputDebugString ("Received headers:\n");
		do
		{
			cbCookies=sizeof(szCookies);
			HttpQueryInfo (hIO->hRequest, HTTP_QUERY_FLAG_REQUEST_HEADERS|HTTP_QUERY_RAW_HEADERS_CRLF, szCookies, &cbCookies, &dwIndex);
			OutputDebugString (szCookies);
		} while (GetLastError() == ERROR_SUCCESS);
	}
	*/


	while (InternetQueryDataAvailable (hIO->hRequest, &dwRemaining, 0, 0) && dwRemaining > 0)
	{
		if (p = Fifo_AllocBuffer (hIO->hResult, dwRemaining))
			InternetReadFile (hIO->hRequest, p, dwRemaining, &dwRemaining);
	}
	if (!pdwLength)
	{
		// Get string
		Fifo_Add (hIO->hResult, "", 1);
		p = Fifo_Get (hIO->hResult, NULL);
	}
	else
	{
		// Get binary, return size of buffer
		*pdwLength = (unsigned int)-1;
		p = Fifo_Get (hIO->hResult, pdwLength);
	}
	InternetCloseHandle (hIO->hRequest);
	hIO->hRequest = NULL;
	InternetCloseHandle (hUrl);
OutputDebugString(p);
OutputDebugString("\n");
	return p;
}