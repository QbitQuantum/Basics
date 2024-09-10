BOOL CDlgFtch::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString str;
	str.LoadStringW(IDS_STRING9030);
	GetDlgItem(IDC_STATIC_EDIT1)->SetWindowText(str);

	str.LoadStringW(IDS_STRING9031);
	this->SetWindowTextW(str);
	this->MoveWindow(0,0,625,90);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}