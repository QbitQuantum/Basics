BOOL CImportOptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	NewGUI_TranslateCWnd(this);
	EnumChildWindows(this->m_hWnd, NewGUI_TranslateWindowCb, 0);

	NewGUI_XPButton(m_btOK, IDB_OK, IDB_OK);
	NewGUI_XPButton(m_btCancel, IDB_CANCEL, IDB_CANCEL);

	NewGUI_ConfigSideBanner(&m_banner, this);
	m_banner.SetIcon(AfxGetApp()->LoadIcon(IDI_ICONPIC),
		KCSB_ICON_LEFT | KCSB_ICON_VCENTER);
	m_banner.SetTitle(TRL("Options"));
	m_banner.SetCaption(_T(" "));

	CFontUtil::SetDefaultFontFrom(GetDlgItem(IDC_RADIO_CREATENEW));

	// m_fBold.CreateFont(-10, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
	//	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	//	DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("MS Shell Dlg"));

	// GetDlgItem(IDC_RADIO_CREATENEW)->SetFont(&m_fBold);
	// GetDlgItem(IDC_RADIO_OVERWRITE_ALWAYS)->SetFont(&m_fBold);
	// GetDlgItem(IDC_RADIO_OVERWRITE_TIMEBASED)->SetFont(&m_fBold);
	CFontUtil::AssignBold(GetDlgItem(IDC_RADIO_CREATENEW), this);
	CFontUtil::AssignBold(GetDlgItem(IDC_RADIO_OVERWRITE_ALWAYS), this);
	CFontUtil::AssignBold(GetDlgItem(IDC_RADIO_OVERWRITE_TIMEBASED), this);

	return TRUE;
}