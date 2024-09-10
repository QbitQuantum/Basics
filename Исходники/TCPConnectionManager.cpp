/**
 * @details
 * Accept client connections for data
 */
void TCPConnectionManager::acceptClientConnection()
{
    // Get new client connection
    QTcpSocket *client = _tcpServer->nextPendingConnection();

    if (_processIncomming(client))
    {
        // Connect socket error() signals
        connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(connectionError(QAbstractSocket::SocketError)),
            Qt::DirectConnection);
        connect(client, SIGNAL(readyRead()), this, SLOT(_incomingFromClient()),
            Qt::DirectConnection);
    }
    else {
        // Closes the I/O device for the socket,
        // disconnects the socket's connection with the host,
        // closes the socket, and resets the name, address,
        // port number and underlying socket descriptor.
        client->close();
        delete client;
    }
}