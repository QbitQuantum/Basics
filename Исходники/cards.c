/*
 * Initialize card library and return cards width and height
 */
BOOL WINAPI cdtInit(INT *Width, INT *Height)
{
    DWORD dwIndex;

    /* Report card width and height to user */
	*Width = CARD_WIDTH;
	*Height = CARD_HEIGHT;

	/* Load images */
	for (dwIndex = 0; dwIndex < MAX_CARD_BITMAPS; ++dwIndex)
		g_CardBitmaps[dwIndex] =
			(HBITMAP)LoadBitmapA(g_hModule, MAKEINTRESOURCEA(dwIndex + 1));

	return TRUE;
}