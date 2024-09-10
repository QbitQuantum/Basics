HMONITOR CMonitorInfo::GetFullScreenRect(HWND hWnd, CRect& rc)
{
	CRect	wr;
	::GetWindowRect(hWnd, wr);
	// try to get screen size from monitor API in case we're dual-monitor
	MONITORINFO	mi;
	mi.cbSize = sizeof(mi);
	HMONITOR	hMon = MonitorFromRect(wr, MONITOR_DEFAULTTONEAREST);
	if (hMon != NULL && GetMonitorInfo(hMon, &mi)) {
		rc = mi.rcMonitor;
	} else {	// fall back to older API
		rc = CRect(0, 0, GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN));
	}
	return(hMon);
}