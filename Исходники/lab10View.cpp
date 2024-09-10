void Clab10View::DesenhaRetangulo(CRetangulo r)
{
	Clab10Doc *pDoc = GetDocument();
	CDC *pDC = GetDC();

	CBrush brush(r.m_brush);
	CPen pen(PS_SOLID, 4, r.m_pen);

	pDC->SelectObject(brush);
	pDC->SelectObject(pen);

	pDC->Rectangle(r.m_area);
	ReleaseDC(pDC);
}