void muiWindow::BringWindowToForeground()
{
	// Windows 98 and later very much restricts what SetForegroundWindow() does - in most cases it just flashes the taskbar.
	// Here we will force it to actually brind the window to the foreground & get the keyboard focus
	HWND hwndForegroundWindow = GetForegroundWindow();
	DWORD dwForegroundThreadId = GetWindowThreadProcessId(hwndForegroundWindow, NULL); 
	DWORD dwThisThreadId = GetWindowThreadProcessId(hwnd, NULL); 

	bool bAttachedToFgThread = (dwThisThreadId != dwForegroundThreadId) && AttachThreadInput(dwThisThreadId, dwForegroundThreadId, TRUE);
	
	SetForegroundWindow(hwnd); 
	//BringWindowToTop(hwnd);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
    
	if (bAttachedToFgThread) AttachThreadInput(dwThisThreadId, dwForegroundThreadId, FALSE); 
}