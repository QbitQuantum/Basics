void CSynBCGPEditCtrl::OnDrawLineNumbersBar( CDC* pDC, CRect rect )
{
	ASSERT_VALID (pDC);

	pDC->FillSolidRect (rect, m_clrBackLineNumber);

	// Draw dividing line:
	rect.DeflateRect (0, 0, 1, 0);

	WORD wHatchBits1 [8] = { 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 };
	WORD wHatchBits2 [8] = { 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF };

	CBitmap bmpPattern;
	bmpPattern.CreateBitmap (8, 8, 1, 1, 
		(rect.top % 2) ? wHatchBits1 : wHatchBits2);

	CBrush br;
	br.CreatePatternBrush (&bmpPattern);

	CRect rectLine = rect;
	rectLine.left = rectLine.right - 1;

	COLORREF clrTextOld = pDC->SetTextColor (m_clrBackSidebar);

	pDC->FillRect (rectLine, &br);
	pDC->SetTextColor (clrTextOld);

	rect.DeflateRect (0, 0, 1, 0);

	// Determine start and end offsets of the visible part of buffer
	CPoint ptTopLeft (m_rectText.left + 1, m_rectText.top);
	CPoint ptBottomRight (m_rectText.right - 1, m_rectText.bottom - 1);

	int nStartOffset = HitTest (ptTopLeft);
	int nEndOffset = HitTest (ptBottomRight);

	if (nStartOffset == -1)
	{
		nStartOffset = 0;
	}

	if (nEndOffset == -1)
	{
		nEndOffset = m_strBuffer.GetLength () - 1;
	}

	nEndOffset = min (nEndOffset, m_strBuffer.GetLength ());

	int nRowColumnTop = RowFromOffset (nStartOffset);
	int nRowColumnBottom = RowFromOffset (nEndOffset);

	// Draw line numbers:
	int nRow = nRowColumnTop;
	int nVirtualRow = GetVirtualRow (nRow);
	int nRowStartOffset = nStartOffset;

	while (nRow <= nRowColumnBottom && nRowStartOffset >= 0)
	{
		CRect rect (rect);
		rect.top = (nVirtualRow - m_nScrollOffsetVert) * m_nLineHeight;
		rect.bottom = rect.top + m_nLineHeight;
		OnDrawLineNumber (pDC, rect, nRow);

		NextRow (nRow, nVirtualRow, nRowStartOffset);
	}
}