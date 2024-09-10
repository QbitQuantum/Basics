LRESULT CEncryptWiz_3::OnWizardBack() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);

	(pSheet->GetDlgItem(IDCANCEL))->SetWindowText(m_strTextCancel);
	
	return CPropertyPage::OnWizardBack();
}