// Loads a bitmap and returns the handle. Retrieves the color of the
// first pixel in the image and replaces that entry in the color table
// with COLOR_3DFACE
HBITMAP WINAPI
LoadTransparentBitmap(HINSTANCE hInstance, UINT nResID)
{
	// Find the resource
	HRSRC	hrsrc = FindResource(hInstance, MAKEINTRESOURCE(nResID), RT_BITMAP);

	assert(hrsrc);
	if (!hrsrc)
		return NULL;

	// Get a handle for the resource
	HGLOBAL	hglb = LoadResource(hInstance, hrsrc);
	if (!hglb)
		return NULL;

	// Get a pointer to the BITMAPINFOHEADER
	LPBITMAPINFOHEADER	lpbi = (LPBITMAPINFOHEADER)LockResource(hglb);

	// We expect a 4-bpp image only
	assert(lpbi->biBitCount == 4);
	if (lpbi->biBitCount != 4) {
		UnlockResource(hglb);
		FreeResource(hglb);
		return NULL;
	}

	// Get a pointer to the color table
	LPRGBQUAD	pColors = (LPRGBQUAD)((LPSTR)lpbi + (WORD)lpbi->biSize);

	// Look at the first pixel and get the palette index
	UINT	nClrUsed = lpbi->biClrUsed == 0 ? 16 : (UINT)lpbi->biClrUsed;
	LPBYTE	lpBits = (LPBYTE)(pColors + nClrUsed);

	// Munge the color table entry
	COLORREF	clrBtnFace = GetSysColor(COLOR_BTNFACE);
	int			nIndex = *lpBits & 0xF;

	pColors[nIndex].rgbRed = GetRValue(clrBtnFace);
	pColors[nIndex].rgbGreen = GetGValue(clrBtnFace);
	pColors[nIndex].rgbBlue = GetBValue(clrBtnFace);

	// Create the DDB
	HBITMAP		hBitmap;
	HDC			hDC = GetDC(NULL);

	hBitmap = CreateDIBitmap(hDC, lpbi, CBM_INIT, lpBits,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
	ReleaseDC(NULL, hDC);

	// Release the resource
	UnlockResource(hglb);
	FreeResource(hglb);

	return hBitmap;
}