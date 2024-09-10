/**
 * Open low level graphics driver.
 *
 * @return The screen drawing surface.
 */
PSD
GdOpenScreen(void)
{
	PSD			psd;
	MWPALENTRY *		stdpal;

	psd = scrdev.Open(&scrdev);
	if (!psd)
		return NULL;

	/* assume no user changable palette entries*/
	gr_firstuserpalentry = (int)psd->ncolors;

	/* set palette according to system colors and devpalX.c*/
	switch((int)psd->ncolors) {

#if !defined(NOSTDPAL1) /* don't require stdpal1 if not needed */
	case 2:		/* 1bpp*/
	{
		extern MWPALENTRY	mwstdpal1[2];
		stdpal = mwstdpal1;
	}
	break;
#endif

#if !defined(NOSTDPAL2) /* don't require stdpal2 if not needed */
	case 4:		/* 2bpp*/
	{
		extern MWPALENTRY	mwstdpal2[4];
		stdpal = mwstdpal2;
	}
	break;
#endif

#if !defined(NOSTDPAL4)
	/* don't require stdpal4 if not needed */
	case 8:		/* 3bpp - not fully supported*/
	case 16:	/* 4bpp*/
	{
		extern MWPALENTRY	mwstdpal4[16];
		stdpal = mwstdpal4;
	}
	break;
#endif

#if !defined(NOSTDPAL8) /* don't require large stdpal8 if not needed */
	case 256:	/* 8bpp*/
	{
		extern MWPALENTRY	mwstdpal8[256];
#if UNIFORMPALETTE
		/* don't change uniform palette if alpha blending*/
		gr_firstuserpalentry = 256;
#else
		/* start after last system-reserved color*/
		gr_firstuserpalentry = FIRSTUSERPALENTRY;
#endif
		stdpal = mwstdpal8;
	} 
	break;
#endif	/* !defined(NOSTDPAL8)*/

	default:	/* truecolor*/
		/* no palette*/
		gr_firstuserpalentry = 0;
		stdpal = NULL;
	}

	/* reset next user palette entry, write hardware palette*/
	GdResetPalette();
	GdSetPalette(psd, 0, (int)psd->ncolors, stdpal);

	/* init local vars*/
	GdSetMode(MWROP_COPY);
	GdSetFillMode(MWFILL_SOLID);  /* Set the fill mode to solid */

	GdSetForegroundColor(psd, MWRGB(255, 255, 255));	/* WHITE*/
	GdSetBackgroundColor(psd, MWRGB(0, 0, 0));		/* BLACK*/
	GdSetUseBackground(TRUE);
	/* select first builtin font (usually MWFONT_SYSTEM_VAR)*/
	//GdSetFont(GdCreateFont(psd, NULL, 0, 0, NULL));

	GdSetDash(0, 0);  /* No dashing to start */
	GdSetStippleBitmap(0,0,0);  /* No stipple to start */

#if !NOCLIPPING
#if DYNAMICREGIONS
	GdSetClipRegion(psd, GdAllocRectRegion(0, 0, psd->xvirtres, psd->yvirtres));
#else
	GdSetClipRects(psd, 0, NULL);
#endif /* DYNAMICREGIONS*/
#endif /* NOCLIPPING*/

	/* fill black (actually fill to first palette entry or truecolor 0*/
	psd->FillRect(psd, 0, 0, psd->xvirtres-1, psd->yvirtres-1, 0);
	return psd;
}