BOOL CBMPImportSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CStatic *hmap = (CStatic *)GetDlgItem(IDC_IMAGE);

	hmap->ShowWindow(SW_HIDE);
	hmap->GetWindowRect(&m_rectImage);
	ScreenToClient(&m_rectImage);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}