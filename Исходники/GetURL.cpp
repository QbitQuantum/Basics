BOOL CGetURL::OnInitDialog() 
{
	CDialog::OnInitDialog();
	IUnknown *pUnk;
	
	CWnd *pWnd = GetDlgItem(IDC_EXPLORER);
	pUnk = NULL;
	if(pWnd)
		m_spBrowser = pWnd->GetControlUnknown();

	pWnd = NULL;
	CRect rcItem;
	pWnd = GetDlgItem(IDC_PHSTATIC);
	if(pWnd)
	{
		pWnd->GetClientRect(rcItem);
		pWnd->ClientToScreen(rcItem);
		pWnd->DestroyWindow();
		ScreenToClient(rcItem);
		rcItem.bottom += 150;
		if(m_AddrCombo.Create(WS_VSCROLL|WS_CHILD|WS_VISIBLE|CBS_DROPDOWN|CBS_AUTOHSCROLL,rcItem,this,IDC_ADDRCOMBO))
		{
			m_AddrCombo.SetCurSel(0);
			m_AddrCombo.GetWindowText(m_szCurAddr);
			if(m_spBrowser && m_szCurAddr.GetLength())
				m_spBrowser->Navigate(m_szCurAddr.AllocSysString(),NULL,NULL,NULL,NULL);
		}
	}
	return TRUE;
}