SyntroStore::SyntroStore(QSettings *settings, QWidget *parent)
	: QMainWindow(parent), m_settings(settings)
{
	m_startingUp = true;
	ui.setupUi(this);

	m_storeStreamDlg = NULL;

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
	connect(ui.actionBasicSetup, SIGNAL(triggered()), this, SLOT(onBasicSetup()));

	initStatusBar();
	initDisplayStats();
	restoreWindowState();

	m_timerId = startTimer(2000);

	SyntroUtils::syntroAppInit(m_settings);
	m_client = new StoreClient(this, m_settings);
	setWindowTitle(QString("%1 - %2")
		.arg(m_settings->value(SYNTRO_PARAMS_APPNAME).toString())
		.arg(m_settings->value(SYNTRO_PARAMS_COMPTYPE).toString()));
	
	connect(this, SIGNAL(refreshStreamSource(int)), m_client, SLOT(refreshStreamSource(int)), Qt::QueuedConnection); 
	m_client->resumeThread();

	m_settings->beginReadArray(SYNTROSTORE_PARAMS_STREAM_SOURCES);
	for (int index = 0; index < SYNTROSTORE_MAX_STREAMS; index++) {
		m_settings->setArrayIndex(index);

		m_rxStreamTable->item(index, SYNTROSTORE_COL_STREAM)->setText(m_settings->value(SYNTROSTORE_PARAMS_STREAM_SOURCE).toString());
		if (m_settings->value(SYNTROSTORE_PARAMS_INUSE).toString() == SYNTRO_PARAMS_TRUE)
			m_useBox[index]->setCheckState(Qt::Checked);
		else
			m_useBox[index]->setCheckState(Qt::Unchecked);
	}
	m_settings->endArray();

	for (int index = 0; index < SYNTROSTORE_MAX_STREAMS; index++)
		emit refreshStreamSource(index);

	m_startingUp = false;
}