void CSocketServer::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	char s[1024]; CString szIP; UINT szPort;

	GetPeerName(szIP,szPort);
	int nLen = Receive(s,1024);
	s[nLen]=L'\0';
	CString strText(s);

	SetInfoReceive(strText);
	SetClientIP(szIP);
	SetClientPort(szPort);
	if (strText.GetLength()>3 && (strText.Left(3) == L"con"))
	{
		CStaticClass::m_bControl = true;
		CStaticClass::m_csReceiveInfo = strText;
		SetEvent(CStaticClass::m_hEventRecieve);
	}


	CSocket::OnReceive(nErrorCode);
}