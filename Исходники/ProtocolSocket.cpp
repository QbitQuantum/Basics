void ProtocolSocket::setSocket(QTcpSocket *socket)
{
    if (socket && socket->state() != QAbstractSocket::ConnectedState) {
        qWarning() << "BUG: ProtocolSocket::setSocket with unconnected socket";
        socket = 0;
    }

    if (socket == m_socket)
        return;

    bool wasConnected = isConnected();

    if (m_socket) {
        /* The existing socket is replaced, and all pending commands
         * are considered failed. This could be improved on. */
        QTcpSocket *oldSocket = m_socket;
        m_socket = 0;

        oldSocket->disconnect(this);
        // XXX can this be avoided if none are sent yet?
        abortCommands();
        oldSocket->abort();
        oldSocket->deleteLater();
    }

    m_socket = socket;

    if (socket) {
        socket->setParent(this);
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
        // QueuedConnection used to make sure socket states are updated first
        connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()),
                Qt::QueuedConnection);
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(socketDisconnected()), Qt::QueuedConnection);

        if (!wasConnected) {
            m_connectedTime.restart();
            emit connected();
        }

        flushCommands();
        read();
    } else {
        emit disconnected();
    }

    emit socketChanged();
}