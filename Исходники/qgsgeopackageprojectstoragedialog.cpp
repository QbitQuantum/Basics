QgsGeoPackageProjectStorageDialog::QgsGeoPackageProjectStorageDialog( bool saving, QWidget *parent )
  : QDialog( parent )
  , mSaving( saving )
{
  setupUi( this );

  connect( buttonBox, &QDialogButtonBox::accepted, this, &QgsGeoPackageProjectStorageDialog::onOK );

  QPushButton *btnManageProjects = new QPushButton( tr( "Manage Projects" ), this );
  QMenu *menuManageProjects = new QMenu( btnManageProjects );
  mActionRemoveProject = menuManageProjects->addAction( tr( "Remove Project" ) );
  connect( mActionRemoveProject, &QAction::triggered, this, &QgsGeoPackageProjectStorageDialog::removeProject );
  btnManageProjects->setMenu( menuManageProjects );
  buttonBox->addButton( btnManageProjects, QDialogButtonBox::ActionRole );
  mFileWidget->lineEdit()->hide();
  mFileWidget->setFilter( QgsVectorFileWriter::filterForDriver( QStringLiteral( "GPKG" ) ) );

  connect( mFileWidget, &QgsFileWidget::fileChanged, [ = ]( const QString & path )
  {
    const QString fileName{QFileInfo( path ).fileName()};
    if ( mCboConnection->findData( path ) == -1 )
    {
      mCboConnection->addItem( QFileInfo( path ).fileName(), path );
      mCboConnection->setItemData( mCboConnection->findText( fileName ), path, Qt::ItemDataRole::ToolTipRole );
    }
    mCboConnection->setCurrentIndex( mCboConnection->findText( fileName ) );
  } );

  if ( saving )
  {
    setWindowTitle( tr( "Save project to GeoPackage" ) );
    mCboProject->setEditable( true );
  }
  else
  {
    setWindowTitle( tr( "Load project from GeoPackage" ) );
  }

  // populate connections
  const auto &connList { QgsOgrDbConnection::connectionList( QStringLiteral( "GPKG" ) ) };
  for ( const auto &connName : connList )
  {
    QgsOgrDbConnection conn { connName, QStringLiteral( "GPKG" ) };
    mCboConnection->addItem( connName, conn.path() );
    mCboConnection->setItemData( mCboConnection->findText( connName ), conn.path(), Qt::ItemDataRole::ToolTipRole );
  }

  connect( mCboProject, qgis::overload<int>::of( &QComboBox::currentIndexChanged ), this, &QgsGeoPackageProjectStorageDialog::projectChanged );
  connect( mCboConnection, qgis::overload<int>::of( &QComboBox::currentIndexChanged ), this, &QgsGeoPackageProjectStorageDialog::populateProjects );

  // If possible, set the item currently displayed database
  QString toSelect = QgsOgrDbConnection::selectedConnection( QStringLiteral( "GPKG" ) );
  mCboConnection->setCurrentIndex( mCboConnection->findText( toSelect ) );

}