void ViewerWindow::setSizeFullScreenWindow()
{
	// Save position of window.
	GetWindowPlacement(m_hWnd, &m_workArea);

	// Get size of desktop.
	HMONITOR hmon = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);

	RECT fullScreenWindowsRect;
	if (!!GetMonitorInfo(hmon, &mi)) {
		fullScreenWindowsRect = mi.rcMonitor;
	}
	else {
		m_logWriter.warning(_T("Get monitor info is failed. Use second method (no multi-screen)."));
		GetWindowRect(GetDesktopWindow(), &fullScreenWindowsRect);
	}
	Rect fullScreenRect;
	fullScreenRect.fromWindowsRect(&fullScreenWindowsRect);
	m_logWriter.detail(_T("full screen window rect: %d, %d; %d, %d"),
		fullScreenRect.left, fullScreenRect.top,
		fullScreenRect.getWidth(), fullScreenRect.getHeight());

	setStyle((getStyle() | WS_MAXIMIZE) & ~(WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_MAXIMIZEBOX));
	setExStyle(getExStyle() | WS_EX_TOPMOST);

	SetWindowPos(m_hWnd, 0,
		fullScreenRect.left, fullScreenRect.top,
		fullScreenRect.getWidth(), fullScreenRect.getHeight(),
		SWP_SHOWWINDOW);
}