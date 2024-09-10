void classTable::LoadColumns()
{
	SQLHSTMT        hstmt;
	SQLRETURN		nReturn             = -1;
	SQLCHAR         szTableName[101]	= "";
	SQLCHAR         szColumnName[101]	= "";
	SQLCHAR         szColumnType[101]	= "";
	SQLCHAR         szDescription[301]	= "";
	QString         qsError;
    classColumn     *pColumn = NULL;

	// CREATE A STATEMENT
	nReturn = SQLAllocStmt( hDbc, &hstmt );
	if ( nReturn != SQL_SUCCESS )
	{
		QMessageBox::warning( pCanvas, "Data Manager",  "Failed to SQLAllocStmt" );
		return;
	}

	// EXECUTE OUR SQL/CALL
	strcpy( (char *)szTableName, qsName.data() );

	if ( SQL_SUCCESS != (nReturn=SQLColumns( hstmt, 0, 0, 0, 0, szTableName, SQL_NTS, 0, 0 )) )
	{
		QMessageBox::warning( pCanvas, "Data Manager",  "Failed to SQLColumns" );
		return;
	}

	// GET RESULTS
	nReturn = SQLFetch( hstmt );
	while ( nReturn == SQL_SUCCESS || nReturn == SQL_SUCCESS_WITH_INFO )
	{
        szDescription[0] = '\0';

		nReturn = SQLGetData( hstmt, SQLColumns_COLUMN_NAME, SQL_C_CHAR, &szColumnName[0], sizeof(szColumnName), 0 );
		if ( nReturn != SQL_SUCCESS )
			strcpy( (char *)szColumnName, "Unknown" );

		nReturn = SQLGetData( hstmt, SQLColumns_TYPE_NAME, SQL_C_CHAR, &szColumnType[0], sizeof(szColumnType), 0 );

		listColumns.append( pColumn = new classColumn( this, pColumn, pCanvas, hDbc, (char *)szColumnName, (char*)szColumnType, (char*)szDescription ) );

		nReturn = SQLFetch( hstmt );
	}

	// FREE STATEMENT
	nReturn = SQLFreeStmt( hstmt, SQL_DROP );
	if ( nReturn != SQL_SUCCESS )
		QMessageBox::warning( pCanvas, "Data Manager",  "Failed to SQLFreeStmt" );

}