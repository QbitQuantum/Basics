void CorrectConsolePos(HWND hConWnd)
{
	RECT rcNew = {};
	if (GetWindowRect(hConWnd, &rcNew))
	{
		HMONITOR hMon = MonitorFromWindow(hConWnd, MONITOR_DEFAULTTOPRIMARY);
		MONITORINFO mi = {sizeof(mi)};
		//int nMaxX = 0, nMaxY = 0;
		if (GetMonitorInfo(hMon, &mi))
		{
			int newW = (rcNew.right-rcNew.left), newH = (rcNew.bottom-rcNew.top);
			int newX = rcNew.left, newY = rcNew.top;

			if (newX < mi.rcWork.left)
				newX = mi.rcWork.left;
			else if (rcNew.right > mi.rcWork.right)
				newX = max(mi.rcWork.left,(mi.rcWork.right-newW));

			if (newY < mi.rcWork.top)
				newY = mi.rcWork.top;
			else if (rcNew.bottom > mi.rcWork.bottom)
				newY = max(mi.rcWork.top,(mi.rcWork.bottom-newH));

			if ((newX != rcNew.left) || (newY != rcNew.top))
				SetWindowPos(hConWnd, HWND_TOP, newX, newY,0,0, SWP_NOSIZE);
		}
	}
}