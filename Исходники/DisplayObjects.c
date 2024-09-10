BOOL
GdiSelectBrush(HDC32 hDC32, LPBRUSHINFO lpBrushInfo)
{
    UINT uiCompatibility;
    BOOL bDither;
    COLORREF crColor,crTemp;
    LPIMAGEINFO lpImageInfo;
    HBITMAP hBitmap;
    int nDepth = 0;
    WORD wBrushType;
    int i;

    if (lpBrushInfo->lpBrush.lbColor & PALETTE_MASK)
	crColor = TWIN_PaletteRGB(hDC32, lpBrushInfo->lpBrush.lbColor);
    else
	crColor = lpBrushInfo->lpBrush.lbColor;

    if (lpBrushInfo->lpBrush.lbStyle == BS_SOLID) {
	wBrushType = LOWORD(lpBrushInfo->dwFlags);
	if (!(lpBrushInfo->dwFlags & DCX_DISPLAY_DC))
	    /* we have to re-realize solid brush, dither if needed */
	    wBrushType = BFP_UNASSIGNED;
	if (hDC32->hBitmap) {
	    /* if the brush is realized, but its depth is different */
	    /* from the currently selected bitmap, it has to be re- */
	    /* realized */
	    lpImageInfo = GETBITMAPINFO(hDC32->hBitmap);
	    nDepth = lpImageInfo->BitsPixel;
	    if (nDepth != (int)LOBYTE(HIWORD(lpBrushInfo->dwFlags)))
		wBrushType = BFP_UNASSIGNED;
	    RELEASEBITMAPINFO(lpImageInfo);
	}

	if (wBrushType == BFP_UNASSIGNED) {
	    /* solid brush needs to be realized;		*/
	    /* gets resolved to either BFP_PIXEL (solid color)	*/
	    /* or BFP_PIXMAP (dithered pattern)		  	*/
	    if (nDepth == 1) {
		if ((crColor == RGB(0,0,0)) || crColor == RGB(255,255,255))
		    bDither = FALSE;
		else
		    bDither = TRUE;
	    }
	    else {
		uiCompatibility = GetCompatibilityFlags(0);
		if (!(uiCompatibility & WD_NODITHERPURE)) {
		    for (i = 0, bDither = TRUE; bDither && i < 16; i ++) 
			if (RGB(VGAColors[i].rgbRed,
				VGAColors[i].rgbGreen,
				VGAColors[i].rgbBlue) == crColor)
			    bDither = FALSE;
		}
		else {
		    crTemp = GetNearestColor(GETHDC16(hDC32),crColor);
		    if (lpBrushInfo->lpBrush.lbColor & PALETTE_RGB) {
			bDither = FALSE;
			crColor = crTemp;
		    }
		    else 
			bDither = (crColor != crTemp);
		}
	    }
	    if (!bDither) {
		wBrushType = BFP_PIXEL;
		lpBrushInfo->lpPrivate = (LPVOID)DRVCALL_COLORS
				(PLH_MAKEPIXEL,
				 crColor,
				 0L,0L);
	    }
	    else {
		hBitmap = GdiDitherColor
			(GETHDC16(hDC32),crColor,nDepth);
		lpBrushInfo->lpBrush.lbHatch = (int)hBitmap;
		wBrushType = BFP_PIXMAP;
		lpImageInfo = GETBITMAPINFO(hBitmap);
		if (!lpImageInfo) {
		    return FALSE;
		}
		lpBrushInfo->lpPrivate = (LPVOID)DRVCALL_IMAGES
				(PIH_CREATEBRUSH,
				BFP_PIXMAP,0L,
				lpImageInfo->lpDrvData);
		RELEASEBITMAPINFO(lpImageInfo);
	    }
	    lpBrushInfo->dwFlags = DCX_DISPLAY_DC | wBrushType;
	    lpBrushInfo->dwFlags |= (BYTE)nDepth << 16;
	}
    }
    if (!lpBrushInfo->fIsRealized) {
	LSDS_PARAMS argptr;
	argptr.lsde_validate.dwInvalidMask = 0;
	argptr.lsde.point = hDC32->ptBrushOrg;
	DRVCALL_GRAPHICS(PGH_SETBRUSHORG,
				(DWORD)hDC32->lpDrvData,0L, &argptr);
	lpBrushInfo->fIsRealized = TRUE;
    }
    return TRUE;
}