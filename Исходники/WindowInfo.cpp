static BOOL CALLBACK EnumWindowsProc (HWND win, LPARAM user){
	EnumerateWindowSettings * settings = (EnumerateWindowSettings*) (user);

	DWORD process;
	GetWindowThreadProcessId (win, &process);

	if (settings->pid && settings->pid != process) {
		return TRUE; // skipping
	}

	WINDOWINFO info;
	GetWindowInfo(win, &info);

	char title [512] = "";
	GetWindowText (win, title, (sizeof title) - 1);

	bool isVisible = (info.dwStyle & WS_VISIBLE) != 0;
	// bool isPopup   = info.dwStyle & WS_POPUP;

	if (isVisible) {
		WindowInfo dst;
		dst.title = title;
		dst.id    = (int64_t) win; // At least in Win7 Window Handles seem unique and could also be interpreted as IDs
		dst.pid   = process;
		dst.area  = dz::Rect(info.rcWindow.left, info.rcWindow.top, info.rcWindow.right - info.rcWindow.left, info.rcWindow.bottom - info.rcWindow.top);
		settings->destination->push_back (dst);
	}
	return TRUE; // continue enumeration
}