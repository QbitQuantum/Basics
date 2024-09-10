BOOL CMediaSettingsPage::OnInitDialog()
{
	CSettingsPage::OnInitDialog();

	m_bEnablePlay		= Settings.MediaPlayer.EnablePlay;
	m_bEnableEnqueue	= Settings.MediaPlayer.EnableEnqueue;

	for ( string_set::const_iterator i = Settings.MediaPlayer.FileTypes.begin() ;
		i != Settings.MediaPlayer.FileTypes.end(); ++i )
	{
		m_wndList.AddString( *i );
	}
	
	m_wndServices.AddString( _T("(") + LoadString( IDS_GENERAL_CUSTOM ) + _T("\x2026)") );
	m_wndServices.AddString( LoadString( IDS_MEDIA_SMPLAYER ) );
	int nSelected = nSnareazaIndex;
	for ( string_set::const_iterator i = Settings.MediaPlayer.ServicePath.begin() ;
		i != Settings.MediaPlayer.ServicePath.end(); ++i )
	{
		CString sPlayer = *i;
		int nAstrix = sPlayer.ReverseFind( _T('*') );
		sPlayer.Remove( _T('*') );
		int nIndex = m_wndServices.AddString( PathFindFileName( sPlayer ) );
		if ( nAstrix != -1 )	// Selected player
			nSelected = nIndex;
		m_wndServices.SetItemDataPtr( nIndex, new CString( sPlayer ) );
	}
	m_wndServices.SetCurSel( nSelected );

	UpdateData( FALSE );

	Update();

	return TRUE;
}