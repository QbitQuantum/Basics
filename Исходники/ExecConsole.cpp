ExecConsole::ExecConsole(QObject *parent)
    : QThread(parent)
{
	SyntroUtils::syntroAppInit();

	m_manager = new ComponentManager();

    connect(m_manager, SIGNAL(running()), this, SLOT(managerRunning()));
    connect(this, SIGNAL(loadComponent(int)), m_manager, SLOT(loadComponent(int)), Qt::QueuedConnection);

	m_manager->resumeThread();
    start();
}