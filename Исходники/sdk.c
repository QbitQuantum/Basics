HIMAGELIST
SdkCreateGrayImageList(
	IN HIMAGELIST himlNormal
	)
{
	int Count, i;
	int Width, Height;
	HIMAGELIST himlGray;
	HDC hdcDesktop;
	HDC hdcMem;
	RECT rc;
	COLORREF crMask;
	HPALETTE hpal;
	UINT index;
	HGDIOBJ hbm;
	HGDIOBJ hbmOld;
	COLORREF rgb;
	BYTE gray;
	HWND hWnd;
	int x, y;

	Count = ImageList_GetImageCount(himlNormal);
	if (Count == 0) {
		return NULL;
	}

	ImageList_GetIconSize(himlNormal, &Width, &Height);
	himlGray = ImageList_Create(Width, Height, ILC_COLOR24 | ILC_MASK, Count, 0);

	hdcDesktop = GetDC(NULL);
	hdcMem = CreateCompatibleDC(NULL);
	
	rc.top = rc.left = 0;
	rc.bottom = Height;
	rc.right = Width;
	crMask = RGB(200, 199, 200);

	if (GetDeviceCaps(hdcDesktop, BITSPIXEL) < 24) {
		hpal = (HPALETTE)GetCurrentObject(hdcDesktop, OBJ_PAL);
		index = GetNearestPaletteIndex(hpal, crMask);
		if (index != CLR_INVALID) { 
			crMask = PALETTEINDEX(index);
		}
	}

	for (i = 0 ; i < Count; ++i) {

		hbm = CreateCompatibleBitmap(hdcDesktop, Width, Height);
		hbmOld = SelectObject(hdcMem, hbm);

		SdkFillSolidRect(hdcMem, crMask, &rc);

		ImageList_SetBkColor(himlNormal, crMask);
		ImageList_Draw(himlNormal, i, hdcMem, 0, 0, ILD_NORMAL);

		for (x = 0 ; x < Width; ++x) {
			for (y = 0; y < Height; ++y) {
				rgb = GetPixel(hdcMem, x, y);
				if (rgb != crMask) { 
					gray = (BYTE) (95 + (GetRValue(rgb) * 3 + GetGValue(rgb) * 6 + GetBValue(rgb)) / 20);
					SetPixel(hdcMem, x, y, RGB(gray, gray, gray));
				}
			}
		}

		hbm = SelectObject(hdcMem, hbmOld);
		ImageList_AddMasked(himlGray, (HBITMAP)hbm, crMask);
		DeleteObject(hbm);
	}

	DeleteDC(hdcMem);
	hWnd = WindowFromDC(hdcDesktop);
	ReleaseDC(hWnd, hdcDesktop);

	return himlGray; 
}