void SFDebugConsole::MoveConsole(int x, int y)
{
	Cons_Handle = FindWindow(NULL, CName);

	if(!Cons_Handle == NULL)
		MoveWindow(Cons_Handle, 500, 500, 200, 100, true);
	else
	{
		Cons_Handler = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT size = { 0, 0, 200, 100 };
		SetConsoleWindowInfo(Cons_Handler, true, &size);
		COORD coord = { x, y };
		SetConsoleCursorPosition(Cons_Handler, coord);
	}
}