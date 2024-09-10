void CCDInfo::DrawOffScreen(HDC hdc, RECT rc)
{
	HBITMAP hbmMem, hbmOld;
	HDC     hdcMem;
	RECT    rcDP;

	// First make sure we have the coordinates in device units and we
	// are offset from 0,0

	LPtoDP(hdc, (LPPOINT)&rc, 2);
	rcDP = rc;
	OffsetRect(&rc, -rc.left, -rc.top);

	// Create a DC to draw into
	hdcMem = CreateCompatibleDC(hdc);

	// Create a bitmap big enough for our drawing
	hbmMem = CreateCompatibleBitmap(hdc, rc.right-rc.left, rc.bottom-rc.top);

	// Select the bitmap into our new DC
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

	// If we can get the ambient background color from the container then we
	// will use it.

	CComVariant var;
	if (SUCCEEDED(m_spAmbientDispatch.GetProperty(DISPID_AMBIENT_BACKCOLOR,
			&var)))
	{
		LOGBRUSH    logbrush;
		COLORREF    col;
		logbrush.lbStyle = BS_SOLID;
		OleTranslateColor(var.lVal, m_hPalette, &col);
		logbrush.lbColor = col;
		HBRUSH hBrush = CreateBrushIndirect(&logbrush);
		FillRect(hdcMem, &rc, hBrush);
		DeleteObject(hBrush);
	}

	RECT rcEllipse = rc;
	ReduceRect(&rcEllipse);
	DrawCD(hdcMem, rcEllipse);

	// Now we can blt our offscreen bitmap onto the passed DC.
	BitBlt(hdc,
		   rcDP.left, rcDP.top,
		   rcDP.right-rcDP.left, rcDP.bottom-rcDP.top,
		   hdcMem,
		   0, 0,
		   SRCCOPY);

	// Clean up our stuff
	SelectObject(hdcMem, hbmOld);
   DeleteObject(hbmMem);
   DeleteDC(hdcMem);
}