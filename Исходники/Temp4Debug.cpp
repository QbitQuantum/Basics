void wrt_Wchr(WCHAR wc[]){
	IS_HANDLE_NULL;
	DWORD ws;
	WriteConsoleW(hConsole,wc,wcslen(wc),&ws,NULL);
	WCHAR enter[]=L"\r\n";
	WriteConsoleW(hConsole,enter,wcslen(enter),&ws,NULL);
}