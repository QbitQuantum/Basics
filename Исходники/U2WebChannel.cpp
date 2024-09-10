U2WebChannel::U2WebChannel(QWebEnginePage *page)
    : QObject(page),
      channel(new QWebChannel(this)),
      port(INVALID_PORT)
{
#if (QT_VERSION < 0x050500)
    QWebSocketServer *server = new QWebSocketServer(QStringLiteral("UGENE Standalone Server"), QWebSocketServer::NonSecureMode, this);
    port = 12346;
    while (!server->listen(QHostAddress::LocalHost, port)) { //TODO: need more useful solution
        port++;
    }

    WebSocketClientWrapper *clientWrapper = new WebSocketClientWrapper(server, this);
    connect(clientWrapper, &WebSocketClientWrapper::clientConnected, channel, &QWebChannel::connectTo);
#else
    page->setWebChannel(channel);
#endif
}