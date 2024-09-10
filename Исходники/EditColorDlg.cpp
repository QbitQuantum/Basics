LRESULT
CEditColorDlg::OnSetCursor( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
{
	RECT rcColorWnd = { 0 };
	CWindow ColorWnd = GetDlgItem( IDC_COLOR );
	ColorWnd.GetWindowRect( &rcColorWnd );

	DWORD dwPos = GetMessagePos();
	POINT pt = { LOWORD( dwPos ), HIWORD( dwPos ) };

	if( PtInRect( &rcColorWnd, pt ) )
		SetCursor( m_hCursorHand );
	else
		bHandled = FALSE;
	return( 0 );
}