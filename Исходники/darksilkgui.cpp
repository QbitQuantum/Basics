void DarkSilkGUI::createToolBars() {
    QLabel* header = new QLabel();
    header->setMinimumSize(48, 48);
    header->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    header->setPixmap(QPixmap(":/icons/darksilk"));
    header->setMaximumSize(48, 48);
    header->setScaledContents(true);

    toolbar = new QToolBar(tr("Tabs toolbar"));
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolbar->setContextMenuPolicy(Qt::PreventContextMenu);
    toolbar->setObjectName("tabs");
    toolbar->setStyleSheet("#tabs { background-color: qradialgradient(cx: -0.8, cy: 0, fx: -0.8, fy: 0, radius: 0.6, stop: 0 #000000, stop: 1 #000000);  }");
    toolbar->addWidget(header);

    QMenu *toolbarMenu = new QMenu();
    toolbarMenu->addAction(overviewAction);
    toolbarMenu->addAction(receiveCoinsAction);
    toolbarMenu->addAction(sendCoinsAction);
    toolbarMenu->addAction(historyAction);
    toolbarMenu->addAction(addressBookAction);
    toolbarMenu->addAction(statisticsAction);
    toolbarMenu->addAction(blockAction);
    toolbarMenu->addAction(stormnodeManagerAction);

    QAction* menuAction = new QAction(QIcon(":/icons/overview"), tr("&Menu"), this);
    menuAction->setToolTip(tr("Access DarkSilk Wallet Tabs"));
    menuAction->setCheckable(false);

    QToolButton* menuToolButton = new QToolButton();
    menuToolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    menuToolButton->setMenu(toolbarMenu);
    menuToolButton->setPopupMode(QToolButton::InstantPopup);
    menuToolButton->setDefaultAction(menuAction);

    netLabel = new QLabel();
    netLabel->setObjectName("netLabel");
    netLabel->setStyleSheet("#netLabel { color: #ffffff; }");

    toolbar->addWidget(menuToolButton);
    toolbar->addWidget(makeToolBarSpacer());
    toolbar->addWidget(netLabel);
    toolbar->setOrientation(Qt::Horizontal);
    toolbar->setMovable(false);

    addToolBar(Qt::TopToolBarArea, toolbar);
}