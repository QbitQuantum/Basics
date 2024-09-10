Bool
qtRealizeInstalledPaletteShadow (ScreenPtr pScreen)
{
#if 0	/* ### NOT YET */
	winScreenPriv(pScreen);
	winPrivCmapPtr	pCmapPriv = NULL;

#if QTDEBUG
	ErrorF ("qtRealizeInstalledPaletteShadow\n");
#endif

	/* Don't do anything if there is not a colormap */
	if (pScreenPriv->pcmapInstalled == NULL)
	{
#if QTDEBUG
		ErrorF ("qtRealizeInstalledPaletteShadow - No colormap "
			"installed\n");
#endif
		return TRUE;
	}

	pCmapPriv = winGetCmapPriv (pScreenPriv->pcmapInstalled);
  
	/* Realize our palette for the screen */
	if (RealizePalette (pScreenPriv->hdcScreen) == _ERROR)
	{
		ErrorF ("qtRealizeInstalledPaletteShadow - RealizePalette () "
			"failed\n");
		return FALSE;
	}
  
	/* Set the DIB color table */
	if (SetDIBColorTable (pScreenPriv->hdcShadow,
			      0,
			      WIN_NUM_PALETTE_ENTRIES,
			      pCmapPriv->rgbColors) == 0)
	{
		ErrorF ("qtRealizeInstalledPaletteShadow - SetDIBColorTable () "
			"failed\n");
		return FALSE;
	}
#endif  
	return TRUE;
}