void UIMoveStatusWindow(HWND hUIWnd, int X, int Y)
{   
	
	/*if (!IsWindow(uiStatus.hWnd))
		UICreateStatusWindow(hUIWnd);*/

	if (IsWindow(uiStatus.hWnd))
	{
		POINT pt;
		RECT screenrc;
		SIZE sz;

		sz.cx = 0;
		sz.cy = 0;
		uiStatus.pt.x = (X>0)?X : 0; 
		uiStatus.pt.y = (Y>0)?Y : 0;
		sz.cx = uiStatus.sz.cx;
		sz.cy = uiStatus.sz.cy;
		pt.x = uiStatus.pt.x;
		pt.y = uiStatus.pt.y;
		
		MONITORINFO mi;
		mi.cbSize=sizeof(MONITORINFO); 
		
		GetMonitorInfo(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
		if( (pt.x + sz.cx) > mi.rcMonitor.right )
			pt.x = mi.rcMonitor.right - 200;
			if( (pt.y + sz.cy) > mi.rcMonitor.bottom )
			pt.y = mi.rcMonitor.bottom - 50;		

/*		SystemParametersInfo(SPI_GETWORKAREA, 0, &screenrc, 0);

		if( (pt.x + sz.cx) > screenrc.right )
			pt.x = screenrc.right - 200;
		if( (pt.y + sz.cy) > screenrc.bottom )
			pt.y = screenrc.bottom - 50;		
*/
		_MoveStatusPage(pt.x, pt.y);
	}
	
}