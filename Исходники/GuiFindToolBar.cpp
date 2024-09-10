GuiFindToolBar::GuiFindToolBar(GuiMainWindow *p)
    : QToolBar(p),
      mainWnd(p)
{
    searchedText = new QLineEdit();
    findTextFlag = false;
    currentRow = -1;
    currentCol = -1;
    pageStartPosition = 0;
    QToolButton *b;
    currentSearchedText = "";
    addWidget(searchedText);

    searchedText->installEventFilter(this);

    b = new QToolButton(this);
    b->setText("Up");
    connect(b, SIGNAL(clicked()), this, SLOT(on_findUp()));
    addWidget(b);

    b = new QToolButton(this);
    b->setText("Down");
    connect(b, SIGNAL(clicked()), this, SLOT(on_findDown()));
    addWidget(b);

    b = new QToolButton(this);
    b->setIcon(QIcon(":/images/cog_alt_16x16.png"));
    b->setMenu(p->menuGetMenuById(MENU_FIND_OPTIONS));
    b->setPopupMode(QToolButton::InstantPopup);
    addWidget(b);

    b = new QToolButton(this);
    b->setIcon(QIcon(":/images/x_14x14.png"));
    connect(b, SIGNAL(clicked()), this, SLOT(on_findClose()));
    addWidget(b);

    setIconSize(QSize(16, 16));
    setMovable(false);
    setAutoFillBackground(true);
    adjustSize();

    searchedText->setFocus();
}