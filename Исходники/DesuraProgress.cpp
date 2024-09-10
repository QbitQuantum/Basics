void DesuraProgress::OnMouseMove(UINT nFlags, CPoint point) 
{
	bool old = m_bMouseOver;

	CRect rect = getCancelRect();
	m_bMouseOver = rect.PtInRect(point);

	if (old != m_bMouseOver)
		refresh();

	if (m_bDragging)
	{
		CPoint pos = point - m_StartPoint;
		ClientToScreen(pos);
		GetParent()->SetWindowPos(pos.x-4, pos.y-26, 0, 0, SWP_NOSIZE);
	}
}