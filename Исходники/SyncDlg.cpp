BOOL CSyncDlg::OnInitDialog()
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

	this->GetDlgItem(IDC_CHECK_PUTTY_KEY)->EnableWindow(CAppUtils::IsSSHPutty());

	/*
	this->m_ctrlAnimate.ShowWindow(SW_NORMAL);
	this->m_ctrlAnimate.Open(IDR_DOWNLOAD);
	this->m_ctrlAnimate.Play(0,-1,-1);
	*/

	// ------------------ Create Tabctrl -----------
	CWnd *pwnd=this->GetDlgItem(IDC_BUTTON_TABCTRL);
	CRect rectDummy;
	pwnd->GetWindowRect(&rectDummy);
	this->ScreenToClient(rectDummy);

	if (!m_ctrlTabCtrl.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, IDC_SYNC_TAB))
	{
		TRACE0("Failed to create output tab window\n");
		return FALSE;      // fail to create
	}
	m_ctrlTabCtrl.SetResizeMode(CMFCTabCtrl::RESIZE_NO);

	// -------------Create Command Log Ctrl ---------
	DWORD dwStyle;
	dwStyle= ES_MULTILINE | ES_READONLY | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL |WS_VSCROLL  ;

	if( !m_ctrlCmdOut.Create(dwStyle,rectDummy,&m_ctrlTabCtrl,IDC_CMD_LOG))
	{
		TRACE0("Failed to create Log commits window\n");
		return FALSE;      // fail to create
	}

	// set the font to use in the log message view, configured in the settings dialog
	CFont m_logFont;
	CAppUtils::CreateFontForLogs(m_logFont);
	//GetDlgItem(IDC_CMD_LOG)->SetFont(&m_logFont);
	m_ctrlCmdOut.SetFont(&m_logFont);
	m_ctrlTabCtrl.InsertTab(&m_ctrlCmdOut, CString(MAKEINTRESOURCE(IDS_LOG)), -1);

	//m_ctrlCmdOut.ReplaceSel(_T("Hello"));

	//----------  Create in coming list ctrl -----------
	dwStyle =LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | LVS_OWNERDATA | WS_BORDER | WS_TABSTOP | WS_CHILD | WS_VISIBLE;;

	if( !m_InLogList.Create(dwStyle,rectDummy,&m_ctrlTabCtrl,IDC_IN_LOGLIST))
	{
		TRACE0("Failed to create output commits window\n");
		return FALSE;      // fail to create
	}

	m_ctrlTabCtrl.InsertTab(&m_InLogList, CString(MAKEINTRESOURCE(IDS_PROC_SYNC_INCOMMITS)), -1);

	m_InLogList.m_ColumnRegKey=_T("SyncIn");
	m_InLogList.InsertGitColumn();

	//----------- Create In Change file list -----------
	dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP |LVS_SINGLESEL |WS_CHILD | WS_VISIBLE;

	if( !m_InChangeFileList.Create(dwStyle,rectDummy,&m_ctrlTabCtrl,IDC_IN_CHANGELIST))
	{
		TRACE0("Failed to create output change files window\n");
		return FALSE;      // fail to create
	}
	m_ctrlTabCtrl.InsertTab(&m_InChangeFileList, CString(MAKEINTRESOURCE(IDS_PROC_SYNC_INCHANGELIST)), -1);

	m_InChangeFileList.Init(GITSLC_COLEXT | GITSLC_COLSTATUS |GITSLC_COLADD|GITSLC_COLDEL , _T("InSyncDlg"),
							(CGitStatusListCtrl::GetContextMenuBit(CGitStatusListCtrl::IDGITLC_COMPARETWO)|
							CGitStatusListCtrl::GetContextMenuBit(CGitStatusListCtrl::IDGITLC_GNUDIFF2)), false, true, GITSLC_COLEXT | GITSLC_COLSTATUS | GITSLC_COLADD| GITSLC_COLDEL);


	//---------- Create Conflict List Ctrl -----------------
	dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP | WS_CHILD | WS_VISIBLE;

	if( !m_ConflictFileList.Create(dwStyle,rectDummy,&m_ctrlTabCtrl,IDC_IN_CONFLICT))
	{
		TRACE0("Failed to create output change files window\n");
		return FALSE;      // fail to create
	}
	m_ctrlTabCtrl.InsertTab(&m_ConflictFileList, CString(MAKEINTRESOURCE(IDS_PROC_SYNC_CONFLICTS)), -1);

	m_ConflictFileList.Init(GITSLC_COLEXT | GITSLC_COLSTATUS |GITSLC_COLADD|GITSLC_COLDEL , _T("ConflictSyncDlg"),
							(CGitStatusListCtrl::GetContextMenuBit(CGitStatusListCtrl::IDGITLC_COMPARETWO)|
							CGitStatusListCtrl::GetContextMenuBit(CGitStatusListCtrl::IDGITLC_GNUDIFF2)|
							GITSLC_POPCONFLICT|GITSLC_POPRESOLVE),false);


	//----------  Create Commit Out List Ctrl---------------

	dwStyle =LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | LVS_OWNERDATA | WS_BORDER | WS_TABSTOP | WS_CHILD | WS_VISIBLE;;

	if( !m_OutLogList.Create(dwStyle,rectDummy,&m_ctrlTabCtrl,IDC_OUT_LOGLIST))
	{
		TRACE0("Failed to create output commits window\n");
		return FALSE;      // fail to create

	}

	m_ctrlTabCtrl.InsertTab(&m_OutLogList, CString(MAKEINTRESOURCE(IDS_PROC_SYNC_OUTCOMMITS)), -1);

	m_OutLogList.m_ColumnRegKey = _T("SyncOut");
	m_OutLogList.InsertGitColumn();

	//------------- Create Change File List Control ----------------

	dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP |LVS_SINGLESEL |WS_CHILD | WS_VISIBLE;

	if( !m_OutChangeFileList.Create(dwStyle,rectDummy,&m_ctrlTabCtrl,IDC_OUT_CHANGELIST))
	{
		TRACE0("Failed to create output change files window\n");
		return FALSE;      // fail to create
	}
	m_ctrlTabCtrl.InsertTab(&m_OutChangeFileList, CString(MAKEINTRESOURCE(IDS_PROC_SYNC_OUTCHANGELIST)), -1);

	m_OutChangeFileList.Init(GITSLC_COLEXT | GITSLC_COLSTATUS | GITSLC_COLADD | GITSLC_COLDEL, _T("OutSyncDlg"),
							(CGitStatusListCtrl::GetContextMenuBit(CGitStatusListCtrl::IDGITLC_COMPARETWO)|
							CGitStatusListCtrl::GetContextMenuBit(CGitStatusListCtrl::IDGITLC_GNUDIFF2)), false, true, GITSLC_COLEXT | GITSLC_COLSTATUS | GITSLC_COLADD| GITSLC_COLDEL);

	if (!m_GitProgressList.Create(dwStyle | LVS_OWNERDATA, rectDummy, &m_ctrlTabCtrl, IDC_CMD_GIT_PROG))
	{
		TRACE0("Failed to create Git Progress List Window\n");
		return FALSE;      // fail to create
	}
	m_ctrlTabCtrl.InsertTab(&m_GitProgressList, CString(MAKEINTRESOURCE(IDS_LOG)), -1);
	m_GitProgressList.m_pAnimate = &m_ctrlAnimate;
	m_GitProgressList.m_pPostWnd = this;
	m_GitProgressList.m_pProgressLabelCtrl = &m_ctrlProgLabel;
	m_GitProgressList.m_pProgControl = &m_ctrlProgress;
	m_GitProgressList.m_pTaskbarList = m_pTaskbarList;

	dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP | WS_CHILD | WS_VISIBLE;
	DWORD exStyle = LVS_EX_HEADERDRAGDROP | LVS_EX_DOUBLEBUFFER | LVS_EX_INFOTIP | LVS_EX_FULLROWSELECT;
	m_refList.Create(dwStyle, rectDummy, &m_ctrlTabCtrl, IDC_REFLIST);
	m_refList.SetExtendedStyle(exStyle);
	m_refList.Init();
	m_ctrlTabCtrl.InsertTab(&m_refList, CString(MAKEINTRESOURCE(IDS_REFLIST)), -1);

	this->m_tooltips.Create(this);

	AddAnchor(IDC_SYNC_TAB,TOP_LEFT,BOTTOM_RIGHT);

	AddAnchor(IDC_GROUP_INFO,TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_COMBOBOXEX_URL,TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_BUTTON_MANAGE,TOP_RIGHT);
	AddAnchor(IDC_BUTTON_PULL,BOTTOM_LEFT);
	AddAnchor(IDC_BUTTON_PUSH,BOTTOM_LEFT);
	AddAnchor(IDC_BUTTON_SUBMODULE,BOTTOM_LEFT);
	AddAnchor(IDC_BUTTON_STASH,BOTTOM_LEFT);
	AddAnchor(IDC_BUTTON_APPLY,BOTTOM_RIGHT);
	AddAnchor(IDC_BUTTON_EMAIL,BOTTOM_RIGHT);
	AddAnchor(IDC_PROGRESS_SYNC,TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDOK,BOTTOM_RIGHT);
	AddAnchor(IDHELP,BOTTOM_RIGHT);
	AddAnchor(IDC_STATIC_STATUS, BOTTOM_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_ANIMATE_SYNC,TOP_LEFT);
	AddAnchor(IDC_BUTTON_COMMIT,BOTTOM_LEFT);
	AddAnchor(IDC_LOG, BOTTOM_LEFT);

	// do not use BRANCH_COMBOX_ADD_ANCHOR here, we want to have different stylings
	AddAnchor(IDC_COMBOBOXEX_LOCAL_BRANCH, TOP_LEFT,TOP_CENTER);
	AddAnchor(IDC_COMBOBOXEX_REMOTE_BRANCH, TOP_CENTER, TOP_RIGHT);
	AddAnchor(IDC_BUTTON_LOCAL_BRANCH, TOP_CENTER);
	AddAnchor(IDC_BUTTON_REMOTE_BRANCH, TOP_RIGHT);
	AddAnchor(IDC_STATIC_REMOTE_BRANCH, TOP_CENTER);
	AddAnchor(IDC_PROG_LABEL, TOP_LEFT);

	AdjustControlSize(IDC_CHECK_PUTTY_KEY);
	AdjustControlSize(IDC_CHECK_FORCE);

	CString WorkingDir=g_Git.m_CurrentDir;
	WorkingDir.Replace(_T(':'),_T('_'));
	m_RegKeyRemoteBranch = CString(_T("Software\\TortoiseGit\\History\\SyncBranch\\"))+WorkingDir;


	this->AddOthersToAnchor();

	this->m_ctrlPush.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_PUSH)));
	this->m_ctrlPush.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_PUSHTAGS)));
	this->m_ctrlPush.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_PUSHNOTES)));

	this->m_ctrlPull.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_PULL)));
	this->m_ctrlPull.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_FETCH)));
	this->m_ctrlPull.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_FETCHREBASE)));
	this->m_ctrlPull.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_REMOTEUPDATE)));
	this->m_ctrlPull.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_CLEANUPSTALEBRANCHES)));

	this->m_ctrlSubmodule.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_SUBKODULEUPDATE)));
	this->m_ctrlSubmodule.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_SUBKODULEINIT)));
	this->m_ctrlSubmodule.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_SYNC_SUBKODULESYNC)));

	this->m_ctrlStash.AddEntry(CString(MAKEINTRESOURCE(IDS_MENUSTASHSAVE)));
	this->m_ctrlStash.AddEntry(CString(MAKEINTRESOURCE(IDS_MENUSTASHPOP)));
	this->m_ctrlStash.AddEntry(CString(MAKEINTRESOURCE(IDS_MENUSTASHAPPLY)));

	WorkingDir.Replace(_T(':'),_T('_'));

	CString regkey ;
	regkey.Format(_T("Software\\TortoiseGit\\TortoiseProc\\Sync\\%s"),WorkingDir);

	this->m_regPullButton = CRegDWORD(regkey+_T("\\Pull"),0);
	this->m_regPushButton = CRegDWORD(regkey+_T("\\Push"),0);
	this->m_regSubmoduleButton = CRegDWORD(regkey+_T("\\Submodule"));
	this->m_regAutoLoadPutty = CRegDWORD(regkey + _T("\\AutoLoadPutty"), CAppUtils::IsSSHPutty());

	this->UpdateData();
	this->m_bAutoLoadPuttyKey  = m_regAutoLoadPutty;
	if(!CAppUtils::IsSSHPutty())
		m_bAutoLoadPuttyKey = false;
	this->UpdateData(FALSE);

	this->m_ctrlPull.SetCurrentEntry(this->m_regPullButton);
	this->m_ctrlPush.SetCurrentEntry(this->m_regPushButton);
	this->m_ctrlSubmodule.SetCurrentEntry(this->m_regSubmoduleButton);

	CString sWindowTitle;
	GetWindowText(sWindowTitle);
	CAppUtils::SetWindowTitle(m_hWnd, g_Git.m_CurrentDir, sWindowTitle);

	EnableSaveRestore(_T("SyncDlg"));

	m_ctrlURL.SetCaseSensitive(TRUE);
	this->m_ctrlURL.LoadHistory(CString(_T("Software\\TortoiseGit\\History\\SyncURL\\"))+WorkingDir, _T("url"));

	STRING_VECTOR list;

	if(!g_Git.GetRemoteList(list))
	{
		for (unsigned int i = 0; i < list.size(); ++i)
		{
			m_ctrlURL.AddString(list[i]);
		}
	}
	m_ctrlURL.SetCurSel(0);
	m_ctrlRemoteBranch.SetCurSel(0);
	m_ctrlURL.SetURLHistory(true);

	this->LoadBranchInfo();

	this->m_bInited=true;
	FetchOutList();

	m_ctrlTabCtrl.ShowTab(IDC_CMD_LOG-1,false);
	m_ctrlTabCtrl.ShowTab(IDC_IN_LOGLIST-1,false);
	m_ctrlTabCtrl.ShowTab(IDC_IN_CHANGELIST-1,false);
	m_ctrlTabCtrl.ShowTab(IDC_IN_CONFLICT-1,false);
	m_ctrlTabCtrl.ShowTab(IDC_CMD_GIT_PROG-1, false);
	m_ctrlTabCtrl.ShowTab(IDC_REFLIST-1, false);

	m_ctrlRemoteBranch.m_bWantReturn = TRUE;
	m_ctrlURL.m_bWantReturn = TRUE;

	this->m_Gitverion = CAppUtils::GetMsysgitVersion();

	if (m_seq > 0 && (DWORD)CRegDWORD(_T("Software\\TortoiseGit\\SyncDialogRandomPos")))
	{
		m_seq %= 5;
		RECT rect;
		GetWindowRect(&rect);
		rect.top -= m_seq * 30;
		rect.bottom -= m_seq * 30;
		if (rect.top < 0)
		{
			rect.top += 150;
			rect.bottom += 150;
		}
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}