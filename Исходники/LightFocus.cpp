LRESULT OverlayWindow::onLeftButtonUp(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT p;
	GetCursorPos(&p);
	if (((MainWindow *)_parent)->getCaptureMode() == 1) {
		ShowWindow(_handle, SW_HIDE);
		_selectedWindow = WindowFromPoint(p);
		ShowWindow(_handle, SW_SHOW);
		_selectedWindow = GetAncestor(_selectedWindow, GA_ROOT);
		if (_selectedWindow != NULL) {
			HRGN overlayrgn = CreateRectRgn(0,0,0,0);
			HRGN combine = CreateRectRgn(0,0,0,0);
			int n = GetWindowRgn(_handle, overlayrgn);
			HRGN hrgn = CreateRectRgn(0,0,0,0);
			int regionType = GetWindowRgn(_selectedWindow, hrgn);
			RECT r1, r2;
			GetWindowRect(_handle, &r1);
			GetWindowRect(_selectedWindow, &r2);
			if (regionType == 0) {
				hrgn = CreateRectRgn(r2.left, r2.top,r2.right,r2.bottom);
			} else {
				OffsetRgn(hrgn, r2.left - r1.left, r2.top - r1.top);
			}
			CombineRgn(combine, overlayrgn, hrgn, RGN_DIFF);
			SetWindowRgn(_handle, combine, TRUE);
			_selection->move(r2.left, r2.top, r2.right - r2.left, r2.bottom - r2.top);
			regionType = GetWindowRgn(_selectedWindow, hrgn);
			if (regionType == 0) {
				hrgn = CreateRectRgn(0, 0, r2.right - r2.left, r2.bottom - r2.top);
			}
			SetWindowRgn(_selection->getHandle(), hrgn, TRUE);
			_selection->show(SW_SHOW);
		}
	} else {
		int x, y, width, height;
		RECT r = getRect();
		HRGN overlayRgn = CreateRectRgn(0, 0, r.right, r.bottom);
		width = p.x - _firstPoint.x;
		height = p.y - _firstPoint.y;
		if (width < 0) {
			width = -width;
			x = p.x;
		} else {
			x = _firstPoint.x;
		}
		if (height < 0) {
			height = -height;
			y = p.y;
		} else {
			y = _firstPoint.y;
		}
		HRGN rgn = CreateRectRgn(0, 0, width, height);
		SetWindowRgn(_selection->getHandle(), rgn, TRUE);
		rgn = CreateRectRgn(0, 0, width, height);
		OffsetRgn(rgn, x, y);
		CombineRgn(overlayRgn, overlayRgn, rgn, RGN_DIFF);
		SetWindowRgn(_handle, overlayRgn, FALSE);
		_selection->move(x, y, width, height, false);
		_selection->show(SW_SHOW);
		_isSelecting = false;
	}
	
	return 0;
}