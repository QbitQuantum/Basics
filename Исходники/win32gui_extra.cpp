void scaleresource_getdpimult (double *dpixmp, double *dpiymp, int *dpixp, int *dpiyp)
{
	GETDPIFORMONITOR pGetDpiForMonitor;
	POINT pt = { 32000, 32000 };
	HMONITOR mon = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);

	*dpixmp = 1.0;
	*dpiymp = 1.0;
	*dpixp = 0;
	*dpiyp = 0;
	pGetDpiForMonitor = (GETDPIFORMONITOR)GetProcAddress(GetModuleHandle(_T("Shcore.dll")), "GetDpiForMonitor");
	if (pGetDpiForMonitor) {
		UINT dpix, dpiy;
		if (SUCCEEDED(pGetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &dpix, &dpiy))) {
			if (dpix > 96)
				*dpixmp = (double)dpix / 96.0;
			if (dpiy > 96)
				*dpiymp = (double)dpiy / 96.0;
			*dpixp = dpix;
			*dpiyp = dpiy;
		}
	}
}