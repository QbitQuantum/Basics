//Êó±êÒÆ¶¯
void HButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bOver)//×¢²áÏûÏ¢
	{
		TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, 0};
		TrackMouseEvent(&tme);
		m_bOver = TRUE;
		Invalidate();
	}
	CButton::OnMouseMove(nFlags, point);
}