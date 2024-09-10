QgsColorButton::QgsColorButton( QWidget *parent, const QString &cdt, QgsColorSchemeRegistry *registry )
  : QToolButton( parent )
  , mColorDialogTitle( cdt.isEmpty() ? tr( "Select Color" ) : cdt )
  , mNoColorString( tr( "No color" ) )
{
  //if a color scheme registry was specified, use it, otherwise use the global instance
  mColorSchemeRegistry = registry ? registry : QgsApplication::colorSchemeRegistry();

  setAcceptDrops( true );
  setMinimumSize( QSize( 24, 16 ) );
  connect( this, &QAbstractButton::clicked, this, &QgsColorButton::buttonClicked );

  //setup drop-down menu
  mMenu = new QMenu( this );
  connect( mMenu, &QMenu::aboutToShow, this, &QgsColorButton::prepareMenu );
  setMenu( mMenu );
  setPopupMode( QToolButton::MenuButtonPopup );

#ifdef Q_OS_WIN
  mMinimumSize = QSize( 120, 22 );
#else
  mMinimumSize = QSize( 120, 28 );
#endif

  mMinimumSize.setHeight( std::max( static_cast<int>( fontMetrics().height() * 1.1 ), mMinimumSize.height() ) );
}