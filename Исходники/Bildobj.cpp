// Umformen einer DIB in eine DDB 
HBITMAP CBildObjekt :: DIBToBitmap (void) 
{
BITMAPINFOHEADER *lpBI;
HPALETTE hPalT;
HDC hDC;
HBITMAP hBM;

	if (!m_hDIB) return NULL;

// Bitmapheader 
	lpBI = (BITMAPINFOHEADER *)GlobalLock (m_hDIB);
	if (!lpBI) return NULL;

// Palette realisieren 
	hDC = :: GetDC (NULL);
	if (m_hPal) {
		hPalT = SelectPalette (hDC, m_hPal, false);
		RealizePalette (hDC);
	}

// device dependent bitmap (DDB) erzeugen 
	hBM = CreateDIBitmap (hDC, lpBI, (long)CBM_INIT,
			(char *)lpBI + lpBI->biSize + 
			DIBNumColors(lpBI)*sizeof(RGBQUAD), //  PaletteSize (lpBI),
			(BITMAPINFO *)lpBI, DIB_RGB_COLORS);

// alte Palette wiedereinstellen
	if (m_hPal)
		SelectPalette (hDC, hPalT, false);

	ReleaseDC (NULL, hDC);
	GlobalUnlock (m_hDIB);

return hBM;
}