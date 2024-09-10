/*******************************************************************************
** Paint the DIL.
** The DIL consists of a recessed border with a hint. It may also be displaying
** a progress meter, if in progress mode.
**/
VOID NEAR PaintDil(HDC hDC)
{
	HPEN  hOldPen;		// Old device pen.
	HFONT hOldFont;	// Old device font.
	RECT  rcClip;		// Text clipping rectangle.
	
	/*
	** Draw border.
	*/
	  
	/* Draw window top black line. */
	hOldPen = SelectObject(hDC, GetStockObject(BLACK_PEN));
	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, iDilWidth, 0);
	
     /* Draw hint border top-left portion. */
	MoveToEx(hDC, LFT_BORDER, iDilHeight-BOT_BORDER, NULL);
	LineTo(hDC, LFT_BORDER, TOP_BORDER);
	LineTo(hDC, iDilWidth-RGT_BORDER, TOP_BORDER);

	/* Draw window top white line. */
	SelectObject(hDC, GetStockObject(WHITE_PEN));
	MoveToEx(hDC, 0, 1, NULL);
	LineTo(hDC, iDilWidth, 1);

     /* Draw hint border bottom-right portion. */
	MoveToEx(hDC, LFT_BORDER, iDilHeight-BOT_BORDER, NULL);
	LineTo(hDC, iDilWidth-RGT_BORDER, iDilHeight-BOT_BORDER);
	LineTo(hDC, iDilWidth-RGT_BORDER, TOP_BORDER);
     
	/* Restore HDC. */
	SelectObject(hDC, hOldPen);

	/*
	** Draw hint.
	*/                 
	
	/* Setup text. */
	hOldFont = SelectObject(hDC, hDilFont);
	SetTextAlign(hDC, TA_TOP | TA_LEFT);
	SetBkMode(hDC, TRANSPARENT);
	
	/* Setup clipping rectangle. */
	rcClip.left   = LFT_BORDER;
	rcClip.top    = TOP_BORDER;
	rcClip.right  = iDilWidth-RGT_BORDER;
	rcClip.bottom = iDilHeight-BOT_BORDER;
	
	/* Output text. */
	ExtTextOut(hDC, LFT_BORDER + TEXT_OFFSET, TOP_BORDER, ETO_CLIPPED, 
				(LPRECT) &rcClip, (LPSTR) szDilHint, lstrlen((LPSTR) szDilHint), NULL);
	     
	/* Restore HDC. */
	SelectObject(hDC, hOldFont);
	
	/* 
	** Draw mode information.
	*/
	if (iDilMode == DIL_PROGRESS)
	{
		RECT	  rcArea;			/* Area to fill. */
		int	  iMeterWidth;		/* Meter width. */

	     /* Calculate meter width. */
     	iMeterWidth = iDilWidth - LFT_BORDER - RGT_BORDER;
     
		/* Calculate the new area. */
		rcArea.left   = LFT_BORDER;
		rcArea.top    = TOP_BORDER;
		rcArea.right  = (int) (((long) iDilLast * (long) iMeterWidth) / (long) iDilMax);
		rcArea.bottom = iDilHeight - BOT_BORDER + 1;

		/* Adjust for border. */
		rcArea.right += LFT_BORDER;
		
		/* Perform the update. */
		InvertRect(hDC, (LPRECT) &rcArea);
	}
}