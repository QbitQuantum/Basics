BOOL CEmailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWnd *wnd = GetDlgItem (IDC_EMAIL);
	if (wnd != NULL)
		wnd->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}