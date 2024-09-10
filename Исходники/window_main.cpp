MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), localServer(0)
{
    QPixmapCache::setCacheLimit(200000);

    client = new RemoteClient;
    connect(client, SIGNAL(connectionClosedEventReceived(const Event_ConnectionClosed &)), this, SLOT(processConnectionClosedEvent(const Event_ConnectionClosed &)));
    connect(client, SIGNAL(serverShutdownEventReceived(const Event_ServerShutdown &)), this, SLOT(processServerShutdownEvent(const Event_ServerShutdown &)));
    connect(client, SIGNAL(loginError(Response::ResponseCode, QString, quint32)), this, SLOT(loginError(Response::ResponseCode, QString, quint32)));
    connect(client, SIGNAL(socketError(const QString &)), this, SLOT(socketError(const QString &)));
    connect(client, SIGNAL(serverTimeout()), this, SLOT(serverTimeout()));
    connect(client, SIGNAL(statusChanged(ClientStatus)), this, SLOT(statusChanged(ClientStatus)));
    connect(client, SIGNAL(protocolVersionMismatch(int, int)), this, SLOT(protocolVersionMismatch(int, int)));
    connect(client, SIGNAL(userInfoChanged(const ServerInfo_User &)), this, SLOT(userInfoReceived(const ServerInfo_User &)), Qt::BlockingQueuedConnection);
    
    clientThread = new QThread(this);
    client->moveToThread(clientThread);
    clientThread->start();

    createActions();
    createMenus();
    
    tabSupervisor = new TabSupervisor(client);
    connect(tabSupervisor, SIGNAL(setMenu(QList<QMenu *>)), this, SLOT(updateTabMenu(QList<QMenu *>)));
    connect(tabSupervisor, SIGNAL(localGameEnded()), this, SLOT(localGameEnded()));
    tabSupervisor->addDeckEditorTab(0);    
    
    setCentralWidget(tabSupervisor);

    retranslateUi();
    
    resize(900, 700);
    restoreGeometry(settingsCache->getMainWindowGeometry());
    aFullScreen->setChecked(windowState() & Qt::WindowFullScreen);
}