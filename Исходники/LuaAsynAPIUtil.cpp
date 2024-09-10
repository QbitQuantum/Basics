void InternetDownload(const std::wstring strUrl)
{
	char buffer[100000];//下载文件的缓冲区

	DWORD dwBufferRead;//下载的字节数


	//打开一个internet连接

	HINTERNET hInternet=InternetOpen(_T("HTTP Downloader"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);

	if(NULL == hInternet)
	{
		TSDEBUG4CXX(L"[InternetDownload] InternetOpen error, code = "<<::GetLastError());
		return;
	}
	//打开一个http url地址
	HINTERNET hFile=InternetOpenUrl(hInternet, strUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);

	if(NULL == hFile)
	{
		InternetCloseHandle(hInternet);
		TSDEBUG4CXX(L"[InternetDownload]  InternetOpenUrl error, code = "<<::GetLastError());
		return;
	}

	BOOL bRead = InternetReadFile(hFile, buffer, 100000, &dwBufferRead);
	if(!bRead)
	{
		InternetCloseHandle(hFile);
		InternetCloseHandle(hInternet);
		TSDEBUG4CXX(L"[InternetDownload]  InternetReadFile error, code = "<<::GetLastError());
		return;
	}

	//关闭连接
	InternetCloseHandle(hFile);
	InternetCloseHandle(hInternet);
}