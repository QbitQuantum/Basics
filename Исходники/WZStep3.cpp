BOOL CWZStep3::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	//-- needn't the help button begin
	(pSheet->GetDlgItem(IDHELP))->ShowWindow(FALSE);
	//-- needn't the help button end

	InitControl();
	return CPropertyPageEx::OnSetActive();
}