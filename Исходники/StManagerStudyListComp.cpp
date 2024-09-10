unsigned StManagerStudyListComp::getSeriesIndex( const SerieInfoVector info )
{
  // no resize, just exit button - reject, result code is 0 -> returned value will be 0
  QDialog *seriesSelectorDialog = new QDialog( this, Qt::WindowTitleHint | Qt::WindowSystemMenuHint| Qt::MSWindowsFixedSizeDialogHint );
  seriesSelectorDialog->setWindowTitle( tr( "Series Selector" ) );

  QVBoxLayout *mainLayout = new QVBoxLayout;

  QLabel *seriesLabel = new QLabel( tr( "Series in selected study:\n(their descriptions)" ) );
  mainLayout->addWidget( seriesLabel );

  QSpacerItem *verticalSpacer = new QSpacerItem( 2, 10, QSizePolicy::Minimum, 
                                                 QSizePolicy::Minimum );
  mainLayout->addItem( verticalSpacer );

  QTableWidget *seriesTable = createSeriesSelectionTable();
  seriesTable->setRowCount( info.size() );
  for ( unsigned i = 0; i < info.size(); i++ ) {
    seriesTable->setItem( i, 0, new QTableWidgetItem( QString( info[i].description.c_str() ) ) );
  }
  connect( seriesTable, SIGNAL(cellClicked( int, int )), seriesSelectorDialog, SLOT(done( int )) );
  mainLayout->addWidget( seriesTable );

  seriesSelectorDialog->setLayout( mainLayout );

  return seriesSelectorDialog->exec();
}