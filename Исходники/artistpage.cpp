void ArtistPage::createContent()
{
  MApplicationPage::createContent();

  QGraphicsWidget *panel = centralWidget();
  MLayout* layout = new MLayout(panel);
  m_policy = new MLinearLayoutPolicy(layout, Qt::Vertical);
  layout->setAnimation(NULL);
  panel->setLayout(layout);
  layout->setLandscapePolicy(m_policy);
  layout->setPortraitPolicy(m_policy);

  if (m_pageMode == ALL_ARTISTS) {
    // Menu Actions
    MAction* actionImportLastfm = new MAction(panel);
    actionImportLastfm->setText(tr("Import from Last.fm"));
    actionImportLastfm->setLocation(MAction::ApplicationMenuLocation);
    addAction(actionImportLastfm);
    connect(actionImportLastfm, SIGNAL(triggered()), this, SLOT(slotImportLastfm()));

    MAction* actionAddArtist = new MAction(panel);
    actionAddArtist->setText(tr("Add artist"));
    actionAddArtist->setLocation(MAction::ApplicationMenuLocation);
    addAction(actionAddArtist);
    connect(actionAddArtist, SIGNAL(triggered()), this, SLOT(slotAddArtist()));

    // Toolbar Actions
    MAction* actionFilter = new MAction("icon-m-toolbar-filter", "", this);
    actionFilter->setLocation(MAction::ToolBarLocation);
    addAction(actionFilter);
    connect(actionFilter, SIGNAL(triggered()), this, SLOT(slotShowFilter()));
  }

  MAction* actionRefresh = new MAction("icon-m-toolbar-refresh", "", this);
  actionRefresh->setLocation(MAction::ToolBarLocation);
  addAction(actionRefresh);
  connect(actionRefresh, SIGNAL(triggered()), this, SLOT(slotRefreshEvents()));

  MAction* actionSearch = new MAction("icon-m-toolbar-search", "", this);
  actionSearch->setLocation(MAction::ToolBarLocation);
  addAction(actionSearch);
  connect(actionSearch, SIGNAL(triggered()), this, SLOT(slotShowSearch()));

  // setup model
  m_artistsModel = new ArtistModel(m_dbStorage, artistsModelQuery());

  // filtering text box
  QGraphicsLinearLayout *containerLayout = new QGraphicsLinearLayout(Qt::Horizontal);

  MLabel* filterLabel = new MLabel(tr("Filter artist:"));
  containerLayout->addItem(filterLabel);

  m_filter = new MTextEdit(MTextEditModel::SingleLine, QString());
  containerLayout->addItem(m_filter);
  m_filter->setObjectName("CommonSingleInputField");
  connect(m_filter, SIGNAL(textChanged()), this, SLOT(slotFilterChanged()));

  m_filterWidget = new MWidget();
  m_filterWidget->setLayout(containerLayout);

  // No artist found label
  m_noArtistLabel = new MLabel(tr("No artist available, add them using one of "
                                  "menu options."));
  m_noArtistLabel->setAlignment(Qt::AlignCenter);
  if (m_artistsModel->rowCount() == 0)
    m_policy->addItem(m_noArtistLabel);

  // MList with fast view
  MList* artistsList = new MList();
  artistsList->setSelectionMode(MList::SingleSelection);

  // Content item creator and item model for the list
  artistsList->setCellCreator(new ArtistItemCreator(m_pageMode, m_dbStorage,
                                                    m_country));
  artistsList->setItemModel(m_artistsModel);
  m_policy->addItem(artistsList);

  connect(artistsList, SIGNAL(itemClicked(QModelIndex)),
           this, SLOT(slotArtistClicked(QModelIndex)));
  connect(DBManager::instance(m_dbStorage), SIGNAL(artistAdded(int,bool)),
           this, SLOT(slotArtistAdded(int,bool)));

  if (m_pageMode == ARTIST_NEAR_LOCATION_SEARCH) {
    //overwrite history
    MApplicationWindow* appWindow = applicationWindow();
    MScene* scene = appWindow->scene();
    MSceneManager* sceneManager = scene->sceneManager();
    QList<MSceneWindow*> history = sceneManager->pageHistory();
    if (history.last()->metaObject()->className() == NearLocationSearchPage::staticMetaObject.className()) {
      // overwrite history only if the last page is NearLocationSearchPage
      history.removeAt(history.size()-1);
      if (history.last()->metaObject()->className() != NearLocationMainPage::staticMetaObject.className()) {
        MApplicationPage* prevPage = new NearLocationMainPage();
        history << prevPage;
      }
      sceneManager->setPageHistory(history);
    }

    //search events
    m_lastfm->getEventsNearLocation(m_latitude, m_longitude, m_distance);
  }

  if (m_dbStorage == DBManager::DISK) {
    DBManager* db = DBManager::instance(m_dbStorage);
    QStringList incompleteArtists = db->incompleteArtists();
    foreach(QString artist, incompleteArtists) {
      m_lastfm->getEventsForArtist(artist);
    }