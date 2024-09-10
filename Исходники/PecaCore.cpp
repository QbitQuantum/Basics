void	CPecaCore::threadServer()
{
	CPecaServer	server;

	CSocket	sockServer;
	sockServer.bind();

	while (1) {
		CSocket*	psock = sockServer.accept();
		if (psock) {
			char strIP[64];
			psock->GetFromHost().toStr(strIP);
			LOG_DEBUG(_T("%s から接続要求"), strIP);

			boost::thread(boost::bind(&CPecaCore::handshake, this, psock));
		}
		::Sleep(10);
	}


	//server.

}