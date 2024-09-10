// Startup monitor ay be specified from command line
// Example: ConEmu.exe -Monitor <1 | x10001 | "\\.\DISPLAY1">
HMONITOR MonitorFromParam(LPCWSTR asMonitor)
{
	if (!asMonitor || !*asMonitor)
		return NULL;

	wchar_t* pszEnd;
	HMONITOR hMon = NULL;
	MONITORINFO mi = {sizeof(mi)};

	if (asMonitor[0] == L'x' || asMonitor[0] == L'X')
		hMon = (HMONITOR)(DWORD_PTR)wcstoul(asMonitor+1, &pszEnd, 16);
	else if (asMonitor[0] == L'0' && (asMonitor[1] == L'x' || asMonitor[1] == L'X'))
		hMon = (HMONITOR)(DWORD_PTR)wcstoul(asMonitor+2, &pszEnd, 16);
	// HMONITOR was already specified?
	if (GetMonitorInfo(hMon, &mi))
		return hMon;

	// Monitor name or index?
	struct impl {
		HMONITOR hMon;
		LPCWSTR pszName;
		LONG nIndex;

		static BOOL CALLBACK FindMonitor(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
		{
			impl* p = (impl*)dwData;
			MONITORINFOEX mi; ZeroStruct(mi); mi.cbSize = sizeof(mi);
			if (GetMonitorInfo(hMonitor, &mi))
			{
				// Get monitor by name?
				if (p->pszName && (0 == lstrcmpi(p->pszName, mi.szDevice)))
				{
					p->hMon = hMonitor;
					return FALSE; // Stop
				}
				// Get monitor by index
				if ((--p->nIndex) <= 0)
				{
					p->hMon = hMonitor;
					return FALSE; // Stop
				}
			}
			return TRUE; // Continue enum
		};
	} Impl = {};

	if (isDigit(asMonitor[0]))
		Impl.nIndex = wcstoul(asMonitor, &pszEnd, 10);
	else
		Impl.pszName = asMonitor;
	EnumDisplayMonitors(NULL, NULL, impl::FindMonitor, (LPARAM)&Impl);

	// Return what found or not
	return Impl.hMon;
}