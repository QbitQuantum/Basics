static DWORD WINAPI _stdinthreadproc(LPVOID lpParameter)
{
#define STDIN_WCHAR_BUF_SIZE (1024 * 2)
#define STDIN_CCHAR_BUF_SIZE (1024 * 4)
	WCHAR wbuf[STDIN_WCHAR_BUF_SIZE];
	char cbuf[STDIN_CCHAR_BUF_SIZE];
	HANDLE hconsolein = GetStdHandle(STD_INPUT_HANDLE);
	UINT oldcp = GetConsoleCP();
	SetConsoleCP(CP_UTF8);
	(void)lpParameter;
	do
	{
		DWORD cmode;
		if(GetConsoleMode(hconsolein, &cmode))
		{
			SetConsoleMode(hconsolein, cmode | ENABLE_LINE_INPUT);
		}
	}
	while(0);
	while(1)
	{
		DWORD read;
		int x;
		if(!ReadConsoleW(hconsolein, wbuf, STDIN_WCHAR_BUF_SIZE, &read, NULL))
			break;
		cbuf[0] = 0;
		_widetoutf8(wbuf, read, cbuf, STDIN_CCHAR_BUF_SIZE);
		_fix_stdinsockaddr();
		x = bind(_stdinsock, (struct sockaddr*)&_stdinsockaddr, sizeof(struct sockaddr_in));
		_fix_stdinsockaddr();
		x = sendto(_stdinsock, cbuf, strlen(cbuf), 0, (struct sockaddr*)&_stdinsockaddr, sizeof(struct sockaddr_in));
	}
	SetConsoleCP(oldcp);
	CloseHandle(hconsolein);
	return 0;
}