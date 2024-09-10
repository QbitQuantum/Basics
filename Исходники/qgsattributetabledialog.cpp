QgsAttributeTableDialog::QgsAttributeTableDialog( QgsVectorLayer *layer, QgsAttributeTableFilterModel::FilterMode initialMode, QWidget *parent, Qt::WindowFlags flags )
  : QDialog( parent, flags )
  , mLayer( layer )

{
  setObjectName( QStringLiteral( "QgsAttributeTableDialog/" ) + layer->id() );
  setupUi( this );
  connect( mActionCutSelectedRows, &QAction::triggered, this, &QgsAttributeTableDialog::mActionCutSelectedRows_triggered );
  connect( mActionCopySelectedRows, &QAction::triggered, this, &QgsAttributeTableDialog::mActionCopySelectedRows_triggered );
  connect( mActionPasteFeatures, &QAction::triggered, this, &QgsAttributeTableDialog::mActionPasteFeatures_triggered );
  connect( mActionToggleEditing, &QAction::toggled, this, &QgsAttributeTableDialog::mActionToggleEditing_toggled );
  connect( mActionSaveEdits, &QAction::triggered, this, &QgsAttributeTableDialog::mActionSaveEdits_triggered );
  connect( mActionReload, &QAction::triggered, this, &QgsAttributeTableDialog::mActionReload_triggered );
  connect( mActionInvertSelection, &QAction::triggered, this, &QgsAttributeTableDialog::mActionInvertSelection_triggered );
  connect( mActionRemoveSelection, &QAction::triggered, this, &QgsAttributeTableDialog::mActionRemoveSelection_triggered );
  connect( mActionSelectAll, &QAction::triggered, this, &QgsAttributeTableDialog::mActionSelectAll_triggered );
  connect( mActionZoomMapToSelectedRows, &QAction::triggered, this, &QgsAttributeTableDialog::mActionZoomMapToSelectedRows_triggered );
  connect( mActionPanMapToSelectedRows, &QAction::triggered, this, &QgsAttributeTableDialog::mActionPanMapToSelectedRows_triggered );
  connect( mActionSelectedToTop, &QAction::toggled, this, &QgsAttributeTableDialog::mActionSelectedToTop_toggled );
  connect( mActionAddAttribute, &QAction::triggered, this, &QgsAttributeTableDialog::mActionAddAttribute_triggered );
  connect( mActionRemoveAttribute, &QAction::triggered, this, &QgsAttributeTableDialog::mActionRemoveAttribute_triggered );
  connect( mActionOpenFieldCalculator, &QAction::triggered, this, &QgsAttributeTableDialog::mActionOpenFieldCalculator_triggered );
  connect( mActionDeleteSelected, &QAction::triggered, this, &QgsAttributeTableDialog::mActionDeleteSelected_triggered );
  connect( mMainView, &QgsDualView::currentChanged, this, &QgsAttributeTableDialog::mMainView_currentChanged );
  connect( mActionAddFeature, &QAction::triggered, this, &QgsAttributeTableDialog::mActionAddFeature_triggered );
  connect( mActionExpressionSelect, &QAction::triggered, this, &QgsAttributeTableDialog::mActionExpressionSelect_triggered );
  connect( mMainView, &QgsDualView::showContextMenuExternally, this, &QgsAttributeTableDialog::showContextMenu );

  const QgsFields fields = mLayer->fields();
  for ( const QgsField &field : fields )
  {
    mVisibleFields.append( field.name() );
  }

  // Fix selection color on losing focus (Windows)
  setStyleSheet( QgisApp::instance()->styleSheet() );

  setAttribute( Qt::WA_DeleteOnClose );

  layout()->setMargin( 0 );
  layout()->setContentsMargins( 0, 0, 0, 0 );
  static_cast< QGridLayout * >( layout() )->setVerticalSpacing( 0 );

  QgsSettings settings;

  int size = settings.value( QStringLiteral( "/qgis/iconSize" ), 16 ).toInt();
  if ( size > 32 )
  {
    size -= 16;
  }
  else if ( size == 32 )
  {
    size = 24;
  }
  else
  {
    size = 16;
  }
  mToolbar->setIconSize( QSize( size, size ) );

  // Initialize the window geometry
  restoreGeometry( settings.value( QStringLiteral( "Windows/BetterAttributeTable/geometry" ) ).toByteArray() );

  myDa = new QgsDistanceArea();

  myDa->setSourceCrs( mLayer->crs(), QgsProject::instance()->transformContext() );
  myDa->setEllipsoid( QgsProject::instance()->ellipsoid() );

  mEditorContext.setDistanceArea( *myDa );
  mEditorContext.setVectorLayerTools( QgisApp::instance()->vectorLayerTools() );
  mEditorContext.setMapCanvas( QgisApp::instance()->mapCanvas() );

  QgsFeatureRequest r;
  bool needsGeom = false;
  if ( mLayer->geometryType() != QgsWkbTypes::NullGeometry &&
       initialMode == QgsAttributeTableFilterModel::ShowVisible )
  {
    QgsMapCanvas *mc = QgisApp::instance()->mapCanvas();
    QgsRectangle extent( mc->mapSettings().mapToLayerCoordinates( layer, mc->extent() ) );
    r.setFilterRect( extent );
    needsGeom = true;
  }
  else if ( initialMode == QgsAttributeTableFilterModel::ShowSelected )
  {
    r.setFilterFids( layer->selectedFeatureIds() );
  }
  if ( !needsGeom )
    r.setFlags( QgsFeatureRequest::NoGeometry );

  // Initialize dual view
  mMainView->init( mLayer, QgisApp::instance()->mapCanvas(), r, mEditorContext, false );

  QgsAttributeTableConfig config = mLayer->attributeTableConfig();
  mMainView->setAttributeTableConfig( config );

  // Initialize filter gui elements
  mFilterActionMapper = new QSignalMapper( this );
  mFilterColumnsMenu = new QMenu( this );
  mActionFilterColumnsMenu->setMenu( mFilterColumnsMenu );
  mApplyFilterButton->setDefaultAction( mActionApplyFilter );

  // Set filter icon in a couple of places
  QIcon filterIcon = QgsApplication::getThemeIcon( "/mActionFilter2.svg" );
  mActionShowAllFilter->setIcon( filterIcon );
  mActionAdvancedFilter->setIcon( filterIcon );
  mActionSelectedFilter->setIcon( filterIcon );
  mActionVisibleFilter->setIcon( filterIcon );
  mActionEditedFilter->setIcon( filterIcon );

  mActionFeatureActions = new QToolButton();
  mActionFeatureActions->setAutoRaise( false );
  mActionFeatureActions->setPopupMode( QToolButton::InstantPopup );
  mActionFeatureActions->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mAction.svg" ) ) );
  mActionFeatureActions->setText( tr( "Actions" ) );
  mActionFeatureActions->setToolTip( tr( "Actions" ) );
  mToolbar->addWidget( mActionFeatureActions );

  // Connect filter signals
  connect( mActionAdvancedFilter, &QAction::triggered, this, &QgsAttributeTableDialog::filterExpressionBuilder );
  connect( mActionShowAllFilter, &QAction::triggered, this, &QgsAttributeTableDialog::filterShowAll );
  connect( mActionSelectedFilter, &QAction::triggered, this, &QgsAttributeTableDialog::filterSelected );
  connect( mActionVisibleFilter, &QAction::triggered, this, &QgsAttributeTableDialog::filterVisible );
  connect( mActionEditedFilter, &QAction::triggered, this, &QgsAttributeTableDialog::filterEdited );
  connect( mFilterActionMapper, SIGNAL( mapped( QObject * ) ), SLOT( filterColumnChanged( QObject * ) ) );
  connect( mFilterQuery, &QLineEdit::returnPressed, this, &QgsAttributeTableDialog::filterQueryAccepted );
  connect( mActionApplyFilter, &QAction::triggered, this, &QgsAttributeTableDialog::filterQueryAccepted );
  connect( mActionSetStyles, &QAction::triggered, this, &QgsAttributeTableDialog::openConditionalStyles );

  // info from layer to table
  connect( mLayer, &QgsVectorLayer::editingStarted, this, &QgsAttributeTableDialog::editingToggled );
  connect( mLayer, &QgsVectorLayer::editingStopped, this, &QgsAttributeTableDialog::editingToggled );
  connect( mLayer, &QObject::destroyed, mMainView, &QgsDualView::cancelProgress );
  connect( mLayer, &QgsVectorLayer::selectionChanged, this, &QgsAttributeTableDialog::updateTitle );
  connect( mLayer, &QgsVectorLayer::featureAdded, this, &QgsAttributeTableDialog::updateTitle );
  connect( mLayer, &QgsVectorLayer::featuresDeleted, this, &QgsAttributeTableDialog::updateTitle );
  connect( mLayer, &QgsVectorLayer::editingStopped, this, &QgsAttributeTableDialog::updateTitle );
  connect( mLayer, &QgsVectorLayer::attributeAdded, this, &QgsAttributeTableDialog::columnBoxInit );
  connect( mLayer, &QgsVectorLayer::attributeDeleted, this, &QgsAttributeTableDialog::columnBoxInit );
  connect( mLayer, &QgsVectorLayer::readOnlyChanged, this, &QgsAttributeTableDialog::editingToggled );

  // connect table info to window
  connect( mMainView, &QgsDualView::filterChanged, this, &QgsAttributeTableDialog::updateTitle );
  connect( mMainView, &QgsDualView::filterExpressionSet, this, &QgsAttributeTableDialog::formFilterSet );
  connect( mMainView, &QgsDualView::formModeChanged, this, &QgsAttributeTableDialog::viewModeChanged );

  // info from table to application
  connect( this, &QgsAttributeTableDialog::saveEdits, this, [ = ] { QgisApp::instance()->saveEdits(); } );

  const bool dockTable = settings.value( QStringLiteral( "qgis/dockAttributeTable" ), false ).toBool();
  if ( dockTable )
  {
    mDock = new QgsAttributeTableDock( QString(), QgisApp::instance() );
    mDock->setWidget( this );
    connect( this, &QObject::destroyed, mDock, &QWidget::close );
    QgisApp::instance()->addDockWidget( Qt::BottomDockWidgetArea, mDock );
  }
  mActionDockUndock->setChecked( dockTable );
  connect( mActionDockUndock, &QAction::toggled, this, &QgsAttributeTableDialog::toggleDockMode );
  installEventFilter( this );

  columnBoxInit();
  updateTitle();

  mActionRemoveSelection->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionDeselectAll.svg" ) ) );
  mActionSelectAll->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionSelectAll.svg" ) ) );
  mActionSelectedToTop->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionSelectedToTop.svg" ) ) );
  mActionCopySelectedRows->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionEditCopy.svg" ) ) );
  mActionPasteFeatures->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionEditPaste.svg" ) ) );
  mActionZoomMapToSelectedRows->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionZoomToSelected.svg" ) ) );
  mActionPanMapToSelectedRows->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionPanToSelected.svg" ) ) );
  mActionInvertSelection->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionInvertSelection.svg" ) ) );
  mActionToggleEditing->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionToggleEditing.svg" ) ) );
  mActionSaveEdits->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionSaveEdits.svg" ) ) );
  mActionDeleteSelected->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionDeleteSelected.svg" ) ) );
  mActionOpenFieldCalculator->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionCalculateField.svg" ) ) );
  mActionAddAttribute->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionNewAttribute.svg" ) ) );
  mActionRemoveAttribute->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionDeleteAttribute.svg" ) ) );
  mTableViewButton->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionOpenTable.svg" ) ) );
  mAttributeViewButton->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionFormView.svg" ) ) );
  mActionExpressionSelect->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mIconExpressionSelect.svg" ) ) );
  mActionAddFeature->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mActionNewTableRow.svg" ) ) );
  mActionFeatureActions->setIcon( QgsApplication::getThemeIcon( QStringLiteral( "/mAction.svg" ) ) );

  // toggle editing
  bool canChangeAttributes = mLayer->dataProvider()->capabilities() & QgsVectorDataProvider::ChangeAttributeValues;
  bool canDeleteFeatures = mLayer->dataProvider()->capabilities() & QgsVectorDataProvider::DeleteFeatures;
  bool canAddAttributes = mLayer->dataProvider()->capabilities() & QgsVectorDataProvider::AddAttributes;
  bool canDeleteAttributes = mLayer->dataProvider()->capabilities() & QgsVectorDataProvider::DeleteAttributes;
  bool canAddFeatures = mLayer->dataProvider()->capabilities() & QgsVectorDataProvider::AddFeatures;

  mActionToggleEditing->blockSignals( true );
  mActionToggleEditing->setCheckable( true );
  mActionToggleEditing->setChecked( mLayer->isEditable() );
  mActionToggleEditing->blockSignals( false );

  mActionSaveEdits->setEnabled( mActionToggleEditing->isEnabled() && mLayer->isEditable() );
  mActionReload->setEnabled( ! mLayer->isEditable() );
  mActionAddAttribute->setEnabled( ( canChangeAttributes || canAddAttributes ) && mLayer->isEditable() );
  mActionRemoveAttribute->setEnabled( canDeleteAttributes && mLayer->isEditable() );
  if ( !canDeleteFeatures )
  {
    mToolbar->removeAction( mActionDeleteSelected );
    mToolbar->removeAction( mActionCutSelectedRows );
  }
  mActionAddFeature->setEnabled( canAddFeatures && mLayer->isEditable() );
  mActionPasteFeatures->setEnabled( canAddFeatures && mLayer->isEditable() );
  if ( !canAddFeatures )
  {
    mToolbar->removeAction( mActionAddFeature );
    mToolbar->removeAction( mActionPasteFeatures );
  }

  mMainViewButtonGroup->setId( mTableViewButton, QgsDualView::AttributeTable );
  mMainViewButtonGroup->setId( mAttributeViewButton, QgsDualView::AttributeEditor );

  switch ( initialMode )
  {
    case QgsAttributeTableFilterModel::ShowVisible:
      filterVisible();
      break;

    case QgsAttributeTableFilterModel::ShowSelected:
      filterSelected();
      break;

    case QgsAttributeTableFilterModel::ShowAll:
    default:
      filterShowAll();
      break;
  }

  // Layer might have been destroyed while loading!
  if ( mLayer )
  {
    mUpdateExpressionText->registerExpressionContextGenerator( this );
    mFieldCombo->setFilters( QgsFieldProxyModel::AllTypes | QgsFieldProxyModel::HideReadOnly );
    mFieldCombo->setLayer( mLayer );

    connect( mRunFieldCalc, &QAbstractButton::clicked, this, &QgsAttributeTableDialog::updateFieldFromExpression );
    connect( mRunFieldCalcSelected, &QAbstractButton::clicked, this, &QgsAttributeTableDialog::updateFieldFromExpressionSelected );
    // NW TODO Fix in 2.6 - Doesn't work with field model for some reason.
    //  connect( mUpdateExpressionText, SIGNAL( returnPressed() ), this, SLOT( updateFieldFromExpression() ) );
    connect( mUpdateExpressionText, static_cast < void ( QgsFieldExpressionWidget::* )( const QString &, bool ) > ( &QgsFieldExpressionWidget::fieldChanged ), this, &QgsAttributeTableDialog::updateButtonStatus );
    mUpdateExpressionText->setLayer( mLayer );
    mUpdateExpressionText->setLeftHandButtonStyle( true );

    int initialView = settings.value( QStringLiteral( "qgis/attributeTableView" ), -1 ).toInt();
    if ( initialView < 0 )
    {
      initialView = settings.value( QStringLiteral( "qgis/attributeTableLastView" ), QgsDualView::AttributeTable ).toInt();
    }
    mMainView->setView( static_cast< QgsDualView::ViewMode >( initialView ) );
    mMainViewButtonGroup->button( initialView )->setChecked( true );

    connect( mActionToggleMultiEdit, &QAction::toggled, mMainView, &QgsDualView::setMultiEditEnabled );
    connect( mActionSearchForm, &QAction::toggled, mMainView, &QgsDualView::toggleSearchMode );
    updateMultiEditButtonState();

    if ( mLayer->editFormConfig().layout() == QgsEditFormConfig::UiFileLayout )
    {
      //not supported with custom UI
      mActionToggleMultiEdit->setEnabled( false );
      mActionToggleMultiEdit->setToolTip( tr( "Multiedit is not supported when using custom UI forms" ) );
      mActionSearchForm->setEnabled( false );
      mActionSearchForm->setToolTip( tr( "Search is not supported when using custom UI forms" ) );
    }

    editingToggled();
    // Close and delete if the layer has been destroyed
    connect( mLayer, &QObject::destroyed, this, &QWidget::close );
  }
  else
  {
    QWidget::close();
  }
}