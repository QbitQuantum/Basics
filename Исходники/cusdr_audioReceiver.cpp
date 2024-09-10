void AudioReceiver::initClient() {

    quint16 port = (quint16) (set->getAudioPort() + (io->audio_rx * 2));

    QUdpSocket *socket = new QUdpSocket();
    socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    if (socket->bind(port, QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress)) {

        CHECKED_CONNECT(
            socket,
            SIGNAL(error(QAbstractSocket::SocketError)),
            this,
            SLOT(displayAudioRcvrSocketError(QAbstractSocket::SocketError)));

        CHECKED_CONNECT(
            socket,
            SIGNAL(readyRead()),
            this,
            SLOT(readPendingAudioRcvrData()));

        clientConnections.append(socket);

        AUDIO_RECEIVER << "client socket binding successful.";
        m_message = tr("[server]: listening for rx %1 audio on port %2.");
        emit messageEvent(m_message.arg(io->audio_rx).arg(port));

        //m_dataEngine->clientConnected = true;
        // need to implement connection in dataEngine !!!!
        emit clientConnectedEvent(true);
        //rcveIQ_toggle = false;
    }
    else {

        m_message = tr("[server]: bind socket failed for socket on port %1.");
        emit messageEvent(m_message.arg(port));
    }
}