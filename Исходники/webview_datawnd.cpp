void ValidatePosition(HWND hwndDlg)
{
	RECT r;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);

	POINT pt = { 0, 0 };
	HMONITOR hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST); // always 

	MONITORINFO monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFO);
	if (GetMonitorInfo(hMonitor, &monitorInfo))
		memcpy(&r, &monitorInfo.rcMonitor, sizeof(RECT));

	// /window going off right of screen*
	if (Xposition + WindowWidth >= r.right)
		Xposition = r.right - WindowWidth;

	// window going off bottom of screen
	if (Yposition + WindowHeight >= r.bottom)
		Yposition = r.bottom - WindowHeight;

	// window going off left of screen
	if (Xposition >= r.right)
		Xposition = 0;
}