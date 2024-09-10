BOOL CEasyPage1::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons(PSWIZB_NEXT);

	// (pSheet->GetDlgItem(ID_WIZBACK))->ShowWindow(FALSE);
	(pSheet->GetDlgItem(IDHELP))->ShowWindow(FALSE);

	return CPropertyPage::OnSetActive();
}