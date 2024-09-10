static void* ui_companion_qt_init(void)
{
   ui_companion_qt_t *handle = (ui_companion_qt_t*)calloc(1, sizeof(*handle));
   MainWindow *mainwindow = NULL;
   QHBoxLayout *browserButtonsHBoxLayout = NULL;
   QVBoxLayout *layout = NULL;
   QVBoxLayout *launchWithWidgetLayout = NULL;
   QHBoxLayout *coreComboBoxLayout = NULL;
   QMenuBar *menu = NULL;
   QDesktopWidget *desktop = NULL;
   QMenu *fileMenu = NULL;
   QMenu *editMenu = NULL;
   QMenu *viewMenu = NULL;
   QMenu *viewClosedDocksMenu = NULL;
   QMenu *toolsMenu = NULL;
   QMenu *updaterMenu = NULL;
   QMenu *helpMenu = NULL;
   QRect desktopRect;
   QDockWidget *thumbnailDock = NULL;
   QDockWidget *thumbnail2Dock = NULL;
   QDockWidget *thumbnail3Dock = NULL;
   QDockWidget *browserAndPlaylistTabDock = NULL;
   QDockWidget *coreSelectionDock = NULL;
   QTabWidget *browserAndPlaylistTabWidget = NULL;
   QWidget *widget = NULL;
   QWidget *browserWidget = NULL;
   QWidget *playlistWidget = NULL;
   QWidget *coreSelectionWidget = NULL;
   QWidget *launchWithWidget = NULL;
   ThumbnailWidget *thumbnailWidget = NULL;
   ThumbnailWidget *thumbnail2Widget = NULL;
   ThumbnailWidget *thumbnail3Widget = NULL;
   QPushButton *browserDownloadsButton = NULL;
   QPushButton *browserUpButton = NULL;
   QPushButton *browserStartButton = NULL;
   ThumbnailLabel *thumbnail = NULL;
   ThumbnailLabel *thumbnail2 = NULL;
   ThumbnailLabel *thumbnail3 = NULL;
   QAction *editSearchAction = NULL;
   QAction *loadCoreAction = NULL;
   QAction *unloadCoreAction = NULL;
   QAction *exitAction = NULL;
   QComboBox *launchWithComboBox = NULL;
   QSettings *qsettings = NULL;
   QListWidget *listWidget = NULL;
   int i = 0;

   if (!handle)
      return NULL;

   handle->app = static_cast<ui_application_qt_t*>(ui_application_qt.initialize());
   handle->window = static_cast<ui_window_qt_t*>(ui_window_qt.init());

   desktop = qApp->desktop();
   desktopRect = desktop->availableGeometry();

   mainwindow = handle->window->qtWindow;

   qsettings = mainwindow->settings();

   mainwindow->resize(qMin(desktopRect.width(), INITIAL_WIDTH), qMin(desktopRect.height(), INITIAL_HEIGHT));
   mainwindow->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, mainwindow->size(), desktopRect));

   mainwindow->setWindowTitle("RetroArch");
   mainwindow->setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks | GROUPED_DRAGGING);

   listWidget = mainwindow->playlistListWidget();

   widget = new FileDropWidget(mainwindow);
   widget->setObjectName("tableWidget");
   widget->setContextMenuPolicy(Qt::CustomContextMenu);

   QObject::connect(widget, SIGNAL(filesDropped(QStringList)), mainwindow, SLOT(onPlaylistFilesDropped(QStringList)));
   QObject::connect(widget, SIGNAL(deletePressed()), mainwindow, SLOT(deleteCurrentPlaylistItem()));
   QObject::connect(widget, SIGNAL(customContextMenuRequested(const QPoint&)), mainwindow, SLOT(onFileDropWidgetContextMenuRequested(const QPoint&)));

   layout = new QVBoxLayout();
   layout->addWidget(mainwindow->contentTableWidget());
   layout->addWidget(mainwindow->contentGridWidget());

   widget->setLayout(layout);

   mainwindow->setCentralWidget(widget);

   menu = mainwindow->menuBar();

   fileMenu = menu->addMenu(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_FILE));

   loadCoreAction = fileMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_FILE_LOAD_CORE), mainwindow, SLOT(onLoadCoreClicked()));
   loadCoreAction->setShortcut(QKeySequence("Ctrl+L"));

   unloadCoreAction = fileMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_FILE_UNLOAD_CORE), mainwindow, SLOT(onUnloadCoreMenuAction()));
   unloadCoreAction->setObjectName("unloadCoreAction");
   unloadCoreAction->setEnabled(false);
   unloadCoreAction->setShortcut(QKeySequence("Ctrl+U"));

   exitAction = fileMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_FILE_EXIT), mainwindow, SLOT(close()));
   exitAction->setShortcut(QKeySequence::Quit);

   editMenu = menu->addMenu(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_EDIT));
   editSearchAction = editMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_EDIT_SEARCH), mainwindow->searchLineEdit(), SLOT(setFocus()));
   editSearchAction->setShortcut(QKeySequence::Find);

   viewMenu = menu->addMenu(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_VIEW));
   viewClosedDocksMenu = viewMenu->addMenu(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_VIEW_CLOSED_DOCKS));
   viewClosedDocksMenu->setObjectName("viewClosedDocksMenu");

   QObject::connect(viewClosedDocksMenu, SIGNAL(aboutToShow()), mainwindow, SLOT(onViewClosedDocksAboutToShow()));

   viewMenu->addSeparator();
   viewMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_VIEW_TYPE_ICONS), mainwindow, SLOT(onIconViewClicked()));
   viewMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_VIEW_TYPE_LIST), mainwindow, SLOT(onListViewClicked()));
   viewMenu->addSeparator();
   viewMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_VIEW_OPTIONS), mainwindow->viewOptionsDialog(), SLOT(showDialog()));

   toolsMenu = menu->addMenu(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_TOOLS));
   updaterMenu = toolsMenu->addMenu(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ONLINE_UPDATER));
#ifdef Q_OS_WIN
   updaterMenu->addAction(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_UPDATE_RETROARCH_NIGHTLY), mainwindow, SLOT(updateRetroArchNightly()));
#endif
   helpMenu = menu->addMenu(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_HELP));
   helpMenu->addAction(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_HELP_DOCUMENTATION)), mainwindow, SLOT(showDocs()));
   helpMenu->addAction(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_HELP_ABOUT)) + "...", mainwindow, SLOT(showAbout()));
   helpMenu->addAction("About Qt...", qApp, SLOT(aboutQt()));

   playlistWidget = new QWidget();
   playlistWidget->setLayout(new QVBoxLayout());
   playlistWidget->setObjectName("playlistWidget");

   playlistWidget->layout()->addWidget(mainwindow->playlistListWidget());

   browserWidget = new QWidget();
   browserWidget->setLayout(new QVBoxLayout());
   browserWidget->setObjectName("browserWidget");

   browserDownloadsButton = new QPushButton(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_ASSETS_DIRECTORY));
   browserUpButton = new QPushButton(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_TAB_FILE_BROWSER_UP));
   browserStartButton = new QPushButton(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_FAVORITES));

   QObject::connect(browserDownloadsButton, SIGNAL(clicked()), mainwindow, SLOT(onBrowserDownloadsClicked()));
   QObject::connect(browserUpButton, SIGNAL(clicked()), mainwindow, SLOT(onBrowserUpClicked()));
   QObject::connect(browserStartButton, SIGNAL(clicked()), mainwindow, SLOT(onBrowserStartClicked()));

   browserButtonsHBoxLayout = new QHBoxLayout();
   browserButtonsHBoxLayout->addWidget(browserUpButton);
   browserButtonsHBoxLayout->addWidget(browserStartButton);
   browserButtonsHBoxLayout->addWidget(browserDownloadsButton);

   qobject_cast<QVBoxLayout*>(browserWidget->layout())->addLayout(browserButtonsHBoxLayout);
   browserWidget->layout()->addWidget(mainwindow->dirTreeView());

   browserAndPlaylistTabWidget = mainwindow->browserAndPlaylistTabWidget();
   browserAndPlaylistTabWidget->setObjectName("browserAndPlaylistTabWidget");

   /* Several functions depend on the same tab title strings here, so if you change these, make sure to change those too
    * setCoreActions()
    * onTabWidgetIndexChanged()
    * onCurrentListItemChanged()
    */
   browserAndPlaylistTabWidget->addTab(playlistWidget, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_TAB_PLAYLISTS));
   browserAndPlaylistTabWidget->addTab(browserWidget, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_TAB_FILE_BROWSER));

   browserAndPlaylistTabDock = new QDockWidget(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_DOCK_CONTENT_BROWSER), mainwindow);
   browserAndPlaylistTabDock->setObjectName("browserAndPlaylistTabDock");
   browserAndPlaylistTabDock->setProperty("default_area", Qt::LeftDockWidgetArea);
   browserAndPlaylistTabDock->setProperty("menu_text", msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_MENU_DOCK_CONTENT_BROWSER));
   browserAndPlaylistTabDock->setWidget(browserAndPlaylistTabWidget);

   mainwindow->addDockWidget(static_cast<Qt::DockWidgetArea>(browserAndPlaylistTabDock->property("default_area").toInt()), browserAndPlaylistTabDock);

   browserButtonsHBoxLayout->addItem(new QSpacerItem(browserAndPlaylistTabWidget->tabBar()->width(), 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

   thumbnailWidget = new ThumbnailWidget();
   thumbnail2Widget = new ThumbnailWidget();
   thumbnail3Widget = new ThumbnailWidget();

   thumbnailWidget->setLayout(new QVBoxLayout());
   thumbnail2Widget->setLayout(new QVBoxLayout());
   thumbnail3Widget->setLayout(new QVBoxLayout());

   thumbnailWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
   thumbnail2Widget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
   thumbnail3Widget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

   thumbnail = new ThumbnailLabel();
   thumbnail->setObjectName("thumbnail");

   thumbnail2 = new ThumbnailLabel();
   thumbnail2->setObjectName("thumbnail2");

   thumbnail3 = new ThumbnailLabel();
   thumbnail3->setObjectName("thumbnail3");

   thumbnail->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
   thumbnail2->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
   thumbnail3->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

   QObject::connect(mainwindow, SIGNAL(thumbnailChanged(const QPixmap&)), thumbnail, SLOT(setPixmap(const QPixmap&)));
   QObject::connect(mainwindow, SIGNAL(thumbnail2Changed(const QPixmap&)), thumbnail2, SLOT(setPixmap(const QPixmap&)));
   QObject::connect(mainwindow, SIGNAL(thumbnail3Changed(const QPixmap&)), thumbnail3, SLOT(setPixmap(const QPixmap&)));

   thumbnailWidget->layout()->addWidget(thumbnail);
   thumbnail2Widget->layout()->addWidget(thumbnail2);
   thumbnail3Widget->layout()->addWidget(thumbnail3);

   thumbnailDock = new QDockWidget(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_THUMBNAIL_BOXART), mainwindow);
   thumbnailDock->setObjectName("thumbnailDock");
   thumbnailDock->setProperty("default_area", Qt::RightDockWidgetArea);
   thumbnailDock->setProperty("menu_text", msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_THUMBNAIL_BOXART));
   thumbnailDock->setWidget(thumbnailWidget);

   mainwindow->addDockWidget(static_cast<Qt::DockWidgetArea>(thumbnailDock->property("default_area").toInt()), thumbnailDock);

   thumbnail2Dock = new QDockWidget(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_THUMBNAIL_TITLE_SCREEN), mainwindow);
   thumbnail2Dock->setObjectName("thumbnail2Dock");
   thumbnail2Dock->setProperty("default_area", Qt::RightDockWidgetArea);
   thumbnail2Dock->setProperty("menu_text", msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_THUMBNAIL_TITLE_SCREEN));
   thumbnail2Dock->setWidget(thumbnail2Widget);

   mainwindow->addDockWidget(static_cast<Qt::DockWidgetArea>(thumbnail2Dock->property("default_area").toInt()), thumbnail2Dock);

   thumbnail3Dock = new QDockWidget(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_THUMBNAIL_SCREENSHOT), mainwindow);
   thumbnail3Dock->setObjectName("thumbnail3Dock");
   thumbnail3Dock->setProperty("default_area", Qt::RightDockWidgetArea);
   thumbnail3Dock->setProperty("menu_text", msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_THUMBNAIL_SCREENSHOT));
   thumbnail3Dock->setWidget(thumbnail3Widget);

   mainwindow->addDockWidget(static_cast<Qt::DockWidgetArea>(thumbnail3Dock->property("default_area").toInt()), thumbnail3Dock);

   mainwindow->tabifyDockWidget(thumbnailDock, thumbnail2Dock);
   mainwindow->tabifyDockWidget(thumbnailDock, thumbnail3Dock);

   /* when tabifying the dock widgets, the last tab added is selected by default, so we need to re-select the first tab */
   thumbnailDock->raise();

   coreSelectionWidget = new QWidget();
   coreSelectionWidget->setLayout(new QVBoxLayout());

   launchWithComboBox = mainwindow->launchWithComboBox();

   launchWithWidgetLayout = new QVBoxLayout();

   launchWithWidget = new QWidget();
   launchWithWidget->setLayout(launchWithWidgetLayout);

   coreComboBoxLayout = new QHBoxLayout();

   mainwindow->runPushButton()->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding));
   mainwindow->stopPushButton()->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding));
   mainwindow->startCorePushButton()->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding));

   coreComboBoxLayout->addWidget(launchWithComboBox);
   coreComboBoxLayout->addWidget(mainwindow->startCorePushButton());
   coreComboBoxLayout->addWidget(mainwindow->coreInfoPushButton());
   coreComboBoxLayout->addWidget(mainwindow->runPushButton());
   coreComboBoxLayout->addWidget(mainwindow->stopPushButton());

   mainwindow->stopPushButton()->hide();

   coreComboBoxLayout->setStretchFactor(launchWithComboBox, 1);

   launchWithWidgetLayout->addLayout(coreComboBoxLayout);

   coreSelectionWidget->layout()->addWidget(launchWithWidget);

   coreSelectionWidget->layout()->addItem(new QSpacerItem(20, browserAndPlaylistTabWidget->height(), QSizePolicy::Minimum, QSizePolicy::Expanding));

   coreSelectionDock = new QDockWidget(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_CORE), mainwindow);
   coreSelectionDock->setObjectName("coreSelectionDock");
   coreSelectionDock->setProperty("default_area", Qt::LeftDockWidgetArea);
   coreSelectionDock->setProperty("menu_text", msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_CORE));
   coreSelectionDock->setWidget(coreSelectionWidget);

   mainwindow->addDockWidget(static_cast<Qt::DockWidgetArea>(coreSelectionDock->property("default_area").toInt()), coreSelectionDock);

   mainwindow->splitDockWidget(browserAndPlaylistTabDock, coreSelectionDock, Qt::Vertical);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
   mainwindow->resizeDocks(QList<QDockWidget*>() << coreSelectionDock, QList<int>() << 1, Qt::Vertical);
#endif

   /* this should come last */
   mainwindow->resizeThumbnails(true, true, true);

   if (qsettings->contains("all_playlists_list_max_count"))
      mainwindow->setAllPlaylistsListMaxCount(qsettings->value("all_playlists_list_max_count", 0).toInt());

   if (qsettings->contains("all_playlists_grid_max_count"))
      mainwindow->setAllPlaylistsGridMaxCount(qsettings->value("all_playlists_grid_max_count", 5000).toInt());

   if (qsettings->contains("geometry"))
      if (qsettings->contains("save_geometry"))
         mainwindow->restoreGeometry(qsettings->value("geometry").toByteArray());

   if (qsettings->contains("save_dock_positions"))
      if (qsettings->contains("dock_positions"))
         mainwindow->restoreState(qsettings->value("dock_positions").toByteArray());

   if (qsettings->contains("theme"))
   {
      QString themeStr = qsettings->value("theme").toString();
      MainWindow::Theme theme = mainwindow->getThemeFromString(themeStr);

      if (qsettings->contains("custom_theme") && theme == MainWindow::THEME_CUSTOM)
      {
         QString customThemeFilePath = qsettings->value("custom_theme").toString();

         mainwindow->setCustomThemeFile(customThemeFilePath);
      }

      mainwindow->setTheme(theme);
   }
   else
      mainwindow->setTheme();

   if (qsettings->contains("view_type"))
   {
      QString viewType = qsettings->value("view_type", "list").toString();

      if (viewType == "list")
         mainwindow->setCurrentViewType(MainWindow::VIEW_TYPE_LIST);
      else if (viewType == "icons")
         mainwindow->setCurrentViewType(MainWindow::VIEW_TYPE_ICONS);
      else
         mainwindow->setCurrentViewType(MainWindow::VIEW_TYPE_LIST);

      /* we set it to the same thing a second time so that m_lastViewType is also equal to the startup view type */
      mainwindow->setCurrentViewType(mainwindow->getCurrentViewType());
   }
   else
      mainwindow->setCurrentViewType(MainWindow::VIEW_TYPE_LIST);

   /* We make sure to hook up the tab widget callback only after the tabs themselves have been added,
    * but before changing to a specific one, to avoid the callback firing before the view type is set.
    */
   QObject::connect(browserAndPlaylistTabWidget, SIGNAL(currentChanged(int)), mainwindow, SLOT(onTabWidgetIndexChanged(int)));

   /* setting the last tab must come after setting the view type */
   if (qsettings->contains("save_last_tab"))
   {
      int lastTabIndex = qsettings->value("last_tab", 0).toInt();

      if (lastTabIndex >= 0 && browserAndPlaylistTabWidget->count() > lastTabIndex)
      {
         browserAndPlaylistTabWidget->setCurrentIndex(lastTabIndex);
         mainwindow->onTabWidgetIndexChanged(lastTabIndex);
      }
   }
   else
   {
      browserAndPlaylistTabWidget->setCurrentIndex(0);
      mainwindow->onTabWidgetIndexChanged(0);
   }

   for (i = 0; i < listWidget->count() && listWidget->count() > 0; i++)
   {
      /* select the first non-hidden row */
      if (!listWidget->isRowHidden(i))
      {
         listWidget->setCurrentRow(i);
         break;
      }
   }

   return handle;
}