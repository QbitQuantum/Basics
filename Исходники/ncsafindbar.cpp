NCSAFindBar::NCSAFindBar( Okular::Document * document, QWidget * parent )
  : QWidget( parent )
  , m_active( false )
{
    doc = document;
    if(NULL != doc)
    {
      doc->addObserver(this);
    }
    QVBoxLayout * vlay = new QVBoxLayout( this );
    QHBoxLayout * displayRow = new QHBoxLayout();
    vlay->addLayout( displayRow );
    display = new QLabel("");
    displayRow->addWidget(display);
    displayRow->insertStretch(1);
    resultComboBox = new QComboBox();
    //resultComboBox->addItems(fonts);
    displayRow->addWidget(resultComboBox);

    QHBoxLayout * lay = new QHBoxLayout();
    vlay->setMargin( 2 );
    vlay->addLayout(lay);


    QPushButton * optionsBtn = new QPushButton( this );
    optionsBtn->setText( i18n( "NCSA Options" ) );
    optionsBtn->setToolTip( i18n( "Modify search behavior" ) );
    QMenu * optionsMenu = new QMenu( optionsBtn );
    m_buildFontAct = optionsMenu->addAction( i18n( "Create custom font" ) );
    connect( m_buildFontAct, SIGNAL(triggered(bool)), this, SLOT(buildFontAct(bool)) );

    optionsBtn->setMenu( optionsMenu );
    lay->addWidget( optionsBtn );
    
    QStringList fonts = QFontDatabase().families();
    
    fontComboBox = new QComboBox();
    fontComboBox->addItems(fonts);
    lay->addWidget(fontComboBox);
    connect( fontComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFont(int)) );
    connect( resultComboBox, SIGNAL(highlighted(int)), this, SLOT(resultComboBoxIndexChanged(int)) );

    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::white);
    display->setAutoFillBackground(true);
    display->setPalette(p);
    display->setText("Lalala");
    QFont font;
    font.setPointSize(32);
    font.setBold(true);
    font.setFamily(fonts.at(16));

    display->setFont(font);
    
    searchLine = new QLineEdit();
    lay->addWidget(searchLine);
    
    connect(searchLine,SIGNAL(textChanged(QString)),this,SLOT(searchLineTextChanged(QString)));
    hide();
    
    QPushButton * searchBtn = new QPushButton( KIcon( "Search" ), i18nc( "Search using word spotting technique", "search" ), this );
    searchBtn->setToolTip( i18n( "Search using word spotting technique" ) );
    lay->addWidget( searchBtn );
    connect( searchBtn, SIGNAL(clicked()), this, SLOT(performSearch()) );

    // "activate" it only at th very end
    m_active = true;
    wordSpottingUtil = NULL;
    
}