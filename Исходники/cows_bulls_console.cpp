// draw the field
// argument - width and height of the field
// resizes console window for no reason
// prints instructions how to interact
void drawTable(COORD size)
{
	DWORD cWritten;
	HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(con, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(con, &cursorInfo);
	
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 480, TRUE);

	FillConsoleOutputCharacter(con, '+', 1, { 0, 3 }, &cWritten);
	FillConsoleOutputCharacter(con, '+', 1, { size.X, 3 }, &cWritten);
	FillConsoleOutputCharacter(con, '-', size.X - 1, { 1, 3 }, &cWritten);
	FillConsoleOutputCharacter(con, '_', 4, { 3, 1 }, &cWritten);

	for (int i = 0; i < size.Y; ++i)
	{
		if (i != 3)
		{
			FillConsoleOutputCharacter(con, '|', 1, { 0, i }, &cWritten);
			FillConsoleOutputCharacter(con, '|', 1, { size.X, i }, &cWritten);
		}
	}

	print({size.X + 2, 1}, "COWS AND BULLS");
	print({size.X + 2, 3}, "0-9 - add digit");
	print({size.X + 2, 4}, "Backspace - remove last digit");
	print({size.X + 2, 5}, "Enter - confirm");
	print({size.X + 2, 6}, "Esc - quit");
}