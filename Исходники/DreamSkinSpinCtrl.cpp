LRESULT CDreamSkinSpinCtrl::OnMouseMove(UINT nFlags, POINTS point)
{
	TRACKMOUSEEVENT EventTrack;
	EventTrack.cbSize = sizeof(TRACKMOUSEEVENT);
	EventTrack.dwFlags = TME_LEAVE;
	EventTrack.hwndTrack = m_hWnd;
	EventTrack.dwHoverTime = 0;

	TrackMouseEvent(&EventTrack);

	POINT pt;
	pt.x = point.x;
	pt.y = point.y;

	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);

	RECT rcClient;
	::GetClientRect(m_hWnd, &rcClient);

	int nHover = SpinCtrlHitTest(rcClient, pt, dwStyle);
	if (m_nHover != nHover)
	{
		m_nHover = nHover;
		::InvalidateRect(m_hWnd, &rcClient, FALSE);
	}

	return 0;
}