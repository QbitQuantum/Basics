DirBrowser::DirBrowser(QWidget *parent, Playlist *pl)
    : QWidget(parent), ui(new Ui::DirBrowser), m_pl(pl), m_insertactive(false)
{
    QKeySequence seq;
    QShortcut *sc;

    ui->setupUi(this);
    ui->searchFrame->hide();
    ui->tabs->setTabsClosable(true);

    QToolButton *plusbut = new QToolButton(this);
    QString icon_path = Helper::getIconPath();
    QIcon icon = QIcon(icon_path + "/addtab.png");
    plusbut->setIcon(icon);
    ui->tabs->setCornerWidget(plusbut, Qt::TopRightCorner);
    plusbut->setCursor(Qt::ArrowCursor);
    plusbut->setAutoRaise(true);
    plusbut->setToolTip(tr("Add tab"));
    connect(plusbut, SIGNAL(clicked()), this, SLOT(addTab()));
    seq = QKeySequence("Ctrl+t");
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL (activated()), this, SLOT(addTab()));
    seq = QKeySequence("Ctrl+w");
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL (activated()), this, SLOT(closeCurrentTab()));

    connect(ui->tabs, SIGNAL(currentChanged(int)), 
            this, SLOT(onCurrentTabChanged(int)));
    connect(ui->tabs, SIGNAL(tabCloseRequested(int)), 
            this, SLOT(closeTab(int)));
            
    icon = QIcon(icon_path + "/cross.png");
    ui->closeSearchTB->setIcon(icon);
    connect(ui->closeSearchTB, SIGNAL(clicked()), 
            this, SLOT(closeSearchPanel()));
    seq = QKeySequence("Ctrl+f");
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL (activated()), this, SLOT(openSearchPanel()));
    seq = QKeySequence("/");
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL (activated()), this, SLOT(openSearchPanel()));
    seq = QKeySequence("Esc");
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL (activated()), this, SLOT(closeSearchPanel()));

    seq = QKeySequence(Qt::Key_F3);
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL(activated()), this, SLOT(searchNext()));
    seq = QKeySequence(Qt::SHIFT + Qt::Key_F3);
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL(activated()), this, SLOT(searchPrev()));
    connect(ui->searchCMB->lineEdit(), SIGNAL(textChanged(const QString&)), 
            this, SLOT(onSearchTextChanged(const QString&)));
    connect(ui->nextTB, SIGNAL(clicked()), this, SLOT(searchNext()));
    connect(ui->prevTB, SIGNAL(clicked()), this, SLOT(searchPrev()));
    connect(ui->searchCMB->lineEdit(), SIGNAL(returnPressed()),
            this, SLOT(returnPressedInSearch()));
    seq = QKeySequence("Ctrl+s");
    sc = new QShortcut(seq, this);
    connect(sc, SIGNAL(activated()), this, SLOT(toggleSearchKind()));
    connect(ui->serverSearchCB, SIGNAL(stateChanged(int)), 
            this, SLOT(onSearchKindChanged(int)));
    connect(ui->execSearchPB, SIGNAL(clicked()), this, SLOT(serverSearch()));

    onSearchKindChanged(int(ui->serverSearchCB->checkState()));
    ui->execSearchPB->hide();
    setPlaylist(pl);
}