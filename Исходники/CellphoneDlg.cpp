BOOL CCellphoneDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_device = &((CChatDlg*)m_pChatDlg)->m_pHugMe->m_device;

	CEdit* status = (CEdit*)GetDlgItem(IDC_STATUS);
	CButton* ok = (CButton*)GetDlgItem(ID_YES);
	CButton* cancel = (CButton*)GetDlgItem(ID_NO);

	status->SetWindowText("Listen to a cellphone?");
	ok->SetWindowText("Listen");

	ok->ShowWindow(TRUE);
	cancel->ShowWindow(FALSE);

	m_bIsListening = false;
	m_bIsConnected = false;
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}