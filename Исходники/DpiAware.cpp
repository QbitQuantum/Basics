void CDpiAware::GetCenteredRect(HWND hWnd, RECT& rcCentered, HMONITOR hDefault /*= NULL*/)
{
	bool lbCentered = false;
	HMONITOR hMon;

	if (hWnd)
		hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
	else
		hMon = MonitorFromRect(&rcCentered, MONITOR_DEFAULTTONEAREST);

	MONITORINFO mi = {};
	GetNearestMonitorInfo(&mi, hDefault, hWnd ? NULL : &rcCentered, hWnd);

	int iWidth  = rcCentered.right - rcCentered.left;
	int iHeight = rcCentered.bottom - rcCentered.top;

	RECT rcNew = {
			(mi.rcWork.left + mi.rcWork.right - iWidth)/2,
			(mi.rcWork.top + mi.rcWork.bottom - iHeight)/2
	};
	rcNew.right = rcNew.left + iWidth;
	rcNew.bottom = rcNew.top + iHeight;

	rcCentered = rcNew;
}