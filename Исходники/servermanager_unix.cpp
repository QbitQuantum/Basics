int ServerManager::createListeningSocket(const QHostAddress &address, quint16 port)
{
    int sd = 0;
    QTcpServer server;

    if (!server.listen(address, port)) {
        qCritical("listen failed");
        return sd;
    }

    sd = ::fcntl(server.socketDescriptor(), F_DUPFD, 0);
#if defined(FD_CLOEXEC)
    ::fcntl(sd, F_SETFD, 0);
#endif
    server.close();
    return sd;
}