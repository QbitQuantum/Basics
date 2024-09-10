void CWzEmailPg2::DoEnable()
{
	CWnd *pWnd = GetDlgItem( IDC_USERNAME );
	if ( pWnd != NULL ) pWnd->EnableWindow( m_bLogin );
	pWnd = GetDlgItem( IDC_PASSWORD );
	if ( pWnd != NULL ) pWnd->EnableWindow( m_bLogin );

	pWnd = GetDlgItem( IDC_AUTHDETECT );
	if ( pWnd != NULL ) pWnd->EnableWindow( m_bLogin );
	pWnd = GetDlgItem( IDC_AUTHTYPE );
	if ( pWnd != NULL ) pWnd->EnableWindow( m_bLogin && !m_bAuthDetect );

}