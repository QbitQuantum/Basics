BOOL CStartDlg::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class

	CPropertySheet *parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons(/*PSWIZB_BACK |*/ PSWIZB_NEXT);

	CWnd* backButton = parent->GetDlgItem(ID_WIZBACK);
	backButton->EnableWindow(false);

	CString csNextstr;

	csNextstr.LoadString(ID_WIZNEXT);
	CWnd* nextButton = parent->GetDlgItem(ID_WIZNEXT);
	nextButton->SetWindowText(csNextstr);

	return CPropertyPage::OnSetActive();
}