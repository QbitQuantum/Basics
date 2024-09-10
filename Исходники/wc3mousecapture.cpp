WC3MouseCapture::WC3MouseCapture(QWidget *parent)
: QWidget(parent), m_icon(QIcon(ICON_NAME), this), m_timer(this), m_menu(this),
m_exitAction(EXIT_ACTION_TITLE, this), m_isDisabled(false) {
	// Set up trayicon
	m_icon.show();

	// Hide widget
	//QTimer::singleShot(0, this, SLOT(hide()));

	// Set up menu
	m_menu.addAction(&m_exitAction);
	m_icon.setContextMenu(&m_menu);

	// Save default mouse rect
	GetClipCursor(&m_defaultRect);

	// Connect signals & slots
	QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(checkActiveWindow()));
	QObject::connect(this, SIGNAL(wc3Activated(HWND&)), this, SLOT(captureMouse(HWND&)));
	QObject::connect(this, SIGNAL(wc3Deactivated()), this, SLOT(endCapture()));
	QObject::connect(&m_exitAction, SIGNAL(activated()), this, SLOT(close()));

	// Start the timer
	m_timer.start(DEFAULT_TIMEOUT);

	// Register hotkey
	RegisterHotKey(QWidget::winId(), NULL, NULL, DEFAULT_HOTKEY);
}