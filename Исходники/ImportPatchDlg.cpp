BOOL CImportPatchDlg::OnInitDialog()
{
	CResizableStandAloneDialog::OnInitDialog();
	CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

	// Let the TaskbarButtonCreated message through the UIPI filter. If we don't
	// do this, Explorer would be unable to send that message to our window if we
	// were running elevated. It's OK to make the call all the time, since if we're
	// not elevated, this is a no-op.
	CHANGEFILTERSTRUCT cfs = { sizeof(CHANGEFILTERSTRUCT) };
	typedef BOOL STDAPICALLTYPE ChangeWindowMessageFilterExDFN(HWND hWnd, UINT message, DWORD action, PCHANGEFILTERSTRUCT pChangeFilterStruct);
	CAutoLibrary hUser = AtlLoadSystemLibraryUsingFullPath(_T("user32.dll"));
	if (hUser)
	{
		ChangeWindowMessageFilterExDFN *pfnChangeWindowMessageFilterEx = (ChangeWindowMessageFilterExDFN*)GetProcAddress(hUser, "ChangeWindowMessageFilterEx");
		if (pfnChangeWindowMessageFilterEx)
		{
			pfnChangeWindowMessageFilterEx(m_hWnd, WM_TASKBARBTNCREATED, MSGFLT_ALLOW, &cfs);
		}
	}
	m_pTaskbarList.Release();
	if (FAILED(m_pTaskbarList.CoCreateInstance(CLSID_TaskbarList)))
		m_pTaskbarList = nullptr;

	CRect rectDummy;

	GetClientRect(m_DlgOrigRect);
	m_cList.GetClientRect(m_PatchListOrigRect);

	CWnd *pwnd=this->GetDlgItem(IDC_AM_DUMY_TAB);
	pwnd->GetWindowRect(&rectDummy);
	this->ScreenToClient(rectDummy);

	if (!m_ctrlTabCtrl.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, IDC_AM_TAB))
	{
		TRACE0("Failed to create output tab window\n");
		return FALSE;      // fail to create
	}
	m_ctrlTabCtrl.SetResizeMode(CMFCTabCtrl::RESIZE_NO);
	// Create output panes:
	//const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	DWORD dwStyle =LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP |LVS_SINGLESEL |WS_CHILD | WS_VISIBLE;

	if( ! this->m_PatchCtrl.Create(_T("Scintilla"),_T("source"),0,rectDummy,&m_ctrlTabCtrl,0,0) )
	{
		TRACE0("Failed to create log message control");
		return FALSE;
	}
	m_PatchCtrl.Init(0);
	m_PatchCtrl.Call(SCI_SETREADONLY, TRUE);
	m_PatchCtrl.SetUDiffStyle();

	dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutput.Create(_T("Scintilla"),_T("source"),0,rectDummy, &m_ctrlTabCtrl, 0,0) )
	{
		TRACE0("Failed to create output windows\n");
		return -1;      // fail to create
	}
	m_wndOutput.Init(0);
	m_wndOutput.Call(SCI_SETREADONLY, TRUE);

	m_tooltips.Create(this);

	m_tooltips.AddTool(IDC_CHECK_3WAY,IDS_AM_3WAY_TT);
	m_tooltips.AddTool(IDC_CHECK_IGNORE_SPACE,IDS_AM_IGNORE_SPACE_TT);

	m_ctrlTabCtrl.AddTab(&m_PatchCtrl, CString(MAKEINTRESOURCE(IDS_PATCH)), 0);
	m_ctrlTabCtrl.AddTab(&m_wndOutput, CString(MAKEINTRESOURCE(IDS_LOG)), 1);

	AddAmAnchor();
	AdjustControlSize(IDC_CHECK_3WAY);
	AdjustControlSize(IDC_CHECK_IGNORE_SPACE);
	AdjustControlSize(IDC_SIGN_OFF);
	AdjustControlSize(IDC_KEEP_CR);

	m_PathList.SortByPathname(true);
	m_cList.SetExtendedStyle( m_cList.GetExtendedStyle()| LVS_EX_CHECKBOXES );

	for (int i = 0; i < m_PathList.GetCount(); ++i)
	{
		m_cList.InsertItem(0,m_PathList[i].GetWinPath());
		m_cList.SetCheck(0,true);
	}

	DWORD yPos = CRegDWORD(_T("Software\\TortoiseGit\\TortoiseProc\\ResizableState\\AMDlgSizer"));
	RECT rcDlg, rcLogMsg, rcFileList;
	GetClientRect(&rcDlg);
	m_cList.GetWindowRect(&rcLogMsg);
	ScreenToClient(&rcLogMsg);
	this->m_ctrlTabCtrl.GetWindowRect(&rcFileList);
	ScreenToClient(&rcFileList);
	if (yPos)
	{
		RECT rectSplitter;
		m_wndSplitter.GetWindowRect(&rectSplitter);
		ScreenToClient(&rectSplitter);
		int delta = yPos - rectSplitter.top;
		if ((rcLogMsg.bottom + delta > rcLogMsg.top)&&(rcLogMsg.bottom + delta < rcFileList.bottom - 30))
		{
			m_wndSplitter.SetWindowPos(NULL, 0, yPos, 0, 0, SWP_NOSIZE);
			DoSize(delta);
		}
	}

	CAppUtils::SetListCtrlBackgroundImage(m_cList.GetSafeHwnd(), IDI_IMPORTPATHCES_BKG);

	CString sWindowTitle;
	GetWindowText(sWindowTitle);
	CAppUtils::SetWindowTitle(m_hWnd, g_Git.m_CurrentDir, sWindowTitle);

	EnableSaveRestore(_T("ImportDlg"));

	SetSplitterRange();

	return TRUE;
}