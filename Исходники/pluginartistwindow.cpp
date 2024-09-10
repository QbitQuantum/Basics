void PluginArtistWindow::loadBaseUi() {
    setWindowTitle(tr("Artist"));
    setCentralWidget(new QWidget);
        
    m_view->setModel(m_model);
    m_view->setItemDelegate(new NavDelegate(m_view));
    
    m_avatar->setFixedSize(100, 100);
    m_avatar->setFallbackSource(QUrl::fromLocalFile("/usr/share/icons/hicolor/96x96/hildon/general_default_avatar.png"));
    
    m_titleLabel->setWordWrap(true);
        
    QWidget *scrollWidget = new QWidget(m_scrollArea);
    QVBoxLayout *vbox = new QVBoxLayout(scrollWidget);
    vbox->addWidget(m_avatar, Qt::AlignLeft);
    vbox->addWidget(m_titleLabel, Qt::AlignLeft | Qt::AlignTop);
    vbox->addWidget(m_descriptionLabel, Qt::AlignTop);
    vbox->setStretch(2, 1);
    vbox->setContentsMargins(0, 0, 0, 0);
    m_scrollArea->setWidget(scrollWidget);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFixedWidth(410);
    
    m_layout = new QHBoxLayout(centralWidget());
    m_layout->addWidget(m_scrollArea);
    m_layout->addWidget(m_view);
    m_layout->setStretch(1, 1);
    m_layout->setContentsMargins(0, 0, 0, 0);
    
    menuBar()->addAction(m_nowPlayingAction);
    
    connect(m_view, SIGNAL(activated(QModelIndex)), this, SLOT(showWindow(QModelIndex)));
    connect(m_descriptionLabel, SIGNAL(anchorClicked(QUrl)), this, SLOT(showResource(QUrl)));
}