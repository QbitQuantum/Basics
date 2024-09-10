LRESULT CSelProcDlg::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	m_hProc = NULL;

	DlgResize_Init( false );

	m_lst.SubclassWindow( GetDlgItem( IDC_PROCESS_LIST ) );
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_HEADERDRAGDROP;
	m_lst.SetExtendedListViewStyle( dwStyle );

	TCHAR szHeaders[128];
	AtlLoadString( IDS_PROCESS_LIST_HEADER, szHeaders, _countof(szHeaders) );

	RECT rect;
	m_lst.GetWindowRect( &rect );
	int nWidth = rect.right - rect.left;

	int nIndex = 0;
	LPCTSTR sz = _tcstok( szHeaders, _T("\n") );
	while( sz != NULL )
	{
		int w = _ttoi(_tcstok( NULL, _T("\n") )) * nWidth / 100;
		m_lst.InsertColumn( nIndex++, sz, LVCFMT_LEFT, w, 0 );
		sz = _tcstok( NULL, _T("\n") );
	}

	m_lst.SetColumnSortType( 0, LVCOLSORT_TEXTNOCASE );
	m_lst.SetColumnSortType( 1, LVCOLSORT_LONG );
	m_lst.SetColumnSortType( 2, LVCOLSORT_TEXTNOCASE );
	m_lst.SetSortColumn( 0 );

	RefreshProcessList();
	return TRUE;
}