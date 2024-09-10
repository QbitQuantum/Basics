void debug(const wchar_t* format, ...)
{
	wchar_t tmpbuf[128];
	time_t rawtime;
	struct tm timeinfo;
	va_list valist;

	if (!DEBUG && EXECUTE_FROM_GPE)
		return;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	wcsftime(tmpbuf, 128, L"%Y-%m-%d %H:%M:%S ", &timeinfo);

	va_start(valist, format);
	if (!EXECUTE_FROM_GPE){
		fwprintf_s(stdout, L"%ls", tmpbuf);
		vfwprintf_s(stdout, format, valist);
	}
	if (debugfh != NULL && DEBUG) {
		fwprintf_s(debugfh, L"%ls", tmpbuf);
		vfwprintf_s(debugfh, format, valist);
		fflush(debugfh);
	}
	va_end(valist);
}