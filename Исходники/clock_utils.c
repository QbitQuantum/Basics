void Clock_PositionWindow(HWND hwnd, int padding) {
	POINT cursor_pos;
	MONITORINFO moni = {sizeof(moni)};
	int wProp, hProp;
	HWND hwnd_clock;
	
	GetWindowRect(hwnd, &moni.rcWork); // Options dialog dimensions
	wProp = moni.rcWork.right-moni.rcWork.left;  //----------+++--> Width
	hProp = moni.rcWork.bottom-moni.rcWork.top; //----------+++--> Height
	
	GetCursorPos(&cursor_pos);
	GetMonitorInfo(MonitorFromPoint(cursor_pos,MONITOR_DEFAULTTONEAREST),&moni);
	
	if(moni.rcWork.top!=moni.rcMonitor.top || moni.rcWork.bottom!=moni.rcMonitor.bottom) { // taskbar is horizontal
		moni.rcMonitor.left=moni.rcWork.right-wProp-padding;
		if(moni.rcWork.top!=moni.rcMonitor.top) // top
			moni.rcMonitor.top=moni.rcWork.top+padding;
		else // bottom
			moni.rcMonitor.top=moni.rcWork.bottom-hProp-padding;
		// center small windows within clock dimension when possible
		hwnd_clock = gs_hwndClock;
		if(!hwnd_clock)
			hwnd_clock = FindClock();
		if(hwnd_clock) {
			GetClientRect(hwnd_clock, &moni.rcWork);
			if(wProp < moni.rcWork.right)
				moni.rcMonitor.left -= ((moni.rcWork.right - wProp)>>1) + api.desktop_button_size;
		}
	}else if(moni.rcWork.left!=moni.rcMonitor.left || moni.rcWork.right!=moni.rcMonitor.right){ // vertical