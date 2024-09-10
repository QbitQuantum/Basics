void clrscr() {
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD coordScreen = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hConsole, &csbi );
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD cCharsWritten;
	FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );
	GetConsoleScreenBufferInfo( hConsole, &csbi );
	FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );
	SetConsoleCursorPosition( hConsole, coordScreen );
}