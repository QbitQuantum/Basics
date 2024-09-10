void OutputDebugPrint(LPCWSTR szFormat, ...)
{
	WCHAR szBuffer[1024];

	va_list ap;
	va_start(ap, szFormat);
	
	StringCbVPrintfW(szBuffer, sizeof(szBuffer), szFormat, ap);

	va_end(ap);

	OutputDebugStringW(szBuffer);
}