void CSwingCheckBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rectItem(lpDIS->rcItem);

	CRect rectCheck(rectItem);
	rectCheck.right = rectCheck.left + 12;
	rectCheck.bottom = rectCheck.top + 12;

	CPoint TopLeft(rectCheck.left, rectCheck.top);
	CPoint BottomRight(rectCheck.right, rectCheck.bottom);
	CPoint TopRight(rectCheck.right, rectCheck.top);
	CPoint BottomLeft(rectCheck.left, rectCheck.bottom);
	// TODO: Add your code to draw the specified item

	pDC->SelectObject(&nInactiveBrush);
	pDC->SelectStockObject(NULL_PEN);
	pDC->Rectangle(rectItem);

	pDC->SelectObject(&nDarkBorder);
	pDC->MoveTo(TopLeft);
	pDC->LineTo(TopRight);
	pDC->MoveTo(TopLeft);
	pDC->LineTo(BottomLeft);

	pDC->MoveTo(BottomLeft.x, BottomLeft.y - 1);
	pDC->LineTo(BottomRight.x, BottomRight.y - 1);
	pDC->MoveTo(BottomRight.x - 1, BottomRight.y);
	pDC->LineTo(TopRight.x - 1, TopRight.y);

	pDC->SelectObject(&nWhiteBorder);

	pDC->MoveTo(BottomLeft);
	pDC->LineTo(BottomRight);
	pDC->MoveTo(BottomRight);
	pDC->LineTo(TopRight);

	pDC->MoveTo(TopLeft.x + 1, TopLeft.y + 1);
	pDC->LineTo(TopRight.x - 1, TopRight.y + 1);
	pDC->MoveTo(TopLeft.x + 1, TopLeft.y + 1);
	pDC->LineTo(BottomLeft.x + 1, BottomLeft.y - 1);

	pDC->SelectStockObject(DEFAULT_GUI_FONT);
	pDC->TextOut(16, 0, m_strCaption);

	if (m_Checked)
	{
		pDC->SelectObject(&nCheck);
		pDC->MoveTo(2, 3);
		pDC->LineTo(3, 8);
		pDC->MoveTo(3, 9);
		pDC->LineTo(9, 3);
	}

	if (lpDIS->itemState & ODS_FOCUS)
	{
		pDC->SelectObject(&nSelectedBorder);
		pDC->SelectStockObject(NULL_BRUSH);
		int xlen = pDC->GetTextExtent(m_strCaption).cx;

		pDC->Rectangle(15, 0, 13 + xlen + 3, 12);
	}

}