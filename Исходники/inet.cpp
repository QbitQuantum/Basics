int InternetDownloadFile(char *URL, char *FileDest)
{
DWORD dwFlags;
DWORD dwResult = INTERNET_ERROR_OPEN;
InternetGetConnectedState(&dwFlags, 0);
CHAR strAgent[64];
sprintf(strAgent, "Agent%ld", timeGetTime());

HINTERNET hOpen;
if(!(dwFlags & INTERNET_CONNECTION_PROXY))
hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
else
hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
if(hOpen)
{
	dwResult = InternetGetFile(hOpen, URL, FileDest);
	InternetCloseHandle(hOpen);
}
else return INTERNET_ERROR_OPEN;
return dwResult;
}