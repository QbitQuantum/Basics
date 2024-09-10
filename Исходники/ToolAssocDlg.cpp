BOOL CToolAssocDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	EnableToolTips();
	m_tooltips.Create(this);

	CString title;
	if (m_sType == _T("Diff"))
	{
		title.LoadString(m_bAdd ? IDS_DLGTITLE_ADD_DIFF_TOOL : IDS_DLGTITLE_EDIT_DIFF_TOOL);
		m_tooltips.AddTool(IDC_TOOLEDIT, IDS_SETTINGS_EXTDIFF_TT);
	}
	else
	{
		title.LoadString(m_bAdd ? IDS_DLGTITLE_ADD_MERGE_TOOL : IDS_DLGTITLE_EDIT_MERGE_TOOL);
		m_tooltips.AddTool(IDC_TOOLEDIT, IDS_SETTINGS_EXTMERGE_TT);
	}

	SetWindowText(title);
	SHAutoComplete(::GetDlgItem(m_hWnd, IDC_TOOLEDIT), SHACF_FILESYSTEM | SHACF_FILESYS_ONLY);

	UpdateData(FALSE);
	return TRUE;
}