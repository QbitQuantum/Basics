manageVestigeInstrumentView::manageVestigeInstrumentView( Instrument * _instrument,
							QWidget * _parent, vestigeInstrument * m_vi2 ) :
	InstrumentView( _instrument, _parent )
{
	m_vi = m_vi2;
	m_vi->m_scrollArea = new QScrollArea( this );
	widget = new QWidget(this);
	l = new QGridLayout( this );

	m_vi->m_subWindow = engine::mainWindow()->workspace()->addSubWindow(new QMdiSubWindow, Qt::SubWindow |
			Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	m_vi->m_subWindow->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::MinimumExpanding );
	m_vi->m_subWindow->setFixedWidth( 960 );
	m_vi->m_subWindow->setMinimumHeight( 300 );
	m_vi->m_subWindow->setWidget(m_vi->m_scrollArea);
	m_vi->m_subWindow->setWindowTitle( m_vi->instrumentTrack()->name()
								+ tr( " - VST plugin control" ) );
	m_vi->m_subWindow->setWindowIcon( PLUGIN_NAME::getIconPixmap( "logo" ) );
	//m_vi->m_subWindow->setAttribute(Qt::WA_DeleteOnClose);


	l->setContentsMargins( 20, 10, 10, 10 );
	l->setVerticalSpacing( 10 );
	l->setHorizontalSpacing( 23 );

	m_syncButton = new QPushButton( tr( "VST Sync" ), this );
	connect( m_syncButton, SIGNAL( clicked() ), this,
							SLOT( syncPlugin() ) );
	m_syncButton->setWhatsThis(
		tr( "Click here if you want to synchronize all parameters with VST plugin." ) );

	l->addWidget( m_syncButton, 0, 0, 1, 2, Qt::AlignLeft );

	m_displayAutomatedOnly = new QPushButton( tr( "Automated" ), this );
	connect( m_displayAutomatedOnly, SIGNAL( clicked() ), this,
							SLOT( displayAutomatedOnly() ) );
	m_displayAutomatedOnly->setWhatsThis(
		tr( "Click here if you want to display automated parameters only." ) );

	l->addWidget( m_displayAutomatedOnly, 0, 1, 1, 2, Qt::AlignLeft );


	m_closeButton = new QPushButton( tr( "    Close    " ), widget );
	connect( m_closeButton, SIGNAL( clicked() ), this,
							SLOT( closeWindow() ) );
	m_closeButton->setWhatsThis(
		tr( "Close VST plugin knob-controller window." ) );

	l->addWidget( m_closeButton, 0, 2, 1, 7, Qt::AlignLeft );


	for( int i = 0; i < 10; i++ )
	{
		l->addItem( new QSpacerItem( 68, 45, QSizePolicy::Fixed, QSizePolicy::Fixed ), 0, i );
	}

	const QMap<QString, QString> & dump = m_vi->m_plugin->parameterDump();
	m_vi->paramCount = dump.size();

	bool isVstKnobs = true;

	if (m_vi->vstKnobs == NULL) {
		m_vi->vstKnobs = new knob *[ m_vi->paramCount ];
		isVstKnobs = false;
	}
	if (m_vi->knobFModel == NULL) {
		m_vi->knobFModel = new FloatModel *[ m_vi->paramCount ];
	}

	char paramStr[35];
	QStringList s_dumpValues;

	if (isVstKnobs == false) {
		for( int i = 0; i < m_vi->paramCount; i++ )
		{
			sprintf( paramStr, "param%d", i);
    			s_dumpValues = dump[ paramStr ].split( ":" );

			m_vi->vstKnobs[ i ] = new knob( knobBright_26, this, s_dumpValues.at( 1 ) );
			m_vi->vstKnobs[ i ]->setHintText( s_dumpValues.at( 1 ) + ":", "" );
			m_vi->vstKnobs[ i ]->setLabel( s_dumpValues.at( 1 ).left( 15 ) );

			sprintf( paramStr, "%d", i);
			m_vi->knobFModel[ i ] = new FloatModel( (s_dumpValues.at( 2 )).toFloat(),
				0.0f, 1.0f, 0.01f, castModel<vestigeInstrument>(), tr( paramStr ) );
			connect( m_vi->knobFModel[i], SIGNAL( dataChanged() ), this, SLOT( setParameter() ) );
			m_vi->vstKnobs[i] ->setModel( m_vi->knobFModel[i] );
		}
	}

	int i = 0;
	for( int lrow = 1; lrow < ( int( m_vi->paramCount / 10 ) + 1 ) + 1; lrow++ )
	{
		for( int lcolumn = 0; lcolumn < 10; lcolumn++ )
		{
			if( i < m_vi->paramCount )
			{
				l->addWidget( m_vi->vstKnobs[i], lrow, lcolumn, Qt::AlignCenter );
			}
			i++;
		}
	}

	l->setRowStretch( ( int( m_vi->paramCount / 10) + 1), 1 );
	l->setColumnStretch( 10, 1 );

	widget->setLayout(l);
	widget->setAutoFillBackground(true);

	m_vi->m_scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	m_vi->m_scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	m_vi->m_scrollArea->setPalette( QApplication::palette( m_vi->m_scrollArea ) );
	m_vi->m_scrollArea->setMinimumHeight( 64 );

	m_vi->m_scrollArea->setWidget( widget );

	m_vi->m_subWindow->show();
}