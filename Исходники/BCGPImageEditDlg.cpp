//********************************************************************************
void Create16ColorsStdPalette (CPalette& pal)
{
	const int nStdColorCount = 20;
	CPalette* pPalDefault = CPalette::FromHandle ((HPALETTE) ::GetStockObject (DEFAULT_PALETTE));
	if (pPalDefault == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	const int nColors = 16;
	UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
	LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

	pLP->palVersion = 0x300;
	pLP->palNumEntries = (USHORT) nColors;

	pal.CreatePalette (pLP);

	delete[] pLP;

	PALETTEENTRY palEntry;
	int iDest = 0;

	for (int i = 0; i < nStdColorCount; i++)
	{
		if (i < 8 || i >= 12)
		{
			pPalDefault->GetPaletteEntries (i, 1, &palEntry);
			pal.SetPaletteEntries (iDest++, 1, &palEntry);
		}
	}
}