void Logger::PlatformLog(eLogLevel ll, const char16* text)
{
	wprintf(L"%s", text);
}