BOOL CDebugLog::Log(TCHAR *fmt, ...)
{
	if(m_hLogFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	size_t nLen;

	TCHAR szOutBuffer[1024]	= {0};
	TCHAR szInBuffer[1024]	= {0};

	DWORD dwInBuffer	= _countof(szInBuffer);
	DWORD dwOutBuffer	= _countof(szOutBuffer);
	DWORD dwBytesWritten;

	auto va_list	argptr;

	time_t			rawtime		= 0;
	struct tm 		timeinfo	= {0};

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	_wasctime_s(szInBuffer, _countof(szInBuffer), &timeinfo);

	nLen = wcslen(szInBuffer);
	szInBuffer[nLen - 1] = ' ';

	va_start(argptr, fmt);
	vswprintf_s(szInBuffer + nLen, _countof(szInBuffer) - nLen - 1, fmt, argptr);
	va_end(argptr);

	nLen = wcslen(szInBuffer);

	if(nLen == 0)
	{
		return TRUE;
	}

	wcscat_s(szInBuffer, _countof(szInBuffer), _T("\n"));

	dwInBuffer			= (DWORD)wcslen(szInBuffer);
	char *pszOutBuffer	= new char[dwInBuffer + 4];
	WideCharToMultiByte(CP_ACP, 0, szInBuffer, -1, pszOutBuffer, dwInBuffer + 1, NULL, NULL);

	if(m_hLogFile == INVALID_HANDLE_VALUE)
	{
		delete [] pszOutBuffer;
		return FALSE;
	}

	OutputDebugString(szInBuffer);
	WriteFile(m_hLogFile, pszOutBuffer, dwInBuffer, &dwBytesWritten, NULL);

	delete [] pszOutBuffer;

	return TRUE;
}