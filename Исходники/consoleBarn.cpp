/////////////////////////////////////////////////
// cursorOff(): cursor invisible.
void cursorOff()
{
	CONSOLE_CURSOR_INFO cursorInfo;   
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 

	GetConsoleCursorInfo( hStdOut, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo( hStdOut, &cursorInfo);
}