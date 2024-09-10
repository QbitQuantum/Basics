void CBarButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	if (m_bLButtonDown 
		&& rect.PtInRect(point)
		&& m_hNotify
		&& m_uMsg)
		::PostMessage(m_hNotify, m_uMsg, GetDlgCtrlID(), 0);

	m_bLButtonDown = FALSE;

	Repaint();

	CButton::OnLButtonUp(nFlags, point);
}