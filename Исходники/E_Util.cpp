HBITMAP E_Util::ConvertIconToBitmap(HICON hIcon, int nWidth, int nHeight, COLORREF clrBackground)
{
	if (hIcon == NULL)
		return NULL;
	HDC hDC = NULL;
	HDC hMemDC = NULL;
	HBITMAP hBitmap = NULL;
	HBITMAP hOldBitmap = NULL;
	HBRUSH hBrush = NULL;
	HBRUSH hOldBrush = NULL;



	BOOL bGotBitmap = false;

	try {
		hDC = ::GetDC(NULL);
		if (hDC != NULL) {
			hBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);
			if (hBitmap != NULL) {
				hMemDC = CreateCompatibleDC(hDC);
				if (hMemDC != NULL) {
					// Select the bitmap into the memory device context
					hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

					hBrush = CreateSolidBrush(clrBackground);
					if (hBrush != NULL) {
						// Fill the bitmap with the background color
						hOldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
						PatBlt(hMemDC, 0, 0, nWidth, nHeight, PATCOPY);

						// Draw the icon
						DrawIconEx(hMemDC, 0, 0, hIcon, nWidth, nHeight, 0, NULL, DI_IMAGE);
						bGotBitmap = true;
					}
				}
			}
		}

		// Cleanup
		if (hOldBrush != NULL)
			SelectObject(hMemDC, hOldBrush);
		if (hOldBitmap != NULL)
			SelectObject(hMemDC, hOldBitmap);
		if (hBrush != NULL)
			DeleteObject(hBrush);
		if (hMemDC != NULL)
			DeleteDC(hMemDC);
		if (hDC != NULL)
			::ReleaseDC(NULL, hDC);

		if (!bGotBitmap && hBitmap != NULL) {
			DeleteObject(hBitmap);
			hBitmap = NULL;
		}
	}
	catch (...) {
	}
	return hBitmap;
}