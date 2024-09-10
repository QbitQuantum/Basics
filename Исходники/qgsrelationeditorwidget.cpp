QgsRelationEditorWidget::QgsRelationEditorWidget( QWidget* parent )
    : QgsCollapsibleGroupBox( parent )
    , mViewMode( QgsDualView::AttributeEditor )
    , mVisible( false )
{
  QVBoxLayout* topLayout = new QVBoxLayout( this );
  topLayout->setContentsMargins( 0, 9, 0, 0 );
  setLayout( topLayout );

  // buttons
  QHBoxLayout* buttonLayout = new QHBoxLayout();
  buttonLayout->setContentsMargins( 0, 0, 0, 0 );
  // toogle editing
  mToggleEditingButton = new QToolButton( this );
  mToggleEditingButton->setObjectName( "mToggleEditingButton" );
  mToggleEditingButton->setIcon( QgsApplication::getThemeIcon( "/mActionToggleEditing.svg" ) );
  mToggleEditingButton->setText( tr( "Toggle editing" ) );
  mToggleEditingButton->setEnabled( false );
  mToggleEditingButton->setCheckable( true );
  mToggleEditingButton->setToolTip( tr( "Toggle editing mode for child layer" ) );
  buttonLayout->addWidget( mToggleEditingButton );
  // save Edits
  mSaveEditsButton = new QToolButton( this );
  mSaveEditsButton->setIcon( QgsApplication::getThemeIcon( "/mActionSaveEdits.svg" ) );
  mSaveEditsButton->setText( tr( "Save child layer edits" ) );
  mSaveEditsButton->setToolTip( tr( "Save child layer edits" ) );
  mSaveEditsButton->setEnabled( true );
  buttonLayout->addWidget( mSaveEditsButton );
  // add feature
  mAddFeatureButton = new QToolButton( this );
  mAddFeatureButton->setIcon( QgsApplication::getThemeIcon( "/mActionNewTableRow.svg" ) );
  mAddFeatureButton->setText( tr( "Add child feature" ) );
  mAddFeatureButton->setToolTip( tr( "Add child feature" ) );
  mAddFeatureButton->setObjectName( "mAddFeatureButton" );
  buttonLayout->addWidget( mAddFeatureButton );
  // delete feature
  mDeleteFeatureButton = new QToolButton( this );
  mDeleteFeatureButton->setIcon( QgsApplication::getThemeIcon( "/mActionDeleteSelected.svg" ) );
  mDeleteFeatureButton->setText( tr( "Delete child feature" ) );
  mDeleteFeatureButton->setToolTip( tr( "Delete child feature" ) );
  mDeleteFeatureButton->setObjectName( "mDeleteFeatureButton" );
  buttonLayout->addWidget( mDeleteFeatureButton );
  // link feature
  mLinkFeatureButton = new QToolButton( this );
  mLinkFeatureButton->setIcon( QgsApplication::getThemeIcon( "/mActionLink.svg" ) );
  mLinkFeatureButton->setText( tr( "Link existing features" ) );
  mLinkFeatureButton->setToolTip( tr( "Link existing child features" ) );
  mLinkFeatureButton->setObjectName( "mLinkFeatureButton" );
  buttonLayout->addWidget( mLinkFeatureButton );
  // unlink feature
  mUnlinkFeatureButton = new QToolButton( this );
  mUnlinkFeatureButton->setIcon( QgsApplication::getThemeIcon( "/mActionUnlink.svg" ) );
  mUnlinkFeatureButton->setText( tr( "Unlink feature" ) );
  mUnlinkFeatureButton->setToolTip( tr( "Unlink child feature" ) );
  mUnlinkFeatureButton->setObjectName( "mUnlinkFeatureButton" );
  buttonLayout->addWidget( mUnlinkFeatureButton );
  // spacer
  buttonLayout->addItem( new QSpacerItem( 0, 0, QSizePolicy::Expanding ) );
  // form view
  mFormViewButton = new QToolButton( this );
  mFormViewButton->setText( tr( "Form view" ) );
  mFormViewButton->setToolTip( tr( "Switch to form view" ) );
  mFormViewButton->setIcon( QgsApplication::getThemeIcon( "/mActionPropertyItem.png" ) );
  mFormViewButton->setCheckable( true );
  mFormViewButton->setChecked( mViewMode == QgsDualView::AttributeEditor );
  buttonLayout->addWidget( mFormViewButton );
  // table view
  mTableViewButton = new QToolButton( this );
  mTableViewButton->setText( tr( "Table view" ) );
  mTableViewButton->setToolTip( tr( "Switch to table view" ) );
  mTableViewButton->setIcon( QgsApplication::getThemeIcon( "/mActionOpenTable.svg" ) );
  mTableViewButton->setCheckable( true );
  mTableViewButton->setChecked( mViewMode == QgsDualView::AttributeTable );
  buttonLayout->addWidget( mTableViewButton );
  // button group
  mViewModeButtonGroup = new QButtonGroup( this );
  mViewModeButtonGroup->addButton( mFormViewButton, QgsDualView::AttributeEditor );
  mViewModeButtonGroup->addButton( mTableViewButton, QgsDualView::AttributeTable );

  // add buttons layout
  topLayout->addLayout( buttonLayout );

  mRelationLayout = new QGridLayout();
  mRelationLayout->setContentsMargins( 0, 0, 0, 0 );
  topLayout->addLayout( mRelationLayout );

  mDualView = new QgsDualView( this );
  mDualView->setView( mViewMode );
  mFeatureSelectionMgr = new QgsGenericFeatureSelectionManager( mDualView );
  mDualView->setFeatureSelectionManager( mFeatureSelectionMgr );

  mRelationLayout->addWidget( mDualView );

  connect( this, SIGNAL( collapsedStateChanged( bool ) ), this, SLOT( onCollapsedStateChanged( bool ) ) );
  connect( mViewModeButtonGroup, SIGNAL( buttonClicked( int ) ), this, SLOT( setViewMode( int ) ) );
  connect( mToggleEditingButton, SIGNAL( clicked( bool ) ), this, SLOT( toggleEditing( bool ) ) );
  connect( mSaveEditsButton, SIGNAL( clicked() ), this, SLOT( saveEdits() ) );
  connect( mAddFeatureButton, SIGNAL( clicked() ), this, SLOT( addFeature() ) );
  connect( mDeleteFeatureButton, SIGNAL( clicked() ), this, SLOT( deleteFeature() ) );
  connect( mLinkFeatureButton, SIGNAL( clicked() ), this, SLOT( linkFeature() ) );
  connect( mUnlinkFeatureButton, SIGNAL( clicked() ), this, SLOT( unlinkFeature() ) );
  connect( mFeatureSelectionMgr, SIGNAL( selectionChanged( QgsFeatureIds, QgsFeatureIds, bool ) ), this, SLOT( updateButtons() ) );

  // Set initial state for add/remove etc. buttons
  updateButtons();
}