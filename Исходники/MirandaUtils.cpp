//http://www.shloemi.com/2012/09/solved-setforegroundwindow-win32-api-not-always-works/
void MirandaUtils::ForceForegroundWindow(HWND hWnd)
{
	DWORD foreThread = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
	DWORD appThread = GetCurrentThreadId();

	if (foreThread != appThread) {
		AttachThreadInput(foreThread, appThread, true);
		BringWindowToTop(hWnd);
		ShowWindow(hWnd, SW_SHOW);
		AttachThreadInput(foreThread, appThread, false);
	} else {
		BringWindowToTop(hWnd);
		ShowWindow(hWnd, SW_SHOW);
	}
}