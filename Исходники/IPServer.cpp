void CIPServer::OnAccept(int nErrorCode)
{
	CCardSwipeServiceApp* pApp = (CCardSwipeServiceApp*)AfxGetApp();
	CSocket newSocket;
	SOCKADDR saddr;
	char ch[96];
	CString sAddress;
	CString sIPAddress, sError;
	long nCardReaderId = -1;
	int iReturn;

	this->Accept(newSocket);
	memset(&saddr,0,sizeof(SOCKADDR));
	int iLen = sizeof(saddr);
	newSocket.GetSockName(&saddr,&iLen);
	// get dotted ip address
	lstrcpyA(ch,inet_ntoa(((SOCKADDR_IN*)&saddr)->sin_addr));
	sIPAddress = ch;
	sAddress.Format("%s:%d",ch,((SOCKADDR_IN*)&saddr)->sin_port);

	// is this address in the database?
	OysterClassLibrary::IOysterPtr pOyster;
	OysterClassLibrary::ICardReaderPtr pCardReader;

	HRESULT hr = pOyster.CreateInstance(OysterClassLibrary::CLSID_Oyster);
	if (hr != ERROR_SUCCESS)
	{
		GetLastErrorString(sError,hr);
		throw CGeneralException("CIPServer::OnAccept","Could not create OysterClassLibrary object (%d): %s",hr,sError);
	}

	memset(ch,0,sizeof(ch));
	iReturn = newSocket.Receive(ch,sizeof(ch));
	if (iReturn <= 0)
	{
		// either closed or an error occured
		GetError(sError,iReturn);
		throw CGeneralException("CIPServer::OnAccept","Receive function failed (%d): %s",iReturn,sError);
	}
	nCardReaderId = (long)&ch[0];
	pCardReader = pOyster->GetCardReaderById(nCardReaderId);
	if (pCardReader)
	{
		CVirtualCardReaderSocket* pNewSocket = new CVirtualCardReaderSocket(nCardReaderId);
		pNewSocket->Attach(newSocket.m_hSocket);
		newSocket.Detach();
		pNewSocket->Send(ECMD_COMMANDSTRING[ECMD_CONNECTSUCCESS],strlen(ECMD_COMMANDSTRING[ECMD_CONNECTSUCCESS]));
		pApp->m_mapCardSwipeIdToCardSwipe
		pApp->m_vClients.push_back(pNewSocket);
		DebugTell(_T("New client connection from %s\n"),(LPCTSTR)sAddress);
	}
	else
	{
		// invalid connection, send notification
		newSocket.Send(ECMD_COMMANDSTRING[ECMD_ERRORCONNECT],strlen(ECMD_COMMANDSTRING[ECMD_ERRORCONNECT]));
	}
	pOyster.Release();

	UNREFERENCED_PARAMETER(nErrorCode);

	CSocket::OnAccept(nErrorCode);
}