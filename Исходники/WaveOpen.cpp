void CWaveOpen::OnFileNameChange() {
	CString str = GetPathName();
	str.MakeLower();
	CWnd *pWnd = GetDlgItem( IDC_BTN_PLAY );
	if( pWnd == NULL ) {
		return;
	}
	if( str.Find( ".wav" ) >= 0 ) {
		pWnd->EnableWindow( TRUE );
	} else {
		pWnd->EnableWindow( FALSE );
	}
}