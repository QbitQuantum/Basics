void TopWindow::SyncCaption()
{
	GuiLock __;
	LLOG("TopWindow::SyncCaption " << UPP::Name(this));
	if(fullscreen)
		return;
	HWND hwnd = GetHWND();
	if(hwnd) {
		style = ::GetWindowLong(hwnd, GWL_STYLE);
		exstyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);
	}
	style &= ~(WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU|WS_POPUP|WS_DLGFRAME);
	exstyle &= ~(WS_EX_TOOLWINDOW|WS_EX_DLGMODALFRAME);
	style |= WS_CAPTION;
	if(hasdhctrl)
		style |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	if(minimizebox)
		style |= WS_MINIMIZEBOX;
	if(maximizebox)
		style |= WS_MAXIMIZEBOX;
	if(sizeable)
		style |= WS_THICKFRAME;
#ifndef PLATFORM_WINCE
	if(frameless)
		style = (style & ~WS_CAPTION) | WS_POPUP;
	else
	if(IsNull(icon) && !maximizebox && !minimizebox || noclosebox) {
		style |= WS_POPUPWINDOW|WS_DLGFRAME;
		exstyle |= WS_EX_DLGMODALFRAME;
		if(noclosebox)
			style &= ~WS_SYSMENU;
	}
	else
#endif
		style |= WS_SYSMENU;
	if(tool)
		exstyle |= WS_EX_TOOLWINDOW;
	if(fullscreen)
		style = WS_POPUP;
	if(hwnd) {
		::SetWindowLong(hwnd, GWL_STYLE, style);
		::SetWindowLong(hwnd, GWL_EXSTYLE, exstyle);
		SyncTitle();
		if(urgent) {
			if(IsForeground()) urgent = false;
			FLASHWINFO fi;
			memset(&fi, 0, sizeof(fi));
			fi.cbSize = sizeof(fi);
			fi.hwnd = hwnd;
			fi.dwFlags = urgent ? FLASHW_TIMER|FLASHW_ALL : FLASHW_STOP;
			FlashWindowEx(&fi);
		}
	}
	DeleteIco();
#ifndef PLATFORM_WINCE //TODO!!!
	if(hwnd) {
		::SendMessage(hwnd, WM_SETICON, false, (LPARAM)(ico = SystemDraw::IconWin32(icon)));
		::SendMessage(hwnd, WM_SETICON, true, (LPARAM)(lico = SystemDraw::IconWin32(largeicon)));
	}
#endif
}