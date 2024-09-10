BOOL CFindInDbDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	NewGUI_TranslateCWnd(this);
	EnumChildWindows(this->m_hWnd, NewGUI_TranslateWindowCb, 0);

	NewGUI_XPButton(m_btOK, IDB_OK, IDB_OK);
	NewGUI_XPButton(m_btCancel, IDB_CANCEL, IDB_CANCEL);

	NewGUI_ConfigSideBanner(&m_banner, this);
	m_banner.SetIcon(AfxGetApp()->LoadIcon(IDI_SEARCH),
		KCSB_ICON_LEFT | KCSB_ICON_VCENTER);
	m_banner.SetTitle(TRL("Find"));
	m_banner.SetCaption(TRL("Find a string in the entry list."));

	if(m_lpGroupName != NULL)
	{
		CString str;

		str = TRL("Find"); str += _T(" - "); str += TRL("Group:");
		str += _T(" "); str += m_lpGroupName;
		m_banner.SetTitle(str);

		GetDlgItem(IDC_CHECK_GROUPNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_EXCLUDEBACKUPS)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_EDIT_FINDTEXT)->SetFocus();
	return FALSE; // Return TRUE unless you set the focus to a control
}