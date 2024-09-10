/**
@SYMTestCaseID          SYSLIB-DBMS-CT-0645
@SYMTestCaseDesc        Searching for data from a database
@SYMTestPriority        Medium
@SYMTestActions         Tests for EDbColText,EDbColLongText column type
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
static void TestSearchL( TInt aIndex )
	{
	// Default database
	_LIT( KComposer1, "Elgar" );
	_LIT( KCol1, "Artist" );
	_LIT( KCol2, "Notes" );
	_LIT( KTable, "CDs" );

	TInt err = TheFsSession.Delete( KSearchTestDbPath );
	if ( ( err != KErrNone ) && ( err != KErrNotFound ) && ( err != KErrPathNotFound ) )
		{
		__LEAVE( err );
		}

	RDbNamedDatabase db;
	CleanupClosePushL( db );
	__LEAVE_IF_ERROR( db.Create( TheFsSession, KSearchTestDbPath ) );

	//
	// Create the database table
	//
	// Create a table definition
	CDbColSet* columns = CDbColSet::NewLC();
	// add the columns
	columns->AddL( TDbCol( KCol1, EDbColText ) );
	if ( aIndex == 0 )
		columns->AddL( TDbCol( KCol2, EDbColText ) );
	else
		columns->AddL( TDbCol( KCol2, EDbColLongText ) );
	// if the column is of type "EDbColText" instead,
	// all searching is working properly
	// Create a table
	__LEAVE_IF_ERROR( db.CreateTable( KTable, *columns ) );
	// cleanup the column set
	CleanupStack::PopAndDestroy( columns );

	//
	// Add data
	//
	// create a view on the database
	_LIT( KSQLStatement, "select Artist,Notes from CDs order by Artist" );
	RDbView view;
	__LEAVE_IF_ERROR( view.Prepare( db, TDbQuery( KSQLStatement, EDbCompareNormal ) ) );
	__LEAVE_IF_ERROR( view.EvaluateAll() );

	// Get the structure of rowset
	CDbColSet* colSet = view.ColSetL();
	// insert a row
	view.InsertL();
	view.SetColL( colSet->ColNo( KCol1 ), KComposer1 ); // Artist
	// Use the stream
	// RDbColWriteStream out;
	// TDbColNo col = colSet->ColNo( KCol2 ); // Ordinal position of long column
	//
	// out.OpenLC( view, col );
	// out.WriteL( _L( "Some additional comment here." ) );
	// out.Close();
	//
	// CleanupStack::PopAndDestroy(); // out
	view.SetColL( colSet->ColNo( KCol2 ), _L( "Some additional comment here." ) );
	view.PutL();
	// close the view
	view.Close();
	delete colSet;

	//
	// Display the data
	//
	_LIT( KRowFormatter, "\r\n Artist: %S \r\n Notes: %S \r\n" );
	__LEAVE_IF_ERROR( view.Prepare( db, TDbQuery( KSQLStatement, EDbCompareNormal ) ) );
	__LEAVE_IF_ERROR( view.EvaluateAll() );

	// Get the structure of the rowset
	colSet = view.ColSetL();
	// iterate across the row set
	for ( view.FirstL(); view.AtRow(); view.NextL() )
		{
		// retrieve the row
		view.GetL();
		// while the rowset is on this row, can use a TPtrC to
		// refer to any text columns
		TPtrC artist = view.ColDes( colSet->ColNo( KCol1 ) );
		// and a stream for long columns
		RDbColReadStream in;
		TDbColNo col = colSet->ColNo( KCol2 ); // Ordinal position of long column
		TBuf<256> notes; // Buffer for out notes
		in.OpenLC( view, col );
		in.ReadL( notes, view.ColLength( col ) );
		in.Close();
		CleanupStack::PopAndDestroy(); // in
		// Display the artist and notes
		TBuf<512> msg;
		msg.Format( KRowFormatter, &artist, &notes );
		TheTest.Printf( msg );
		}
	// close the view
	view.Close();
	delete colSet;

	//
	// Search for the data
	//
	TInt result;
	result = SearchForL( _L( "Some*" ), db ); // matches
	TEST(result == 1);
	result = SearchForL( _L( "some*" ), db ); // defect causes no match, should match
	TEST(result == 1);
	result = SearchForL( _L( "*some*" ), db ); // matches
	TEST(result == 1);
	result = SearchForL( _L( "s?me*" ), db ); // matches
	TEST(result == 1);
	result = SearchForL( _L( "Some additional comment here." ), db ); // matches
	TEST(result == 1);
	result = SearchForL( _L( "some additional comment here." ), db ); // defect causes no match, should match
	TEST(result == 1);

	CleanupStack::PopAndDestroy( &db );
	}