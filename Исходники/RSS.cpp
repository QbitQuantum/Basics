_bstr_t HttpGetUrl(const _bstr_t& url)
{
	_bstr_t retval;

	HINTERNET hSession = InternetOpen(_T("HttpGet"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (hSession)
	{
		bool isSsl = false;
		//const char* u = static_cast<const char*>(url);

		HINTERNET hFile = InternetOpenUrl(hSession, url, NULL, 0, 0, 0);
		
		if (hFile)
		{
			DWORD bytesAvailable = 0;
			
			if (InternetQueryDataAvailable(hFile, &bytesAvailable, 0, 0))
			{
				const int BUFFLEN = 1024;
				TCHAR buffer[BUFFLEN];
				DWORD dwRead;
	
				while (InternetReadFile(hFile, buffer, BUFFLEN - sizeof(TCHAR), &dwRead))
				{
					if (dwRead == 0)
						break;
	
					buffer[dwRead / sizeof(TCHAR)] = _T('\0');
					retval += buffer;
				}
	
				InternetCloseHandle(hFile);
			}
		}

		InternetCloseHandle(hSession);
	}

	return retval;
}