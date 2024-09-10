void RemoteProcess::readyRead()
{
    Q_ASSERT(m_server != NULL);
    Q_ASSERT(m_socket != NULL);
    Q_ASSERT(isConnected());

    m_socket->blockSignals(true);

    while ( m_socket->bytesAvailable() > 0 ) {
        QByteArray msg;
        if( !::readMessage(m_socket, &msg) ) {
            log( "Incorrect message from remote process.", LogError );
            emit connectionError();
            return;
        }
        emit newMessage(msg);
    }

    m_socket->blockSignals(false);
}