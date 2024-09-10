int IsWindowMaximized(HWND hWnd) {
	RECT rect;
	if (GetWindowRect(hWnd, &rect)) {
		POINT p;
		p.x = rect.left;
		p.y = rect.top;
		MONITORINFO info;
		memset(&info, 0, sizeof(info));
		info.cbSize = sizeof(info);
		HMONITOR hMonitor;
		if ((hMonitor = MonitorFromPoint(p, MONITOR_DEFAULTTOPRIMARY)) &&
			GetMonitorInfo(hMonitor, &info) &&
			memcmp(&info.rcMonitor, &rect, sizeof(rect)) == 0) {
			return 1;
		}
	}
	return 0;
}