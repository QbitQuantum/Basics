int ACEEngine::AddConnector(int connectorIndex, char* szIP, unsigned short port)
{
	ACE_SOCK_Stream* stream = new ACE_SOCK_Stream();
	ACE_INET_Addr connectAddr(port, szIP);
	ACE_SOCK_Connector connector;
	int result = connector.connect(*stream, connectAddr);
	if (-1 == result)
		return -1;

	_SessionDesc sessionDesc;
	sessionDesc.identifier = connectorIndex;
	sessionDesc.sessionType = SESSION_TYPE::SESSION_CONNECTOR;

	ProactorService* pService = new ProactorService();
	pService->SetOwner(this);
	pService->SetSessionDesc(sessionDesc);

	ACE_Message_Block mb;
	pService->open(stream->get_handle(), mb);
	delete stream;
	stream = NULL;

	return pService->GetSerial();
}