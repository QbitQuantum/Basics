BOOL CDlgMaintabDownload::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	// get last active tab id in MaintabDownload
	int nLastActiveTab = thePrefs.GetMaintabDownloadLastActiveTab();
	ETabId eLastActiveTabId;
	switch (nLastActiveTab)
	{
	case TI_DOWNLOADING:
		eLastActiveTabId = TI_DOWNLOADING;
		break;
	case TI_DOWNLOADED:
		eLastActiveTabId = TI_DOWNLOADED;
		break;
	case TI_RSSWND:
		eLastActiveTabId = TI_RSSWND;
		break;
	default:
		eLastActiveTabId = TI_DOWNLOADING;
		break;
	}

	ModifyStyle(0, WS_CLIPCHILDREN);

	theWndMgr.SetWndHandle(CWndMgr::WI_MAINTAB_DOWNLOAD_DLG, m_hWnd);

	InitTabs();

	if(thePrefs.GetSplitterbarPositionDownload() == 100)
	{
		m_wndSplitter.m_nflag = 0;
		m_wndSplitter.m_bActive = FALSE;
	}
	else
	{
		m_wndSplitter.m_nflag = 1;
		m_wndSplitter.m_bActive = TRUE;
	}

	//m_wndSplitter.m_nflag = 1;

	CRect rcWnd;
	GetWindowRect(rcWnd);
	ScreenToClient(rcWnd);

	InitControlContainer();

	LONG splitpos = thePrefs.GetSplitterbarPositionDownload() * rcWnd.Height() / 100;

	CRect rcDlgItem;
	m_DownloadTabWnd.GetWindowRect(rcDlgItem);
	ScreenToClient(rcDlgItem);
	rcDlgItem.bottom = splitpos - m_wndSplitter.GetHBreadth();
	m_DownloadTabWnd.MoveWindow(rcDlgItem);

	m_tabwndInfo.GetWindowRect(rcDlgItem);
	ScreenToClient(rcDlgItem);
	rcDlgItem.top = splitpos;
	m_tabwndInfo.MoveWindow(rcDlgItem);

	AddAnchor(m_DownloadTabWnd, TOP_LEFT, CSize(100, thePrefs.GetSplitterbarPositionDownload()));
	AddAnchor(m_wndSplitter, CSize(0, thePrefs.GetSplitterbarPositionDownload()), BOTTOM_RIGHT);
	AddAnchor(m_tabwndInfo, CSize(0, thePrefs.GetSplitterbarPositionDownload()), BOTTOM_RIGHT);

	SetDownloadlistActiveTab(eLastActiveTabId);

	return TRUE; 
}