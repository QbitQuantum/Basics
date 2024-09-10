QwtDial *CockpitGrid::createDial( int pos )
{
    QwtDial *dial = NULL;
    switch( pos )
    {
        case 0:
        {
            d_clock = new QwtAnalogClock( this );
#if 0
            // disable minor ticks
            d_clock->scaleDraw()->setTickLength( QwtScaleDiv::MinorTick, 0 );
#endif

            const QColor knobColor = QColor( Qt::gray ).light( 130 );

            for ( int i = 0; i < QwtAnalogClock::NHands; i++ )
            {
                QColor handColor = QColor( Qt::gray ).light( 150 );
                int width = 8;

                if ( i == QwtAnalogClock::SecondHand )
                {
                    handColor = Qt::gray;
                    width = 5;
                }

                QwtDialSimpleNeedle *hand = new QwtDialSimpleNeedle(
                    QwtDialSimpleNeedle::Arrow, true, handColor, knobColor );
                hand->setWidth( width );

                d_clock->setHand( static_cast<QwtAnalogClock::Hand>( i ), hand );
            }

            QTimer *timer = new QTimer( d_clock );
            timer->connect( timer, SIGNAL( timeout() ),
                d_clock, SLOT( setCurrentTime() ) );
            timer->start( 1000 );

            dial = d_clock;
            break;
        }
        case 1:
        {
            d_speedo = new SpeedoMeter( this );
            d_speedo->setScaleStepSize( 20.0 );
            d_speedo->setScale( 0.0, 240.0 );
            d_speedo->scaleDraw()->setPenWidth( 2 );

            QTimer *timer = new QTimer( d_speedo );
            timer->connect( timer, SIGNAL( timeout() ),
                this, SLOT( changeSpeed() ) );
            timer->start( 50 );

            dial = d_speedo;
            break;
        }
        case 2:
        {
            d_ai = new AttitudeIndicator( this );
            d_ai->scaleDraw()->setPenWidth( 3 );

            QTimer *gradientTimer = new QTimer( d_ai );
            gradientTimer->connect( gradientTimer, SIGNAL( timeout() ),
                this, SLOT( changeGradient() ) );
            gradientTimer->start( 100 );

            QTimer *angleTimer = new QTimer( d_ai );
            angleTimer->connect( angleTimer, SIGNAL( timeout() ),
                this, SLOT( changeAngle() ) );
            angleTimer->start( 100 );

            dial = d_ai;
            break;
        }

    }

    if ( dial )
    {
        dial->setReadOnly( true );
        dial->setLineWidth( 4 );
        dial->setFrameShadow( QwtDial::Sunken );
    }
    return dial;
}