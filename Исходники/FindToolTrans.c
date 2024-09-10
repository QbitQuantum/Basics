void UpdatePanelTrans(HWND hwndPanel, RECT *rect)
{
	POINT ptZero = { 0, 0 };
	COLORREF crKey = RGB(0, 0, 0);

	const BYTE SourceConstantAlpha = 220;//255;
	BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 0, AC_SRC_ALPHA };
	blendPixelFunction.SourceConstantAlpha = SourceConstantAlpha;
	RECT rect2;
	//rect->right = rect->left + 316;
	//rect->bottom = rect->top + 382;

	POINT pt;
	pt.x = rect->left;
	pt.y = rect->top;
	SIZE sz;
	sz.cx = GetRectWidth(rect);
	sz.cy = GetRectHeight(rect);

	HDC hdcSrc = GetDC(0);
	HDC hdcMem = CreateCompatibleDC(hdcSrc);
	HBITMAP hbm;
	HANDLE hold;

	GetClientRect(hwndPanel, &rect2);
	hbm = MakeDockPanelBitmap(rect);
	hold = SelectObject(hdcMem, hbm);

	//FillRect(hdcMem, &rect, GetSysColorBrush(COLOR_HIGHLIGHT));
	//SetWindowLongPtr(hwndPanel, GWL_EXSTYLE, GetWindowLongPtr(hwndPanel, GWL_EXSTYLE) | WS_EX_LAYERED);

	UpdateLayeredWindow(hwndPanel,
		hdcSrc,
		&pt, //pos
		&sz, //size
		hdcMem,
		&ptZero,
		crKey,
		&blendPixelFunction,
		ULW_ALPHA);

	SelectObject(hdcMem, hold);
	DeleteDC(hdcMem);
	ReleaseDC(0, hdcSrc);
}