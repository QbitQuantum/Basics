int QDeclarativeBluetoothServicePrivate::listen() {

    if (m_service->socketProtocol() == QBluetoothServiceInfo::UnknownProtocol) {
        qWarning() << "Unknown protocol, can't make service" << m_protocol;
        return -1;
    }
    QBluetoothServiceInfo::Protocol serverType = QBluetoothServiceInfo::UnknownProtocol;
    if (m_service->socketProtocol() == QBluetoothServiceInfo::L2capProtocol)
        serverType = QBluetoothServiceInfo::L2capProtocol;
    else if (m_service->socketProtocol() == QBluetoothServiceInfo::RfcommProtocol)
        serverType = QBluetoothServiceInfo::RfcommProtocol;

    QBluetoothServer *server = new QBluetoothServer(serverType);
    server->setMaxPendingConnections(1);
    server->listen(QBluetoothAddress());
    server->serverPort();
    m_server = server;

    return server->serverPort();
}