SysCacheClient::SysCacheClient(QObject *parent) : QObject(parent){
  curSock = new QLocalSocket(this);
    connect(curSock, SIGNAL(connected()), this, SLOT(startRequest()));
    connect(curSock, SIGNAL(disconnected()), this, SLOT(requestFinished()) );
    connect(curSock, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(connectionError()));
}