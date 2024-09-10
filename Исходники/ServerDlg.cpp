void CServerDlg::OnOK() 
{
	//int nIndex = m_serverList2.GetCurSel();
	//if (nIndex != LB_ERR)
	//	m_serverList2.GetLBText(nIndex, serverName);
  
	WTSFreeMemory(&pServerInfo);
	m_serverList2.GetWindowText( serverName);
	//AfxMessageBox(serverName);
	g_pDoc->SetServerName( (TCHAR *) LPCTSTR(serverName));

	CDialog::OnOK();
}