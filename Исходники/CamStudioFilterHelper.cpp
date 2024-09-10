void AddMouse(HDC hMemDC, LPRECT lpRect, HDC hScrDC, HWND hwnd) {
	POINT p;

	// GetCursorPos(&p); // get current x, y 0.008 ms
	
	CURSORINFO globalCursor;
	globalCursor.cbSize = sizeof(CURSORINFO); // could cache I guess...
	::GetCursorInfo(&globalCursor);
	HCURSOR hcur = globalCursor.hCursor;

	if(hwnd)
	  ScreenToClient(hwnd, &p); // 0.010ms
	else
	  GetCursorPos(&p);

	ICONINFO iconinfo;
	BOOL ret = ::GetIconInfo(hcur, &iconinfo); // 0.09ms

	if(ret) {
		p.x -= iconinfo.xHotspot; // align mouse, I guess...
		p.y -= iconinfo.yHotspot;

		// avoid some memory leak or other...
		if (iconinfo.hbmMask) {
			::DeleteObject(iconinfo.hbmMask);
		}
		if (iconinfo.hbmColor) {
			::DeleteObject(iconinfo.hbmColor);
		}
	}
	
	DrawIcon(hMemDC, p.x-lpRect->left, p.y-lpRect->top, hcur); // 0.042ms
}