//I'm in a new network, let's be polite and introduce myself
void LanLinkProvider::broadcastToNetwork()
{

    if (!mServer->isListening()) {
        //Not started
        return;
    }

    Q_ASSERT(mTcpPort != 0);

    qCDebug(KDECONNECT_CORE()) << "Broadcasting identity packet";

    QHostAddress destAddress = mTestMode? QHostAddress::LocalHost : QHostAddress(QStringLiteral("255.255.255.255"));

    NetworkPackage np(QLatin1String(""));
    NetworkPackage::createIdentityPackage(&np);
    np.set(QStringLiteral("tcpPort"), mTcpPort);

#ifdef Q_OS_WIN
    //On Windows we need to broadcast from every local IP address to reach all networks
    QUdpSocket sendSocket;
    for (const QNetworkInterface &iface : QNetworkInterface::allInterfaces()) {
        if ( (iface.flags() & QNetworkInterface::IsUp)
          && (iface.flags() & QNetworkInterface::IsRunning)
          && (iface.flags() & QNetworkInterface::CanBroadcast)) {
            for (const QNetworkAddressEntry &ifaceAddress : iface.addressEntries()) {
                QHostAddress sourceAddress = ifaceAddress.ip();
                if (sourceAddress.protocol() == QAbstractSocket::IPv4Protocol && sourceAddress != QHostAddress::LocalHost) {
                    qCDebug(KDECONNECT_CORE()) << "Broadcasting as" << sourceAddress;
                    sendSocket.bind(sourceAddress, PORT);
                    sendSocket.writeDatagram(np.serialize(), destAddress, PORT);
                    sendSocket.close();
                }
            }
        }
    }
#else
    mUdpSocket.writeDatagram(np.serialize(), destAddress, PORT);
#endif

}