DWORD
lsd_display_realizepal(WORD wMsg,
	LPDC lpDC,
	DWORD dwParam,
	LPLSDS_PARAMS lpParam)
{
	LPPALETTE lpPalette;
	LPLOGPALETTE lpLogPalette;
	LPUINT lpSystemPaletteIndex;
	BOOL bForegroundPalette, bInitSystemPalette;
	UINT u;

	APISTR((LF_API, "lsd_display_realizepal: wMsg %d lpDC %p\n",
		wMsg, lpDC));

	ASSERT_PALETTE(lpPalette, lpDC->hPalette, GDI_ERROR);

	if (!(lpLogPalette = lpPalette->lpLogPalette))
	{
		SetLastErrorEx(1, 0);
		return (DWORD)((UINT) GDI_ERROR);
	}

	if (!(lpSystemPaletteIndex = (LPUINT)
		WinRealloc(lpDC->lpSystemPaletteIndex,
		(lpLogPalette->palNumEntries + 1) * sizeof(UINT))))
	{
		SetLastErrorEx(1, 0);
		return (DWORD)((UINT) GDI_ERROR);
	}

	if (0)
	{
		LOGSTR((LF_LOG, "lsd_display_realizepal:"
			" realizing foreground palette\n"));
/*
		DRVCALL_COLORS(PLG_,
*/


	}
	bForegroundPalette = TRUE;



/* SEND WM_PALETTECHANGED here */
/* OR let SetFocus() send WM_PALETTE... */


	for (u = 0; u < lpLogPalette->palNumEntries; u++)
	{
		bInitSystemPalette = ((u == 0) && (bForegroundPalette == TRUE))
			? TRUE : FALSE;
		lpSystemPaletteIndex[u] = (UINT)
			DRVCALL_COLORS(PLH_SETSYSTEMPALETTE,
				(DWORD) lpDC->lpDrvData,
				(DWORD) bInitSystemPalette,
				(LPPALETTEENTRY)
					&(lpLogPalette->palPalEntry[u]));
		LOGSTR((LF_LOG, "lsd_display_realizepal:\n"
			" palette index [%d] rgb (%d, %d, %d) flags %d"
			" <-> system palette index [%d]\n", u,
			lpLogPalette->palPalEntry[u].peRed,
			lpLogPalette->palPalEntry[u].peGreen,
			lpLogPalette->palPalEntry[u].peBlue,
			lpLogPalette->palPalEntry[u].peFlags,
			lpSystemPaletteIndex[u]));
	}
	lpDC->lpSystemPaletteIndex = lpSystemPaletteIndex;

	lpPalette->fIsRealized = TRUE;

	UNLOCK_PALETTE(hPalette);

	return (u);

}