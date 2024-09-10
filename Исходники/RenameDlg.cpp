BOOL CRenameDlg::OnInitDialog()
{
	CHorizontalResizableStandAloneDialog::OnInitDialog();
	CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

	SHAutoComplete(GetDlgItem(IDC_NAME)->m_hWnd, SHACF_DEFAULT);

	if (!m_windowtitle.IsEmpty())
		this->SetWindowText(m_windowtitle);
	if (!m_label.IsEmpty())
		SetDlgItemText(IDC_LABEL, m_label);

	if (!m_name.IsEmpty())
	{
		CString sTmp;
		sTmp.Format(IDS_RENAME_INFO, (LPCWSTR)m_name);
		SetDlgItemText(IDC_RENINFOLABEL, sTmp);
	}

	AddAnchor(IDC_RENINFOLABEL, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_LABEL, TOP_LEFT);
	AddAnchor(IDC_NAME, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDOK, BOTTOM_RIGHT);
	AddAnchor(IDCANCEL, BOTTOM_RIGHT);

	CControlsBridge::AlignHorizontally(this, IDC_LABEL, IDC_NAME);
	if (hWndExplorer)
		CenterWindow(CWnd::FromHandle(hWndExplorer));
	EnableSaveRestore(_T("RenameDlg"));
	m_originalName = m_name;
	return TRUE;
}