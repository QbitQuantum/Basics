QgsGeometryCheckerSetupTab::QgsGeometryCheckerSetupTab( QgisInterface *iface, QDialog *checkerDialog, QWidget *parent )
  : QWidget( parent )
  , mIface( iface )
  , mCheckerDialog( checkerDialog )

{
  ui.setupUi( this );
  ui.progressBar->hide();
  ui.labelStatus->hide();
  mRunButton = ui.buttonBox->addButton( tr( "Run" ), QDialogButtonBox::ActionRole );
  mAbortButton = new QPushButton( tr( "Abort" ) );
  mRunButton->setEnabled( false );

  const auto drivers = QgsVectorFileWriter::ogrDriverList( QgsVectorFileWriter::SortRecommended | QgsVectorFileWriter::SkipNonSpatialFormats );
  for ( const QgsVectorFileWriter::DriverDetails &driver : drivers )
  {
    ui.comboBoxOutputFormat->addItem( driver.longName, driver.driverName );
  }
  ui.listWidgetInputLayers->setIconSize( QSize( 16, 16 ) );

  ui.lineEditFilenamePrefix->setText( QSettings().value( "/geometry_checker/previous_values/filename_prefix", tr( "checked_" ) ).toString() );

  connect( mRunButton, &QAbstractButton::clicked, this, &QgsGeometryCheckerSetupTab::runChecks );
  connect( ui.listWidgetInputLayers, &QListWidget::itemChanged, this, &QgsGeometryCheckerSetupTab::validateInput );
  connect( QgsProject::instance(), &QgsProject::layersAdded, this, &QgsGeometryCheckerSetupTab::updateLayers );
  connect( QgsProject::instance(), static_cast<void ( QgsProject::* )( const QStringList & )>( &QgsProject::layersRemoved ), this, &QgsGeometryCheckerSetupTab::updateLayers );
  connect( ui.radioButtonOutputNew, &QAbstractButton::toggled, ui.frameOutput, &QWidget::setEnabled );
  connect( ui.buttonGroupOutput, static_cast<void ( QButtonGroup::* )( int )>( &QButtonGroup::buttonClicked ), this, &QgsGeometryCheckerSetupTab::validateInput );
  connect( ui.pushButtonOutputDirectory, &QAbstractButton::clicked, this, &QgsGeometryCheckerSetupTab::selectOutputDirectory );
  connect( ui.lineEditOutputDirectory, &QLineEdit::textChanged, this, &QgsGeometryCheckerSetupTab::validateInput );
  connect( ui.checkBoxSliverPolygons, &QAbstractButton::toggled, ui.widgetSliverThreshold, &QWidget::setEnabled );
  connect( ui.checkBoxSliverArea, &QAbstractButton::toggled, ui.doubleSpinBoxSliverArea, &QWidget::setEnabled );
  connect( ui.checkLineLayerIntersection, &QAbstractButton::toggled, ui.comboLineLayerIntersection, &QComboBox::setEnabled );
  connect( ui.checkBoxFollowBoundaries, &QAbstractButton::toggled, ui.comboBoxFollowBoundaries, &QComboBox::setEnabled );

  for ( const QgsGeometryCheckFactory *factory : QgsGeometryCheckFactoryRegistry::getCheckFactories() )
  {
    factory->restorePrevious( ui );
  }
  updateLayers();
}