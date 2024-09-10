BOOL CContainerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CLSID clsid;
	CLSIDFromProgID(L"WmTER32X.WSTer32XCtrl.1",&clsid);

	m_wndTerX.CreateControl(clsid, _T("TERX"),WS_VISIBLE|WS_CHILD, CRect(0,0,640,430),this,1001);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}