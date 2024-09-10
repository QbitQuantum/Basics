ProceduralLevelGenerator::ProceduralLevelGenerator( QWidget* parent, GL2DProceduralLevel* params )
   : QFrame( parent )
   , m_params( params )
   , m_root( params->getParent() )
{
   QVBoxLayout* layout = new QVBoxLayout( this );
   setLayout( layout );

   QToolBar* toolbar = new QToolBar( this );
   {
      layout->addWidget( toolbar );

      QAction* generateLevelAction = toolbar->addAction( QIcon( ":/TamyEditor/Resources/Icons/Editor/play.png" ), "Generate level" );
      connect( generateLevelAction, SIGNAL( triggered() ), this, SLOT( generateScene() ) );
   }
   
   QFrame* statusBar = new QFrame( this );
   {
      layout->addWidget( statusBar );

      QHBoxLayout* statusBarLayout = new QHBoxLayout( statusBar );
      statusBarLayout->setSpacing( 0 );
      statusBarLayout->setMargin( 0 );
      statusBar->setLayout( statusBarLayout );

      QLabel* statusLabel = new QLabel( "Status: ", this );
      statusLabel->setMaximumWidth( 100 );
      statusBarLayout->addWidget( statusLabel );

      m_status = new QLabel( this );
      statusBarLayout->addWidget( m_status );
   }
}