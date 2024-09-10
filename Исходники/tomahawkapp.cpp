void
TomahawkApp::init()
{
    if ( arguments().contains( "--help" ) || arguments().contains( "-h" ) )
    {
        printHelp();
        ::exit( 0 );
    }

    qDebug() << "TomahawkApp thread:" << thread();
    Logger::setupLogfile();
    qsrand( QTime( 0, 0, 0 ).secsTo( QTime::currentTime() ) );

    tLog() << "Starting Tomahawk...";

#ifdef ENABLE_HEADLESS
    m_headless = true;
#else
    m_mainwindow = 0;
    m_headless = arguments().contains( "--headless" );
    setWindowIcon( QIcon( RESPATH "icons/tomahawk-icon-128x128.png" ) );
    setQuitOnLastWindowClosed( false );

    QFont f = APP->font();
    f.setPixelSize( HeaderLabel::defaultFontSize() );
    QFontMetrics fm( f );
    TomahawkUtils::setHeaderHeight( fm.height() + 8 );
#endif

    TomahawkSettings* s = TomahawkSettings::instance();

    tDebug( LOGINFO ) << "Setting NAM.";
    // Cause the creation of the nam, but don't need to address it directly, so prevent warning
    Q_UNUSED( TomahawkUtils::nam() );

    m_audioEngine = QWeakPointer<AudioEngine>( new AudioEngine );
    m_scanManager = QWeakPointer<ScanManager>( new ScanManager( this ) );

    // init pipeline and resolver factories
    new Pipeline( this );

#ifndef ENABLE_HEADLESS
    Pipeline::instance()->addExternalResolverFactory( boost::bind( &QtScriptResolver::factory, _1 ) );
    Pipeline::instance()->addExternalResolverFactory( boost::bind( &ScriptResolver::factory, _1 ) );

    new ActionCollection( this );
    connect( ActionCollection::instance()->getAction( "quit" ), SIGNAL( triggered() ), SLOT( quit() ), Qt::UniqueConnection );
#endif

    m_servent = QWeakPointer<Servent>( new Servent( this ) );
    connect( m_servent.data(), SIGNAL( ready() ), SLOT( initSIP() ) );

    tDebug() << "Init Database.";
    initDatabase();

    QByteArray magic = QByteArray::fromBase64( enApiSecret );
    QByteArray wand = QByteArray::fromBase64( QCoreApplication::applicationName().toLatin1() );
    int length = magic.length(), n2 = wand.length();
    for ( int i=0; i<length; i++ ) magic[i] = magic[i] ^ wand[i%n2];
    Echonest::Config::instance()->setAPIKey( magic );

#ifndef ENABLE_HEADLESS
    tDebug() << "Init Echonest Factory.";
    GeneratorFactory::registerFactory( "echonest", new EchonestFactory );
#endif
    tDebug() << "Init Database Factory.";
    GeneratorFactory::registerFactory( "database", new DatabaseFactory );

    // Register shortcut handler for this platform
#ifdef Q_WS_MAC
    m_shortcutHandler = QWeakPointer<Tomahawk::ShortcutHandler>( new MacShortcutHandler( this ) );
    Tomahawk::setShortcutHandler( static_cast<MacShortcutHandler*>( m_shortcutHandler.data() ) );

    Tomahawk::setApplicationHandler( this );
    increaseMaxFileDescriptors();
#endif

    // Connect up shortcuts
    if ( !m_shortcutHandler.isNull() )
    {
        connect( m_shortcutHandler.data(), SIGNAL( playPause() ), m_audioEngine.data(), SLOT( playPause() ) );
        connect( m_shortcutHandler.data(), SIGNAL( pause() ), m_audioEngine.data(), SLOT( pause() ) );
        connect( m_shortcutHandler.data(), SIGNAL( stop() ), m_audioEngine.data(), SLOT( stop() ) );
        connect( m_shortcutHandler.data(), SIGNAL( previous() ), m_audioEngine.data(), SLOT( previous() ) );
        connect( m_shortcutHandler.data(), SIGNAL( next() ), m_audioEngine.data(), SLOT( next() ) );
        connect( m_shortcutHandler.data(), SIGNAL( volumeUp() ), m_audioEngine.data(), SLOT( raiseVolume() ) );
        connect( m_shortcutHandler.data(), SIGNAL( volumeDown() ), m_audioEngine.data(), SLOT( lowerVolume() ) );
        connect( m_shortcutHandler.data(), SIGNAL( mute() ), m_audioEngine.data(), SLOT( mute() ) );
    }

    tDebug() << "Init InfoSystem.";
    m_infoSystem = QWeakPointer<Tomahawk::InfoSystem::InfoSystem>( new Tomahawk::InfoSystem::InfoSystem( this ) );

    Echonest::Config::instance()->setNetworkAccessManager( TomahawkUtils::nam() );
#ifndef ENABLE_HEADLESS
    EchonestGenerator::setupCatalogs();


    if ( !m_headless )
    {
        tDebug() << "Init MainWindow.";
        m_mainwindow = new TomahawkWindow();
        m_mainwindow->setWindowTitle( "Tomahawk" );
        m_mainwindow->setObjectName( "TH_Main_Window" );
        if ( !arguments().contains( "--hide" ) )
        {
            m_mainwindow->show();
        }
    }
#endif

    tDebug() << "Init Local Collection.";
    initLocalCollection();
    tDebug() << "Init Pipeline.";
    initPipeline();

#ifdef LIBATTICA_FOUND
#ifndef ENABLE_HEADLESS
    // load remote list of resolvers able to be installed
    AtticaManager::instance();
#endif
#endif

    if ( arguments().contains( "--http" ) || TomahawkSettings::instance()->value( "network/http", true ).toBool() )
    {
        initHTTP();
    }

#ifndef ENABLE_HEADLESS
    if ( !s->hasScannerPaths() )
    {
        m_mainwindow->showSettingsDialog();
    }
#endif

#ifdef LIBLASTFM_FOUND
    tDebug() << "Init Scrobbler.";
    m_scrobbler = new Scrobbler( this );
#endif

    if ( arguments().contains( "--filescan" ) )
    {
        m_scanManager.data()->runScan( true );
    }

    // Set up echonest catalog synchronizer
    Tomahawk::EchonestCatalogSynchronizer::instance();

#ifndef ENABLE_HEADLESS
    // Make sure to init GAM in the gui thread
    GlobalActionManager::instance();

    // check if our spotify playlist api server is up and running, and enable spotify playlist drops if so
    QNetworkReply* r = TomahawkUtils::nam()->get( QNetworkRequest( QUrl( SPOTIFY_PLAYLIST_API_URL "/playlist/test" ) ) );
    connect( r, SIGNAL( finished() ), this, SLOT( spotifyApiCheckFinished() ) );
#endif

#ifdef Q_WS_MAC
    // Make sure to do this after main window is inited
    Tomahawk::enableFullscreen();
#endif
}