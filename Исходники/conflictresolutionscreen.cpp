ConflictResolutionScreen::ConflictResolutionScreen()
{
    setStyleSheet( "background-color: white;" );

    new OneclickinstallerAdaptor( this );
    QDBusConnection connection = QDBusConnection::systemBus();
    if ( !connection.isConnected() ) {
        qFatal( "Cannot connect to the D-Bus system bus" );
        exit( 1 );
    }
    connection.registerObject( "/OCI", this );
    if ( !connection.registerService("org.opensuse.oneclickinstaller") ) {
        qFatal( qPrintable( QDBusConnection::systemBus().lastError().message() ) );
        exit( 1 );
    }

    m_mainLayout = new QVBoxLayout;

    //QObject::connect( m_ociHelper, SIGNAL( displayProblemAndSolutions( QString, QString ) ), this, SLOT( problemSolutionWidget( QString, QString ) ) );
    QDBusConnection sysBus = QDBusConnection::systemBus();
    if ( !sysBus.isConnected() ) {
        qFatal( "Cannot connect to the D-Bus system bus" );
        exit( 1 );
    }
    sysBus.connect( QString(), QString(), "org.opensuse.OCIHelper", "displayProblemAndSolutions", this, SLOT( problemSolutionWidget( QString, QStringList ) ) );

    setLayout ( m_mainLayout );
}