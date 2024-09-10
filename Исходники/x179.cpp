void OpenWebPluginRequest(CString& strURL, CString& strResult)
{
	HINTERNET handle = InternetOpen("x179", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);

	if(handle == NULL)
	{
		return;
	}

	HINTERNET internetopenurl = 
		InternetOpenUrl(handle, strURL.GetBuffer(), NULL, 0, 
		INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_CACHE_WRITE, 0);

	if(internetopenurl != NULL)
	{
		byte buffer[10240] = {0};
		DWORD dwReadBytes = 0;
		DWORD dwTotal = 0;

		while(InternetReadFile(internetopenurl, &buffer[dwTotal], 10240-dwTotal, &dwReadBytes)
			&& dwReadBytes > 0)
		{
			dwTotal += dwReadBytes;
			dwReadBytes = 0;
			if(10240-dwTotal <= 0)
				break;
		}

		buffer[dwTotal] = 0;
		strResult = (char*)buffer;

		InternetCloseHandle(internetopenurl);
	}

	InternetCloseHandle(handle);
}