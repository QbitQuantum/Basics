BOOL CWZStep4::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	
	// pSheet->SetWizardButtons(PSWIZB_NEXT | PSWIZB_FINISH);
	
	//-- for debug
	// pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_FINISH);
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	//-- end for debug

	//-- for debug temp comment
	InitDialogItem();
	//-- end for debug temp comment

	//-- this is third time added begin
	
	// pSheet->SetFinishText("Restore");

	
	(pSheet->GetDlgItem(IDCANCEL))->GetWindowText(g_strTextCancel);
	
	CString strRestore;
	strRestore.LoadString(IDS_RESTORE);
	(pSheet->GetDlgItem(ID_WIZFINISH))->SetWindowText(strRestore);

	CString strClose;
	strClose.LoadString(IDS_CLOSE);
    
	(pSheet->GetDlgItem(IDCANCEL))->SetWindowText(strClose);

	(pSheet->GetDlgItem(IDHELP))->ShowWindow(FALSE);

	//-- this is third time added end
	
	return CPropertyPageEx::OnSetActive();
}