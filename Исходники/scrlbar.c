void
MwPaintScrollbars(HWND hwnd, HDC hdc, DWORD style)
{
	BOOL	vertbar = (style==SBS_VERT);
        BOOL	horzbar = (style==SBS_HORZ);
	BOOL	fGotDC = FALSE;
	RECT	rc,rc2;

	POINT	p3[3];
	int	shrink=2;

        int start = 0;
        RECT rcHBar, rcVBar;

	int cx,cy;
    	MWSCROLLBARINFO* pData;
	
        pData = (MWSCROLLBARINFO *)hwnd->userdata;
	rc = hwnd->winrect;
	cx=rc.right-rc.left;
	cy=rc.bottom-rc.top;

	if (!hdc && (horzbar || vertbar)) {
		hdc = GetWindowDC(hwnd);
		fGotDC = TRUE;
	}

	if (vertbar) {

#if 1
		/* bkgnd */
		rc2.left=rc.left; rc2.right=rc2.left+ cx;
		rc2.top=rc.top;
		rc2.bottom=rc2.top+ cx;
		FillRect(hdc, &rc2, (HBRUSH)(COLOR_BTNFACE+1));
		rc2.top=rc.bottom- cx;
		rc2.bottom=rc2.top+ cx;
		FillRect(hdc, &rc2, (HBRUSH)(COLOR_BTNFACE+1));
#endif
		/* up */
		Draw3dUpDownState(hdc, rc.left, rc.top,
			cx, cx,
			pData->status & SBS_UPARROW);
		/* down */
		Draw3dUpDownState(hdc, rc.left,rc.bottom-cx,
			cx, cx,
			pData->status & SBS_DOWNARROW);
/* jmt: draw arrows */
		SelectObject(hdc,GetStockObject(BLACK_BRUSH));
		/* up */
		p3[0].x= rc.left + (cx/2) - 1;
		p3[0].y= rc.top + 2 + shrink;
		p3[1].x= rc.left + 2 + shrink - 1;
		p3[1].y= rc.top + (cx-4) - shrink;
		p3[2].x= rc.left + (cx-4) - shrink;
		p3[2].y= rc.top + (cx-4) - shrink;
		Polygon(hdc,p3,3);
		/* down */
		p3[0].x= rc.left + (cx/2) - 1;
		p3[0].y= rc.bottom - 4 - shrink;
		p3[1].x= rc.left + 2 + shrink - 1;
		p3[1].y= rc.bottom-cx + 2 + shrink;
		p3[2].x= rc.left + (cx-4) - shrink;
		p3[2].y= rc.bottom-cx + 2 + shrink;
		Polygon(hdc,p3,3);

        	/* draw moving bar */

    		wndGetVScrollBarRect (hwnd, &rcVBar);
    		rcVBar.left -- ;
    		/*rcVBar.right -- ;*/

        	start = rcVBar.top + cx + pData->barStart;
                    
        	if (start + pData->barLen > rcVBar.bottom)
            		start = rcVBar.bottom - pData->barLen;
		
		if (pData->barLen == 0)
			pData->barLen=rc.bottom-rc.top-(cx*2); 

		/* bkgnd */
		rc2.left=rc.left; rc2.right=rc.right/*-1*/;
		rc2.top=rc.top+cx;
		rc2.bottom=start;
		if (rc2.bottom>rc2.top)
			FillRect(hdc, &rc2, (HBRUSH)GetStockObject(DKGRAY_BRUSH));   

		rc2.top=start+pData->barLen;
		rc2.bottom=rc.bottom-cx;
		if (rc2.bottom>rc2.top)
			FillRect(hdc, &rc2, (HBRUSH)GetStockObject(DKGRAY_BRUSH));   

        	Draw3dUpFrame (hdc, rcVBar.left, start, rcVBar.right,
	    		start + pData->barLen);
		/*printf("barv:(l,t,r,b):(%d,%d,%d,%d)\n",
        		rcVBar.left, start, rcVBar.right,
	    		start + pData->barLen);*/

	}
	if (horzbar) {
#if 1
		/* bkgnd */
		rc2.top=rc.top; rc2.bottom=rc2.top+ cy;
		rc2.left=rc.left;
		rc2.right=rc2.left+ cy;
		FillRect(hdc, &rc2, (HBRUSH)(COLOR_BTNFACE+1));
		rc2.left=rc.right- cy;
		rc2.right=rc2.left+ cy;
		FillRect(hdc, &rc2, (HBRUSH)(COLOR_BTNFACE+1));
#endif
		/* left */
		Draw3dUpDownState(hdc, rc.left, rc.top,
			cy, cy,
			pData->status & SBS_LEFTARROW);
		/* right */
		Draw3dUpDownState(hdc, rc.right-cy, rc.top,
			cy, cy,
			pData->status & SBS_RIGHTARROW);
/* jmt: draw arrows */
		SelectObject(hdc,GetStockObject(BLACK_BRUSH));
		/* left */
		p3[0].x= rc.left + 2 + shrink;
		p3[0].y= rc.top + (cy/2) ;
		p3[1].x= rc.left + (cy-4) - shrink ;
		p3[1].y= rc.top + 2 + shrink;
		p3[2].x= rc.left + (cy-4) - shrink;
		p3[2].y= rc.bottom - 4 - shrink + 1;
		Polygon(hdc,p3,3);
		/* right */
		p3[0].x= rc.right - 4 - shrink;
		p3[0].y= rc.top + (cy/2) ;
		p3[1].x= rc.right-cy + 2 + shrink ;
		p3[1].y= rc.top + 2 + shrink;
		p3[2].x= rc.right-cy + 2 + shrink;
		p3[2].y= rc.bottom - 4 - shrink + 1;
		Polygon(hdc,p3,3);

        	/* draw moving bar. */

    		wndGetHScrollBarRect (hwnd, &rcHBar);
    		rcHBar.top -- ;
    		/*rcHBar.bottom -- ;*/

        	start = rcHBar.left + cy + pData->barStart;

        	if (start + pData->barLen > rcHBar.right)
            		start = rcHBar.right - pData->barLen;

		if (pData->barLen == 0)
			pData->barLen=rc.right-rc.left-(cy*2); 

		/* bkgnd */
		rc2.top=rc.top; rc2.bottom=rc.bottom/*-1*/;
		rc2.left=rc.left+cy;
		rc2.right=start;
		if (rc2.right>rc2.left)
			FillRect(hdc, &rc2, (HBRUSH)GetStockObject(DKGRAY_BRUSH));   

		rc2.left=start+pData->barLen;
		rc2.right=rc.right-cy;
		if (rc2.right>rc2.left)
			FillRect(hdc, &rc2, (HBRUSH)GetStockObject(DKGRAY_BRUSH));   

        	Draw3dUpFrame (hdc, start, rcHBar.top, start + pData->barLen,
	    		rcHBar.bottom);
		/*printf("barh:(l,t,r,b):(%d,%d,%d,%d)\n",
        		start, rcHBar.top, start + pData->barLen,
	    		rcHBar.bottom);*/
	}

	if (fGotDC)
		ReleaseDC(hwnd, hdc);
}