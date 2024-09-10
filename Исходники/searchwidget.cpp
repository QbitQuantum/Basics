void SearchWidget::showEvent(QShowEvent *event)
{
    if (!event->spontaneous() && !searchEngine) {
        QVBoxLayout *vLayout = new QVBoxLayout(this);
        vLayout->setMargin(0);
        vLayout->setSpacing(0);

        searchEngine = new QHelpSearchEngine(&LocalHelpManager::helpEngine(), this);

        Utils::StyledBar *toolbar = new Utils::StyledBar(this);
        toolbar->setSingleRow(false);
        QHelpSearchQueryWidget *queryWidget = searchEngine->queryWidget();
        QLayout *tbLayout = new QVBoxLayout();
        tbLayout->setSpacing(6);
        tbLayout->setMargin(4);
        tbLayout->addWidget(queryWidget);
        toolbar->setLayout(tbLayout);

        Utils::StyledBar *toolbar2 = new Utils::StyledBar(this);
        toolbar2->setSingleRow(false);
        tbLayout = new QVBoxLayout();
        tbLayout->setSpacing(0);
        tbLayout->setMargin(0);
        tbLayout->addWidget(resultWidget = searchEngine->resultWidget());
        toolbar2->setLayout(tbLayout);

        vLayout->addWidget(toolbar);
        vLayout->addWidget(toolbar2);

        setFocusProxy(queryWidget);

        connect(queryWidget, SIGNAL(search()), this, SLOT(search()));
        connect(resultWidget, &QHelpSearchResultWidget::requestShowLink, this,
                [this](const QUrl &url) {
                    emit linkActivated(url, currentSearchTerms(), false/*newPage*/);
                });

        connect(searchEngine, SIGNAL(searchingStarted()), this,
            SLOT(searchingStarted()));
        connect(searchEngine, SIGNAL(searchingFinished(int)), this,
            SLOT(searchingFinished(int)));

        QTextBrowser* browser = resultWidget->findChild<QTextBrowser*>();
        browser->viewport()->installEventFilter(this);

        connect(searchEngine, SIGNAL(indexingStarted()), this,
            SLOT(indexingStarted()));
        connect(searchEngine, SIGNAL(indexingFinished()), this,
            SLOT(indexingFinished()));

        QMetaObject::invokeMethod(&LocalHelpManager::helpEngine(), "setupFinished",
            Qt::QueuedConnection);
    }