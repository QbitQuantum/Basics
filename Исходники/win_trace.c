void win_traceA(const char *pszFmt, ...){
	CHAR tchbuf[1024] = {'$',0};
	va_list argList = NULL;
	va_start(argList, pszFmt);
	wvsprintfA(&tchbuf[1], pszFmt, argList);
	va_end(argList);
	lstrcatA(tchbuf, "\r\n");
	if(IsDebuggerPresent()){
		OutputDebugStringA(tchbuf);
	}else{
		DWORD dwWrt;
		WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), tchbuf, lstrlenA(tchbuf), &dwWrt, NULL);
	}
}