static void ColorBox(CDC* pDC, CPoint pt, COLORREF clr, BOOL bHover)
{
	CBrush br(clr);

	CBrush* obr = pDC->SelectObject(&br);

	pDC->PatBlt(pt.x, pt.y, 13, 13, PATCOPY);
	pDC->SelectObject(obr);

	CRect rc;
	rc.SetRect(pt.x - 2, pt.y - 2, pt.x + 15, pt.y + 15);

	pDC->DrawEdge(&rc, (bHover) ? BDR_SUNKENOUTER : BDR_RAISEDINNER, BF_RECT);
}