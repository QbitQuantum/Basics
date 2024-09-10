void WindowsConsole::setDimensions(short w, short h) {
	HANDLE hCon = GetStdHandle( STD_OUTPUT_HANDLE );
	SMALL_RECT size;
	COORD b_size;

	size.Left = 0;
	size.Top = 0;
	size.Right = w - 1;
	size.Bottom = h - 1;
	b_size.X = w;
	b_size.Y = h;

	SetConsoleWindowInfo( hCon , true , & size );
	SetConsoleScreenBufferSize( hCon , b_size );
}