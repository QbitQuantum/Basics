bool CAmHttpSocket::PostUrl(const char *url, const char *PostData, int PostDataLength)
{
	//check length of postdata
	if (PostDataLength == -1)
		PostDataLength = strlen(PostData);
	//some variable that we need...
	URL_COMPONENTSA uc;
	//let's split the url...
	uc.dwStructSize = sizeof(uc);
	uc.lpszScheme = NULL;
	uc.dwSchemeLength = 0;
	uc.lpszHostName = NULL;
	uc.dwHostNameLength = 1;
	uc.nPort = 0;
	uc.lpszUserName = NULL;
	uc.dwUserNameLength = 0;
	uc.lpszPassword = NULL;
	uc.dwPasswordLength = 0;
	uc.lpszUrlPath = NULL;
	uc.dwUrlPathLength = 1;
	uc.lpszExtraInfo = NULL;
	uc.dwExtraInfoLength = 0;
	InternetCrackUrlA(url, strlen(url), 0, &uc);
	//post the data...
	if (hCO != NULL) InternetCloseHandle(hCO);
	CHAR *HostName = strdup(uc.lpszHostName);
	if(!HostName){
		LastError = -2;
		return false;
	}
	HostName[uc.dwHostNameLength] = '\0';
	CHAR *FileName = strdup(uc.lpszUrlPath);
	FileName[uc.dwUrlPathLength] = '\0';
	if (hIS != NULL) InternetCloseHandle(hIS); //if open, close the handle to the connection
	DWORD flags;
	if (uc.nPort == 80)
	{
		//we are talking plain http
		flags = INTERNET_FLAG_NO_CACHE_WRITE;
	}
	else
	{
		//we are talking secure https
		flags = INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_SECURE |
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
	}
	CHAR headers[] = ("Content-Type: application/x-www-form-urlencoded"); //content type for post...
	CHAR szAccept[] = ("*/*"); //we accept everything...
	LPSTR AcceptTypes[2]={0};
	AcceptTypes[0]=szAccept;
	hCO = InternetConnectA(hIO, HostName, uc.nPort, (""), (""), INTERNET_SERVICE_HTTP, INTERNET_FLAG_NO_CACHE_WRITE, 0);
	hIS = HttpOpenRequestA(hCO, ("POST"), FileName, NULL, NULL, (LPCSTR *)AcceptTypes, flags, 0);
	if (!HttpSendRequestA(hIS, headers, strlen(headers), (TCHAR*)PostData, PostDataLength))
	{
		LastError = GetLastError();
		free(HostName);
		free(FileName);
		return false;
	}
	free(HostName);
	free(FileName);
	return true;
}