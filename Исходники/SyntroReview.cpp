SyntroReview::SyntroReview(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	layoutWindow();
	restoreWindowState();

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
	connect(m_slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
	connect(ui.actionBasicSetup, SIGNAL(triggered()), this, SLOT(onBasicSetup()));
	connect(ui.actionCFSSelection, SIGNAL(triggered()), this, SLOT(onCFSSelection()));
	connect(ui.actionAudioSetup, SIGNAL(triggered()), this, SLOT(onAudioSetup()));
	ui.actionOpen->setEnabled(false);
	ui.actionClose->setEnabled(false);
	ui.actionCFSSelection->setEnabled(false);

	SyntroUtils::syntroAppInit();

	m_audioSize = -1;
	m_audioRate = -1;
	m_audioChannels = -1;

#if defined(Q_OS_OSX) || defined(Q_OS_WIN32)
		m_audioOut = NULL;
		m_audioOutDevice = NULL;
#else
		m_audioOutIsOpen = false;
#endif

    QSettings *settings = SyntroUtils::getSettings();

    settings->beginGroup(AUDIO_GROUP);

    if (!settings->contains(AUDIO_OUTPUT_DEVICE))

#ifdef Q_OS_OSX
        settings->setValue(AUDIO_OUTPUT_DEVICE, AUDIO_DEFAULT_DEVICE_MAC);
#else
#ifdef Q_OS_LINUX
        settings->setValue(AUDIO_OUTPUT_DEVICE, 0);

    if (!settings->contains(AUDIO_OUTPUT_CARD))
        settings->setValue(AUDIO_OUTPUT_CARD, 0);
#else
        settings->setValue(AUDIO_OUTPUT_DEVICE, AUDIO_DEFAULT_DEVICE);
#endif
#endif
    if (!settings->contains(AUDIO_ENABLE))
        settings->setValue(AUDIO_ENABLE, true);

	m_audioEnabled = settings->value(AUDIO_ENABLE).toBool();

	settings->endGroup();
	delete settings;
	m_client = new ReviewClient(this);
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(onClose()));
	connect(m_client, SIGNAL(newDirectory(QStringList)), this, SLOT(newDirectory(QStringList)), Qt::QueuedConnection);
	connect(m_client, SIGNAL(showImage(QImage, QByteArray, unsigned int, QDateTime)), 
			this, SLOT(showImage(QImage, QByteArray, unsigned int, QDateTime)), Qt::QueuedConnection);
	connect(m_client, SIGNAL(newAudio(QByteArray, int, int, int)), this, SLOT(newAudio(QByteArray, int, int, int)));
	connect(m_client, SIGNAL(newCFSState(int)), this, SLOT(newCFSState(int)), Qt::QueuedConnection);
	connect(m_client, SIGNAL(newFileLength(unsigned int)), this, SLOT(newFileLength(unsigned int)), Qt::QueuedConnection);
	connect(this, SIGNAL(openFile(QString)), m_client, SLOT(openFile(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(closeFile()), m_client, SLOT(closeFile()), Qt::QueuedConnection);
	connect(this, SIGNAL(setPlayMode(int, bool)), m_client, SLOT(setPlayMode(int, bool)), Qt::QueuedConnection);
	connect(m_client, SIGNAL(newPlayMode(int)), this, SLOT(newPlayMode(int)), Qt::QueuedConnection);
	connect(this, SIGNAL(setFrameIndex(unsigned int, int, bool)), m_client, SLOT(setFrameIndex(unsigned int, int, bool)), Qt::QueuedConnection);

	connect(m_client, SIGNAL(dirResponse(QStringList)), this, SLOT(dirResponse(QStringList)));
	connect(this, SIGNAL(requestDir()), m_client, SLOT(requestDir()));
	connect(this, SIGNAL(newCFSList()), m_client, SLOT(newCFSList()));

	m_client->resumeThread();

	m_statusTimer = startTimer(2000);
	m_directoryTimer = startTimer(10000);

	setWindowTitle(QString("%1 - %2")
		.arg(SyntroUtils::getAppType())
		.arg(SyntroUtils::getAppName()));

	setDisabledPlayControls();
}