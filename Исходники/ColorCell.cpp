BOOL CColorCell::HitTest(CPoint point)
{
	if (m_bAtFirstType)
	{
		CRgn rgn;
		rgn.CreatePolygonRgn(m_Points, 6, ALTERNATE);
		return rgn.PtInRegion(point);
	}
	else
	{
		CRgn rgn;
		rgn.CreateRectRgn(m_rcPosition.left, m_rcPosition.top, m_rcPosition.right, m_rcPosition.bottom);
		return rgn.PtInRegion(point);
	}
}