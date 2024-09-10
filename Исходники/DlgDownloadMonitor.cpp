BOOL CDownloadMonitorDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	SkinMe( _T("CDownloadMonitorDlg"), IDI_DOWNLOAD_MONITOR );

	CMenu* pMenu = GetSystemMenu( FALSE );
	pMenu->InsertMenu( 0, MF_BYPOSITION|MF_SEPARATOR, ID_SEPARATOR );
	pMenu->InsertMenu( 0, MF_BYPOSITION|MF_STRING, SC_NEXTWINDOW, _T("&Always on Top") );

	CSingleLock pLock( &Transfers.m_pSection, TRUE );

	if ( Downloads.Check( m_pDownload ) )
	{
		m_sName = m_pDownload->m_sName;
		m_wndIcon.SetIcon( ShellIcons.ExtractIcon(
			ShellIcons.Get( m_sName, 32 ), 32 ) );
		m_wndFile.SetWindowText( m_sName );
	}

	pLock.Unlock();

	m_pGraph	= new CLineGraph();
	m_pItem		= new CGraphItem( 0, 1.0f, RGB( 0xFF, 0, 0 ) );

	m_pGraph->m_bShowLegend		= FALSE;
	m_pGraph->m_bShowAxis		= FALSE;
	m_pGraph->m_crBack			= RGB( 255, 255, 240 );
	m_pGraph->m_crGrid			= RGB( 220, 220, 170 );
	m_pGraph->m_nMinGridVert	= 16;

	m_pGraph->AddItem( m_pItem );

	OnTimer( 1 );

	CenterWindow();
	ShowWindow( SW_SHOW );

	SetTimer( 1, 100, NULL );
	EnableToolTips();

	return TRUE;
}