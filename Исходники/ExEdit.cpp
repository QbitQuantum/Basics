void CExEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	TRACKMOUSEEVENT mouseEvent;

	mouseEvent.cbSize = sizeof( TRACKMOUSEEVENT );
	mouseEvent.dwFlags = TME_HOVER | TME_LEAVE;
	mouseEvent.dwHoverTime = 0;
	mouseEvent.hwndTrack = m_hWnd;

	_TrackMouseEvent( &mouseEvent );

	CEdit::OnMouseMove(nFlags, point);
}