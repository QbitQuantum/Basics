bool ServerPool::listen(QList<QHostAddress> addrs, quint16 port,
                        bool requireall, PoolServerType servertype)
{
    m_port = port;
    QList<QHostAddress>::const_iterator it;

    for (it = addrs.begin(); it != addrs.end(); ++it)
    {
        PrivTcpServer *server = new PrivTcpServer(this, servertype);
#if (QT_VERSION >= 0x050000)
            connect(server, &PrivTcpServer::newConnection,
                this,   &ServerPool::newTcpConnection);
#else
            connect(server, SIGNAL(newConnection(qt_socket_fd_t)),
                this,   SLOT(newTcpConnection(qt_socket_fd_t)));
#endif

        server->setProxy(m_proxy);
        server->setMaxPendingConnections(m_maxPendingConn);

        if (server->listen(*it, m_port))
        {
            LOG(VB_GENERAL, LOG_INFO, QString("Listening on TCP %1:%2")
                    .arg(PRETTYIP(it)).arg(port));
            if (servertype == kTCPServer)
                m_tcpServers.append(server);
            else

            if (m_port == 0)
                m_port = server->serverPort();
        }
        else
        {
            LOG(VB_GENERAL, LOG_ERR,
                    QString("Failed listening on TCP %1:%2 - Error %3: %4")
                        .arg(PRETTYIP(it))
                        .arg(port)
                        .arg(server->serverError())
                        .arg(server->errorString()));
            server->disconnect();
            server->deleteLater();

            if (server->serverError() == QAbstractSocket::HostNotFoundError)
            {
                LOG(VB_GENERAL, LOG_ERR,
                    QString("Address %1 no longer exists - ignoring")
                    .arg(PRETTYIP(it)));
                continue;
            }

            if (requireall)
            {
                close();
                return false;
            }
        }
    }

    if (m_tcpServers.size() == 0)
        return false;

    m_listening = true;
    return true;
}