BOOL DownloadWebPageW(std::string& page, HINTERNET hInternet, LPCWSTR url)
{
	TRACEST(_T("DownloadWebPageW"), CW2CT(url));
	BOOL bDownloadSuccess = FALSE;
	if (hInternet == NULL)
		return FALSE;
	HINTERNET hFile = InternetOpenUrlW(hInternet, url, NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE, 0);
	if (hFile)
	{   
		bDownloadSuccess = ReadInternetFile2StringW(hFile, page);
		InternetCloseHandle(hFile);
	}
	else
		HandleInternetError(_T("DownloadWebPage. InternetOpenUrlW"));
	return bDownloadSuccess;
}