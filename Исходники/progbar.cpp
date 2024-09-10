void CProgressBar::DoPaint(CDC* pDC)
// Paints the bar, assuming that the background has already been cleared to grey.
// The bar has a percentage display on the left, followed by a progress bar
// which is sized to fit the available space up to a maximum of MAXBARWIDTH pixels
// If there is enough room, the current Job Description will also be displayed, to
// the right of the bar.
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	CControlBar::DoPaint(pDC);      // draw border

	CRect rect;
	GetClientRect(rect);
	CalcInsideRect(rect);

	ASSERT(m_hFont != NULL);
	CFont *OurFont = CHECKFONT(CFont::FromHandle(m_hFont));		// Get a CFont* for this HFONT
	CFont *OldFont = CHECKFONT(pDC->SelectObject(OurFont));

	rect.InflateRect(-CX_BORDER, -CY_BORDER);

	CString PercentText("00%");							// Generate %age string
	if (CurrentPercent > 0 && CurrentPercent < 100)
	{
		if (CurrentPercent > 9)
			PercentText.SetAt(0, (CurrentPercent / 10) + '0');
		PercentText.SetAt(1, (CurrentPercent % 10) + '0');
	}

	pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));		// Draw %age string
	pDC->SetBkColor(GetSysColor(COLOR_BTNFACE));
	pDC->SetBkMode(OPAQUE);
	SetTextAlign(pDC->m_hDC, TA_LEFT | TA_BOTTOM);
	pDC->TextOut(rect.left, rect.bottom, PercentText);

	CSize TextSize = pDC->GetTextExtent(PercentText, 3);

	INT32 BarStart = rect.left + TextSize.cx + 4;			// Calc bar position, size
	INT32 WindowEnd = rect.right - 4;
	INT32 BarWidth = WindowEnd - BarStart;
	
	if (BarWidth < 10) return;		// Not enough room to do a bar!

	if (BarWidth > MAXBARWIDTH) BarWidth = MAXBARWIDTH;

	if (JobDescription != NULL && WindowEnd - BarStart > MAXBARWIDTH + 64)
	{	// If enough room for some text, add the job description
		CString OutText = TEXT(*JobDescription);

		rect.left = BarStart + BarWidth + 4;
		rect.right = WindowEnd;
		pDC->TextOut(rect.left, rect.bottom, OutText);
	}

	CHECKFONT(pDC->SelectObject(OldFont));	// Restore previous font 

	rect.left = BarStart;				// Finally, calc and paint the bar,,,
	rect.right = BarStart+BarWidth;
	rect.bottom -= m_FontDescent - 2;	// Line up bar bottom with text baseline
	Paint3dPlinth(pDC, &rect, FALSE);
	
	BarWidth -= 4;						// Bar is 2 pixels inside plinth rectangle
	rect.left = BarStart + 2;
	rect.top += 2;
	rect.bottom -= 2;
	rect.right = rect.left + (INT32) (((WORD)BarWidth * (WORD)CurrentPercent) / 100);

	CBrush BlueBrush(RGB(0,0,255));
	pDC->FillRect(rect, &BlueBrush);
}