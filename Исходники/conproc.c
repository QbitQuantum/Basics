BOOL SetConsoleCXCY(HANDLE hStdout, int cx, int cy)
{
	CONSOLE_SCREEN_BUFFER_INFO	info;
	COORD						coordMax;
 
	coordMax = GetLargestConsoleWindowSize(hStdout);

	if (cy > coordMax.Y)
		cy = coordMax.Y;

	if (cx > coordMax.X)
		cx = coordMax.X;
 
	if (!GetConsoleScreenBufferInfo(hStdout, &info))
		return false;
 
// height
    info.srWindow.Left = 0;         
    info.srWindow.Right = info.dwSize.X - 1;                
    info.srWindow.Top = 0;
    info.srWindow.Bottom = cy - 1;          
 
	if (cy < info.dwSize.Y)
	{
		if (!SetConsoleWindowInfo(hStdout, true, &info.srWindow))
			return false;
 
		info.dwSize.Y = cy;
 
		if (!SetConsoleScreenBufferSize(hStdout, info.dwSize))
			return false;
    }
    else if (cy > info.dwSize.Y)
    {
		info.dwSize.Y = cy;
 
		if (!SetConsoleScreenBufferSize(hStdout, info.dwSize))
			return false;
 
		if (!SetConsoleWindowInfo(hStdout, true, &info.srWindow))
			return false;
    }
 
	if (!GetConsoleScreenBufferInfo(hStdout, &info))
		return false;
 
// width
	info.srWindow.Left = 0;         
	info.srWindow.Right = cx - 1;
	info.srWindow.Top = 0;
	info.srWindow.Bottom = info.dwSize.Y - 1;               
 
	if (cx < info.dwSize.X)
	{
		if (!SetConsoleWindowInfo(hStdout, true, &info.srWindow))
			return false;
 
		info.dwSize.X = cx;
    
		if (!SetConsoleScreenBufferSize(hStdout, info.dwSize))
			return false;
	}
	else if (cx > info.dwSize.X)
	{
		info.dwSize.X = cx;
 
		if (!SetConsoleScreenBufferSize(hStdout, info.dwSize))
			return false;
 
		if (!SetConsoleWindowInfo(hStdout, true, &info.srWindow))
			return false;
	}
 
	return true;
}