void QgsDelimitedTextSourceSelect::updateFieldLists()
{
  // Update the x and y field dropdown boxes
  QgsDebugMsg( "Updating field lists" );

  disconnect( cmbXField, SIGNAL( currentIndexChanged( int ) ), this, SLOT( enableAccept() ) );
  disconnect( cmbYField, SIGNAL( currentIndexChanged( int ) ), this, SLOT( enableAccept() ) );
  disconnect( cmbWktField, SIGNAL( currentIndexChanged( int ) ), this, SLOT( enableAccept() ) );
  disconnect( geomTypeXY, SIGNAL( toggled( bool ) ), cmbXField, SLOT( setEnabled( bool ) ) );
  disconnect( geomTypeXY, SIGNAL( toggled( bool ) ), cmbYField, SLOT( setEnabled( bool ) ) );
  disconnect( geomTypeXY, SIGNAL( toggled( bool ) ), cmbWktField, SLOT( setDisabled( bool ) ) );

  QString columnX = cmbXField->currentText();
  QString columnY = cmbYField->currentText();
  QString columnWkt = cmbWktField->currentText();

  // clear the field lists
  cmbXField->clear();
  cmbYField->clear();
  cmbWktField->clear();

  geomTypeXY->setEnabled( false );
  geomTypeWKT->setEnabled( false );
  cmbXField->setEnabled( false );
  cmbYField->setEnabled( false );
  cmbWktField->setEnabled( false );

  // clear the sample text box
  tblSample->clear();

  if ( ! haveValidFileAndDelimiters() )
    return;

  QFile file( txtFilePath->text() );
  if ( !file.open( QIODevice::ReadOnly ) )
    return;

  int skipLines = rowCounter->value();

  QTextStream stream( &file );
  QString line;
  do
  {
    line = QgsDelimitedTextProvider::readLine( &stream ); // line of text excluding '\n'
  }
  while ( !line.isEmpty() && skipLines-- > 0 );

  QgsDebugMsg( QString( "Attempting to split the input line: %1 using delimiter %2" ).arg( line ).arg( txtDelimiter->text() ) );

  QStringList fieldList = splitLine( line );

  QgsDebugMsg( QString( "Split line into %1 parts" ).arg( fieldList.size() ) );

  // We don't know anything about a text based field other
  // than its name. All fields are assumed to be text
  bool haveFields = false;

  foreach ( QString field, fieldList )
  {
    if (( field.left( 1 ) == "'" || field.left( 1 ) == "\"" ) &&
        field.left( 1 ) == field.right( 1 ) )
      // eat quotes
      field = field.mid( 1, field.length() - 2 );

    if ( field.length() == 0 )
      // skip empty field names
      continue;

    cmbXField->addItem( field );
    cmbYField->addItem( field );
    cmbWktField->addItem( field );
    haveFields = true;
  }

  int indexWkt = -1;
  if ( ! columnWkt.isEmpty() )
  {
    indexWkt = cmbWktField->findText( columnWkt );
  }
  if ( indexWkt < 0 )
  {
    indexWkt = cmbWktField->findText( "wkt", Qt::MatchContains );
  }
  if ( indexWkt < 0 )
  {
    indexWkt = cmbWktField->findText( "geometry", Qt::MatchContains );
  }
  if ( indexWkt < 0 )
  {
    indexWkt = cmbWktField->findText( "shape", Qt::MatchContains );
  }
  cmbWktField->setCurrentIndex( indexWkt );

  int indexX = -1;
  if ( !columnX.isEmpty() )
  {
    indexX = cmbXField->findText( columnX );
  }

  if ( indexX < 0 )
  {
    indexX = cmbXField->findText( "lon", Qt::MatchContains );
  }

  if ( indexX < 0 )
  {
    indexX = cmbXField->findText( "x", Qt::MatchContains );
  }

  cmbXField->setCurrentIndex( indexX );

  int indexY = -1;
  if ( !columnY.isEmpty() )
  {
    indexY = cmbYField->findText( columnY );
  }

  if ( indexY < 0 )
  {
    indexY = cmbYField->findText( "lat", Qt::MatchContains );
  }

  if ( indexY < 0 )
  {
    indexY = cmbYField->findText( "y", Qt::MatchContains );
  }

  cmbYField->setCurrentIndex( indexY );


  bool isXY = ( geomTypeXY->isChecked() && indexX >= 0 && indexY >= 0 ) || indexWkt < 0;

  geomTypeXY->setChecked( isXY );
  geomTypeWKT->setChecked( ! isXY );

  if ( haveFields )
  {
    geomTypeXY->setEnabled( true );
    geomTypeWKT->setEnabled( true );
    cmbXField->setEnabled( isXY );
    cmbYField->setEnabled( isXY );
    cmbWktField->setEnabled( !  isXY );

    connect( cmbXField, SIGNAL( currentIndexChanged( int ) ), this, SLOT( enableAccept() ) );
    connect( cmbYField, SIGNAL( currentIndexChanged( int ) ), this, SLOT( enableAccept() ) );
    connect( cmbWktField, SIGNAL( currentIndexChanged( int ) ), this, SLOT( enableAccept() ) );
    connect( geomTypeXY, SIGNAL( toggled( bool ) ), cmbXField, SLOT( setEnabled( bool ) ) );
    connect( geomTypeXY, SIGNAL( toggled( bool ) ), cmbYField, SLOT( setEnabled( bool ) ) );
    connect( geomTypeXY, SIGNAL( toggled( bool ) ), cmbWktField, SLOT( setDisabled( bool ) ) );
  }

  tblSample->setColumnCount( fieldList.size() );
  tblSample->setHorizontalHeaderLabels( fieldList );

  // put a few more lines into the sample box
  int counter = 0;
  line = QgsDelimitedTextProvider::readLine( &stream );
  while ( !line.isEmpty() && counter < 20 )
  {
    QStringList values = splitLine( line );

    tblSample->setRowCount( counter + 1 );

    for ( int i = 0; i < tblSample->columnCount(); i++ )
    {
      QString value = i < values.size() ? values[i] : "";
      bool ok = true;
      if ( i == indexX || i == indexY )
      {
        if ( !decimalPoint->text().isEmpty() )
        {
          value.replace( decimalPoint->text(), "." );
        }

        value.toDouble( &ok );
      }
      QTableWidgetItem *item = new QTableWidgetItem( value );
      if ( !ok )
        item->setTextColor( Qt::red );
      tblSample->setItem( counter, i, item );
    }

    counter++;
    line = QgsDelimitedTextProvider::readLine( &stream );
  }
  // close the file
  file.close();

  // put a default layer name in the text entry
  QFileInfo finfo( txtFilePath->text() );
  txtLayerName->setText( finfo.completeBaseName() );
}