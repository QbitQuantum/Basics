//-------------------------------------------------------------------------------------------
//!
//-------------------------------------------------------------------------------------------
tPageBase::tPageBase( const Page::ePageId id, const QString& title, tIInstrumentProductFactory* pProductFactory, tInstrumentState* pAppState , QWidget* pParent )
: QWidget( pParent )
,m_Id( id )
,m_Title( title )
,m_pProductFactory( pProductFactory )
,m_pAppState( pAppState )
{
    Assert( m_pProductFactory );

    setAutoFillBackground( true );

    m_InstanceCount++;

    m_pMainLayout = new QGridLayout( this );
    m_pMainLayout->setContentsMargins( 0, 0, 0, 0 );
    m_pMainLayout->setSpacing( 0 );

    m_pTitleLabel = new QLabel( m_Title, this );
    m_pTitleLabel->hide();

    m_pMainLayout->addWidget( m_pTitleLabel, 0, 0, Qt::AlignCenter );

    setLayout( m_pMainLayout );

    CreateCommonActions();

    Connect( tInstrumentUiSettings::Instance(), SIGNAL( ColorChanged() ), this, SLOT( UpdateColors() ) );
    Connect( tSystemSettings::Instance(), SIGNAL( NightModeChanged(bool,bool) ), this, SLOT( UpdateColors() ) );
    Connect( tUiSettings::Instance(), SIGNAL( NightModeTextColorChanged( eNightModeTextColor ) ), this, SLOT( UpdateColors() ) );

    UpdateColors();
}