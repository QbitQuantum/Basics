//-----------------------------------------------------------------------------
//! Constructor for a dialog
//-----------------------------------------------------------------------------
tAutopilotAdvancedDialog::tAutopilotAdvancedDialog( tPilotController& pilotDevice, QWidget* pParent )
: tSaveCancelDialog( tDialog::Full, pParent )
, m_PilotDevice(pilotDevice)
{
    setWindowTitle( tr( "Advanced" ) );

    tPilotH5000AdvancedInterface::tH5000AdvancedParameters h5000AdvancedParameters;
    m_PilotDevice.GetH5000AdvancedInterface()->GetH5000AdvancedParameters( &h5000AdvancedParameters );

    // Gust response
    tLabel* pGustResponseLbl = new tLabel( QString( tr( "Gust response" ) ), this );

    // Gust response - enable
    tLabel* pGustResponseEnableLbl = new tLabel( QString( tr( "Enable" ) ), this );
    m_pGustResponseCheck = new tCheckBox( false, this );
    m_pGustResponseCheck->setChecked( h5000AdvancedParameters.gustResponse );
    Connect( m_pGustResponseCheck, SIGNAL( toggled( bool ) ), this, SLOT( OnGustResponseEnableChanged( bool ) ) );

    // Gust response - Gust MIN
    tLabel* pGustMinLbl = new tLabel( QString( tr( "Gust MIN" ) ), this );
    m_pGustMinEdit = new tIntEdit( h5000AdvancedParameters.gustMin, 1, 10, this );
    m_pGustMinEdit->setFixedWidth( 100 );
    m_pGustMinEdit->setEnabled( m_pGustResponseCheck->isChecked() );
    Connect( m_pGustMinEdit, SIGNAL( EditingFinished( int ) ), this, SLOT( OnEdit() ) );

    // Gust response - Response rate
    tLabel* pGuestResponseRateLbl = new tLabel( QString( tr( "Response rate" ) ), this );
    m_pGustResponseRateEdit = new tIntEdit( h5000AdvancedParameters.gustResponseRate, 1, 10, this );
    m_pGustResponseRateEdit->setFixedWidth( 100 );
    m_pGustResponseRateEdit->setEnabled( m_pGustResponseCheck->isChecked() );
    Connect( m_pGustResponseRateEdit, SIGNAL( EditingFinished( int ) ), this, SLOT( OnEdit() ) );
    
    // Gust response - TWA response
    tLabel* pTWAResponseLbl = new tLabel( QString( tr( "TWA response" ) ), this );
    m_pTWAReponseEdit = new tDoubleEdit( h5000AdvancedParameters.TWAResponse, 1.0F, 5.0F, 1, this );
    m_pTWAReponseEdit->setFixedWidth( 100 );
    m_pTWAReponseEdit->setEnabled( m_pGustResponseCheck->isChecked() );
    Connect( m_pTWAReponseEdit, SIGNAL( EditingFinished() ), this, SLOT( OnEdit() ) );
    
    // TWS response
    tLabel* pTWSResponseLbl = new tLabel( QString( tr( "TWS response" ) ), this );

    // TWS response - enable
    tLabel* pTWSResponseEnableLbl = new tLabel( QString( tr( "Enable" ) ), this );
    m_pTWSCheck = new tCheckBox( false, this );
    m_pTWSCheck->setChecked( h5000AdvancedParameters.TWSResponse );
    Connect( m_pTWSCheck, SIGNAL( toggled( bool ) ), this, SLOT( OnTWSResponseEnableChanged( bool ) ) );

    // TWS response - Response rate
    tLabel* pTWSResponseRateLbl = new tLabel( QString( tr( "Response rate" ) ), this );
    m_pTWSResponseRateEdit = new tIntEdit( h5000AdvancedParameters.TWSResponseRate, 1, 10, this );
    m_pTWSResponseRateEdit->setFixedWidth( 100 );
    m_pTWSResponseRateEdit->setEnabled( m_pTWSCheck->isChecked() );
    Connect( m_pTWSResponseRateEdit, SIGNAL( EditingFinished( int ) ), this, SLOT( OnEdit() ) );
    
    // Heel compensation
    tLabel* pHeelCompensationLbl = new tLabel( QString( tr( "Heel compensation" ) ), this );

    // Heel compensation - enable
    tLabel* pHeelCompensationEnableLbl = new tLabel( QString( tr( "Enable" ) ), this );
    m_pHeelCompensationCheck = new tCheckBox( false, this );
    m_pHeelCompensationCheck->setChecked( h5000AdvancedParameters.heelCompensation );
    Connect( m_pHeelCompensationCheck, SIGNAL( toggled( bool ) ), this, SLOT( OnHeelCompensationEnableChanged( bool ) ) );

    // Heel compensation - Response rate
    tLabel* pHeelCompensationResponseRateLbl = new tLabel( QString( tr( "Response rate" ) ), this );
    m_pHeelCompensationResponseRateEdit = new tIntEdit( h5000AdvancedParameters.heelCompensationRate, 1, 10, this );
    m_pHeelCompensationResponseRateEdit->setFixedWidth( 100 );
    m_pHeelCompensationResponseRateEdit->setEnabled( m_pHeelCompensationCheck->isChecked() );
    Connect( m_pHeelCompensationResponseRateEdit, SIGNAL( EditingFinished( int ) ), this, SLOT( OnEdit() ) );
    
    int row( 0 );
    QGridLayout* pGridLayout = new QGridLayout( this );

    // Gust response
    pGridLayout->addWidget( pGustResponseLbl, row++, 0 ); 
    pGridLayout->addWidget( pGustResponseEnableLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pGustResponseCheck, row++, 1 );
    pGridLayout->addWidget( pGustMinLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pGustMinEdit, row++, 1 );
    pGridLayout->addWidget( pGuestResponseRateLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pGustResponseRateEdit, row++, 1 );
    pGridLayout->addWidget( pTWAResponseLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pTWAReponseEdit, row++, 1 );

    // TWS response
    pGridLayout->addWidget( pTWSResponseLbl, row++, 0 ); 
    pGridLayout->addWidget( pTWSResponseEnableLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pTWSCheck, row++, 1 );
    pGridLayout->addWidget( pTWSResponseRateLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pTWSResponseRateEdit, row++, 1 );

    // Heel compensation
    pGridLayout->addWidget( pHeelCompensationLbl, row++, 0 ); 
    pGridLayout->addWidget( pHeelCompensationEnableLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pHeelCompensationCheck, row++, 1 );
    pGridLayout->addWidget( pHeelCompensationResponseRateLbl, row, 0, Qt::AlignRight  ); 
    pGridLayout->addWidget( m_pHeelCompensationResponseRateEdit, row++, 1 );

    setLayout( pGridLayout );

    m_pGustResponseCheck->setFocus();

    Connect ( m_PilotDevice.GetH5000AdvancedInterface(), SIGNAL( H5000AdvancedParametersChanged( tPilotH5000AdvancedInterface::tH5000AdvancedParameters ) ),
              this, SLOT( OnH5000AdvancedParametersChanged( tPilotH5000AdvancedInterface::tH5000AdvancedParameters ) ) );
}