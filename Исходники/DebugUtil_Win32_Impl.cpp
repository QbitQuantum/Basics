void DebugUtil_Win32_Impl::Error(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[MAX_BUFFER_SIZE];
	vsprintf_s(szOut, MAX_BUFFER_SIZE, format, marker);
	va_end(marker);

	OutputLog("ERROR: ", szOut);
}