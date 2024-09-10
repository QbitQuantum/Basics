int myPrintfToLog(const char* format, ...)
{
	if (g_logFile == INVALID_HANDLE_VALUE)
		return 1;

	va_list arglist;
	va_start(arglist, format);

	char buffer[2048];
	int len = _vsnprintf_s(buffer, 2048, _TRUNCATE, format, arglist);
	if (len <= 0)
		return 0;

	DWORD cbWritten;
	WriteFile(g_logFile, buffer, len, &cbWritten, NULL);
	return 1;
}