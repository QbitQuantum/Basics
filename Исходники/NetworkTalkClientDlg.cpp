void CNetworkTalkClientDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	CSocket sockClient;
	sockClient.Create();
	sockClient.Connect(m_serverIPAddress,8000);
	g_serverIPAddress=m_serverIPAddress;
	sockClient.Send(m_sendText,m_sendText.GetLength());
	sockClient.Close();
	
}