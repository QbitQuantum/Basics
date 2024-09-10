BOOL CChangePasDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_First)
	{
		SetWindowText("Задание начального пароля");
		CEdit *Ed = (CEdit *)GetDlgItem(IDC_PWDOLD);
		Ed->EnableWindow(false);
		Ed = (CEdit *)GetDlgItem(IDC_PWDNEW);
		Ed->SetFocus();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}