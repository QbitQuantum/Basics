VOID NdPerfLog(__in LPCWSTR logfile, __in __format_string LPCWSTR  fmt, ...)
{
	va_list argList;
	va_start(argList, fmt);	
	WCHAR szMsg[4096];
	StringCchVPrintfW(szMsg, _countof(szMsg), fmt, argList);
	va_end(argList);

	//MSG(동기화 추가);
	HANDLE hFile = CreateFile(
		logfile,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_stprintf_s(szMsg, L"Cannot create a log file. [errcode: %d][%s]\n", GetLastError(), logfile);
		OutputDebugString(szMsg);
	}
	else
	{
		(VOID)SetFilePointer(hFile, 0, 0, FILE_END);
		std::string s;
		s.append(ToAnsiStr(GetCurrentTimeStr().c_str()));
		s.append(" ");
		s.append(ToAnsiStr(szMsg));
		s.append("");
		DWORD dwWritten;
		(VOID)WriteFile(hFile, s.c_str(), (DWORD)s.size(), &dwWritten, 0);
		CloseHandle(hFile);
	}
}