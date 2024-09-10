BOOL CTaiChuQuanSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	
	if( m_OperateID == 'M')
	   this->SetWindowText("修改除权信息");
	CWnd *pWnd = GetDlgItem(IDC_EDIT_CQDATE);
	if(!pWnd) return TRUE;

	CRect rc;
	pWnd->GetWindowRect(rc);
	pWnd->DestroyWindow(); 
	ScreenToClient(rc);
	m_DateTime.Create(WS_CHILD|WS_VISIBLE|DTS_LONGDATEFORMAT|DTS_UPDOWN,rc,this,IDC_DATETIME_1);
	
	CTime pMinRange = CTime(1988,9,1,1,1,1);
	CTime pMaxRange = CTime(2037,9,1,1,1,1);
	this->m_DateTime.SetRange( &pMinRange, &pMaxRange );


	if(m_timet!=0&&m_timet!=1)
	{
		CTime tm(m_timet);
		m_DateTime .SetTime(&tm);
	}
	GetDlgItem(IDC_RADIO_FIR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_SEC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_END)->ShowWindow(SW_HIDE);
	return TRUE;  
}