FindBar::FindBar( Okular::Document * document, QWidget * parent )
  : QWidget( parent )
  , m_active( false )
{
    QHBoxLayout * lay = new QHBoxLayout( this );
    lay->setMargin( 2 );

    QToolButton * closeBtn = new QToolButton( this );
    closeBtn->setIcon( KIcon( "dialog-close" ) );
    closeBtn->setToolTip( i18n( "Close" ) );
    closeBtn->setAutoRaise( true );
    lay->addWidget( closeBtn );

    QLabel * label = new QLabel( i18nc( "Find text", "F&ind:" ), this );
    lay->addWidget( label );

    m_search = new SearchLineWidget( this, document );
    m_search->lineEdit()->setSearchCaseSensitivity( Qt::CaseInsensitive );
    m_search->lineEdit()->setSearchMinimumLength( 0 );
    m_search->lineEdit()->setSearchType( Okular::Document::NextMatch );
    m_search->lineEdit()->setSearchId( PART_SEARCH_ID );
    m_search->lineEdit()->setSearchColor( qRgb( 255, 255, 64 ) );
    m_search->lineEdit()->setSearchMoveViewport( true );
    m_search->lineEdit()->setToolTip( i18n( "Text to search for" ) );
    m_search->installEventFilter( this );
    label->setBuddy( m_search->lineEdit() );
    lay->addWidget( m_search );

    QPushButton * findNextBtn = new QPushButton( KIcon( "go-down-search" ), i18nc( "Find and go to the next search match", "Next" ), this );
    findNextBtn->setToolTip( i18n( "Jump to next match" ) );
    lay->addWidget( findNextBtn );

    QPushButton * findPrevBtn = new QPushButton( KIcon( "go-up-search" ), i18nc( "Find and go to the previous search match", "Previous" ), this );
    findPrevBtn->setToolTip( i18n( "Jump to previous match" ) );
    lay->addWidget( findPrevBtn );

    QPushButton * optionsBtn = new QPushButton( this );
    optionsBtn->setText( i18n( "Options" ) );
    optionsBtn->setToolTip( i18n( "Modify search behavior" ) );
    QMenu * optionsMenu = new QMenu( optionsBtn );
    m_caseSensitiveAct = optionsMenu->addAction( i18n( "Case sensitive" ) );
    m_caseSensitiveAct->setCheckable( true );
    m_fromCurrentPageAct = optionsMenu->addAction( i18n( "From current page" ) );
    m_fromCurrentPageAct->setCheckable( true );
    optionsBtn->setMenu( optionsMenu );
    lay->addWidget( optionsBtn );

    connect( closeBtn, SIGNAL(clicked()), this, SLOT(closeAndStopSearch()) );
    connect( findNextBtn, SIGNAL(clicked()), this, SLOT(findNext()) );
    connect( findPrevBtn, SIGNAL(clicked()), this, SLOT(findPrev()) );
    connect( m_caseSensitiveAct, SIGNAL(toggled(bool)), this, SLOT(caseSensitivityChanged()) );
    connect( m_fromCurrentPageAct, SIGNAL(toggled(bool)), this, SLOT(fromCurrentPageChanged()) );

    m_caseSensitiveAct->setChecked( Okular::Settings::searchCaseSensitive() );
    m_fromCurrentPageAct->setChecked( Okular::Settings::searchFromCurrentPage() );

    hide();

    // "activate" it only at th very end
    m_active = true;
}