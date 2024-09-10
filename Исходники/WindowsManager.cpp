void WindowsManager::addWindow(Window *window, OpenHints hints)
{
	if (!window)
	{
		return;
	}

	int index = ((!(hints & EndOpen) && SettingsManager::getValue(QLatin1String("TabBar/OpenNextToActive")).toBool()) ? (m_tabBar->currentIndex() + 1) : m_tabBar->count());

	if (!window->isPinned())
	{
		const int offset = m_tabBar->getPinnedTabsAmount();

		if (index < offset)
		{
			index = offset;
		}
	}

	m_tabBar->addTab(index, window);

	m_mdi->addWindow(window);

	if (!(hints & BackgroundOpen))
	{
		m_tabBar->setCurrentIndex(index);

		if (m_isRestored)
		{
			setActiveWindow(index);
		}
	}

	connect(window, SIGNAL(titleChanged(QString)), this, SLOT(setTitle(QString)));
	connect(window, SIGNAL(requestedOpenUrl(QUrl,OpenHints)), this, SLOT(open(QUrl,OpenHints)));
	connect(window, SIGNAL(requestedOpenBookmark(BookmarksItem*,OpenHints)), this, SLOT(open(BookmarksItem*,OpenHints)));
	connect(window, SIGNAL(requestedSearch(QString,QString,OpenHints)), this, SLOT(search(QString,QString,OpenHints)));
	connect(window, SIGNAL(requestedAddBookmark(QUrl,QString)), this, SIGNAL(requestedAddBookmark(QUrl,QString)));
	connect(window, SIGNAL(requestedNewWindow(ContentsWidget*,OpenHints)), this, SLOT(openWindow(ContentsWidget*,OpenHints)));
	connect(window, SIGNAL(requestedCloseWindow(Window*)), this, SLOT(closeWindow(Window*)));

	emit windowAdded(index);
}