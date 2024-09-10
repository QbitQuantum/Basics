BOOL CToolSetupPage::OnInitDialog()
{
	m_BackgroundBrush = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	return CPropertyPage::OnInitDialog();
}