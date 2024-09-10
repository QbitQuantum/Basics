int conprintf(const char* fmt, ...)
{
#ifdef WIN32
	char s[1024];
	va_list list;

	va_start(list, fmt);
	vsprintf(s,fmt, list);
	va_end(list);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if(handle == INVALID_HANDLE_VALUE)
		return 0;

	DWORD written = 0;
	WriteConsoleA(handle, s, strlen(s), &written, 0);
	FlushFileBuffers(handle);

	return written;
#else
	va_list list;
	va_start(list, fmt);
	int ret = vsprintf(stderr,fmt,list);
	va_end(list);
	return ret;
#endif
}