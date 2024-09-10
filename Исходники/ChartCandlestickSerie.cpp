bool CChartCandlestickSerie::IsPointOnSerie(const CPoint& screenPoint, 
											unsigned& uIndex) const
{
	uIndex = INVALID_POINT;
	if (!m_bIsVisible)
		return false;

	unsigned uFirst=0, uLast=0;
	if (!GetVisiblePoints(uFirst,uLast))
		return false;
	if (uFirst>0)
		uFirst--;
	if (uLast<GetPointsCount())
		uLast++;

	bool bResult = false;
	for (unsigned i=uFirst ; i < uLast ; i++)
	{
		SChartCandlestickPoint Point = GetPoint(i);
		int ScreenXVal = m_pHorizontalAxis->ValueToScreen(Point.XVal);
		int ScreenLow = m_pVerticalAxis->ValueToScreen(Point.Low);
		int ScreenHigh = m_pVerticalAxis->ValueToScreen(Point.High);

		int halfWidth = m_iCandlestickWidth/2;
		CRect Rectangle;
		if (ScreenLow > ScreenHigh) 
			Rectangle.SetRect(ScreenXVal-halfWidth, ScreenHigh,
			ScreenXVal+halfWidth+1, ScreenLow+1);
		else 
			Rectangle.SetRect(ScreenXVal-halfWidth, ScreenLow,
			ScreenXVal+halfWidth+1, ScreenHigh+1);
		if (Rectangle.PtInRect(screenPoint))
		{
			bResult = true;
			uIndex = i;
			break;
		}
	}
	return bResult; 
}