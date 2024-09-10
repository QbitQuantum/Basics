void draw_box(HDC _hDC, const RECT& _rBox, int _EdgeRoundness, float _Alpha)
{
	if (equal(_Alpha, 1.0f))
	{
		if (_EdgeRoundness)
			oVB(RoundRect(_hDC, _rBox.left, _rBox.top, _rBox.right, _rBox.bottom, _EdgeRoundness, _EdgeRoundness));
		else
			oVB(Rectangle(_hDC, _rBox.left, _rBox.top, _rBox.right, _rBox.bottom));
		return;
	}

	// Copy the contents out (is there no way to access things directly?)
	BITMAPINFO bmi = {0};
	surface::info_t si;
	si.dimensions = int3(oWinRectW(_rBox), oWinRectH(_rBox), 1);
	si.format = surface::format::b8g8r8a8_unorm;

	bmi.bmiHeader = make_header(si);
	if (!bmi.bmiHeader.biWidth || !bmi.bmiHeader.biHeight)
		return;
	
	HDC hDCBitmap = CreateCompatibleDC(_hDC);
	scoped_bitmap hBmp(CreateDIBSection(hDCBitmap, (BITMAPINFO*)&bmi, DIB_RGB_COLORS, nullptr, nullptr, 0));

	scoped_select ScopedSelectBmp(hDCBitmap, hBmp);
	scoped_select ScopedSelectPen(hDCBitmap, current_pen(_hDC));
	scoped_select ScopedSelectBrush(hDCBitmap, current_brush(_hDC));

	// Resolve areas around the curved corners so we can to the blend directly
	// later on. But just do the minimum necessary, don't copy the interior that
	// we're going to re-draw with a RECT.
	if (_EdgeRoundness)
	{
		// Minimize rects...
		int dist = _EdgeRoundness;
		RECT TL = { _rBox.left, _rBox.top, _rBox.left + dist, _rBox.top + dist };
		RECT RT = { _rBox.right - dist, _rBox.top, _rBox.right, _rBox.top + dist };
		RECT BL = { _rBox.left, _rBox.bottom - dist, _rBox.left + dist, _rBox.bottom };
		RECT BR = { _rBox.right - dist, _rBox.bottom - dist, _rBox.right, _rBox.bottom };
		BitBlt(hDCBitmap, 0, 0, dist, dist, _hDC, _rBox.left, _rBox.top, SRCCOPY);
		BitBlt(hDCBitmap, bmi.bmiHeader.biWidth - dist, 0, dist, dist, _hDC, _rBox.right - dist, _rBox.top, SRCCOPY);
		BitBlt(hDCBitmap, 0, bmi.bmiHeader.biHeight - dist, dist, dist, _hDC, _rBox.left, _rBox.bottom - dist, SRCCOPY);
		BitBlt(hDCBitmap, bmi.bmiHeader.biWidth - dist, bmi.bmiHeader.biHeight - dist, dist, dist, _hDC, _rBox.right - dist, _rBox.bottom - dist, SRCCOPY);
		oVB(RoundRect(hDCBitmap, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, _EdgeRoundness, _EdgeRoundness));
	}

	else
		oVB(Rectangle(hDCBitmap, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight));

	BLENDFUNCTION blend = { AC_SRC_OVER, 0, (BYTE)(static_cast<int>(_Alpha * 255.0f) & 0xff), 0 };
	oVB(AlphaBlend(_hDC, _rBox.left, _rBox.top, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hDCBitmap, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, blend));
}