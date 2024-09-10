BOOL CRemoteSettingsPage::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint point;
	GetCursorPos( &point );
	CRect rect;
	m_wndURL.GetWindowRect( &rect );

	if ( rect.PtInRect( point ) && m_wndURL.IsWindowEnabled() )
	{
		SetCursor( AfxGetApp()->LoadCursor( IDC_HAND ) );
		return TRUE;
	}
	else
	{
		return CSettingsPage::OnSetCursor( pWnd, nHitTest, message );
	}
}