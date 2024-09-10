//*******************************************************************************
BOOL CBCGPChartLineObject::HitTest(const CBCGPPoint& pt) const
{
	double dblWidth = m_format.m_outlineFormat.GetLineWidth(TRUE) / 2;

	CBCGPPoint ptTopLeft = m_rectScreen.TopLeft();
	CBCGPPoint ptBottomRight = m_rectScreen.BottomRight();

	if (ptTopLeft.x == ptBottomRight.x)
	{
		CBCGPRect r = m_rectScreen.NormalizedRect();
		r.InflateRect(dblWidth, dblWidth);
		return r.PtInRect(pt);
	}
	
	double dblACoef = (ptBottomRight.y - ptTopLeft.y) / (ptBottomRight.x - ptTopLeft.x);
	double dblBCoef = ptBottomRight.y - dblACoef * ptBottomRight.x;
	
	double dblY = dblACoef * pt.x + dblBCoef;

	return pt.y > dblY - dblWidth && pt.y < dblY + dblWidth;
}