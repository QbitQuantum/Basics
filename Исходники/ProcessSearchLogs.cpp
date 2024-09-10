BOOL CProcessSearchLogs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ResultSettings.SetCurSel( 0 );
	m_FileMask = _T("*");

	CEdit *cEdtSearch = (CEdit *)GetDlgItem( IDC_EDIT4 );	
	cEdtSearch->SetFocus();

	UpdateData( false );	
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}