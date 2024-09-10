void CHyperlink::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_Hovering) {
		TRACKMOUSEEVENT	tme;
		memset(&tme, 0, sizeof(tme));
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		_TrackMouseEvent(&tme);	// request WM_MOUSELEAVE notification
		m_Hovering = TRUE;
		Invalidate();
	}
	CStatic::OnMouseMove(nFlags, point);
}