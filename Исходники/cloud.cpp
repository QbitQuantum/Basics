BOOL baidu_download(CString dfile, CString token, CString fname,DWORD *process)
{
	if (dfile == L"")
	{
		MessageBox(NULL,L"ÎÄ¼þÂ·¾¶²»ÄÜÎª¿Õ", 0, 0);
		return FALSE;
	}
	if (token == L"")
	{
		MessageBox(NULL, L"token²»ÄÜÎª¿Õ", 0, 0);
		return FALSE;
	}
	if (fname == L"")
	{
		MessageBox(NULL, L"ÎÄ¼þÃû²»ÄÜÎª¿Õ", 0, 0);
		return FALSE;
	}
	CString url(L"/rest/2.0/pcs/file?method=download&path=%2Fapps%2Fhitdisk%2F" + fname + L"&access_token=" + token);


	DWORD headlength;
	DWORD FileLength;//ÎÄ¼þ³¤¶È
	TCHAR* szBuff;//»º³åÇø
	DWORD bfsize = 1024 * 64;//»º³åÇø´óÐ¡
	TCHAR* FileBuff;//½âÎöÎÄ¼þ³¤¶ÈÖ¸Õë

	BOOL bResult = TRUE;
	HINTERNET hRequest = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hnet = InternetOpen(TEXT("Test"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	hConnect = InternetConnect(hnet, TEXT("pcs.baidu.com"), 443, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	hRequest = HttpOpenRequest(hConnect, TEXT("GET"), url, NULL, NULL, NULL, INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_NO_UI | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_RELOAD, 0);

	bResult = HttpSendRequest(hRequest, NULL, 0, NULL, 0);

	//½âÎöÎÄ¼þ³¤¶È
	DWORD i;
	szBuff = new TCHAR[bfsize];
	headlength = bfsize;
	bResult = HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, szBuff, &headlength, NULL);
	FileBuff = wcsstr(szBuff, L"Content-Length");
	FileBuff += 16;
	for (i = 0;; i++)
	{
		if (FileBuff[i] == '\r')
			break;
	}
	FileLength = CharToDword(FileBuff, i);

	CFile cfile(dfile, CFile::modeWrite | CFile::modeCreate);

	DWORD wbfclength = 0;//»º³åÇøµ±Ç°Êý¾Ý³¤¶È
	DWORD wbfsize = 1024 * 1024;//»º³åÇø´óÐ¡
	char *WriteBuffer = new char[wbfsize];//ÎÄ¼þÐ´Èë»º³åÇø

	CString show_process;
	DWORD dwBytesAvailable;
	DWORD FileReceived = 0;
	BOOL error = TRUE;
	BOOL cmp = 0;
	while (InternetQueryDataAvailable(hRequest, &dwBytesAvailable, 0, 0))
	{
		DWORD dwBytesRead;
		if (dwBytesAvailable <= bfsize)
		{
			bResult = InternetReadFile(hRequest, szBuff, dwBytesAvailable, &dwBytesRead);
		}
		else
		{
			bResult = InternetReadFile(hRequest, szBuff, bfsize, &dwBytesRead);
		}
		FileReceived += dwBytesRead;

		CopyMemory(WriteBuffer + wbfclength, szBuff, dwBytesRead);
		if (error)
		{
			szBuff[13] = '\0';
			cmp = _strnicmp((char *)szBuff,"{\"error_code\"" , 13);
			if (cmp == 0)
			{
				*process = 100;
				InternetCloseHandle(hRequest);
				InternetCloseHandle(hConnect);
				InternetCloseHandle(hnet);
				cfile.Close();
				cfile.Remove(dfile);
				delete[] szBuff;
				delete[] WriteBuffer;
				return FALSE;
			}
		}
		wbfclength += dwBytesRead;
		if (wbfclength > wbfsize - bfsize)
		{
			cfile.Write(WriteBuffer, wbfclength);
			wbfclength = 0;
		}
		*process = (DWORD)(100 * (double)FileReceived / FileLength);
		if (dwBytesRead == 0)
			break;  // End of File.
	}

	if (wbfclength)
		cfile.Write(WriteBuffer, wbfclength);

	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hnet);
	cfile.Close();
	delete[] szBuff;
	delete[] WriteBuffer;

	return TRUE;
}