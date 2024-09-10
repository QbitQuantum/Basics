FREObject __cdecl AmbireCaptureGetScreenSize(FREContext ctx, void * functionData, uint32_t argc, FREObject argv[]) {
	POINT pt = { 0 };
	HMONITOR hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO mi = { 0 };
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonitor, &mi);
	int W = mi.rcMonitor.right - mi.rcMonitor.left;
	int H = mi.rcMonitor.bottom - mi.rcMonitor.top;
	int N = W | (H << 16);
	FREObject rv = 0;
	FRENewObjectFromInt32(N, &rv);
	return rv;
}