void WorkerTCP::Init()
{
    globalData = new char[ProgramVariables::K4];
    globalLength = 0;
    state = Peers::STATE::FREE;
    board = new Board();

    time = new QTimer();
    connect(time,SIGNAL(timeout()),this,SLOT(Reconnect()));

    waitForOKMessageTimer = new QTimer();
    connect(waitForOKMessageTimer,SIGNAL(timeout()),this,SLOT(NoResponseFromServer()));
    waitForOKMessageTimer->setInterval(ProgramVariables::GetMaxTimeWaitToServer());

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadDataFromServer()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ConnectionError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(HandleStateChange(QAbstractSocket::SocketState)));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(Connected()));

    waitForIATimer = new QTimer();
    waitForIATimer->setInterval(10);
    connect(waitForIATimer,SIGNAL(timeout()), this, SLOT(CheckStatus()));
}