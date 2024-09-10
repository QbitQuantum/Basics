Utils::Port LocalQmlProfilerRunner::findFreePort(QString &host)
{
    QTcpServer server;
    if (!server.listen(QHostAddress::LocalHost)
            && !server.listen(QHostAddress::LocalHostIPv6)) {
        qWarning() << "Cannot open port on host for QML profiling.";
        return Utils::Port();
    }
    host = server.serverAddress().toString();
    return Utils::Port(server.serverPort());
}