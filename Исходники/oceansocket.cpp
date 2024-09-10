OceanSocket::OceanSocket(QObject *parent) :
    QObject(parent)
{
    // setup the heartbeat timer
    heartbeat = new QTimer(this);
    connect(heartbeat, SIGNAL(timeout()), this, SLOT(heartbeatTimer()));

    // setup our ocean sockets
    groupAddress = QHostAddress(MULTICAST_ADDRESS);

    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < ifaces.count(); i++) {
        QNetworkInterface iface = ifaces.at(i);
        if (iface.flags().testFlag(QNetworkInterface::IsUp) && !iface.flags().testFlag(QNetworkInterface::IsLoopBack) && iface.flags().testFlag(QNetworkInterface::CanMulticast)) {
            for (int j = 0; j < iface.addressEntries().count(); j++) {
                if (iface.addressEntries().at(j).ip().protocol() != QAbstractSocket::IPv4Protocol) continue;
                qDebug() << "Ocean bind to iface: " << iface.name() << endl << "IP: " << iface.addressEntries().at(j).ip().toString() << endl;
                QUdpSocket* socket = new QUdpSocket(this);
                socket->bind(QHostAddress::AnyIPv4, 8047, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
                socket->joinMulticastGroup(groupAddress, iface);
                connect(socket, SIGNAL(readyRead()), this, SLOT(processIncomingWaves()));
                boundAddresses.append(iface.addressEntries().at(j).ip());
                multicastSockets.append(socket);
            }
        }
    }

    sendSocket = new QUdpSocket(this);
    sendSocket->bind();
}