BOOL CRepositoryBrowser::OnInitDialog()
{
	CResizableStandAloneDialog::OnInitDialog();
	CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

	AddAnchor(IDC_STATIC_REPOURL, TOP_LEFT);
	AddAnchor(IDC_REPOBROWSER_URL, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_STATIC_REF, TOP_RIGHT);
	AddAnchor(IDC_BUTTON_REVISION, TOP_RIGHT);
	AddAnchor(IDC_REPOTREE, TOP_LEFT, BOTTOM_LEFT);
	AddAnchor(IDC_REPOLIST, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDHELP, BOTTOM_RIGHT);
	AddAnchor(IDC_INFOLABEL, BOTTOM_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDOK, BOTTOM_RIGHT);
	AddAnchor(IDCANCEL, BOTTOM_RIGHT);

	CRepositoryBrowser::s_bSortLogical = !CRegDWORD(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoStrCmpLogical", 0, false, HKEY_CURRENT_USER);
	if (CRepositoryBrowser::s_bSortLogical)
		CRepositoryBrowser::s_bSortLogical = !CRegDWORD(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoStrCmpLogical", 0, false, HKEY_LOCAL_MACHINE);

	static UINT columnNames[] = { IDS_STATUSLIST_COLFILENAME, IDS_STATUSLIST_COLEXT, IDS_LOG_SIZE };
	static int columnWidths[] = { 150, 100, 100 };
	DWORD dwDefaultColumns = (1 << eCol_Name) | (1 << eCol_Extension) | (1 << eCol_FileSize);
	m_ColumnManager.SetNames(columnNames, _countof(columnNames));
	m_ColumnManager.ReadSettings(dwDefaultColumns, 0, _T("RepoBrowser"), _countof(columnNames), columnWidths);

	// set up the list control
	// set the extended style of the list control
	// the style LVS_EX_FULLROWSELECT interferes with the background watermark image but it's more important to be able to select in the whole row.
	CRegDWORD regFullRowSelect(_T("Software\\TortoiseGit\\FullRowSelect"), TRUE);
	DWORD exStyle = LVS_EX_HEADERDRAGDROP | LVS_EX_DOUBLEBUFFER | LVS_EX_INFOTIP | LVS_EX_SUBITEMIMAGES;
	if (DWORD(regFullRowSelect))
		exStyle |= LVS_EX_FULLROWSELECT;
	m_RepoList.SetExtendedStyle(exStyle);
	m_RepoList.SetImageList(&SYS_IMAGE_LIST(), LVSIL_SMALL);
	CAppUtils::SetListCtrlBackgroundImage(m_RepoList.GetSafeHwnd(), IDI_REPOBROWSER_BKG);

	m_RepoTree.SetImageList(&SYS_IMAGE_LIST(), TVSIL_NORMAL);
	if (SysInfo::Instance().IsVistaOrLater())
	{
		DWORD exStyle = TVS_EX_FADEINOUTEXPANDOS | TVS_EX_AUTOHSCROLL | TVS_EX_DOUBLEBUFFER;
		m_RepoTree.SetExtendedStyle(exStyle, exStyle);
	}

	m_nExternalOvl = SYS_IMAGE_LIST().AddIcon((HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_EXTERNALOVL), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));
	// set externaloverlay in SYS_IMAGE_LIST() in Refresh method, so that it is updated after every launch of the logdialog

	SetWindowTheme(m_RepoTree.GetSafeHwnd(), L"Explorer", NULL);
	SetWindowTheme(m_RepoList.GetSafeHwnd(), L"Explorer", NULL);

	m_nIconFolder = SYS_IMAGE_LIST().GetDirIconIndex();
	m_nOpenIconFolder = SYS_IMAGE_LIST().GetDirOpenIconIndex();

	EnableSaveRestore(L"Reposbrowser");

	DWORD xPos = CRegDWORD(_T("Software\\TortoiseGit\\TortoiseProc\\ResizableState\\RepobrowserDivider"), 0);
	if (xPos == 0)
	{
		RECT rc;
		GetDlgItem(IDC_REPOTREE)->GetClientRect(&rc);
		xPos = rc.right - rc.left;
	}
	HandleDividerMove(CPoint(xPos + 20, 10), false);

	CString sWindowTitle;
	GetWindowText(sWindowTitle);
	CAppUtils::SetWindowTitle(m_hWnd, g_Git.m_CurrentDir, sWindowTitle);

	m_bHasWC = !g_GitAdminDir.IsBareRepo(g_Git.m_CurrentDir);

	Refresh();

	m_RepoList.SetFocus();

	return FALSE;
}