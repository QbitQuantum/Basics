void TcpSrvGui::initConnections() {
	connect(pbListen, SIGNAL(clicked()), &tcpSrv, SLOT(slListen()));
	connect(pbClose, SIGNAL(clicked()), &tcpSrv, SLOT(slClose()));
	connect(pbClose, SIGNAL(clicked()), this, SLOT(slClosed()));

	connect(&tcpSrv, SIGNAL(sgListen()), this, SLOT(slListen()));
	connect(&tcpSrv, SIGNAL(sgAccepted()), this, SLOT(slAccepted()));
	connect(&tcpSrv, SIGNAL(sgNotListen()), this, SLOT(slError()));
	connect(&tcpSrv, SIGNAL(sgNotAccepted()), this, SLOT(slError()));
	connect(&tcpSrv, SIGNAL(sgDisconnected()), this, SLOT(slDisconnect()));
	connect(&tcpSrv, SIGNAL(sgRecvData(QByteArray,int)), this, SLOT(slGotData(QByteArray,int)));
}