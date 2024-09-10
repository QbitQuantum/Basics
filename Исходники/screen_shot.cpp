BOOL CALLBACK EnumDesktopWinProc(HWND hwnd, LPARAM lParam)
{
	if (hwnd && IsWindowVisible(hwnd)/* && IsWindowEnabled(hwnd)*/)
	{
		if (0x000902F4 == (int)hwnd)
		{
			int a = 2;
		}
		RECT rect = {0};
		::GetWindowRect(hwnd, &rect);
		//if (rect.left > 0 && rect.top > 0 && rect.right > 0 && rect.bottom > 0)
		TCHAR lpWinTitle[256],lpClassName[256]; 
		::GetWindowTextW(hwnd,lpWinTitle,256-1); //获得窗口caption
		::GetClassNameW(hwnd,lpClassName,256-1); //获得窗口类名
		if (*lpWinTitle && *lpClassName) 
		{
			g_winRects.push_back(rect);
		}

		EnumChildWindows(hwnd, EnumChildWinProc, NULL);
		return TRUE;
	}

	return TRUE;
}