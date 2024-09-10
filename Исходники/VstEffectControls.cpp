manageVSTEffectView::manageVSTEffectView( VstEffect * _eff, VstEffectControls * m_vi ) :
	m_effect( _eff )
{
	m_vi2 = m_vi;
	widget = new QWidget();
        m_vi->m_scrollArea = new QScrollArea( widget );
	l = new QGridLayout( widget );

	m_vi->m_subWindow = gui->mainWindow()->addWindowedWidget(NULL, Qt::SubWindow | 
			Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	m_vi->m_subWindow->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
	m_vi->m_subWindow->setFixedSize( 960, 300);
	m_vi->m_subWindow->setWidget(m_vi->m_scrollArea);
	m_vi->m_subWindow->setWindowTitle( _eff->m_plugin->name() + tr( " - VST parameter control" ) );
	m_vi->m_subWindow->setWindowIcon( PLUGIN_NAME::getIconPixmap( "logo" ) );
	m_vi->m_subWindow->setAttribute(Qt::WA_DeleteOnClose, false);


	l->setContentsMargins( 20, 10, 10, 10 );
	l->setVerticalSpacing( 10 );
	l->setHorizontalSpacing( 23 );

	m_syncButton = new QPushButton( tr( "VST sync" ), widget );
	connect( m_syncButton, SIGNAL( clicked() ), this,
							SLOT( syncPlugin() ) );

	l->addWidget( m_syncButton, 0, 0, 1, 2, Qt::AlignLeft );

	m_displayAutomatedOnly = new QPushButton( tr( "Automated" ), widget );
	connect( m_displayAutomatedOnly, SIGNAL( clicked() ), this,
							SLOT( displayAutomatedOnly() ) );

	l->addWidget( m_displayAutomatedOnly, 0, 1, 1, 2, Qt::AlignLeft );


	m_closeButton = new QPushButton( tr( "    Close    " ), widget );
	connect( m_closeButton, SIGNAL( clicked() ), this,
							SLOT( closeWindow() ) );

	l->addWidget( m_closeButton, 0, 2, 1, 7, Qt::AlignLeft );


	for( int i = 0; i < 10; i++ )
	{
		l->addItem( new QSpacerItem( 68, 45, QSizePolicy::Fixed, QSizePolicy::Fixed ), 0, i );
	}

	const QMap<QString, QString> & dump = m_effect->m_plugin->parameterDump();
	m_vi->paramCount = dump.size();

	vstKnobs = new Knob *[ m_vi->paramCount ];

	bool hasKnobModel = true;
	if (m_vi->knobFModel == NULL) {
		m_vi->knobFModel = new FloatModel *[ m_vi->paramCount ];
		hasKnobModel = false;
	}

	char paramStr[35];
	QStringList s_dumpValues;

	for( int i = 0; i < m_vi->paramCount; i++ )
	{
		sprintf( paramStr, "param%d", i);
		s_dumpValues = dump[ paramStr ].split( ":" );

		vstKnobs[ i ] = new Knob( knobBright_26, widget, s_dumpValues.at( 1 ) );
		vstKnobs[ i ]->setHintText( s_dumpValues.at( 1 ) + ":", "" );
		vstKnobs[ i ]->setLabel( s_dumpValues.at( 1 ).left( 15 ) );

		if( !hasKnobModel )
		{
			sprintf( paramStr, "%d", i);
			m_vi->knobFModel[ i ] = new FloatModel( ( s_dumpValues.at( 2 ) ).toFloat(), 
					0.0f, 1.0f, 0.01f, _eff, tr( paramStr ) );
		}
		connect( m_vi->knobFModel[ i ], SIGNAL( dataChanged() ), this, 
								SLOT( setParameter() ) );
		vstKnobs[ i ] ->setModel( m_vi->knobFModel[ i ] );
	}

	int i = 0;
	for( int lrow = 1; lrow < ( int( m_vi->paramCount / 10 ) + 1 ) + 1; lrow++ )
	{
		for( int lcolumn = 0; lcolumn < 10; lcolumn++ )
		{
			if( i < m_vi->paramCount )
			{
				l->addWidget( vstKnobs[i], lrow, lcolumn, Qt::AlignCenter );
			}
			i++;
		}
	}

	l->setRowStretch( ( int( m_vi->paramCount / 10 ) + 1 ), 1 );
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