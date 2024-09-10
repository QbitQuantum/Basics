void QLocalServerPrivate::_q_onNewConnection()
{
    Q_Q(QLocalServer);
    QTcpSocket* tcpSocket = tcpServer.nextPendingConnection();
    if (!tcpSocket) {
        qWarning("QLocalServer: no pending connection");
        return;
    }

    tcpSocket->setParent(q);
    const quintptr socketDescriptor = tcpSocket->socketDescriptor();
    q->incomingConnection(socketDescriptor);
}