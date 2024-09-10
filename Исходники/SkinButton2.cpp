void CSkinButton2::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bUseResponseRect && !m_rcResponse.PtInRect(point))
	{
		//CButton::OnMouseMove(nFlags, point);
		SendMouseMessageToParent(WM_MOUSEMOVE, nFlags, point);
		return;
	}
	if( !m_bSelected && IsWindowEnabled()&&m_bHandMouse )
	{
#ifndef IDC_HAND
#define IDC_HAND            MAKEINTRESOURCE(32649)
#endif
		::SetCursor(::LoadCursor(NULL, IDC_HAND));
	}

	if (!m_bMouseOnButton) 
	{ 
		TRACKMOUSEEVENT   tme; 
		tme.cbSize   =   sizeof(tme); 
		tme.hwndTrack   =   m_hWnd; 
		tme.dwFlags   =   TME_LEAVE   |   TME_HOVER; 
		tme.dwHoverTime   =   1; 
		m_bMouseOnButton   =   _TrackMouseEvent(&tme); 
	} 
	CButton::OnMouseMove(nFlags, point);
}