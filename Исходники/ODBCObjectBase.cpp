bool CODBCObjectBase::Refresh_Error_Status( SQLRETURN error_code )
{
	FATAL_ASSERT( EnvironmentHandle != 0 );

	Errors.clear();
	BadRowNumber = -1;

	if ( error_code == SQL_SUCCESS )
	{
		ErrorState = DBEST_SUCCESS;
		return true;
	}
	else if ( error_code == SQL_INVALID_HANDLE )
	{
		ErrorState = DBEST_FATAL_ERROR;
		return true;
	}

	SQLSMALLINT handle_type = SQL_HANDLE_ENV;
	SQLHANDLE handle = EnvironmentHandle;
	if ( StatementHandle != 0 )
	{
		handle_type = SQL_HANDLE_STMT;
		handle = StatementHandle;
	}
	else if ( ConnectionHandle != 0 )
	{
		handle_type = SQL_HANDLE_DBC;
		handle = ConnectionHandle;
	}

	SQLINTEGER record_count = 0;
	SQLRETURN ec = SQLGetDiagField( handle_type, handle, 0, SQL_DIAG_NUMBER, &record_count, SQL_IS_INTEGER, NULL );
	FATAL_ASSERT( ec == SQL_SUCCESS );

	SQLWCHAR sql_state[ 6 ] = { 0 };
	SQLINTEGER sql_error_code = 0;
	SQLSMALLINT text_length = 0;
	SQLWCHAR error_buffer[ 1024 ] = { 0 };

	for ( SQLSMALLINT i = 1; i <= record_count; ++i )
	{
		ec = SQLGetDiagRec( handle_type, handle, i, sql_state, &sql_error_code, error_buffer, sizeof( error_buffer ) / sizeof( SQLWCHAR ), &text_length );
		FATAL_ASSERT( ec == SQL_SUCCESS );

		Errors.push_back( SODBCError( sql_error_code, sql_state, std::wstring( error_buffer ) ) );

		if ( handle_type == SQL_HANDLE_STMT && BadRowNumber == -1 )
		{
			SQLLEN bad_row = 0;
			ec = SQLGetDiagField( handle_type, handle, i, SQL_DIAG_ROW_NUMBER, &bad_row, SQL_IS_INTEGER, NULL );
			FATAL_ASSERT( ec == SQL_SUCCESS );

			if ( bad_row >= 1 )
			{
				BadRowNumber = static_cast< int32_t >( bad_row - 1 );
			}
		}
	}

	return false;
}