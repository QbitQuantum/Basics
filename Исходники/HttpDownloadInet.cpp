HINTERNET HttpDownloadInet::_internetOpenUrl(wchar_t* URL) const
{
	HINTERNET hRemoteFile;

	hRemoteFile = InternetOpenUrl(m_hInternet, URL, NULL, 0,
//#if DEVELOPMENT_VERSION
//		0, // Allows catching (speeds ups downloads during development)
//#else
		INTERNET_FLAG_RELOAD, // Prevents local caching (for release version)
//#endif
		0);	

	if (hRemoteFile == 0)
		return NULL;

	int status = _getStatusCode(hRemoteFile);
	if (status == ERROR_FILE_NOTFOUND || status == ERROR_SERVER_ERROR)
	{
		g_log.Log(L"HttpDownloadInet::_internetOpenUrl. Error '%u' getting '%s'", (wchar_t *) status, URL);
		InternetCloseHandle(hRemoteFile);
		return NULL;
	}
	return hRemoteFile;
}