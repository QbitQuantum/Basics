void WicdApplet::init()
{
    m_theme->resize(contentsRect().size());
    
    Plasma::ToolTipManager::self()->registerWidget(this);

    //load dataengine
    Plasma::DataEngine *engine = dataEngine("wicd");
    if (!engine->isValid()) {
        setFailedToLaunch(true, i18n("Unable to load the Wicd data engine."));
        return;
    }
    
    setupActions();
    
    //build the popup dialog
    QGraphicsWidget *appletDialog = new QGraphicsWidget(this);
    m_dialoglayout = new QGraphicsLinearLayout(Qt::Vertical);
    
    //Network list
    m_scrollWidget = new Plasma::ScrollWidget(appletDialog);
    m_scrollWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollWidget->setFlag(QGraphicsItem::ItemClipsChildrenToShape);
    m_scrollWidget->setMaximumHeight(400);

    m_networkView = new NetworkView(m_scrollWidget);
    m_scrollWidget->setWidget(m_networkView);

    m_busyWidget = new Plasma::BusyWidget(m_scrollWidget);
    m_busyWidget->hide();

    m_dialoglayout->addItem(m_scrollWidget);
    
    //Separator
    m_dialoglayout->addItem(new Plasma::Separator(appletDialog));
    
    //Bottom bar
    QGraphicsLinearLayout* bottombarLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    
    m_messageBox = new Plasma::Label(appletDialog);
    m_messageBox->setWordWrap(false);
    bottombarLayout->addItem(m_messageBox);
    
    bottombarLayout->addStretch();
    
    m_abortButton = new Plasma::ToolButton(appletDialog);
    m_abortButton->setIcon(KIcon("dialog-cancel"));
    m_abortButton->nativeWidget()->setToolTip(i18n("Abort"));
    connect(m_abortButton, SIGNAL(clicked()), this, SLOT(cancelConnect()));
    bottombarLayout->addItem(m_abortButton);
    
    Plasma::ToolButton *reloadButton = new Plasma::ToolButton(appletDialog);
    reloadButton->nativeWidget()->setToolTip(i18n("Reload"));
    reloadButton->setAction(action("reload"));
    bottombarLayout->addItem(reloadButton);
    
    m_dialoglayout->addItem(bottombarLayout);
    
    appletDialog->setLayout(m_dialoglayout);
    setGraphicsWidget(appletDialog);

    setHasConfigurationInterface(true);
    
    // read config
    configChanged();

    connect(Plasma::Theme::defaultTheme(), SIGNAL(themeChanged()), SLOT(updateColors()));


    //prevent notification on startup
    m_status.State = 10;
    m_isScanning = false;
    //connect dataengine
    m_wicdService = engine->serviceForSource("");
    engine->connectSource("status", this);
    engine->connectSource("daemon", this);
}