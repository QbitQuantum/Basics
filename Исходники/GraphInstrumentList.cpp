// 画网格图
void CGraphInstrumentList::DrawGrid(CDC* pDC, int iPaperX, int iPaperY, int iGridX, int iGridY)
{

	COLORREF oldBkColor = m_oPaperColor;

	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = iPaperX;
	rect.bottom = iPaperY;

	// Center lines
	CPen penDash;
	penDash.CreatePen(PS_DASH, 0, m_oGridColor);
	CPen* pOldPen = pDC->SelectObject(&penDash);

	pDC->MoveTo(0, rect.top);
	pDC->LineTo(0, rect.bottom);
	pDC->MoveTo(rect.left, 0);
	pDC->LineTo(rect.right, 0);

	// Major unit lines
	CPen penDot;
	penDot.CreatePen(PS_DOT, 0, m_oGridColor);
	pDC->SelectObject(&penDot);

	for (int x = 0; x < rect.right; x += iGridX)
	{
		if (x != 0)
		{
			pDC->MoveTo(x, rect.top);
			pDC->LineTo(x, rect.bottom);
		}
	}

	for (int y = 0; y < rect.bottom; y += iGridY)
	{
		if (y != 0)
		{
			pDC->MoveTo(rect.left, y);
			pDC->LineTo(rect.right, y);
		}
	}

	// Outlines
	CPen penSolid;
	penSolid.CreatePen(PS_SOLID, 0, m_oGridColor);
	pDC->SelectObject(&penSolid);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(rect.left, rect.bottom);
	pDC->LineTo(rect.left, rect.top);

	pDC->SelectObject(pOldPen);
	pDC->SetBkColor(oldBkColor);
}