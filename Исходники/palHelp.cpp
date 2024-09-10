void initMapPalette()
{
	LOGPALETTE* pPal = (LOGPALETTE*) malloc(sizeof(LOGPALETTE) 
	                         + 256 * sizeof(PALETTEENTRY));
	pPal->palVersion = 0x300;  // Windows 3.0
	pPal->palNumEntries = 256; // table size
	for (int i=0; i<256; i++)  {
		pPal->palPalEntry[i].peRed = (UInt8)i;
		pPal->palPalEntry[i].peGreen = 0;
		pPal->palPalEntry[i].peBlue = 0;
		pPal->palPalEntry[i].peFlags = PC_EXPLICIT;
	}
	gMapPalette.CreatePalette(pPal);
	free (pPal);
}