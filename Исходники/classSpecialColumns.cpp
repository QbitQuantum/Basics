void classSpecialColumns::LoadColumns()
{
	SQLHSTMT        hstmt;
	SQLRETURN		nReturn             = -1;
	SQLCHAR         szTableName[101]	= "";
	SQLCHAR         szColumnName[101]	= "";
	QString         qsError;

	// CREATE A STATEMENT
	nReturn = SQLAllocStmt( hDbc, &hstmt );
	if ( nReturn != SQL_SUCCESS )
	{
		QMessageBox::warning( pCanvas, "Data Manager",  "Failed to SQLAllocStmt" );
		return;
	}

	// EXECUTE OUR SQL/CALL
	strcpy( (char *)szTableName, qsTable.data() );

	if ( SQL_SUCCESS != (nReturn=SQLSpecialColumns( hstmt, SQL_BEST_ROWID, 0, 0, 0, 0, szTableName, SQL_NTS, SQL_SCOPE_SESSION, SQL_NULLABLE )) )
	{
		QMessageBox::warning( pCanvas, "Data Manager",  "Failed to SQLSpecialColumns" );
		return;
	}

	// GET RESULTS
	nReturn = SQLFetch( hstmt );
	while ( nReturn == SQL_SUCCESS || nReturn == SQL_SUCCESS_WITH_INFO )
	{
		nReturn = SQLGetData( hstmt, 2, SQL_C_CHAR, &szColumnName[0], sizeof(szColumnName), 0 );
		if ( nReturn != SQL_SUCCESS )
			strcpy( (char *)szColumnName, "Unknown" );

		listColumns.append( new classColumn( this, pCanvas, hDbc, (char *)szColumnName ) );

		nReturn = SQLFetch( hstmt );
	}

	// FREE STATEMENT
	nReturn = SQLFreeStmt( hstmt, SQL_DROP );
	if ( nReturn != SQL_SUCCESS )
		QMessageBox::warning( pCanvas, "Data Manager",  "Failed to SQLFreeStmt" );

}