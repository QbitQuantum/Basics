LPBYTE DownloadToMemory(IN LPCTSTR lpszURL, OUT PDWORD_PTR lpSize)
{
	LPBYTE lpszReturn = 0;
	*lpSize = 0;
	const HINTERNET hSession = InternetOpen(TEXT("GetGitHubRepositoryList"), INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, INTERNET_FLAG_NO_COOKIES);
	if (hSession)
	{
		URL_COMPONENTS uc = { 0 };
		TCHAR HostName[MAX_PATH];
		TCHAR UrlPath[MAX_PATH];
		uc.dwStructSize = sizeof(uc);
		uc.lpszHostName = HostName;
		uc.lpszUrlPath = UrlPath;
		uc.dwHostNameLength = MAX_PATH;
		uc.dwUrlPathLength = MAX_PATH;
		InternetCrackUrl(lpszURL, 0, 0, &uc);
		const HINTERNET hConnection = InternetConnect(hSession, HostName, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, 0);
		if (hConnection)
		{
			const HINTERNET hRequest = HttpOpenRequest(hConnection, TEXT("GET"), UrlPath, 0, 0, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
			if (hRequest)
			{
				HttpSendRequest(hRequest, 0, 0, 0, 0);
				lpszReturn = (LPBYTE)GlobalAlloc(GMEM_FIXED, 1);
				DWORD dwRead;
				static BYTE szBuf[1024 * 4];
				LPBYTE lpTmp;
				for (;;)
				{
					if (!InternetReadFile(hRequest, szBuf, (DWORD)sizeof(szBuf), &dwRead) || !dwRead) break;
					lpTmp = (LPBYTE)GlobalReAlloc(lpszReturn, (SIZE_T)(*lpSize + dwRead), GMEM_MOVEABLE);
					if (lpTmp == NULL) break;
					lpszReturn = lpTmp;
					CopyMemory(lpszReturn + *lpSize, szBuf, dwRead);
					*lpSize += dwRead;
				}
				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnection);
		}
		InternetCloseHandle(hSession);
	}
	return lpszReturn;
}