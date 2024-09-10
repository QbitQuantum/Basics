void ApiServer::stopListening()
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO;

    // Closes the server. The server will no longer listen for incoming connections.
    close();

    m_lockedClient = NULL;

    emit updateDeviceLockStatus(Api::DeviceUnlocked);

    QMap<QTcpSocket*, ClientInfo>::iterator i;
    for (i = m_clients.begin(); i != m_clients.end(); ++i)
    {
        QTcpSocket * client = dynamic_cast<QTcpSocket*>(i.key());

        disconnect(client, SIGNAL(readyRead()), this, SLOT(clientProcessCommands()));
        disconnect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

        client->abort();
        client->deleteLater();
    }

    m_clients.clear();
}