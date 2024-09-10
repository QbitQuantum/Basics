BOOL CCloneDlg::OnInitDialog()
{
	CHorizontalResizableStandAloneDialog::OnInitDialog();
	CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

	AddAnchor(IDC_URLCOMBO, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_CLONE_BROWSE_URL, TOP_RIGHT);
	AddAnchor(IDC_CLONE_DIR, TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_CLONE_DIR_BROWSE, TOP_RIGHT);
	AddAnchor(IDOK,BOTTOM_RIGHT);
	AddAnchor(IDCANCEL,BOTTOM_RIGHT);

	AddAnchor(IDC_GROUP_CLONE,TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_PUTTYKEYFILE_BROWSE,TOP_RIGHT);
	AddAnchor(IDC_PUTTYKEY_AUTOLOAD,TOP_LEFT);
	AddAnchor(IDC_PUTTYKEYFILE,TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_CLONE_GROUP_SVN,TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDHELP, BOTTOM_RIGHT);

	AdjustControlSize(IDC_CHECK_DEPTH);
	AdjustControlSize(IDC_CHECK_RECURSIVE);
	AdjustControlSize(IDC_CHECK_BARE);
	AdjustControlSize(IDC_PUTTYKEY_AUTOLOAD);
	AdjustControlSize(IDC_CHECK_SVN);
	AdjustControlSize(IDC_CHECK_SVN_TRUNK);
	AdjustControlSize(IDC_CHECK_SVN_TAG);
	AdjustControlSize(IDC_CHECK_SVN_BRANCH);
	AdjustControlSize(IDC_CHECK_SVN_FROM);
	AdjustControlSize(IDC_CHECK_USERNAME);

	CString tt;
	tt.LoadString(IDS_CLONE_DEPTH_TT);
	m_tooltips.AddTool(IDC_EDIT_DEPTH,tt);
	m_tooltips.AddTool(IDC_CHECK_DEPTH,tt);

	this->AddOthersToAnchor();

	if (m_Directory.IsEmpty())
	{
		CString dir = m_regCloneDir;
		int index = dir.ReverseFind('\\');
		if (index >= 0)
			dir = dir.Left(index);
		m_Directory = dir;
	}
	if (m_Directory.IsEmpty())
	{
		TCHAR szPath[MAX_PATH] = {0};
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, szPath)))
			m_Directory = szPath;
	}
	UpdateData(FALSE);

	m_URLCombo.SetCaseSensitive(TRUE);
	m_URLCombo.SetURLHistory(TRUE);
	m_URLCombo.LoadHistory(_T("Software\\TortoiseGit\\History\\repoURLS"), _T("url"));
	if(m_URL.IsEmpty())
	{
		CString str = CAppUtils::GetClipboardLink(_T("git clone "));
		str.Trim();
		if(str.IsEmpty())
			m_URLCombo.SetCurSel(0);
		else
			m_URLCombo.SetWindowText(str);
	}
	else
		m_URLCombo.SetWindowText(m_URL);

	CWnd *window=this->GetDlgItem(IDC_CLONE_DIR);
	if(window)
		SHAutoComplete(window->m_hWnd, SHACF_FILESYSTEM);

	this->m_BrowseUrl.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_CLONE_DIR)));
	this->m_BrowseUrl.AddEntry(CString(MAKEINTRESOURCE(IDS_PROC_CLONE_WEB)));
	m_BrowseUrl.SetCurrentEntry(m_regBrowseUrl);

	m_PuttyKeyCombo.SetPathHistory(TRUE);
	m_PuttyKeyCombo.LoadHistory(_T("Software\\TortoiseGit\\History\\puttykey"), _T("key"));
	m_PuttyKeyCombo.SetCurSel(0);

	this->GetDlgItem(IDC_PUTTYKEY_AUTOLOAD)->EnableWindow( CAppUtils::IsSSHPutty() );
	this->GetDlgItem(IDC_PUTTYKEYFILE)->EnableWindow(m_bAutoloadPuttyKeyFile);
	this->GetDlgItem(IDC_PUTTYKEYFILE_BROWSE)->EnableWindow(m_bAutoloadPuttyKeyFile);

	EnableSaveRestore(_T("CloneDlg"));

	OnBnClickedCheckSvn();
	OnBnClickedCheckDepth();
	OnBnClickedCheckBranch();
	OnBnClickedCheckOrigin();
	return TRUE;  // return TRUE  unless you set the focus to a control
}