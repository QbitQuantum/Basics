// CSvrSocket member functions
void CSvrSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	CLoginResultMsg* pMsg = new CLoginResultMsg();
	pMsg->Header.type = ID_CUSTOM_SOCK_CONN_RESULT;
	pMsg->Error = nErrorCode;
	SendMsg(pMsg,"");

	if ( nErrorCode == 0)
	{
		BOOL bDontLinger = FALSE;
		BOOL bRet = SetSockOpt(SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));
	}

	bConnected = nErrorCode == 0;
		
	
	CAsyncSocket::OnConnect(nErrorCode);
}