BOOL CImageCode::InternetGetFile(TCHAR *szUrl, TCHAR *szFileName)
{
    DWORD dwFlags = 0;
	BOOL bRes = FALSE;
	HINTERNET hOpen = NULL;
	if (!InternetGetConnectedState(&dwFlags, 0))
	{
		g_ImgCodeLog.Trace(LOGL_TOP,LOGT_ERROR, __TFILE__,__LINE__, _T("网络未连接, err:%d"), GetLastError());
	}

	if(!(dwFlags & INTERNET_CONNECTION_PROXY))
		hOpen = InternetOpen(_T("SUMENGINE2"), INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	else
		hOpen = InternetOpen(_T("SUMENGINE2"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if(!hOpen)
	{
		g_ImgCodeLog.Trace(LOGL_TOP,LOGT_ERROR, __TFILE__,__LINE__, _T("InternetOpen错误, err:%d"), GetLastError());
		return bRes;
	}
	
	DWORD dwSize;
	TCHAR   szHead[] = _T("Accept: */*\r\n\r\n");
	BYTE szTemp[16384];             //16kb
	HINTERNET  hConnect = NULL;
	CFile file;
	CFileException e;
	DWORD dwErr = 0;

	//设置超时
	long lTimeout = 10000;
	InternetSetOption(hOpen,INTERNET_OPTION_CONNECT_TIMEOUT,(LPVOID)&lTimeout,sizeof(long));
	InternetSetOption(hOpen,INTERNET_OPTION_RECEIVE_TIMEOUT,(LPVOID)&lTimeout,sizeof(long));
	InternetSetOption(hOpen,INTERNET_OPTION_DATA_RECEIVE_TIMEOUT,(LPVOID)&lTimeout,sizeof(long));


	if ( !(hConnect = InternetOpenUrl( hOpen, szUrl, szHead,
		 _tcslen(szHead), INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0)))
	{
		g_ImgCodeLog.Trace(LOGL_TOP,LOGT_ERROR, __TFILE__,__LINE__, _T("InternetOpenUrl错误, err:%d"), GetLastError());
        goto end;
	}
	
	try
	{
		if  (!file.Open(szFileName, CFile::modeWrite | CFile::modeCreate, &e))
		{
			g_ImgCodeLog.Trace(LOGL_TOP,LOGT_ERROR, __TFILE__,__LINE__, _T("打开文件失败：%d"), e.m_cause);
			goto end;	    
		}

// 		DWORD dwByteToRead = 0;
// 		DWORD dwSizeOfRq = 4;
// 		DWORD dwFactBytes = 0;

		////当HTTP请求返回的头中不包括Content-length时，会返回12150错误，但这并不表示不可以下载
		//// 所以，不再使用头中的数据长度作为下载完整的判断依据。InternetReadFile本身就可以判断，参考MSDN
// 		if (HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, 
// 			(LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
// 		{
			do
			{
				memset(szTemp,0,sizeof(szTemp));
				if (!InternetReadFile (hConnect, szTemp, sizeof(szTemp),  &dwSize))
				{
					g_ImgCodeLog.Trace(LOGL_TOP,LOGT_ERROR, __TFILE__,__LINE__, _T("InternetReadFile错误, err:%d"), GetLastError());
					break;
				}

				if (dwSize==0)
				{
					bRes = TRUE;
					break;
				}
				else
					file.Write(szTemp, dwSize);

				//dwFactBytes += dwSize;

			}while (dwSize != 0);

// 			if (dwFactBytes == dwByteToRead)
// 			{
// 				bRes = TRUE;
// 			}

		//}
		//else
		//{
		//	dwErr = GetLastError();
		//}
		file.Close();
	}
	catch(...)
	{
		bRes = FALSE;
	}

end:
	if (NULL != hConnect)
		InternetCloseHandle(hConnect);

	if (NULL != hOpen)
		InternetCloseHandle(hOpen);

	return bRes;
}