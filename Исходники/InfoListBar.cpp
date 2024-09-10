// At the creation
//
int CInfoListBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndMyListCtrl.Create(LVS_REPORT|WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_SINGLESEL|LVS_OWNERDRAWFIXED,CRect(0,0,0,0), this, 30003))
        return -1;

	if( !m_wndIcon.Create(NULL,SS_BITMAP|WS_CHILD|WS_VISIBLE,CRect(0,0,110,100), this, 2))
		return -1;
	m_bmp.LoadBitmap(IDB_INFOLIST);
	m_wndIcon.SetBitmap( (HBITMAP) m_bmp );

	CString StrResource;
	StrResource.LoadString( IDS_INFOBAR );
	if( !m_wndText.Create( StrResource ,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), this, 3))
		return -1;

    if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		if (!m_font.CreatePointFont(80, _T("MS Sans Serif")))
            return -1;

    m_wndText.SetFont(&m_font);

	// Define the minimum size of this window
	m_szMin.cx = 110;
	m_szMin.cy = 100;

	m_ImageList.Create( IDB_IMAGELIST_INFO, 16, 3, RGB(255,0,255) );

	m_wndMyListCtrl.SetSpecialList( true );

	m_wndMyListCtrl.SetImageList( &m_ImageList, LVSIL_SMALL );
	CString Str;
	Str.LoadStringW( IDS_INFO_COLUMN );
	CGlobalIHM::CreateColumnListCtrl( &m_wndMyListCtrl, Str );
	LVCOLUMN Column;
	Column.mask = LVCF_FMT;
	Column.fmt = LVCFMT_CENTER;
	m_wndMyListCtrl.SetColumn( 1, &Column );

    return 0;
}