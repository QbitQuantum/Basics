void CPgImageProp::DoEnable()
{
	UpdateData( TRUE );

	CWnd *pWnd = GetDlgItem( IDC_WIDTH );
	if ( pWnd != NULL ) pWnd->EnableWindow( m_bCustomSize );
	pWnd = GetDlgItem( IDC_HEIGHT );
	if ( pWnd != NULL ) pWnd->EnableWindow( m_bCustomSize );
}