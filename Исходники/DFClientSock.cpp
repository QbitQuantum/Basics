void DFClientSock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	int iZero = 2048;
	SetSockOpt(SO_RCVBUF, &iZero, sizeof(iZero));

	((DFHideMainFrame*)(((CDFOpenMindApp*)AfxGetApp())->m_pMainWnd))->LogonProcess();
	CAsyncSocket::OnConnect(nErrorCode);
}