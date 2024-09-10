/* internal version of ExtTextOut, passed flags for text data type*/
static BOOL
MwExtTextOut(HDC hdc, int x, int y, UINT fuOptions, CONST RECT *lprc,
	LPCVOID lpszString, UINT cbCount, CONST INT *lpDx, int flags)
{
	HWND	hwnd;
	POINT	pt;
	RECT	rc;

	hwnd = MwPrepareDC(hdc);
	if(!hwnd)
		return FALSE;

	pt.x = x;
	pt.y = y;
	if(MwIsClientDC(hdc))
		ClientToScreen(hwnd, &pt);

	/* optionally fill passed rectangle*/
	if(lprc && (fuOptions&ETO_OPAQUE)) {
		rc = *lprc;
		if(MwIsClientDC(hdc))
			MapWindowPoints(hwnd, NULL, (LPPOINT)&rc, 2);

		/* fill rectangle with current background color*/
		GdSetForegroundColor(hdc->psd, hdc->bkcolor);
		GdFillRect(hdc->psd, rc.left, rc.top, rc.right - rc.left,
			rc.bottom - rc.top);
		GdSetUseBackground(FALSE);
	} else {
		/* use current background mode for text background draw*/
		GdSetUseBackground(hdc->bkmode == OPAQUE? TRUE: FALSE);
		/* always set background color in case GdArea is
		 * used to draw, which compares gr_foreground != gr_background
		 * if gr_usebg is false...
		 */
		/*if(hdc->bkmode == OPAQUE)*/
			GdSetBackgroundColor(hdc->psd, hdc->bkcolor);
	}

	if (cbCount == 0) {
		/* Special case - no text.  Used to fill rectangle. */
		return TRUE;
	}

	/* nyi: lpDx*/

	/* draw text in current text foreground and background color*/
	GdSetForegroundColor(hdc->psd, hdc->textcolor);
	//GdSetFont(hdc->font->pfont);

	/* this whole text alignment thing needs rewriting*/
	if((hdc->textalign & TA_BASELINE) == TA_BASELINE) {
		 /* this is not right... changed for kaffe port
		flags |= MWTF_TOP;
		 */
		flags |= MWTF_BASELINE;
	} else if(hdc->textalign & TA_BOTTOM) {
		MWCOORD	ph, pw, pb;

		if(lprc)
			pt.y += lprc->bottom - lprc->top;
		else {
			GdGetTextSize(hdc->font->pfont, lpszString, cbCount, &pw, &ph, &pb, flags);
			pt.y += ph;
		}
		flags |= MWTF_BOTTOM;
	} else
		flags |= MWTF_TOP;

	if((hdc->textalign & TA_CENTER) == TA_CENTER) {
		MWCOORD     ph, pw, pb;

		GdGetTextSize(hdc->font->pfont, lpszString, cbCount, &pw, &ph, &pb, flags);
		pt.x -= pw/2;
	} else if(hdc->textalign & TA_RIGHT) {
		MWCOORD     ph, pw, pb;

		GdGetTextSize(hdc->font->pfont, lpszString, cbCount, &pw, &ph, &pb, flags);
		pt.x -= pw;
	}
	GdText(hdc->psd, hdc->font->pfont, pt.x, pt.y, lpszString, cbCount, flags);

	return TRUE;
}