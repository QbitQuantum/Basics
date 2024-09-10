QgsVectorLayerProperties::QgsVectorLayerProperties(
  QgsVectorLayer *lyr,
  QWidget * parent,
  Qt::WindowFlags fl
)
    : QgsOptionsDialogBase( "VectorLayerProperties", parent, fl )
    , layer( lyr )
    , mMetadataFilled( false )
    , mSaveAsMenu( 0 )
    , mLoadStyleMenu( 0 )
    , mRendererDialog( 0 )
    , labelingDialog( 0 )
    , labelDialog( 0 )
    , actionDialog( 0 )
    , diagramPropertiesDialog( 0 )
    , mFieldsPropertiesDialog( 0 )
{
  setupUi( this );
  // QgsOptionsDialogBase handles saving/restoring of geometry, splitter and current tab states,
  // switching vertical tabs between icon/text to icon-only modes (splitter collapsed to left),
  // and connecting QDialogButtonBox's accepted/rejected signals to dialog's accept/reject slots
  initOptionsBase( false );

  QPushButton* b = new QPushButton( tr( "Style" ) );
  QMenu* m = new QMenu( this );
  mActionLoadStyle = m->addAction( tr( "Load Style..." ), this, SLOT( loadStyle_clicked() ) );
  mActionSaveStyleAs = m->addAction( tr( "Save Style..." ), this, SLOT( saveStyleAs_clicked() ) );
  m->addSeparator();
  m->addAction( tr( "Save As Default" ), this, SLOT( saveDefaultStyle_clicked() ) );
  m->addAction( tr( "Restore Default" ), this, SLOT( loadDefaultStyle_clicked() ) );
  b->setMenu( m );
  connect( m, SIGNAL( aboutToShow() ), this, SLOT( aboutToShowStyleMenu() ) );
  buttonBox->addButton( b, QDialogButtonBox::ResetRole );

  connect( lyr->styleManager(), SIGNAL( currentStyleChanged( QString ) ), this, SLOT( syncToLayer() ) );

  connect( buttonBox->button( QDialogButtonBox::Apply ), SIGNAL( clicked() ), this, SLOT( apply() ) );
  connect( this, SIGNAL( accepted() ), this, SLOT( apply() ) );
  connect( this, SIGNAL( rejected() ), this, SLOT( onCancel() ) );

  connect( mOptionsStackedWidget, SIGNAL( currentChanged( int ) ), this, SLOT( mOptionsStackedWidget_CurrentChanged( int ) ) );

  connect( insertFieldButton, SIGNAL( clicked() ), this, SLOT( insertField() ) );
  connect( insertExpressionButton, SIGNAL( clicked() ), this, SLOT( insertExpression() ) );

  // connections for Map Tip display
  connect( htmlRadio, SIGNAL( toggled( bool ) ), htmlMapTip, SLOT( setEnabled( bool ) ) );
  connect( htmlRadio, SIGNAL( toggled( bool ) ), insertFieldButton, SLOT( setEnabled( bool ) ) );
  connect( htmlRadio, SIGNAL( toggled( bool ) ), fieldComboBox, SLOT( setEnabled( bool ) ) );
  connect( htmlRadio, SIGNAL( toggled( bool ) ), insertExpressionButton, SLOT( setEnabled( bool ) ) );
  connect( fieldComboRadio, SIGNAL( toggled( bool ) ), displayFieldComboBox, SLOT( setEnabled( bool ) ) );

  if ( !layer )
    return;

  QVBoxLayout *layout;

  if ( layer->hasGeometryType() )
  {
    // Create the Labeling dialog tab
    layout = new QVBoxLayout( labelingFrame );
    layout->setMargin( 0 );
    labelingDialog = new QgsLabelingGui( layer, QgisApp::instance()->mapCanvas(), labelingFrame );
    labelingDialog->layout()->setContentsMargins( -1, 0, -1, 0 );
    layout->addWidget( labelingDialog );
    labelingFrame->setLayout( layout );

    // Create the Labeling (deprecated) dialog tab
    layout = new QVBoxLayout( labelOptionsFrame );
    layout->setMargin( 0 );
    labelDialog = new QgsLabelDialog( layer->label(), labelOptionsFrame );
    labelDialog->layout()->setMargin( 0 );
    layout->addWidget( labelDialog );
    labelOptionsFrame->setLayout( layout );
    connect( labelDialog, SIGNAL( labelSourceSet() ), this, SLOT( setLabelCheckBox() ) );
  }
  else
  {
    labelingDialog = 0;
    labelDialog = 0;
    mOptsPage_Labels->setEnabled( false ); // disable labeling item
    mOptsPage_LabelsOld->setEnabled( false ); // disable labeling (deprecated) item
  }

  // Create the Actions dialog tab
  QVBoxLayout *actionLayout = new QVBoxLayout( actionOptionsFrame );
  actionLayout->setMargin( 0 );
  const QgsFields &fields = layer->pendingFields();
  actionDialog = new QgsAttributeActionDialog( layer->actions(), fields, actionOptionsFrame );
  actionDialog->layout()->setMargin( 0 );
  actionLayout->addWidget( actionDialog );

  // Create the menu for the save style button to choose the output format
  mSaveAsMenu = new QMenu( this );
  mSaveAsMenu->addAction( tr( "QGIS Layer Style File" ) );
  mSaveAsMenu->addAction( tr( "SLD File" ) );

  //Only if the provider support loading & saving styles to db add new choices
  if ( layer->dataProvider()->isSaveAndLoadStyleToDBSupported() )
  {
    //for loading
    mLoadStyleMenu = new QMenu();
    mLoadStyleMenu->addAction( tr( "Load from file" ) );
    mLoadStyleMenu->addAction( tr( "Load from database" ) );
    //mActionLoadStyle->setContextMenuPolicy( Qt::PreventContextMenu );
    mActionLoadStyle->setMenu( mLoadStyleMenu );

    QObject::connect( mLoadStyleMenu, SIGNAL( triggered( QAction * ) ),
                      this, SLOT( loadStyleMenuTriggered( QAction * ) ) );

    //for saving
    mSaveAsMenu->addAction( tr( "Save in database (%1)" ).arg( layer->providerType() ) );
  }