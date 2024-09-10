void DataSocket::OnClose(int nErrorCode) 
{
	TRACE0("CDataSocket() OnClose()\n");
	if (m_pConnectSocket)
	{
		// shutdown sends
		ShutDown(1);

		if (m_nStatus == XFERMODE_RECEIVE)
		{
			while(Receive() != 0)
			{
				// receive remaining data				
			}
		}
		else
		{
			/*m_pConnectSocket->SendResponse("426 Connection closed; transfer aborted.");
			// destroy this socket
			AfxGetThread()->PostThreadMessage(WM_THREADMSG, 0, 0);
			// upload failed
			((ConnectThread *)AfxGetThread())->UpdateStatistic(FTPSTAT_UPLOADFAILED);*/
		}
	}
	m_nStatus = XFERMODE_IDLE;	
	m_bConnected = FALSE;
	CAsyncSocket::OnClose(nErrorCode);
}