void CommTcpClient::open()
{
    if (isConnected())
        close();

    _socket = new QTcpSocket();
    _reader = new MessageReader(_socket);
    // forward signal
    connect(_reader, SIGNAL(received(int, const QByteArray)),
            this,    SIGNAL(received(int, const QByteArray)));

    connect(_socket, &QTcpSocket::disconnected,
            this,    &CommTcpClient::socketDisconnected);

    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,    SLOT(connectionError(QAbstractSocket::SocketError))); // error(...) overload, any c++11 way to select specific function

    _socket->connectToHost(QHostAddress::LocalHost, _port);
}