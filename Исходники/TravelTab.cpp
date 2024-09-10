void CTravelTab::OnRButtonDown(UINT nFlags, CPoint point) 
{
	ClientToScreen(&point);
	CRect rect;
	m_TravelMap.GetWindowRect(&rect);
	if ( rect.PtInRect(point) )
	{
		xscroll = point.x-rect.left;
		yscroll = point.y-rect.top;
	}
	else
	{
		ScreenToClient(&point);
		CDockingPage::OnRButtonDown(nFlags, point);
	}
}