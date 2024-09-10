TabDeckEditor::TabDeckEditor(TabSupervisor *_tabSupervisor, QWidget *parent)
    : Tab(_tabSupervisor, parent), modified(false)
{
    aClearSearch = new QAction(QString(), this);
    aClearSearch->setIcon(QIcon(":/resources/icon_clearsearch.svg"));
    connect(aClearSearch, SIGNAL(triggered()), this, SLOT(actClearSearch()));

    searchLabel = new QLabel();
    searchEdit = new SearchLineEdit;
    searchLabel->setBuddy(searchEdit);
    setFocusProxy(searchEdit);
    setFocusPolicy(Qt::ClickFocus);

    searchEdit->installEventFilter(&searchKeySignals);
    connect(searchEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateSearch(const QString &)));
    connect(&searchKeySignals, SIGNAL(onEnter()), this, SLOT(actAddCard()));
    connect(&searchKeySignals, SIGNAL(onCtrlAltEqual()), this, SLOT(actAddCard()));
    connect(&searchKeySignals, SIGNAL(onCtrlAltRBracket()), this, SLOT(actAddCardToSideboard()));
    connect(&searchKeySignals, SIGNAL(onCtrlAltMinus()), this, SLOT(actDecrementCard()));
    connect(&searchKeySignals, SIGNAL(onCtrlAltLBracket()), this, SLOT(actDecrementCardFromSideboard()));
    connect(&searchKeySignals, SIGNAL(onCtrlAltEnter()), this, SLOT(actAddCardToSideboard()));
    connect(&searchKeySignals, SIGNAL(onCtrlEnter()), this, SLOT(actAddCardToSideboard()));

    QToolBar *deckEditToolBar = new QToolBar;
    deckEditToolBar->setOrientation(Qt::Horizontal);
    deckEditToolBar->setIconSize(QSize(24, 24));

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(deckEditToolBar);
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);

    databaseModel = new CardDatabaseModel(db, this);
    databaseDisplayModel = new CardDatabaseDisplayModel(this);
    databaseDisplayModel->setSourceModel(databaseModel);
    databaseDisplayModel->setFilterKeyColumn(0);
    databaseDisplayModel->sort(0, Qt::AscendingOrder);

    databaseView = new QTreeView();
    databaseView->setFocusProxy(searchEdit);
    databaseView->setModel(databaseDisplayModel);
    databaseView->setUniformRowHeights(true);
    databaseView->setRootIsDecorated(false);
    databaseView->setAlternatingRowColors(true);
    databaseView->setSortingEnabled(true);
    databaseView->sortByColumn(0, Qt::AscendingOrder);
    databaseView->resizeColumnToContents(0);
    connect(databaseView->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(updateCardInfoLeft(const QModelIndex &, const QModelIndex &)));
    connect(databaseView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(actAddCard()));
    searchEdit->setTreeView(databaseView);

    QVBoxLayout *leftFrame = new QVBoxLayout;
    leftFrame->addLayout(searchLayout);
    leftFrame->addWidget(databaseView);

    cardInfo = new CardFrame(250, 356);
    aCardTextOnly = new QAction(QString(), this);
    aCardTextOnly->setCheckable(true);
    connect(aCardTextOnly, SIGNAL(triggered()), cardInfo, SLOT(toggleCardTextOnly()));

    filterModel = new FilterTreeModel();
    databaseDisplayModel->setFilterTree(filterModel->filterTree());
    filterView = new QTreeView;
    filterView->setModel(filterModel);
    filterView->setMaximumWidth(250);
    filterView->setUniformRowHeights(true);
    filterView->setHeaderHidden(true);
    filterView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(filterModel, SIGNAL(layoutChanged()), filterView, SLOT(expandAll()));
    connect(filterView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(filterViewCustomContextMenu(const QPoint &)));
    FilterBuilder *filterBuilder = new FilterBuilder;
    filterBuilder->setMaximumWidth(250);
    connect(filterBuilder, SIGNAL(add(const CardFilter *)), filterModel, SLOT(addFilter(const CardFilter *)));

    QVBoxLayout *filter = new QVBoxLayout;
    filter->addWidget(filterBuilder, 0, Qt::AlignTop);
    filter->addWidget(filterView, 10);

    QVBoxLayout *middleFrame = new QVBoxLayout;
    middleFrame->addWidget(cardInfo, 0, Qt::AlignTop);
    middleFrame->addLayout(filter, 10);

    deckModel = new DeckListModel(this);
    connect(deckModel, SIGNAL(deckHashChanged()), this, SLOT(updateHash()));
    deckView = new QTreeView();
    deckView->setModel(deckModel);
    deckView->setUniformRowHeights(true);
    deckView->setSortingEnabled(true);
    deckView->sortByColumn(1, Qt::AscendingOrder);
#if QT_VERSION < 0x050000
    deckView->header()->setResizeMode(QHeaderView::ResizeToContents);
#else
    deckView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
#endif
    deckView->installEventFilter(&deckViewKeySignals);
    connect(deckView->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(updateCardInfoRight(const QModelIndex &, const QModelIndex &)));
    connect(&deckViewKeySignals, SIGNAL(onEnter()), this, SLOT(actIncrement()));
    connect(&deckViewKeySignals, SIGNAL(onCtrlAltEqual()), this, SLOT(actIncrement()));
    connect(&deckViewKeySignals, SIGNAL(onCtrlAltMinus()), this, SLOT(actDecrement()));
    connect(&deckViewKeySignals, SIGNAL(onRight()), this, SLOT(actIncrement()));
    connect(&deckViewKeySignals, SIGNAL(onLeft()), this, SLOT(actDecrement()));
    connect(&deckViewKeySignals, SIGNAL(onDelete()), this, SLOT(actRemoveCard()));

    nameLabel = new QLabel();
    nameEdit = new QLineEdit;
    nameLabel->setBuddy(nameEdit);
    connect(nameEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateName(const QString &)));
    commentsLabel = new QLabel();
    commentsEdit = new QTextEdit;
    commentsEdit->setMaximumHeight(70);
    commentsLabel->setBuddy(commentsEdit);
    connect(commentsEdit, SIGNAL(textChanged()), this, SLOT(updateComments()));
    hashLabel1 = new QLabel();
    hashLabel = new QLabel;

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(nameLabel, 0, 0);
    grid->addWidget(nameEdit, 0, 1);

    grid->addWidget(commentsLabel, 1, 0);
    grid->addWidget(commentsEdit, 1, 1);

    grid->addWidget(hashLabel1, 2, 0);
    grid->addWidget(hashLabel, 2, 1);

    // Update price
    aUpdatePrices = new QAction(QString(), this);
    aUpdatePrices->setIcon(QIcon(":/resources/icon_update.png"));
    connect(aUpdatePrices, SIGNAL(triggered()), this, SLOT(actUpdatePrices()));
    if (!settingsCache->getPriceTagFeature())
        aUpdatePrices->setVisible(false);
    connect(settingsCache, SIGNAL(priceTagFeatureChanged(int)), this, SLOT(setPriceTagFeatureEnabled(int)));

    QToolBar *deckToolBar = new QToolBar;
    deckToolBar->setOrientation(Qt::Vertical);
    deckToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    deckToolBar->setIconSize(QSize(24, 24));
    deckToolBar->addAction(aUpdatePrices);
    QHBoxLayout *deckToolbarLayout = new QHBoxLayout;
    deckToolbarLayout->addStretch();
    deckToolbarLayout->addWidget(deckToolBar);
    deckToolbarLayout->addStretch();

    QVBoxLayout *rightFrame = new QVBoxLayout;
    rightFrame->addLayout(grid);
    rightFrame->addWidget(deckView, 10);
    rightFrame->addLayout(deckToolbarLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftFrame, 10);
    mainLayout->addLayout(middleFrame);
    mainLayout->addLayout(rightFrame);
    setLayout(mainLayout);

    aNewDeck = new QAction(QString(), this);
    aNewDeck->setShortcuts(QKeySequence::New);
    connect(aNewDeck, SIGNAL(triggered()), this, SLOT(actNewDeck()));
    aLoadDeck = new QAction(QString(), this);
    aLoadDeck->setShortcuts(QKeySequence::Open);
    connect(aLoadDeck, SIGNAL(triggered()), this, SLOT(actLoadDeck()));
    aSaveDeck = new QAction(QString(), this);
    aSaveDeck->setShortcuts(QKeySequence::Save);
    connect(aSaveDeck, SIGNAL(triggered()), this, SLOT(actSaveDeck()));
    aSaveDeckAs = new QAction(QString(), this);
//    aSaveDeckAs->setShortcuts(QKeySequence::SaveAs);
    connect(aSaveDeckAs, SIGNAL(triggered()), this, SLOT(actSaveDeckAs()));
    aLoadDeckFromClipboard = new QAction(QString(), this);
    connect(aLoadDeckFromClipboard, SIGNAL(triggered()), this, SLOT(actLoadDeckFromClipboard()));
    aLoadDeckFromClipboard->setShortcuts(QKeySequence::Paste);
    aSaveDeckToClipboard = new QAction(QString(), this);
    connect(aSaveDeckToClipboard, SIGNAL(triggered()), this, SLOT(actSaveDeckToClipboard()));
    aSaveDeckToClipboard->setShortcuts(QKeySequence::Copy);
    aPrintDeck = new QAction(QString(), this);
    aPrintDeck->setShortcuts(QKeySequence::Print);
    connect(aPrintDeck, SIGNAL(triggered()), this, SLOT(actPrintDeck()));
    aAnalyzeDeck = new QAction(QString(), this);
    connect(aAnalyzeDeck, SIGNAL(triggered()), this, SLOT(actAnalyzeDeck()));
    aClose = new QAction(QString(), this);
    connect(aClose, SIGNAL(triggered()), this, SLOT(closeRequest()));

    aEditSets = new QAction(QString(), this);
    connect(aEditSets, SIGNAL(triggered()), this, SLOT(actEditSets()));
    aEditTokens = new QAction(QString(), this);
    connect(aEditTokens, SIGNAL(triggered()), this, SLOT(actEditTokens()));

    deckMenu = new QMenu(this);
    deckMenu->addAction(aNewDeck);
    deckMenu->addAction(aLoadDeck);
    deckMenu->addAction(aSaveDeck);
    deckMenu->addAction(aSaveDeckAs);
    deckMenu->addSeparator();
    deckMenu->addAction(aLoadDeckFromClipboard);
    deckMenu->addAction(aSaveDeckToClipboard);
    deckMenu->addSeparator();
    deckMenu->addAction(aPrintDeck);
    deckMenu->addSeparator();
    deckMenu->addAction(aAnalyzeDeck);
    deckMenu->addSeparator();
    deckMenu->addAction(aClose);
    addTabMenu(deckMenu);

    dbMenu = new QMenu(this);
    dbMenu->addAction(aEditSets);
    dbMenu->addAction(aEditTokens);
    dbMenu->addSeparator();
    dbMenu->addAction(aClearSearch);
    dbMenu->addAction(aCardTextOnly);
    addTabMenu(dbMenu);

    aAddCard = new QAction(QString(), this);
    aAddCard->setIcon(QIcon(":/resources/arrow_right_green.svg"));
    connect(aAddCard, SIGNAL(triggered()), this, SLOT(actAddCard()));
    aAddCardToSideboard = new QAction(QString(), this);
    aAddCardToSideboard->setIcon(QIcon(":/resources/add_to_sideboard.svg"));
    connect(aAddCardToSideboard, SIGNAL(triggered()), this, SLOT(actAddCardToSideboard()));
    aRemoveCard = new QAction(QString(), this);
    aRemoveCard->setIcon(QIcon(":/resources/remove_row.svg"));
    connect(aRemoveCard, SIGNAL(triggered()), this, SLOT(actRemoveCard()));
    aIncrement = new QAction(QString(), this);
    aIncrement->setIcon(QIcon(":/resources/increment.svg"));
    connect(aIncrement, SIGNAL(triggered()), this, SLOT(actIncrement()));
    aDecrement = new QAction(QString(), this);
    aDecrement->setIcon(QIcon(":/resources/decrement.svg"));
    connect(aDecrement, SIGNAL(triggered()), this, SLOT(actDecrement()));

    deckEditToolBar->addAction(aAddCard);
    deckEditToolBar->addAction(aAddCardToSideboard);
    deckEditToolBar->addAction(aRemoveCard);
    deckEditToolBar->addAction(aIncrement);
    deckEditToolBar->addAction(aDecrement);
    deckEditToolBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    
    retranslateUi();
    
    resize(950, 700);
}