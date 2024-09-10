BOOL CheckForHookCursor(HDC dc) {
	CURSORINFO cursorInfo = { 0 };
	int i, j, b = WF_CursorHookBlack, w = WF_CursorHookWhite;
	cursorInfo.cbSize = sizeof(cursorInfo);

	if (GetCursorInfo(&cursorInfo)) {
		byte* bits[1000];
		ICONINFO ii = {0};
		POINT pp = cursorInfo.ptScreenPos;
		int p = GetIconInfo(cursorInfo.hCursor, &ii);
		int counter = 0, rv;
		HDC memDC = CreateCompatibleDC(dc);
		BITMAPINFO bmi;

		memset(&bmi, 0, sizeof(BITMAPINFO)); 
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = 16;
		bmi.bmiHeader.biHeight = 16;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = 0;
		bmi.bmiHeader.biXPelsPerMeter = 0;
		bmi.bmiHeader.biYPelsPerMeter = 0;
		bmi.bmiHeader.biClrUsed	= 0;
		bmi.bmiHeader.biClrImportant = 0;
		GetDIBits(memDC, ii.hbmMask, 0, bmi.bmiHeader.biHeight, (void**)&bits, &bmi, DIB_RGB_COLORS);

		for (i=0;i<16;i++)
		for (j=0;j<16;j++) {
			DWORD c = (DWORD)BITMAPPixel(bmi, i, j, 16);
			if (c == 0x00) b--;
			else if (c = 0xFF) w--;
		}

		DeleteDC(memDC);

		if (w == 0 && b == 0) return TRUE;
	}

	return FALSE;

}