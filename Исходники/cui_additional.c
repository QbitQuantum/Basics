void changeSize(){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	BOOL ok;
	coord.X = WINDOW_WIDTH;
	coord.Y = WINDOW_HEIGHT + 1;
	ok = SetConsoleScreenBufferSize(hStdout, coord);
	SMALL_RECT test = { 0, 0, coord.X - 1, coord.Y - 1 };
	SetConsoleWindowInfo(hStdout, ok, &test);
}