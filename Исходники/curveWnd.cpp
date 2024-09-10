void CurveWnd::resetScroll(){
	RECT cr;

	GetClientRect(hwnd, &cr);

	setScrollInfo(SB_HORZ, 0, canvas.cx, cr.right, 0);
	setScrollInfo(SB_VERT, 0, canvas.cy, cr.bottom, 0);
}