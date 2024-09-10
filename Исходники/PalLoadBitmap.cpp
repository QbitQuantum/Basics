HPALETTE CreateSystemPalette(void)
{
	LOGPALETTE * pLogPal = (LOGPALETTE *) new char[sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 255];

	pLogPal->palVersion    = 0x300;
	pLogPal->palNumEntries = 256;

	HDC hDC = GetDC(NULL);

	GetSystemPaletteEntries(hDC, 0, 256, pLogPal->palPalEntry);
	
	ReleaseDC(NULL, hDC);

	HPALETTE hPal = CreatePalette(pLogPal);
	delete [] (char *) pLogPal;

	return hPal;
}