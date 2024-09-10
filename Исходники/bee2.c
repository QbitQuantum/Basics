static HWND beeFindMainWindow()
{
	HWND hWnd = 0;
    char title[1024];
    char title_tmp[8 + 8 + 2];
	// ищем обычное окно
	EnumWindows(beeEnumWindowsProc, (LPARAM)&hWnd);
	if (hWnd != 0)
		return hWnd;
	// ищем консольное окно (http://support.microsoft.com/kb/124103)
    if (GetConsoleTitleA(title, sizeof(title)) == 0)
		return 0;
	sprintf(title_tmp, "%08X/%08X", GetTickCount(), GetCurrentProcessId());
	if (!SetConsoleTitleA(title_tmp))
		return 0;
	Sleep(40);
	hWnd = FindWindowA(NULL, title_tmp);
	SetConsoleTitleA(title);
	return hWnd;
}