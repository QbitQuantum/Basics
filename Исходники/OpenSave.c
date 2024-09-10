UINT FmtErrorMsg(HWND hwnd, DWORD dwMsgBoxType, DWORD dwError, TCHAR *szFmt, ...)
{
	TCHAR *lpMsgBuf;
	TCHAR *ptr;
	UINT   msgboxerr;
	va_list varg;

	va_start(varg, szFmt);

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		(LPTSTR) &lpMsgBuf, 0, NULL 
		);

	ptr = LocalAlloc(LPTR, LocalSize(lpMsgBuf) + 1000 * sizeof(TCHAR));
	_vstprintf(ptr, szFmt, varg);
	_tcscat(ptr, lpMsgBuf);

	msgboxerr = MessageBox(hwnd, ptr, APP_TITLE, dwMsgBoxType);
	
	LocalFree( lpMsgBuf );
	LocalFree( ptr );
	va_end(varg);

	return msgboxerr;
}