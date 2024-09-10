void OptionsWindow::createTableModel( QString data )
{
	//vytvorenie polozky tabulky
	model = new QStandardItemModel( 0, 2 );
	model->setHeaderData( 0, Qt::Horizontal, QObject::tr( "Attribute" ) );
	model->setHeaderData( 1, Qt::Horizontal, QObject::tr( "Value" ) );

	// rozdelenie dat
	QList<QString> rows = data.split( ";" );

	//postupne sa vytvaraju riadky tabulky
	for ( int i=0; i< rows.length(); i++ ) {
		QList<QString> row = rows[i].split( "," );

		model->insertRow( i );
		model->setData( model->index( i, 0 ), row[0] );
		model->setData( model->index( i, 1 ), row[1] );
		model->item( i,0 )->setFlags( Qt::NoItemFlags );
	}

	view->setVisible( true );
	view->setModel( model );
}