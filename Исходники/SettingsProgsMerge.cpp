BOOL CSettingsProgsMerge::OnInitDialog()
{
	ISettingsPropPage::OnInitDialog();

	EnableToolTips();

	m_sMergePath = m_regMergePath;
	m_iExtMerge = IsExternal(m_sMergePath);

	SHAutoComplete(::GetDlgItem(m_hWnd, IDC_EXTMERGE), SHACF_FILESYSTEM | SHACF_FILESYS_ONLY);

	m_tooltips.Create(this);
	m_tooltips.AddTool(IDC_EXTMERGE, IDS_SETTINGS_EXTMERGE_TT);

	UpdateData(FALSE);
	return TRUE;
}