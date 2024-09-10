tTripDialog::tTripDialog( tIInstrumentProductFactory* pProductFactory, QWidget* pParent, int tripNumber )
: tDialog( tDialog::Full, pParent )
, m_TripNumber(tripNumber)
{
    Assert( pProductFactory );
    if ( pProductFactory )
    {
        QString title = tr( "Trip", "[title]" );
        title += QString(" %1").arg(tripNumber + 1);

        setWindowTitle( title );

        QGridLayout* pGridLayout = new QGridLayout();
        pGridLayout->setContentsMargins( 0, 0, 0, 0 );
        pGridLayout->setSpacing( 0 );

        int row = 0;
        int col = 0;

        m_pGauge1 = pProductFactory->GetDigitalGauge( tDataId(DATA_TYPE_TRIP_DISTANCE, m_TripNumber), this );
        m_pGauge1->SetBorders( false, false, true, true );
        pGridLayout->addWidget( m_pGauge1, row++, col );

        m_pGauge2 = pProductFactory->GetDigitalGauge( tDataId(DATA_TYPE_SPEED_TRIP_AVG, m_TripNumber), this );
        m_pGauge2->SetBorders( false, false, true, false );
        pGridLayout->addWidget( m_pGauge2, row++, col );

        row = 0;
        col++;

        m_pGauge3 = pProductFactory->GetDigitalGauge( tDataId(DATA_TYPE_TRIP_TIME, m_TripNumber), this );
        m_pGauge3->SetBorders( false, false, false, true );
        pGridLayout->addWidget( m_pGauge3, row++, col );

        m_pGauge4 = pProductFactory->GetDigitalGauge( tDataId(DATA_TYPE_SPEED_TRIP_MAX, m_TripNumber), this );
        m_pGauge4->SetBorders( false );
        pGridLayout->addWidget( m_pGauge4, row++, col );

        setLayout( pGridLayout );

        CreateActions();

        Connect( tSystemSettings::Instance(), SIGNAL( NightModeChanged(bool,bool) ), this, SLOT( UpdateColors() ) );
        Connect( tUiSettings::Instance(), SIGNAL( NightModeTextColorChanged( eNightModeTextColor ) ), this, SLOT( UpdateColors() ) );
        UpdateColors();
    }
}