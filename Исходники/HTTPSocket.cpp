HttpSocket::HttpSocket(const QString &iface, quint16 port)
    : QTcpServer(nullptr)
    , cfgInterface(iface)
    , terminated(false)
{
    if (!openPort(port)) {
        openPort(0);
    }

    DBUG << isListening() << serverPort();

    connect(MPDConnection::self(), SIGNAL(socketAddress(QString)), this, SLOT(mpdAddress(QString)));
    connect(MPDConnection::self(), SIGNAL(cantataStreams(QList<Song>,bool)), this, SLOT(cantataStreams(QList<Song>,bool)));
    connect(MPDConnection::self(), SIGNAL(cantataStreams(QStringList)), this, SLOT(cantataStreams(QStringList)));
    connect(MPDConnection::self(), SIGNAL(removedIds(QSet<qint32>)), this, SLOT(removedIds(QSet<qint32>)));
    connect(this, SIGNAL(newConnection()), SLOT(handleNewConnection()));
}