QLayout * PageRoomsList::bodyLayoutDefinition()
{
    // TODO move stylesheet stuff into css/qt.css

    QVBoxLayout * pageLayout = new QVBoxLayout();
    pageLayout->setSpacing(0);

    QGridLayout * topLayout = new QGridLayout();
    topLayout->setSpacing(0);
    pageLayout->addLayout(topLayout, 0);

    // State button

    QPushButton * btnState = new QPushButton(tr("Room state"));
    btnState->setStyleSheet("QPushButton { background-color: #F6CB1C; border-color: #F6CB1C; color: #130F2A; padding: 1px 3px 3px 3px; margin: 0px; border-bottom: none; border-radius: 0px; border-top-left-radius: 10px; } QPushButton:hover { background-color: #FFEB3C; border-color: #F6CB1C; color: #000000 } QPushButton:pressed { background-color: #FFEB3C; border-color: #F6CB1C; color: #000000; }");
    btnState->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    // State menu

    QMenu * stateMenu = new QMenu(btnState);
    showGamesInLobby = new QAction(QAction::tr("Show games in lobby"), stateMenu);
    showGamesInLobby->setCheckable(true);
    showGamesInLobby->setChecked(true);
    showGamesInProgress = new QAction(QAction::tr("Show games in-progress"), stateMenu);
    showGamesInProgress->setCheckable(true);
    showGamesInProgress->setChecked(true);
    showPassword = new QAction(QAction::tr("Show password protected"), stateMenu);
    showPassword->setCheckable(true);
    showPassword->setChecked(true);
    showJoinRestricted = new QAction(QAction::tr("Show join restricted"), stateMenu);
    showJoinRestricted->setCheckable(true);
    showJoinRestricted->setChecked(true);
    stateMenu->addAction(showGamesInLobby);
    stateMenu->addAction(showGamesInProgress);
    stateMenu->addAction(showPassword);
    stateMenu->addAction(showJoinRestricted);
    btnState->setMenu(stateMenu);

    // Help/prompt message at top
    QLabel * lblDesc = new QLabel(tr("Search for a room:"));
    lblDesc->setObjectName("lblDesc");
    lblDesc->setStyleSheet("#lblDesc { color: #130F2A; background: #F6CB1C; border: solid 4px #F6CB1C; padding: 5px 10px 3px 6px;}");
    lblDesc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lblDesc->setFixedHeight(24);
    lblDesc->setMinimumWidth(0);

    // Search text box
    QWidget * searchContainer = new QWidget();
    searchContainer->setFixedHeight(24);
    searchContainer->setObjectName("searchContainer");
    searchContainer->setStyleSheet("#searchContainer { background: #F6CB1C; border-top-right-radius: 10px; padding: 3px; }");
    searchContainer->setFixedWidth(200);
    searchText = new LineEditCursor(searchContainer);
    searchText->setFixedWidth(200);
    searchText->setMaxLength(60);
    searchText->setFixedHeight(22);
    searchText->setStyleSheet("LineEditCursor { border-width: 0px; border-radius: 6px; margin-top: 3px; margin-right: 3px; padding-left: 4px; padding-bottom: 2px; background-color: rgb(23, 11, 54); } LineEditCursor:hover, LineEditCursor:focus { background-color: rgb(13, 5, 68); }");

    // Corner widget
    QLabel * corner = new QLabel();
    corner->setPixmap(QPixmap(QString::fromUtf8(":/res/inverse-corner-bl.png")));
    corner->setFixedSize(10, 10);

    const QIcon& lp = QIcon(":/res/new.png");
    //QSize sz = lp.actualSize(QSize(65535, 65535));
    BtnCreate = new QPushButton();
    BtnCreate->setText(tr("Create room"));
    BtnCreate->setIcon(lp);
    BtnCreate->setStyleSheet("padding: 4px 8px; margin-bottom: 6px;");

    BtnJoin = new QPushButton(tr("Join room"));
    BtnJoin->setStyleSheet("padding: 4px 8px; margin-bottom: 6px; margin-left: 6px;");
    BtnJoin->setEnabled(false);

    // Add widgets to top layout
    topLayout->addWidget(btnState, 1, 0);
    topLayout->addWidget(lblDesc, 1, 1);
    topLayout->addWidget(searchContainer, 1, 2);
    topLayout->addWidget(corner, 1, 3, Qt::AlignBottom);
    topLayout->addWidget(BtnCreate, 0, 5, 2, 1);
    topLayout->addWidget(BtnJoin, 0, 6, 2, 1);

    // Top layout stretch
    topLayout->setRowStretch(0, 1);
    topLayout->setRowStretch(1, 0);
    topLayout->setColumnStretch(4, 1);

    // Rooms list and chat with splitter
    m_splitter = new QSplitter();
    m_splitter->setChildrenCollapsible(false);
    pageLayout->addWidget(m_splitter, 100);

    // Room list
    QWidget * roomsListWidget = new QWidget(this);
    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(roomsListWidget);

    QVBoxLayout * roomsLayout = new QVBoxLayout(roomsListWidget);
    roomsLayout->setMargin(0);

    roomsList = new RoomTableView(this);
    roomsList->setSelectionBehavior(QAbstractItemView::SelectRows);
    roomsList->verticalHeader()->setVisible(false);
    roomsList->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    roomsList->setAlternatingRowColors(true);
    roomsList->setShowGrid(false);
    roomsList->setSelectionMode(QAbstractItemView::SingleSelection);
    roomsList->setStyleSheet("QTableView { border-top-left-radius: 0px; }");
    roomsList->setFocusPolicy(Qt::NoFocus);
    roomsLayout->addWidget(roomsList, 200);

    // Lobby chat

    chatWidget = new HWChatWidget(this, false);
    m_splitter->addWidget(chatWidget);

    return pageLayout;
}