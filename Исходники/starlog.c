static void
starlog_log(Starlog *s)
{
	const size_t MAX_BYTES = 1024;
	unsigned short *log = NULL;
	DWORD textlen, loglen;
	SYSTEMTIME t;

	GetLocalTime(&t);
	textlen = GetWindowTextLengthW(s->edit_log);
	if(!textlen) {
		return;
	}
	log = HeapAlloc(GetProcessHeap(), 0, sizeof(char)*MAX_BYTES);
	loglen = wsprintfW(log, L"~~~ %02d.%02d.%04d %02d:%02d:%02d ~~~\r\n",
		t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);
	loglen += GetWindowTextW(s->edit_log, &log[loglen],
		sizeof(short)*(MAX_BYTES-loglen));
	log[loglen] = '\r';
	log[loglen+1] = '\n';
	log[loglen+2] = 0;
	if(loglen) {
		HANDLE fd = CreateFile(".\\star.log",
			FILE_APPEND_DATA, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(fd==INVALID_HANDLE_VALUE) {
			return;
		}
		DWORD n = lstrlenW(log);
		WriteFile(fd, log, n*sizeof(short), &n, 0);
		CloseHandle(fd);
	}
	HeapFree(GetProcessHeap(), 0, log);
}