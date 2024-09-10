CoverFoundDialog::CoverFoundDialog( const CoverFetchUnit::Ptr unit,
                                    const CoverFetch::Metadata &data,
                                    QWidget *parent )
    : KDialog( parent )
    , m_album( unit->album() )
    , m_isSorted( false )
    , m_sortEnabled( false )
    , m_unit( unit )
    , m_queryPage( 0 )
{
    DEBUG_BLOCK
    setButtons( KDialog::Ok | KDialog::Cancel |
                KDialog::User1 ); // User1: clear icon view

    setButtonGuiItem( KDialog::User1, KStandardGuiItem::clear() );
    connect( button( KDialog::User1 ), SIGNAL(clicked()), SLOT(clearView()) );

    m_save = button( KDialog::Ok );

    QSplitter *splitter = new QSplitter( this );
    m_sideBar = new CoverFoundSideBar( m_album, splitter );

    KVBox *vbox = new KVBox( splitter );
    vbox->setSpacing( 4 );

    KHBox *breadcrumbBox = new KHBox( vbox );
    QLabel *breadcrumbLabel = new QLabel( i18n( "Finding cover for" ), breadcrumbBox );
    AlbumBreadcrumbWidget *breadcrumb = new AlbumBreadcrumbWidget( m_album, breadcrumbBox );

    QFont breadcrumbLabelFont;
    breadcrumbLabelFont.setBold( true );
    breadcrumbLabel->setFont( breadcrumbLabelFont );
    breadcrumbLabel->setIndent( 4 );

    connect( breadcrumb, SIGNAL(artistClicked(const QString&)), SLOT(addToCustomSearch(const QString&)) );
    connect( breadcrumb, SIGNAL(albumClicked(const QString&)), SLOT(addToCustomSearch(const QString&)) );

    KHBox *searchBox = new KHBox( vbox );
    vbox->setSpacing( 4 );

    QStringList completionNames;
    QString firstRunQuery( m_album->name() );
    completionNames << firstRunQuery;
    if( m_album->hasAlbumArtist() )
    {
        const QString &name = m_album->albumArtist()->name();
        completionNames << name;
        firstRunQuery += ' ' + name;
    }
    m_query = firstRunQuery;
    m_album->setSuppressImageAutoFetch( true );

    m_search = new KComboBox( searchBox );
    m_search->setEditable( true ); // creates a KLineEdit for the combobox
    m_search->setTrapReturnKey( true );
    m_search->setInsertPolicy( QComboBox::NoInsert ); // insertion is handled by us
    m_search->setCompletionMode( KGlobalSettings::CompletionPopup );
    m_search->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Fixed );
    qobject_cast<KLineEdit*>( m_search->lineEdit() )->setClickMessage( i18n( "Enter Custom Search" ) );
    m_search->completionObject()->setOrder( KCompletion::Insertion );
    m_search->completionObject()->setIgnoreCase( true );
    m_search->completionObject()->setItems( completionNames );
    m_search->insertItem( 0, KStandardGuiItem::find().icon(), QString() );
    m_search->insertSeparator( 1 );
    m_search->insertItem( 2, KIcon("filename-album-amarok"), m_album->name() );
    if( m_album->hasAlbumArtist() )
        m_search->insertItem( 3, KIcon("filename-artist-amarok"), m_album->albumArtist()->name() );

    m_searchButton = new KPushButton( KStandardGuiItem::find(), searchBox );
    KPushButton *sourceButton = new KPushButton( KStandardGuiItem::configure(), searchBox );
    updateSearchButton( firstRunQuery );

    QMenu *sourceMenu = new QMenu( sourceButton );
    QAction *lastFmAct = new QAction( i18n( "Last.fm" ), sourceMenu );
    QAction *googleAct = new QAction( i18n( "Google" ), sourceMenu );
    QAction *yahooAct = new QAction( i18n( "Yahoo!" ), sourceMenu );
    QAction *discogsAct = new QAction( i18n( "Discogs" ), sourceMenu );
    lastFmAct->setCheckable( true );
    googleAct->setCheckable( true );
    yahooAct->setCheckable( true );
    discogsAct->setCheckable( true );
    connect( lastFmAct, SIGNAL(triggered()), this, SLOT(selectLastFm()) );
    connect( googleAct, SIGNAL(triggered()), this, SLOT(selectGoogle()) );
    connect( yahooAct, SIGNAL(triggered()), this, SLOT(selectYahoo()) );
    connect( discogsAct, SIGNAL(triggered()), this, SLOT(selectDiscogs()) );

    m_sortAction = new QAction( i18n( "Sort by size" ), sourceMenu );
    m_sortAction->setCheckable( true );
    connect( m_sortAction, SIGNAL(triggered(bool)), this, SLOT(sortingTriggered(bool)) );

    QActionGroup *ag = new QActionGroup( sourceButton );
    ag->addAction( lastFmAct );
    ag->addAction( googleAct );
    ag->addAction( yahooAct );
    ag->addAction( discogsAct );
    sourceMenu->addActions( ag->actions() );
    sourceMenu->addSeparator();
    sourceMenu->addAction( m_sortAction );
    sourceButton->setMenu( sourceMenu );

    connect( m_search, SIGNAL(returnPressed(const QString&)), SLOT(insertComboText(const QString&)) );
    connect( m_search, SIGNAL(returnPressed(const QString&)), SLOT(processQuery(const QString&)) );
    connect( m_search, SIGNAL(returnPressed(const QString&)), SLOT(updateSearchButton(const QString&)) );
    connect( m_search, SIGNAL(editTextChanged(const QString&)), SLOT(updateSearchButton(const QString&)) );
    connect( m_search->lineEdit(), SIGNAL(clearButtonClicked()), SLOT(clearQueryButtonClicked()));
    connect( m_searchButton, SIGNAL(clicked()), SLOT(processQuery()) );

    m_view = new KListWidget( vbox );
    m_view->setAcceptDrops( false );
    m_view->setContextMenuPolicy( Qt::CustomContextMenu );
    m_view->setDragDropMode( QAbstractItemView::NoDragDrop );
    m_view->setDragEnabled( false );
    m_view->setDropIndicatorShown( false );
    m_view->setMovement( QListView::Static );
    m_view->setGridSize( QSize( 140, 150 ) );
    m_view->setIconSize( QSize( 120, 120 ) );
    m_view->setSpacing( 4 );
    m_view->setViewMode( QListView::IconMode );
    m_view->setResizeMode( QListView::Adjust );

    connect( m_view, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
             this,   SLOT(currentItemChanged(QListWidgetItem*, QListWidgetItem*)) );
    connect( m_view, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
             this,   SLOT(itemDoubleClicked(QListWidgetItem*)) );
    connect( m_view, SIGNAL(customContextMenuRequested(const QPoint&)),
             this,   SLOT(itemMenuRequested(const QPoint&)) );

    splitter->addWidget( m_sideBar );
    splitter->addWidget( vbox );
    setMainWidget( splitter );

    const KConfigGroup config = Amarok::config( "Cover Fetcher" );
    const QString source = config.readEntry( "Interactive Image Source", "LastFm" );
    m_sortEnabled = config.readEntry( "Sort by Size", false );
    m_sortAction->setChecked( m_sortEnabled );
    m_isSorted = m_sortEnabled;
    restoreDialogSize( config ); // call this after setMainWidget()

    if( source == "LastFm" )
        lastFmAct->setChecked( true );
    else if( source == "Yahoo" )
        yahooAct->setChecked( true );
    else if( source == "Discogs" )
        discogsAct->setChecked( true );
    else
        googleAct->setChecked( true );

    typedef CoverFetchArtPayload CFAP;
    const CFAP *payload = dynamic_cast< const CFAP* >( unit->payload() );
    if( !m_album->hasImage() )
        m_sideBar->setPixmap( QPixmap::fromImage( m_album->image(190 ) ) );
    else if( payload )
        add( m_album->image(), data, payload->imageSize() );
    else
        add( m_album->image(), data );
    m_view->setCurrentItem( m_view->item( 0 ) );
    updateGui();
    
    connect( The::networkAccessManager(), SIGNAL( requestRedirected( QNetworkReply*, QNetworkReply* ) ),
             this, SLOT( fetchRequestRedirected( QNetworkReply*, QNetworkReply* ) ) );
}