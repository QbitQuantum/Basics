ClientServer::ClientServer(QObject *parent_) :
  Avogadro::QtGui::ExtensionPlugin(parent_),
  m_openAction(new QAction(this)), m_settingsAction(new QAction(this)),
  m_molecule(NULL), m_controller(NULL), m_communicator(NULL), m_channel(NULL)
{
  m_openAction->setEnabled(true);
  m_openAction->setText("Open Molecule");
  m_actions.append(m_openAction);

  m_settingsAction->setEnabled(true);
  m_settingsAction->setText("Settings");
  m_actions.append(m_settingsAction);

  connect(m_openAction, SIGNAL(triggered()), SLOT(openFile()));
  connect(m_settingsAction, SIGNAL(triggered()), SLOT(openSettings()));
  connect(this, SIGNAL(connectionError()), SLOT(onConnectionError()));
}