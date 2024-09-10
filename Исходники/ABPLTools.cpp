CString	ABPLTools::DownloadString(CString url, InternetFeedback* pCIF, bool *pbExit)
{
CString			result;
HINTERNET		hSession, hConnect ;
char			szTemp[512] ;
DWORD			dwBytesRead ;
bool			bExit = false;

	if (pbExit==NULL)
		pbExit = &bExit;

	if (hSession = InternetOpen (TEXT("ABP-Launcher (Win)"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0))
	{
		/*unsigned long to = Timeout;
		InternetSetOption(hSession, INTERNET_OPTION_CONNECT_TIMEOUT, &to, sizeof(unsigned long));*/
		if (hConnect = InternetOpenUrl (hSession, url, NULL, 0, INTERNET_FLAG_RELOAD, 0))
		{
			DWORD dwSize = 512, dwIndex=0;
			HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH, szTemp, &dwSize, &dwIndex);
			DWORD totalSize = atol(szTemp);
			DWORD dwTotal=0;
			do
			{	
				dwBytesRead=0;
				if (InternetReadFile (hConnect, szTemp, sizeof (szTemp)-1, &dwBytesRead))
				{
					szTemp[dwBytesRead]=0;
					result.Append(szTemp);
					dwTotal += dwBytesRead;
					if (pCIF)
						pCIF->DownloadFeedback(totalSize, dwTotal);
				}
			}
			while (dwBytesRead > 0 && *pbExit==false);
			InternetCloseHandle (hConnect) ;
		}
		InternetCloseHandle (hSession) ;
	}
	return result ;
}