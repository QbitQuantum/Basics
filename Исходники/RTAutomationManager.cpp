RTAutomationManager::RTAutomationManager()
    : QMainWindow()
{
    ui.setupUi(this);

    layoutWindow();

    m_dialog = NULL;

    m_client = new ManagerClient();

    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(m_client, SIGNAL(clientConnected()), this, SLOT(clientConnected()));
    connect(m_client, SIGNAL(clientDisconnected()), this, SLOT(clientDisconnected()));
    connect(this, SIGNAL(clientRestart()), m_client, SLOT(clientRestart()));
    connect(this, SIGNAL(clientEnable(bool)), m_client, SLOT(clientEnable(bool)));

    m_client->resumeThread();

    restoreWindowState();
    initStatusBar();

    setWindowTitle(RTAutomationArgs::getAppName());
}