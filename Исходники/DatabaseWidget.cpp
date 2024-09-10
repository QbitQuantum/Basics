DatabaseWidget::DatabaseWidget(Database* db, QWidget* parent)
    : QStackedWidget(parent)
    , m_db(db)
    , m_searchUi(new Ui::SearchWidget())
    , m_searchWidget(new QWidget())
    , m_newGroup(Q_NULLPTR)
    , m_newEntry(Q_NULLPTR)
    , m_newParent(Q_NULLPTR)
{
    m_searchUi->setupUi(m_searchWidget);

    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);

    m_mainWidget = new QWidget(this);
    QLayout* layout = new QHBoxLayout(m_mainWidget);
    m_splitter = new QSplitter(m_mainWidget);
    m_splitter->setChildrenCollapsible(false);

    QWidget* rightHandSideWidget = new QWidget(m_splitter);
    m_searchWidget->setParent(rightHandSideWidget);

    m_groupView = new GroupView(db, m_splitter);
    m_groupView->setObjectName("groupView");
    m_groupView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_groupView, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(emitGroupContextMenuRequested(QPoint)));

    m_entryView = new EntryView(rightHandSideWidget);
    m_entryView->setObjectName("entryView");
    m_entryView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_entryView->setGroup(db->rootGroup());
    connect(m_entryView, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(emitEntryContextMenuRequested(QPoint)));

    QAction* closeAction = new QAction(m_searchWidget);
    QIcon closeIcon = filePath()->icon("actions", "dialog-close");
    closeAction->setIcon(closeIcon);
    m_searchUi->closeSearchButton->setDefaultAction(closeAction);
    m_searchUi->closeSearchButton->setShortcut(Qt::Key_Escape);
    m_searchWidget->hide();
    m_searchUi->caseSensitiveCheckBox->setVisible(false);

    QVBoxLayout* vLayout = new QVBoxLayout(rightHandSideWidget);
    vLayout->setMargin(0);
    vLayout->addWidget(m_searchWidget);
    vLayout->addWidget(m_entryView);

    rightHandSideWidget->setLayout(vLayout);

    setTabOrder(m_searchUi->searchRootRadioButton, m_entryView);
    setTabOrder(m_entryView, m_groupView);
    setTabOrder(m_groupView, m_searchWidget);

    m_splitter->addWidget(m_groupView);
    m_splitter->addWidget(rightHandSideWidget);

    m_splitter->setStretchFactor(0, 30);
    m_splitter->setStretchFactor(1, 70);

    layout->addWidget(m_splitter);
    m_mainWidget->setLayout(layout);

    m_editEntryWidget = new EditEntryWidget();
    m_editEntryWidget->setObjectName("editEntryWidget");
    m_historyEditEntryWidget = new EditEntryWidget();
    m_editGroupWidget = new EditGroupWidget();
    m_editGroupWidget->setObjectName("editGroupWidget");
    m_changeMasterKeyWidget = new ChangeMasterKeyWidget();
    m_changeMasterKeyWidget->headlineLabel()->setText(tr("Change master key"));
    QFont headlineLabelFont = m_changeMasterKeyWidget->headlineLabel()->font();
    headlineLabelFont.setBold(true);
    headlineLabelFont.setPointSize(headlineLabelFont.pointSize() + 2);
    m_changeMasterKeyWidget->headlineLabel()->setFont(headlineLabelFont);
    m_databaseSettingsWidget = new DatabaseSettingsWidget();
    m_databaseSettingsWidget->setObjectName("databaseSettingsWidget");
    m_databaseOpenWidget = new DatabaseOpenWidget();
    m_databaseOpenWidget->setObjectName("databaseOpenWidget");
    m_keepass1OpenWidget = new KeePass1OpenWidget();
    m_keepass1OpenWidget->setObjectName("keepass1OpenWidget");
    m_unlockDatabaseWidget = new UnlockDatabaseWidget();
    m_unlockDatabaseWidget->setObjectName("unlockDatabaseWidget");
    addWidget(m_mainWidget);
    addWidget(m_editEntryWidget);
    addWidget(m_editGroupWidget);
    addWidget(m_changeMasterKeyWidget);
    addWidget(m_databaseSettingsWidget);
    addWidget(m_historyEditEntryWidget);
    addWidget(m_databaseOpenWidget);
    addWidget(m_keepass1OpenWidget);
    addWidget(m_unlockDatabaseWidget);

    connect(m_splitter, SIGNAL(splitterMoved(int,int)), SIGNAL(splitterSizesChanged()));
    connect(m_entryView->header(), SIGNAL(sectionResized(int,int,int)), SIGNAL(entryColumnSizesChanged()));
    connect(m_groupView, SIGNAL(groupChanged(Group*)), this, SLOT(clearLastGroup(Group*)));
    connect(m_groupView, SIGNAL(groupChanged(Group*)), SIGNAL(groupChanged()));
    connect(m_groupView, SIGNAL(groupChanged(Group*)), m_entryView, SLOT(setGroup(Group*)));
    connect(m_entryView, SIGNAL(entryActivated(Entry*, EntryModel::ModelColumn)),
            SLOT(entryActivationSignalReceived(Entry*, EntryModel::ModelColumn)));
    connect(m_entryView, SIGNAL(entrySelectionChanged()), SIGNAL(entrySelectionChanged()));
    connect(m_editEntryWidget, SIGNAL(editFinished(bool)), SLOT(switchToView(bool)));
    connect(m_editEntryWidget, SIGNAL(historyEntryActivated(Entry*)), SLOT(switchToHistoryView(Entry*)));
    connect(m_historyEditEntryWidget, SIGNAL(editFinished(bool)), SLOT(switchBackToEntryEdit()));
    connect(m_editGroupWidget, SIGNAL(editFinished(bool)), SLOT(switchToView(bool)));
    connect(m_changeMasterKeyWidget, SIGNAL(editFinished(bool)), SLOT(updateMasterKey(bool)));
    connect(m_databaseSettingsWidget, SIGNAL(editFinished(bool)), SLOT(switchToView(bool)));
    connect(m_databaseOpenWidget, SIGNAL(editFinished(bool)), SLOT(openDatabase(bool)));
    connect(m_keepass1OpenWidget, SIGNAL(editFinished(bool)), SLOT(openDatabase(bool)));
    connect(m_unlockDatabaseWidget, SIGNAL(editFinished(bool)), SLOT(unlockDatabase(bool)));
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(emitCurrentModeChanged()));
    connect(m_searchUi->searchEdit, SIGNAL(textChanged(QString)), this, SLOT(startSearchTimer()));
    connect(m_searchUi->caseSensitiveCheckBox, SIGNAL(toggled(bool)), this, SLOT(startSearch()));
    connect(m_searchUi->searchCurrentRadioButton, SIGNAL(toggled(bool)), this, SLOT(startSearch()));
    connect(m_searchUi->searchRootRadioButton, SIGNAL(toggled(bool)), this, SLOT(startSearch()));
    connect(m_searchUi->searchEdit, SIGNAL(returnPressed()), m_entryView, SLOT(setFocus()));
    connect(m_searchTimer, SIGNAL(timeout()), this, SLOT(search()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeSearch()));

    setCurrentWidget(m_mainWidget);
}