void main()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	CONSOLE_CURSOR_INFO ci = {};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &csbi);
	BOOL lb1 = GetConsoleCursorInfo(hOut, &ci);
	printf("Cursor height before=%i%% (rc=%u)\r\n", ci.dwSize, lb1);
	SetConsoleTitle(_T("Increasing ScreenBufferSize"));
	Sleep(2500);
	csbi.dwSize.X++;
	SetConsoleScreenBufferSize(hOut, csbi.dwSize);
	SetConsoleTitle(_T("Quering current cursor information"));
	Sleep(2500);
	BOOL lb2 = GetConsoleCursorInfo(hOut, &ci);
	printf("Cursor height after=%i%% (rc=%u)\r\n", ci.dwSize, lb2);
}