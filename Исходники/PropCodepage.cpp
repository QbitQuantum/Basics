BOOL PropCodepage::OnInitDialog() 
{
	theApp.TranslateDialog(m_hWnd);
	CPropertyPage::OnInitDialog();
	
	CEdit * pEdit = (CEdit *) GetDlgItem(IDC_CUSTOM_CP_NUMBER);

	// Enable/disable "Custom codepage" edit field
	if (IsDlgButtonChecked(IDC_CP_CUSTOM))
		pEdit->EnableWindow(TRUE);
	else
		pEdit->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}