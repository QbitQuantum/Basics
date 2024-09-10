BOOL CPushDlg::OnInitDialog()
{
	CHorizontalResizableStandAloneDialog::OnInitDialog();
	CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

	AddAnchor(IDOK,BOTTOM_RIGHT);
	AddAnchor(IDCANCEL,BOTTOM_RIGHT);
	AddAnchor(IDC_BRANCH_GROUP, TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_STATIC_REMOTE, TOP_LEFT);
	AddAnchor(IDC_STATIC_SOURCE, TOP_LEFT);

	AddAnchor(IDC_PUSHALL, TOP_LEFT);
	AddAnchor(IDC_BRANCH_REMOTE, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_BUTTON_BROWSE_DEST_BRANCH, TOP_RIGHT);
	AddAnchor(IDC_BRANCH_SOURCE, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_BUTTON_BROWSE_SOURCE_BRANCH, TOP_RIGHT);

	AddAnchor(IDC_URL_GROUP, TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_RD_REMOTE, TOP_LEFT);
	AddAnchor(IDC_RD_URL, TOP_LEFT);

	AddAnchor(IDC_REMOTE, TOP_LEFT, TOP_RIGHT);

	AddAnchor(IDC_URL, TOP_LEFT,TOP_RIGHT);

	AddAnchor(IDC_OPTION_GROUP, TOP_LEFT,TOP_RIGHT);

	AddAnchor(IDC_FORCE, TOP_LEFT);
	AddAnchor(IDC_PACK, TOP_LEFT);
	AddAnchor(IDC_TAGS, TOP_LEFT);
	AddAnchor(IDC_PUTTYKEY_AUTOLOAD,TOP_LEFT);

	AddAnchor(IDC_REMOTE_MANAGE,TOP_RIGHT);
	AddAnchor(IDHELP, BOTTOM_RIGHT);

	AddOthersToAnchor();

	CString sWindowTitle;
	GetWindowText(sWindowTitle);
	CAppUtils::SetWindowTitle(m_hWnd, g_Git.m_CurrentDir, sWindowTitle);

	this->GetDlgItem(IDC_PUTTYKEY_AUTOLOAD)->EnableWindow(CAppUtils::IsSSHPutty());

	EnableSaveRestore(_T("PushDlg"));

	m_RemoteURL.SetURLHistory(TRUE);

	CString WorkingDir=g_Git.m_CurrentDir;
	WorkingDir.Replace(_T(':'),_T('_'));
	m_RemoteURL.LoadHistory(CString(_T("Software\\TortoiseGit\\History\\PushURLS\\"))+WorkingDir, _T("url"));
	CString clippath=CAppUtils::GetClipboardLink();
	if(clippath.IsEmpty())
		m_RemoteURL.SetCurSel(0);
	else
		m_RemoteURL.SetWindowText(clippath);

	m_RemoteURL.EnableWindow(FALSE);
	CheckRadioButton(IDC_RD_REMOTE,IDC_RD_URL,IDC_RD_REMOTE);


	this->m_regAutoLoad = CRegDWORD(CString(_T("Software\\TortoiseGit\\History\\PushDlgAutoLoad\\"))+WorkingDir,
									m_bAutoLoad);
	m_bAutoLoad = this->m_regAutoLoad;
	if(!CAppUtils::IsSSHPutty())
		m_bAutoLoad = false;

	Refresh();


	//m_BranchRemote.SetWindowTextW(m_BranchSource.GetString());

	this->UpdateData(false);
	return TRUE;
}