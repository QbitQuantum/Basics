static void
dlfailure(void)
{
#ifdef _WIN32
    LPSTR msg;
    DWORD dwBufferLength;
    DWORD dwLastError = GetLastError();
    DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
	    FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM;

    if ((dwBufferLength = FormatMessageA(dwFormatFlags, NULL, dwLastError,
		    0, (LPSTR) &msg, 0, NULL))) {
	msg[dwBufferLength] = '\0';
	fprintf(stderr, "Error: %s", msg);
	LocalFree(msg);
    }
#else
    fprintf(stderr, "Error: %s", dlerror());
#endif	/*_WIN32*/

    exit(2);
}