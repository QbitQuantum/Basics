ParameterGroupWidget::ParameterGroupWidget( ParameterWindow* pWindow, BRDFBase* brdfIn )
    : QFrame(), paramWindow(pWindow), brdf(brdfIn), visibleCheckBox(NULL), dirty(true)
{
    // start by setting the draw color of the BRDF
    brdfDrawColor[0] = drawColors[colorIndex][0];
    brdfDrawColor[1] = drawColors[colorIndex][1];
    brdfDrawColor[2] = drawColors[colorIndex][2];

    colorIndex = (colorIndex + 1) % NUM_DRAW_COLORS;



    // now let's get to the layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin( 0 );
    layout->setContentsMargins( 0, 0, 0, 0 );

    // the parameter window needs to know to emit changes whenever this BRDF is reloaded
    connect( this, SIGNAL(brdfChanged(ParameterGroupWidget*)), paramWindow, SLOT(emitBRDFListChanged()) );


    // add and connect the show/hide button
    titleButton = new QPushButton( QString("  ") + QString(extractFilename(brdf->getName()).c_str()) );
    titleButton->setFixedHeight( 22 ); 
    connect( titleButton, SIGNAL(clicked()), this, SLOT(titleButtonPushed()) );


    // set the button color to the BRDF's draw color
    changeTitleButtonColor( false );



    // make the command QFrame - contains the visible checkbox and reload/close buttons
    QFrame* cmdFrame = new QFrame;

    QHBoxLayout* cmdLayout = new QHBoxLayout;
    cmdLayout->setMargin( 0 );
    cmdLayout->setContentsMargins( 0, 0, 0, 0 );
    cmdLayout->setSpacing( 11 );
    cmdFrame->setLayout( cmdLayout );


    visibleCheckBox = new QCheckBox( "Visible" );
    visibleCheckBox->setChecked( true );
    cmdLayout->addWidget( visibleCheckBox );
    connect( visibleCheckBox, SIGNAL(stateChanged(int)), this, SLOT(paramChanged()) );


    // add the solo button
    soloButton = new QPushButton();
    QPixmap* soloPixmap = new QPixmap((getImagesPath() + "soloSmall.png").c_str());
    soloButton->setIconSize( QSize(soloPixmap->width(), soloPixmap->height()) );
    soloButton->setIcon( QIcon(*soloPixmap) );
    soloButton->setFixedWidth( 24 );
    soloButton->setFixedHeight( 20 );
    soloButton->setCheckable( true );
    soloButton->setChecked( false );
    soloButton->setToolTip( "Solo this BRDF" );
    connect( soloButton, SIGNAL(clicked()), this, SLOT(soloButtonPushed()) );
    cmdLayout->addWidget( soloButton );


    // add the solo colors button
    soloColorsButton = new QPushButton();
    QPixmap* soloColorsPixmap = new QPixmap((getImagesPath() + "soloColorsSmall.png").c_str());
    soloColorsButton->setIconSize( QSize(soloColorsPixmap->width(), soloColorsPixmap->height()) );
    soloColorsButton->setIcon( QIcon(*soloColorsPixmap) );
    soloColorsButton->setFixedWidth( 24 );
    soloColorsButton->setFixedHeight( 20 );
    soloColorsButton->setCheckable( true );
    soloColorsButton->setChecked( false );
    soloColorsButton->setToolTip( "Solo this BRDF's color channels" );
    connect( soloColorsButton, SIGNAL(clicked()), this, SLOT(soloColorsButtonPushed()) );
    cmdLayout->addWidget( soloColorsButton );
   
    
    QMenu* optionsMenu = new QMenu;
    QAction* reloadAction = optionsMenu->addAction( "Reload BRDF" );
    QPixmap* reloadPixmap = new QPixmap((getImagesPath() + "reloadSmall.png").c_str());
    reloadAction->setIcon( QIcon(*reloadPixmap) );    
    connect( reloadAction, SIGNAL(triggered()), this, SLOT(reloadButtonPushed()) );
    
    QAction* resetAction = optionsMenu->addAction( "Reload BRDF and reset to default" );
    QPixmap* resetPixmap = new QPixmap((getImagesPath() + "resetSmall.png").c_str());
    resetAction->setIcon( QIcon(*resetPixmap) );
    connect( resetAction, SIGNAL(triggered()), this, SLOT(resetButtonPushed()) );
    
    QAction* saveAction = optionsMenu->addAction( "Save Parameters File..." );
    QPixmap* folderPixmap = new QPixmap((getImagesPath() + "folderSmall.png").c_str());
    saveAction->setIcon( QIcon(*folderPixmap) );
    connect( saveAction, SIGNAL(triggered()), this, SLOT(saveParamsFileButtonPushed()) );
    
    optionsMenu->addSeparator();
    
    QAction* closeAction = optionsMenu->addAction( "Close BRDF" );
    QPixmap* closePixmap = new QPixmap((getImagesPath() + "closeSmall.png").c_str());
    closeAction->setIcon( QIcon(*closePixmap) );
    connect( closeAction, SIGNAL(triggered()), this, SLOT(removeButtonPushed()) );
    

    // add the button with the menu dropdown
    QPushButton* menuButton = new QPushButton();
    menuButton->setFixedWidth( 24 );
    menuButton->setFixedHeight( 20 );
    menuButton->setMenu( optionsMenu );    
    cmdLayout->addWidget( menuButton );


    // make the container frame and its layout
    containerFrame = new QFrame;
    containerLayout = new QVBoxLayout( 0 );
    containerLayout->setMargin( 0 );
    containerLayout->setContentsMargins( 0, 0, 0, 0 );
    containerLayout->addWidget( cmdFrame );
    containerLayout->setSpacing( 2 );
    containerFrame->setLayout( containerLayout );

    addParameterWidgets();

    // add the widgets to the layout
    layout->addWidget( titleButton );
    layout->addWidget( containerFrame );


    setLayout(layout);
}