CXTPColorHex::CRgnCell::CRgnCell(CRect& rect, COLORREF color, int u, int d)
: m_color(color)
{
	m_iCell[0] = u;
	m_iCell[1] = d;

	rect.OffsetRect(XTP_CXSMCELL, 0);
	m_rect = rect;

	m_pts[0] = CPoint(rect.left+7, rect.top);
	m_pts[1] = CPoint(rect.right, rect.top+4);
	m_pts[2] = CPoint(rect.right, rect.top+12);
	m_pts[3] = CPoint(rect.left+7, rect.bottom+1);
	m_pts[4] = CPoint(rect.left, rect.top+12);
	m_pts[5] = CPoint(rect.left, rect.top+4);

	VERIFY(CreatePolygonRgn(m_pts, 6, WINDING));
}