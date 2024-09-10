void SocketHandler::socketReadable()
{
    int sessionId = -1;
    QLocalSocket* socket = (QLocalSocket*)sender();
    ((QLocalSocket*)sender())->read((char*)&sessionId, sizeof(int));

    disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketReadable()));

    if (sessionId >= 0) {
        if(!m_idMap.contains(sessionId))
            m_idMap.insert(sessionId, new SessionData((QLocalSocket*)sender(), this));
    } else {
        sensordLogC() << "[SocketHandler]: Failed to read valid session ID from client. Closing socket.";
        socket->abort();
    }
}