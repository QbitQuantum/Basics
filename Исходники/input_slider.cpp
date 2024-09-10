SeekSlider::SeekSlider( Qt::Orientation q, QWidget *_parent, bool _static )
          : QSlider( q, _parent ), b_classic( _static )
{
    isSliding = false;
    f_buffering = 1.0;
    mHandleOpacity = 1.0;
    chapters = NULL;
    mHandleLength = -1;
    b_seekable = true;
    alternativeStyle = NULL;

    // prepare some static colors
    QPalette p = palette();
    QColor background = p.color( QPalette::Active, QPalette::Window );
    tickpointForeground = p.color( QPalette::Active, QPalette::WindowText );
    tickpointForeground.setHsv( tickpointForeground.hue(),
            ( background.saturation() + tickpointForeground.saturation() ) / 2,
            ( background.value() + tickpointForeground.value() ) / 2 );

    // set the background color and gradient
    QColor backgroundBase( p.window().color() );
    backgroundGradient.setColorAt( 0.0, backgroundBase.darker( 140 ) );
    backgroundGradient.setColorAt( 1.0, backgroundBase );

    // set the foreground color and gradient
    QColor foregroundBase( 50, 156, 255 );
    foregroundGradient.setColorAt( 0.0,  foregroundBase );
    foregroundGradient.setColorAt( 1.0,  foregroundBase.darker( 140 ) );

    // prepare the handle's gradient
    handleGradient.setColorAt( 0.0, p.window().color().lighter( 120 ) );
    handleGradient.setColorAt( 0.9, p.window().color().darker( 120 ) );

    // prepare the handle's shadow gradient
    QColor shadowBase = p.shadow().color();
    if( shadowBase.lightness() > 100 )
        shadowBase = QColor( 60, 60, 60 ); // Palette's shadow is too bright
    shadowDark = shadowBase.darker( 150 );
    shadowLight = shadowBase.lighter( 180 );
    shadowLight.setAlpha( 50 );

    /* Timer used to fire intermediate updatePos() when sliding */
    seekLimitTimer = new QTimer( this );
    seekLimitTimer->setSingleShot( true );

    /* Tooltip bubble */
    mTimeTooltip = new TimeTooltip( this );
    mTimeTooltip->setMouseTracking( true );

    /* Properties */
    setRange( MINIMUM, MAXIMUM );
    setSingleStep( 2 );
    setPageStep( 10 );
    setMouseTracking( true );
    setTracking( true );
    setFocusPolicy( Qt::NoFocus );

    /* Use the new/classic style */
    if( !b_classic )
    {
        alternativeStyle = new SeekStyle;
        setStyle( alternativeStyle );
    }

    /* Init to 0 */
    setPosition( -1.0, 0, 0 );
    secstotimestr( psz_length, 0 );

    animHandle = new QPropertyAnimation( this, "handleOpacity", this );
    animHandle->setDuration( FADEDURATION );
    animHandle->setStartValue( 0.0 );
    animHandle->setEndValue( 1.0 );

    hideHandleTimer = new QTimer( this );
    hideHandleTimer->setSingleShot( true );
    hideHandleTimer->setInterval( FADEOUTDELAY );

    CONNECT( this, sliderMoved( int ), this, startSeekTimer() );
    CONNECT( seekLimitTimer, timeout(), this, updatePos() );
    CONNECT( hideHandleTimer, timeout(), this, hideHandle() );
    mTimeTooltip->installEventFilter( this );
}