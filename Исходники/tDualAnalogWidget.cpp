//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
tDualAnalogWidget::tDualAnalogWidget( int pageNumber, tIInstrumentProductFactory* pProductFactory, QWidget* pParent )
: tTemplateWidget( pProductFactory, pageNumber, pParent )
, m_LeftLimitIndex( 0 )
, m_RightLimitIndex( 0 )
{
    Assert( pProductFactory );
    if ( pProductFactory )
    {
        QVariantList analogRanges = tWidgetSettings::Instance()->TemplateAnalogRanges( m_PageNumber );
        if( analogRanges.length() > 0 )
        {
            m_LeftLimitIndex = analogRanges[0].toInt();
        }
        if( analogRanges.length() > 1 )
        {
            m_RightLimitIndex = analogRanges[1].toInt();
        }

        m_pAnalogGauge1 = pProductFactory->GetAnalogGauge( DATA_TYPE_INVALID, this );
        m_pAnalogGauge1->SetCustomHobartLimits( m_LeftLimitIndex );
        m_pLayout->addWidget( m_pAnalogGauge1, 0, 0, 2, 1 );
        m_Gauges << m_pAnalogGauge1;

        m_pAnalogGauge2 = pProductFactory->GetAnalogGauge( DATA_TYPE_INVALID, this );
        m_pAnalogGauge2->SetCustomHobartLimits( m_RightLimitIndex );
        m_pLayout->addWidget( m_pAnalogGauge2, 1, 1, 1, 2 );
        m_Gauges << m_pAnalogGauge2;

        m_pDigitalGauge1 = pProductFactory->GetDigitalGauge( DATA_TYPE_INVALID, this );
        m_pDigitalGauge1->SetBorders( false, false, true, false );
        m_pLayout->addWidget( m_pDigitalGauge1, 0, 1 );
        m_Gauges << m_pDigitalGauge1;

        m_pDigitalGauge2 = pProductFactory->GetDigitalGauge( DATA_TYPE_INVALID, this );
        m_pDigitalGauge2->SetBorders( false );
        m_pLayout->addWidget( m_pDigitalGauge2, 0, 2 );
        m_Gauges << m_pDigitalGauge2;

        int analog1H = Widgets::GetScreenHeight();
        int analog1W = analog1H;

        int analog2W = Widgets::GetScreenWidth() - analog1W;
        int analog2H = analog2W;

        int digitalH = Widgets::GetScreenHeight() - analog2H;
        int digitalW = analog2W / 2;

        m_pAnalogGauge1 ->setFixedSize( analog1W, analog1H );
        m_pAnalogGauge2 ->setFixedSize( analog2W, analog2H );
        m_pDigitalGauge1 ->setFixedSize( digitalW, digitalH );
        m_pDigitalGauge2 ->setFixedSize( digitalW, digitalH );

        LoadDataItems();
    }
}