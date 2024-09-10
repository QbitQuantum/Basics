QgsColorButtonV2::QgsColorButtonV2( QWidget *parent, QString cdt, QColorDialog::ColorDialogOptions cdo, QgsColorSchemeRegistry* registry )
    : QToolButton( parent )
    , mBehaviour( QgsColorButtonV2::ShowDialog )
    , mColorDialogTitle( cdt.isEmpty() ? tr( "Select Color" ) : cdt )
    , mColor( QColor() )
    , mDefaultColor( QColor() ) //default to invalid color
    , mColorDialogOptions( cdo )
    , mAcceptLiveUpdates( true )
    , mColorSet( false )
    , mShowNoColorOption( false )
    , mNoColorString( tr( "No color" ) )
    , mPickingColor( false )
    , mMenu( 0 )

{
  //if a color scheme registry was specified, use it, otherwise use the global instance
  mColorSchemeRegistry = registry ? registry : QgsColorSchemeRegistry::instance();

  setAcceptDrops( true );
  setMinimumSize( QSize( 24, 16 ) );
  connect( this, SIGNAL( clicked() ), this, SLOT( buttonClicked() ) );

  //setup dropdown menu
  mMenu = new QMenu( this );
  connect( mMenu, SIGNAL( aboutToShow() ), this, SLOT( prepareMenu() ) );
  setMenu( mMenu );
  setPopupMode( QToolButton::MenuButtonPopup );
}