void WinConsoleHelper::SetConsoleSize(int x, int y)
{
	UpdateCSBI();
	COORD windowSize = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
	if (windowSize.X > x || windowSize.Y > y)
	{
		SMALL_RECT info =
		{
			0,
			0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		SetConsoleWindowInfo(hStdOut, TRUE, &info);
	}
	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	SetConsoleScreenBufferSize(hStdOut, { (SHORT)x, (SHORT)y });
	SetConsoleWindowInfo(hStdOut, TRUE, &info);
}