LRESULT CSkinScrollWnd::OnVThumbTrack( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if ( FALSE == ::IsWindow ( ( HWND ) lParam ) )
	{
		return 0;
	}
	CScrollBar ScrollBarWnd;
	ScrollBarWnd.Attach ( ( HWND ) lParam );
	CWindow Wnd = m_MidWnd.GetWindow ( GW_CHILD );
	INT32 nPos =  wParam ;
	m_bOperation = TRUE;
	if ( m_nPos != nPos )
	{
		Wnd.SendMessage ( WM_VSCROLL, MAKELONG ( SB_THUMBTRACK, nPos ), nPos  );
	}
	m_nPos = nPos;
	m_bOperation = FALSE;
	SCROLLINFO SInfo = { 0x00 };
	SInfo.cbSize = sizeof ( SInfo );
	SInfo.fMask = SIF_ALL;
	::GetScrollInfo ( Wnd.m_hWnd, SB_VERT, &SInfo );
	ScrollBarWnd.SetScrollInfo ( &SInfo );

	return 0;
}