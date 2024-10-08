CTracing::CTracing( QWidget* parent, const char* name )
	: QWidget( parent, name, 0 )
{
	QBoxLayout	*playoutTop		= new QVBoxLayout( this, 5 );

    // Tracing
#ifdef QT_V4LAYOUT
	Q3GroupBox *pgroupbox = new Q3GroupBox( this );
#else
	QGroupBox *pgroupbox = new QGroupBox( this );
#endif
	pgroupbox->setFrameStyle( QFrame::Box | QFrame::Raised );
    pgroupbox->setTitle( QString("Tracing") );
	playoutTop->addWidget( pgroupbox, 5 );

    QGridLayout *playoutGrid = new QGridLayout( pgroupbox, 3, 2, 5 );

	QLabel *plabel1	= new QLabel( "Enabled", pgroupbox, "plabel1" );
	pTracing 		= new QCheckBox( pgroupbox, "pTracing" );
	QLabel *plabel3	= new QLabel( "Force Tracing", pgroupbox, "plabel1" );
	pForce 		    = new QCheckBox( pgroupbox, "pForce" );
	QLabel *plabel2	= new QLabel( "File", pgroupbox, "plabel2" );
	pTraceFile		= new CFileSelector( pgroupbox, "pTraceFile" );

	playoutGrid->addWidget( plabel1, 1, 0 );
    playoutGrid->addWidget( pTracing, 1, 1 );
    playoutGrid->addWidget( plabel3, 1, 2 );
    playoutGrid->addWidget( pForce, 1, 3 );
    playoutGrid->addWidget( plabel2, 2, 0 );
    playoutGrid->addWidget( pTraceFile, 2, 1 );

    // Connection Pooling
#ifdef QT_V4LAYOUT
	pgroupbox = new Q3GroupBox( this );
#else
	pgroupbox = new QGroupBox( this );
#endif
	pgroupbox->setFrameStyle( QFrame::Box | QFrame::Raised );
    pgroupbox->setTitle( QString("Connection Pooling") );
	playoutTop->addWidget( pgroupbox, 5 );

    playoutGrid = new QGridLayout( pgroupbox, 3, 3, 5 );
    playoutGrid->setColStretch( 2, 10 );

	plabel1	    = new QLabel( "Enabled", pgroupbox, "plabel1" );
	pPooling    = new QCheckBox( pgroupbox, "pPooling" );

	playoutGrid->addWidget( plabel1, 1, 0 );
    playoutGrid->addWidget( pPooling, 1, 1 );

    // Buttons
    playoutGrid = new QGridLayout( playoutTop, 1, 5, 2 );

	QPushButton *pSetDefault    = new QPushButton( "De&fault", this );
	QPushButton *pApply         = new QPushButton( "A&pply", this );

	playoutGrid->addWidget( pSetDefault, 1, 1 );
    playoutGrid->addWidget( pApply, 1, 3 );

	// helpt text
	QFrame *pframe;
	pframe = new QFrame( this, "Frame_7" );
	pframe->setFrameStyle( QFrame::Box | QFrame::Raised );
	playoutTop->addWidget( pframe, 4 );

    playoutGrid = new QGridLayout( pframe, 1, 2, 5 );

	plabel1 = new QLabel( pframe, "Label_1" );
	plabel1->setGeometry( 20, 20, 32, 32 );
	plabel1->setPixmap( xpmAdvanced );
	plabel1->setMinimumSize( 32, 32 );
//	plabel1->setMaximumSize( 32, 32 );

	plabel2 = new QLabel( pframe, "Label_2" );
	plabel2->setText( "These options are global. As such, they can only be set by the system administrator or someone else with 'root' access. Turn Tracing on to enable logging of calls. Turn Pooling on to enable Driver Pooling options." );
#ifdef QT_V4LAYOUT
	plabel2->setAlignment( Qt::AlignLeft | Qt::WordBreak );
  	plabel2->setWordWrap( true );
#else
	plabel2->setAlignment( AlignLeft | WordBreak );
#endif

	playoutGrid->addWidget( plabel1, 0, 0 );
    playoutGrid->addWidget( plabel2, 0, 1 );
    playoutGrid->setColStretch( 1, 10 );


	// init values        
	char szTracing[10];
	char szForce[10];
	char szTracingFile[FILENAME_MAX];
	char szPooling[10];
	char szGUIPlugin[FILENAME_MAX];

	SQLGetPrivateProfileString( "ODBC", "Trace", "No", szTracing, sizeof(szTracing), "odbcinst.ini" );
	if ( szTracing[0] == '1' || toupper( szTracing[0] ) == 'Y' 
            || ( toupper( szTracing[0] ) == 'O' && toupper( szForce[0] ) == 'N' ))
		pTracing->setChecked( true );
		
	SQLGetPrivateProfileString( "ODBC", "ForceTrace", "No", szForce, sizeof(szForce), "odbcinst.ini" );
	if ( szForce[0] == '1' || toupper( szForce[0] ) == 'Y' 
            || ( toupper( szForce[0] ) == 'O' && toupper( szForce[0] ) == 'N' ))
		pForce->setChecked( true );
		
	SQLGetPrivateProfileString( "ODBC", "TraceFile", "/tmp/sql.log", szTracingFile, sizeof(szTracingFile)-1, "odbcinst.ini" );
	pTraceFile->pLineEdit->setText( szTracingFile );

	SQLGetPrivateProfileString( "ODBC", "Pooling", "No", szPooling, sizeof(szPooling), "odbcinst.ini" );
	if ( szPooling[0] == '1' || toupper( szPooling[0] ) == 'Y' 
            || ( toupper( szPooling[0] ) == 'O'  && toupper( szForce[0] ) == 'N' ))
		pPooling->setChecked( true );
		
	connect( pSetDefault, SIGNAL(clicked()), SLOT(setDefault()) );
	connect( pApply, SIGNAL(clicked()), SLOT(apply()) );
}