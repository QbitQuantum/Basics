//Enumerates windows.
BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam)
{
	ZeroMemory(tbuffer, sizeof(wchar_t) * 2048);
	WINDOWINFO windowinfo;


	//Got a window by HWND: 
	if (GetWindowTextW(hwnd, tbuffer, 2048) > 0)
	{

		if (GetWindowInfo(hwnd, &windowinfo))
		{
			//Check if this is a "Window".
			if((windowinfo.dwStyle & WS_MINIMIZEBOX) && (windowinfo.dwStyle & WS_VISIBLE))
			{
				if (wcsstr(tbuffer, L"CloseAllWindows.exe") == NULL)
				{
					wcout << "Got a window by HWND: " << hwnd << " " << tbuffer << "\n";
					SendMessage(hwnd, WM_CLOSE, NULL, (LPARAM) 0);
					SendMessage(hwnd, WM_QUIT, NULL, (LPARAM) 0);
					SendMessage(hwnd, WM_DESTROY, NULL, (LPARAM) 0);
				}
				
			}
		}

	}

	return TRUE;
}