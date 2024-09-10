void SocketManager::ProcessQueue() {
    WriteBuffer buffer;
    WriteData data;
    {
        std::lock_guard<std::mutex> ulock(m_eventQueueMutex);
        while (!m_writeBufferQueue.empty()) {
            buffer = m_writeBufferQueue.front();
            m_writeBufferQueue.pop();

            auto &desc = m_socketDescriptionVector[buffer.connectionID.sock];

            if (!desc.isOpen) {
                LogDebug("Received packet for write but connection is closed. Packet ignored!");
                continue;
            }

            if (desc.counter != buffer.connectionID.counter)
            {
                LogDebug("Received packet for write but counter is broken. Packet ignored!");
                continue;
            }

            if (desc.useSendMsg) {
                LogError("Some service tried to push rawdata to socket that usees sendmsg!");
                continue;
            }

            std::copy(
                buffer.rawBuffer.begin(),
                buffer.rawBuffer.end(),
                std::back_inserter(desc.rawBuffer));

            FD_SET(buffer.connectionID.sock, &m_writeSet);
        }

        while(!m_writeDataQueue.empty()) {
            data = m_writeDataQueue.front();
            m_writeDataQueue.pop();

            auto &desc = m_socketDescriptionVector[data.connectionID.sock];

            if (!desc.isOpen) {
                LogDebug("Received packet for sendmsg but connection is closed. Packet ignored!");
                continue;
            }

            if (desc.counter != data.connectionID.counter)
            {
                LogDebug("Received packet for write but counter is broken. Packet ignored!");
                continue;
            }

            if (!desc.useSendMsg) {
                LogError("Some service tries to push SendMsgData to socket that uses write!");
                continue;
            }

            desc.sendMsgDataQueue.push(data.sendMsgData);

            FD_SET(data.connectionID.sock, &m_writeSet);
        }
    }

    while (1) {
        ConnectionID connection;
        {
            std::lock_guard<std::mutex> ulock(m_eventQueueMutex);
            if (m_closeQueue.empty())
                return;
            connection = m_closeQueue.front();
            m_closeQueue.pop();
        }

        if (!m_socketDescriptionVector[connection.sock].isOpen)
            continue;

        if (connection.counter != m_socketDescriptionVector[connection.sock].counter)
            continue;

        CloseSocket(connection.sock);
    }
}