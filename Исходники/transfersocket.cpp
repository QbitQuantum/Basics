CSocket* CTransferSocket::CreateSocketServer(int port)
{
	CSocket* pServer = new CSocket(this);
	int res = pServer->Listen(m_pControlSocket->m_pSocket->GetAddressFamily(), port);
	if (res)
	{
		m_pControlSocket->LogMessage(::Debug_Verbose, _T("Could not listen on port %d: %s"), port, CSocket::GetErrorDescription(res).c_str());
		delete pServer;
		return 0;
	}

	SetSocketBufferSizes(pServer);

	return pServer;
}