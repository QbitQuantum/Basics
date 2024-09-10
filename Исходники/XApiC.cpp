const char* X_GetLastError()
{
#if defined WINDOWS || WIN32
    char szBuf[256] = {0};
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf,
		0, NULL);
	return (const char*)lpMsgBuf;
#else
    extern int errno;
    errno = 0;
    return dlerror();
#endif
}