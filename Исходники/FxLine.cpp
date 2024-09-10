FxLine::FxLine( QWidget * _parent, FxMixerView * _mv, int _channelIndex ) :
	QWidget( _parent ),
	m_mv( _mv ),
	m_channelIndex( _channelIndex ),
	m_backgroundActive( Qt::SolidPattern ),
	m_strokeOuterActive( 0, 0, 0 ),
	m_strokeOuterInactive( 0, 0, 0 ),
	m_strokeInnerActive( 0, 0, 0 ),
	m_strokeInnerInactive( 0, 0, 0 ),
	m_inRename( false )
{
	if( !s_sendBgArrow )
	{
		s_sendBgArrow = new QPixmap( embed::getIconPixmap( "send_bg_arrow", 29, 56 ) );
	}
	if( !s_receiveBgArrow )
	{
		s_receiveBgArrow = new QPixmap( embed::getIconPixmap( "receive_bg_arrow", 29, 56 ) );
	}

	setFixedSize( 33, FxLineHeight );
	setAttribute( Qt::WA_OpaquePaintEvent, true );
	setCursor( QCursor( embed::getIconPixmap( "hand" ), 3, 3 ) );

	// mixer sends knob
	m_sendKnob = new Knob( knobBright_26, this, tr( "Channel send amount" ) );
	m_sendKnob->move( 3, 22 );
	m_sendKnob->setVisible( false );

	// send button indicator
	m_sendBtn = new SendButtonIndicator( this, this, m_mv );
	m_sendBtn->move( 2, 2 );

	// channel number
	m_lcd = new LcdWidget( 2, this );
	m_lcd->setValue( m_channelIndex );
	m_lcd->move( 4, 58 );
	m_lcd->setMarginWidth( 1 );
	
	QString name = Engine::fxMixer()->effectChannel( m_channelIndex )->m_name;
	setToolTip( name );

	m_renameLineEdit = new QLineEdit();
	m_renameLineEdit->setText( name );
	m_renameLineEdit->setFixedWidth( 65 );
	m_renameLineEdit->setFont( pointSizeF( font(), 7.5f ) );
	m_renameLineEdit->setReadOnly( true );
	m_renameLineEdit->installEventFilter( this );

	QGraphicsScene * scene = new QGraphicsScene();
	scene->setSceneRect( 0, 0, 33, FxLineHeight );

	m_view = new QGraphicsView( this );
	m_view->setStyleSheet( "border-style: none; background: transparent;" );
	m_view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	m_view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	m_view->setAttribute( Qt::WA_TransparentForMouseEvents, true );
	m_view->setScene( scene );

	QGraphicsProxyWidget * proxyWidget = scene->addWidget( m_renameLineEdit );
	proxyWidget->setRotation( -90 );
	proxyWidget->setPos( 8, 145 );

	connect( m_renameLineEdit, SIGNAL( editingFinished() ), this, SLOT( renameFinished() ) );
}