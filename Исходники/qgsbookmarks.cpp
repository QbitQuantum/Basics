QgsBookmarks::QgsBookmarks( QWidget *parent, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
  setupUi( this );
  restorePosition();

  //
  // Create the zoomto and delete buttons and add them to the
  // toolbar
  //
  QPushButton *btnAdd    = new QPushButton( tr( "&Add" ) );
  QPushButton *btnDelete = new QPushButton( tr( "&Delete" ) );
  QPushButton *btnZoomTo = new QPushButton( tr( "&Zoom to" ) );
  QPushButton *btnImpExp = new QPushButton( tr( "&Share" ) );

  btnZoomTo->setDefault( true );
  buttonBox->addButton( btnAdd, QDialogButtonBox::ActionRole );
  buttonBox->addButton( btnDelete, QDialogButtonBox::ActionRole );
  buttonBox->addButton( btnZoomTo, QDialogButtonBox::ActionRole );
  buttonBox->addButton( btnImpExp, QDialogButtonBox::ActionRole );

  QMenu *share = new QMenu();
  QAction *btnExport = share->addAction( tr( "&Export" ) );
  QAction *btnImport = share->addAction( tr( "&Import" ) );
  connect( btnExport, SIGNAL( triggered() ), this, SLOT( exportToXML() ) );
  connect( btnImport, SIGNAL( triggered() ), this, SLOT( importFromXML() ) );
  btnImpExp->setMenu( share );

  connect( btnAdd, SIGNAL( clicked() ), this, SLOT( addClicked() ) );
  connect( btnDelete, SIGNAL( clicked() ), this, SLOT( deleteClicked() ) );
  connect( btnZoomTo, SIGNAL( clicked() ), this, SLOT( zoomToBookmark() ) );

  // open the database
  QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE", "bookmarks" );
  db.setDatabaseName( QgsApplication::qgisUserDbFilePath() );
  if ( !db.open() )
  {
    QMessageBox::warning( this, tr( "Error" ),
                          tr( "Unable to open bookmarks database.\nDatabase: %1\nDriver: %2\nDatabase: %3" )
                          .arg( QgsApplication::qgisUserDbFilePath() )
                          .arg( db.lastError().driverText() )
                          .arg( db.lastError().databaseText() )
                        );
    deleteLater();
    return;
  }

  QSqlTableModel *model = new QSqlTableModel( this, db );
  model->setTable( "tbl_bookmarks" );
  model->setSort( 0, Qt::AscendingOrder );
  model->setEditStrategy( QSqlTableModel::OnFieldChange );
  model->select();

  // set better headers then column names from table
  model->setHeaderData( 0, Qt::Horizontal, tr( "ID" ) );
  model->setHeaderData( 1, Qt::Horizontal, tr( "Name" ) );
  model->setHeaderData( 2, Qt::Horizontal, tr( "Project" ) );
  model->setHeaderData( 3, Qt::Horizontal, tr( "xMin" ) );
  model->setHeaderData( 4, Qt::Horizontal, tr( "yMin" ) );
  model->setHeaderData( 5, Qt::Horizontal, tr( "xMax" ) );
  model->setHeaderData( 6, Qt::Horizontal, tr( "yMax" ) );
  model->setHeaderData( 7, Qt::Horizontal, tr( "SRID" ) );

  lstBookmarks->setModel( model );

  QSettings settings;
  lstBookmarks->header()->restoreState( settings.value( "/Windows/Bookmarks/headerstate" ).toByteArray() );

#ifndef QGISDEBUG
  lstBookmarks->setColumnHidden( 0, true );
#endif
}