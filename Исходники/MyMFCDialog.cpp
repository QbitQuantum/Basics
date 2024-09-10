BOOL MyMFCDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// we need to read in the photoshop data for our proxy view
	CWnd* pWnd = GetDlgItem(IDC_PROXY);
	if (pWnd == NULL) throw((char*)"No pWnd in MyMFCDialog::OnInitDialog()");

	pWnd->GetClientRect(&m_ProxyRect);

	SetupFilterRecordForProxy();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}