COORD MyGetLargestConsoleWindowSize(HANDLE hConsoleOutput)
{
	// Fails in Wine
	COORD crMax = GetLargestConsoleWindowSize(hConsoleOutput);
	DWORD dwErr = (crMax.X && crMax.Y) ? 0 : GetLastError();
	UNREFERENCED_PARAMETER(dwErr);

	// Wine BUG
	//if (!crMax.X || !crMax.Y)
	if ((crMax.X == 80 && crMax.Y == 24) && IsWine())
	{
		crMax.X = 999;
		crMax.Y = 999;
	}
	#ifdef _DEBUG
	else if (IsWin10())
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi = {};
		GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);

		// Windows 10 Preview had a new bug in GetLargestConsoleWindowSize
		_ASSERTE((crMax.X > (csbi.srWindow.Right-csbi.srWindow.Left+1)) && (crMax.Y > (csbi.srWindow.Bottom-csbi.srWindow.Top+1)));
		//crMax.X = max(crMax.X,555);
		//crMax.Y = max(crMax.Y,555);
	}
	#endif

	return crMax;
}