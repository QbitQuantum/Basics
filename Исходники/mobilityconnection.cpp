void MobilityConnection::connectToSimulator()
{
    // 1. check availability
    QLocalSocket *socket = new QLocalSocket;
    QString simVersion = SimulatorConnection::instance()->simulatorVersion().toString();
    socket->connectToServer(QLatin1String(SIMULATOR_MOBILITY_SERVERNAME) + simVersion, QLocalSocket::ReadWrite);
    if (!socket->waitForConnected(1000)) {
        qFatal("Could not connect to mobility server");
        socket->deleteLater();
        return;
    }
    mSendSocket = socket;

    // 2. Create the local server used for initiating the backchannel.
    const qint64 pid = QCoreApplication::applicationPid();
    QLocalServer *server = new QLocalServer(this);
    if (!server->listen(qt_mobilityServerName(simVersion, pid)))
        qFatal("Can't create local mobility server for this application.");

    // 3. Send initial application connect command.
    ApplicationConnectCommand command;
    ApplicationConnectCommand::Request &request = command.request;
    request.applicationPid = pid;
    request.applicationName[0] = 0;
    request.version = mobilityVersion;
    qt_sendAndReceiveApplicationConnect(socket, command);

    mSimulatorVersion = command.reply.version;

    // We usually want to get the initial state from the simulator directly, probably
    // before the event loop is started up. Hence we block until the simulator has established
    // the back channel.
    if (!server->waitForNewConnection(1000))
        qFatal("Simulator didn't establish mobility-backchannel on time");
    mReceiveSocket = server->nextPendingConnection();
    server->close();

    connect(mReceiveSocket, SIGNAL(readyRead()), SLOT(onReadyRead()));
}