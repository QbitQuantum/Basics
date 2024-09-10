QtMarbleConfigDialog::QtMarbleConfigDialog( MarbleWidget *marbleWidget, QWidget *parent )
    : QDialog( parent ),
      d( new QtMarbleConfigDialogPrivate( marbleWidget ) )
{
    QTabWidget *tabWidget = new QTabWidget( this );
    QDialogButtonBox *buttons = 
    new QDialogButtonBox( QDialogButtonBox::Ok
                        | QDialogButtonBox::Apply
                        | QDialogButtonBox::Cancel,
                          Qt::Horizontal,
                          this );

    // Connect the signals of the ButtonBox
    // to the corresponding slots of the dialog.
    connect( buttons, SIGNAL(accepted()), this, SLOT(accept()) ); // Ok
    connect( buttons, SIGNAL(rejected()), this, SLOT(reject()) ); // Cancel
    connect( buttons->button( QDialogButtonBox::Apply ),SIGNAL(clicked()),
             this, SLOT(writeSettings()) );                         // Apply
    // If the dialog is accepted. Save the settings.
    connect( this, SIGNAL(accepted()), this, SLOT(writeSettings()) );

    // view page
    QWidget *w_viewSettings = new QWidget( this );

    d->ui_viewSettings.setupUi( w_viewSettings );
    tabWidget->addTab( w_viewSettings, tr( "View" ) );

    // It's experimental -- so we remove it for now.
    // FIXME: Delete the following  line once OpenGL support is officially supported.
    d->ui_viewSettings.kcfg_graphicsSystem->removeItem( Marble::OpenGLGraphics );

    QString nativeString ( tr("Native") );

    #ifdef Q_WS_X11
    nativeString = tr( "Native (X11)" );
    #endif
    #ifdef Q_WS_MAC
    nativeString = tr( "Native (Mac OS X Core Graphics)" );
    #endif

    d->ui_viewSettings.kcfg_graphicsSystem->setItemText( Marble::NativeGraphics, nativeString );

    // navigation page
    QWidget *w_navigationSettings = new QWidget( this );

    d->ui_navigationSettings.setupUi( w_navigationSettings );
    tabWidget->addTab( w_navigationSettings, tr( "Navigation" ) );

    // cache page
    QWidget *w_cacheSettings = new QWidget( this );

    d->ui_cacheSettings.setupUi( w_cacheSettings );
    tabWidget->addTab( w_cacheSettings, tr( "Cache and Proxy" ) );
    // Forwarding clear button signals
    connect( d->ui_cacheSettings.button_clearVolatileCache, SIGNAL(clicked()), SIGNAL(clearVolatileCacheClicked()) );
    connect( d->ui_cacheSettings.button_clearPersistentCache, SIGNAL(clicked()), SIGNAL(clearPersistentCacheClicked()) );

    // time page
    QWidget *w_timeSettings = new QWidget( this );
    d->ui_timeSettings.setupUi( w_timeSettings );
    tabWidget->addTab( w_timeSettings, tr( "Date and Time" ) );

    // routing page
    QWidget *w_routingSettings = new RoutingProfilesWidget( marbleWidget->model() );
    tabWidget->addTab( w_routingSettings, tr( "Routing" ) );

    // plugin page
    d->m_pluginModel.setRenderPlugins( d->m_marbleWidget->renderPlugins() );
    d->w_pluginSettings = new MarblePluginSettingsWidget( this );
    d->w_pluginSettings->setModel( &d->m_pluginModel );
    d->w_pluginSettings->setObjectName( "plugin_page" );
    tabWidget->addTab( d->w_pluginSettings, tr( "Plugins" ) );

    // Setting the icons for the plugin dialog.
    d->w_pluginSettings->setAboutIcon( QIcon(":/icons/help-about.png") );
    d->w_pluginSettings->setConfigIcon(  QIcon(":/icons/settings-configure.png") );

    connect( this, SIGNAL(rejected()), &d->m_pluginModel, SLOT(retrievePluginState()) );
    connect( this, SIGNAL(accepted()), &d->m_pluginModel, SLOT(applyPluginState()) );
    
    QWidget *w_cloudSyncSettings = new QWidget( this );
    d->ui_cloudSyncSettings.setupUi( w_cloudSyncSettings );
    tabWidget->addTab( w_cloudSyncSettings, tr( "Synchronization" ) );

    // Layout
    QVBoxLayout *layout = new QVBoxLayout( this );
    layout->addWidget( tabWidget );
    layout->addWidget( buttons );
    
    this->setLayout( layout );

    // When the settings have been changed, write to disk.
    connect( this, SIGNAL(settingsChanged()), this, SLOT(syncSettings()) );

    initializeCustomTimezone();
}