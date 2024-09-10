int CZipExists::RemoteFileExists()
{
	int iResult = -1;   // network error
	DWORD dwFilePos = 0;
	HINTERNET hInternet = NULL, hDownload = NULL; 

   CString csUrl = m_csUrl + m_csFileName;
   //AfxMessageBox(csUrl, MB_ICONINFORMATION); 

	hInternet = InternetOpen(_T("Internet"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if(hInternet != NULL)
	{
		hDownload = InternetOpenUrl(hInternet, csUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);
		if(hDownload != NULL)
		{
         dwFilePos = InternetSetFilePointer(hDownload, 0, NULL, FILE_BEGIN, NULL);
         iResult = (dwFilePos != (DWORD)-1) ? 1 : 0;
			InternetCloseHandle(hDownload);
		}
      else
      {
         GetInetError();
      }
		InternetCloseHandle(hInternet);
	}
   else
   {
      GetInetError();
   }
	return iResult;
}