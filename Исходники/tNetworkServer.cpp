bool tNetworkServer::Init(boost::intrusive_ptr<tINetworkServer> s){

	LOG_DEBUG << "tNetworkServer::Init()";

	this->_storage=s;
	char cc[100];
	::GetCurrentDirectoryA(100,cc);
	strcat(cc,"\\config.ini");
	DWORD res=GetPrivateProfileStringA("Network", "interfaceServer", "127.0.0.1", _interface, 100, cc);
	LOG_DEBUG << cc << _interface;
//	if (memcmp(cInterface,"auto",4)==0)	GetDefaultIP(cInterface);
//	printf("\nSelected Network interface:%s\n",cInterface);

// шаг 1 - подключение библиотеки 
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData)){
		LOG_ERROR << "WSAStartup error: " << WSAGetLastError();
		return false;
    }
	LOG_DEBUG << "WSAStartup() - OK";
	for (int i=0;i<5;i++){
		this->_clients[i].used=false;
		ZeroMemory(&this->_clients[i].clientAddrForRecv,sizeof(sockaddr)) ;
		ZeroMemory(&this->_clients[i].mInfo,sizeof(tNetInfo));
	}
	return true;
}