ConnectionBackend *ConnectionBackend::nextPendingConnection()
{
    Q_ASSERT(state == Listening);
    Q_ASSERT(localServer || tcpServer);
    Q_ASSERT(!socket);

    //qCDebug(KIO_CORE) << "Got a new connection";

    QTcpSocket *newSocket;
    if (mode == LocalSocketMode) {
        newSocket = localServer->nextPendingConnection();
    } else {
        newSocket = tcpServer->nextPendingConnection();
    }

    if (!newSocket) {
        return 0;    // there was no connection...
    }

    ConnectionBackend *result = new ConnectionBackend(Mode(mode));
    result->state = Connected;
    result->socket = newSocket;
    newSocket->setParent(result);
    connect(newSocket, SIGNAL(readyRead()), result, SLOT(socketReadyRead()));
    connect(newSocket, SIGNAL(disconnected()), result, SLOT(socketDisconnected()));

    return result;
}