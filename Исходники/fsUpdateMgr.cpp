BOOL fsUpdateMgr::UrlDownloadToFile(LPCSTR pszUrl, LPCSTR pszFile, int *piProgress)
{
	m_bNeedStop = FALSE;

	if (piProgress)
		*piProgress = 0;

	m_hInet = InternetOpen (PRG_AGENT_NAME, INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, 0);
	if (m_hInet == NULL)
		return FALSE;

	HINTERNET m_hFile = InternetOpenUrl (m_hInet, pszUrl, NULL, 0, 
		INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_UI | 
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0);
	if (m_hFile == NULL)
	{
		InternetCloseHandle (m_hInet);
		return FALSE;
	}

	if (m_bNeedStop)
		return FALSE;

	HANDLE hLocalFile = CreateFile (pszFile, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLocalFile == INVALID_HANDLE_VALUE)
	{
		InternetCloseHandle (m_hFile);
		InternetCloseHandle (m_hInet);
		return FALSE;
	}

	UINT nLen = UINT_MAX, nDownloaded = 0; DWORD dw = sizeof (nLen);
	HttpQueryInfo (m_hFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, 
		&nLen, &dw, NULL);

	BYTE ab [1000]; DWORD dwRead = 1;
	while (InternetReadFile (m_hFile, ab, sizeof (ab), &dwRead) && dwRead != 0)
	{
		if (m_bNeedStop)
			break;

		WriteFile (hLocalFile, ab, dwRead, &dwRead, NULL);
		nDownloaded += dwRead;
		if (piProgress)
			*piProgress = MulDiv (nDownloaded, 100, nLen);
	}

	CloseHandle (hLocalFile);
	InternetCloseHandle (m_hFile);
	InternetCloseHandle (m_hInet);

	if (dwRead != 0 || m_bNeedStop)
	{
		DeleteFile (pszFile);
		return FALSE;
	}

	return TRUE;
}