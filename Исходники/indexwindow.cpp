IndexWindow::IndexWindow()
    : m_searchLineEdit(0)
    , m_indexWidget(0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_searchLineEdit = new Utils::FilterLineEdit();
    m_searchLineEdit->setPlaceholderText(QString());
    setFocusProxy(m_searchLineEdit);
    connect(m_searchLineEdit, SIGNAL(textChanged(QString)), this,
        SLOT(filterIndices(QString)));
    m_searchLineEdit->installEventFilter(this);

    QLabel *l = new QLabel(tr("&Look for:"));
    l->setBuddy(m_searchLineEdit);
    layout->addWidget(l);
    layout->setMargin(0);
    layout->setSpacing(0);

    Utils::StyledBar *toolbar = new Utils::StyledBar(this);
    toolbar->setSingleRow(false);
    QLayout *tbLayout = new QHBoxLayout();
    tbLayout->setSpacing(6);
    tbLayout->setMargin(4);
    tbLayout->addWidget(l);
    tbLayout->addWidget(m_searchLineEdit);
    toolbar->setLayout(tbLayout);
    layout->addWidget(toolbar);

    QHelpEngine *engine = &LocalHelpManager::helpEngine();
    m_indexWidget = engine->indexWidget();
    m_indexWidget->installEventFilter(this);
    connect(engine->indexModel(), SIGNAL(indexCreationStarted()), this,
        SLOT(disableSearchLineEdit()));
    connect(engine->indexModel(), SIGNAL(indexCreated()), this,
        SLOT(enableSearchLineEdit()));
    connect(m_indexWidget, SIGNAL(linkActivated(QUrl,QString)), this,
        SIGNAL(linkActivated(QUrl)));
    connect(m_indexWidget, SIGNAL(linksActivated(QMap<QString,QUrl>,QString)),
        this, SIGNAL(linksActivated(QMap<QString,QUrl>,QString)));
    connect(m_searchLineEdit, SIGNAL(returnPressed()), m_indexWidget,
        SLOT(activateCurrentItem()));
    m_indexWidget->setFrameStyle(QFrame::NoFrame);
    layout->addWidget(m_indexWidget);

    m_indexWidget->viewport()->installEventFilter(this);
}