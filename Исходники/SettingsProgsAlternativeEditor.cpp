BOOL CSettingsProgsAlternativeEditor::OnInitDialog()
{
	ISettingsPropPage::OnInitDialog();

	AdjustControlSize(IDC_ALTERNATIVEEDITOR_OFF);
	AdjustControlSize(IDC_ALTERNATIVEEDITOR_ON);

	EnableToolTips();

	m_sAlternativeEditorPath = m_regAlternativeEditorPath;
	m_iAlternativeEditor = IsExternal(m_sAlternativeEditorPath);

	SHAutoComplete(::GetDlgItem(m_hWnd, IDC_ALTERNATIVEEDITOR), SHACF_FILESYSTEM | SHACF_FILESYS_ONLY);

	m_tooltips.AddTool(IDC_ALTERNATIVEEDITOR, IDS_SETTINGS_ALTERNATIVEEDITOR_TT);

	UpdateData(FALSE);
	return TRUE;
}