// Поставить хук в процесс шелла (explorer.exe)
bool CDefaultTerminal::CheckShellWindow()
{
	bool bHooked = false;
	HWND hDesktop = GetDesktopWindow(); //csrss.exe on Windows 8
	HWND hShell = GetShellWindow();
	HWND hTrayWnd = FindWindowEx(NULL, NULL, L"Shell_TrayWnd", NULL);
	DWORD nDesktopPID = 0, nShellPID = 0, nTrayPID = 0;

	if (!bHooked && hShell)
	{
		if (GetWindowThreadProcessId(hShell, &nShellPID) && nShellPID)
		{
			bHooked = CheckForeground(hShell, nShellPID, false);
		}
	}

	if (!bHooked && hTrayWnd)
	{
		if (GetWindowThreadProcessId(hTrayWnd, &nTrayPID) && nTrayPID
			&& (nTrayPID != nShellPID))
		{
			bHooked = CheckForeground(hTrayWnd, nTrayPID, false);
		}
	}

	if (!bHooked && hDesktop)
	{
		if (GetWindowThreadProcessId(hDesktop, &nDesktopPID) && nDesktopPID
			&& (nDesktopPID != nTrayPID) && (nDesktopPID != nShellPID))
		{
			bHooked = CheckForeground(hDesktop, nDesktopPID, false);
		}
	}

	return bHooked;
}