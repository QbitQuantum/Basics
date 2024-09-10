//-----------------------------------------------------------------------------
//! Dialog to decide which route to keep (local or master version) when the timestamp is invalid
//-----------------------------------------------------------------------------
tMergeRouteDialog::tMergeRouteDialog( const tRoute& route, const bool isDeleted, QWidget* pParent )
: tDialog( tDialog::Partial, pParent ), m_result( keepAllNetwork )
{
    // we don't want to allow the user to just close this dialog, they must make a decision.
    DisableTitleCloseButton();

    setWindowTitle( tr( "Route Merge", "title" ) );

    tRoute networkRoute;
    tIUDBWpRtDB* pUDBWpRtDB = UDB::GetUDBWpRtDB();
    bool networkRouteFound = pUDBWpRtDB->FindRoute( route.GetUuid(), &networkRoute );

    QGridLayout* pLayout = new QGridLayout( this );

    QLabel* pInstructionLabel = new QLabel( tr( "This route has changed and there is no timestamp available to determine the most recent version." ) );
    pInstructionLabel->setWordWrap( true );
    pLayout->addWidget( pInstructionLabel, 0, 0, 1, 2 );

    tMergeRouteInfoWidget* pLocalRouteInfo = new tMergeRouteInfoWidget( route, tr( "Local" ), isDeleted, this ); 
    Connect( pLocalRouteInfo, SIGNAL( KeepPressed() ), this, SLOT( KeepLocalVersion() ) );
    pLayout->addWidget( pLocalRouteInfo, 1, 0 );

    tMergeRouteInfoWidget* pNetworkRouteInfo = new tMergeRouteInfoWidget( networkRoute, tr( "Network" ), !networkRouteFound, this ); 
    Connect( pNetworkRouteInfo, SIGNAL( KeepPressed() ), this, SLOT( KeepNetworkVersion() ) ); 
    pLayout->addWidget( pNetworkRouteInfo, 1, 1 );

    QPushButton* pKeepAllButton = new QPushButton( tr( "Keep all local" ) );
    Connect( pKeepAllButton, SIGNAL( clicked() ), this, SLOT( KeepAllLocalVersions() ) ); 
    pLayout->addWidget( pKeepAllButton, 2, 0 );   

    QPushButton* pKeepAllNetworkButton = new QPushButton( tr( "Keep all network" ) );
    Connect( pKeepAllNetworkButton, SIGNAL( clicked() ), this, SLOT( KeepAllNetworkVersions() ) ); 
    pLayout->addWidget( pKeepAllNetworkButton, 2, 1 );   
    pKeepAllNetworkButton->setFocus();

    setLayout( pLayout );
}