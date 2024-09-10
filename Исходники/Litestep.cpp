void LogInternal(int nLevel, ULONGLONG elapsed, LPCTSTR pszMessage)
{
	// Add timestamp
	WCHAR buffer[128];
	size_t len = _snwprintf_s(buffer, _TRUNCATE, L"%02llu:%02llu:%02llu.%03llu", elapsed / (1000 * 60 * 60), (elapsed / (1000 * 60)) % 60, (elapsed / 1000) % 60, elapsed % 1000);

	Rainmeter->AddAboutLogInfo(nLevel, buffer, pszMessage);

#ifndef _DEBUG
	if (!Rainmeter->GetLogging()) return;
#endif

	std::wstring message;
	switch (nLevel)
	{
	case LOG_ERROR:
		message = L"ERRO";
		break;

	case LOG_WARNING:
		message = L"WARN";
		break;

	case LOG_NOTICE:
		message = L"NOTE";
		break;

	case LOG_DEBUG:
		message = L"DBUG";
		break;
	}
	
	message += L" (";
	message.append(buffer, len);
	message += L") ";
	message += pszMessage;
	message += L'\n';
	
#ifdef _DEBUG
	_RPT0(_CRT_WARN, ConvertToAscii(message.c_str()).c_str());
	if (!Rainmeter->GetLogging()) return;
#endif

	const WCHAR* logFile = Rainmeter->GetLogFile().c_str();
	if (_waccess(logFile, 0) == -1)
	{
		// Disable logging if the file was deleted manually
		Rainmeter->StopLogging();
	}
	else
	{
		FILE* file = _wfopen(logFile, L"a+, ccs=UTF-8");
		if (file)
		{
			fputws(message.c_str(), file);
			fclose(file);
		}
	}
}