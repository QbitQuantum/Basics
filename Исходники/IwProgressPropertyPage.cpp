BOOL CIwProgressPropertyPage::OnInitDialog()
{
	CProgressCtrl* ctlProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
	ctlProgress->SetRange(0, 100);
	ctlProgress->SetPos(1);

	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->PostMessage(PSM_PRESSBUTTON, PSBTN_NEXT, 0);
	CWnd* pwndNextBut = parent->GetDlgItem(ID_WIZNEXT);
	CWnd* pwndCancelBut = parent->GetDlgItem(IDCANCEL);
	if (pwndNextBut)
		pwndNextBut->EnableWindow(0);
	if (pwndCancelBut)
		pwndCancelBut->EnableWindow(0);

	return TRUE;  
}