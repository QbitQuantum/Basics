	EErrorType CDatabaseStatementOdbc::DoInitialise()
	{
		DatabaseConnectionOdbcSPtr connection = DoGetConnectionOdbc();

		if ( !connection )
		{
			DB_EXCEPT( EDatabaseExceptionCodes_StatementError, ERROR_ODBC_LOST_CONNECTION );
		}

		EErrorType errorType;
		HDBC hParentStmt = connection->GetHdbc();
		CLogger::LogDebug( ( Format( DEBUG_ODBC_PREPARING_STATEMENT ) % this ).str() );

		errorType = SqlSuccess( SQLAllocHandle( SQL_HANDLE_STMT, hParentStmt, &_statementHandle ), SQL_HANDLE_STMT, hParentStmt, INFO_ODBC_AllocHandle );
#if defined( _WIN32 )

		if ( errorType == EErrorType_NONE )
		{
			OdbcCheck( SQLSetStmtAttr( _statementHandle, SQL_SOPT_SS_DEFER_PREPARE, SQL_DP_OFF, SQL_IS_UINTEGER ), SQL_HANDLE_STMT, _statementHandle, INFO_ODBC_SetStmtAttr );
		}

#endif

		if ( errorType == EErrorType_NONE )
		{
			OdbcCheck( SQLPrepareA( _statementHandle, ( SqlChar * )_query.c_str(), SQLINTEGER( _query.size() ) ), SQL_HANDLE_STMT, _statementHandle, INFO_ODBC_Prepare );
		}

		if ( errorType == EErrorType_NONE )
		{
			SQLSMALLINT count = 0;
			OdbcCheck( SQLNumParams( _statementHandle, &count ), SQL_HANDLE_STMT, _statementHandle, INFO_ODBC_NumParams );
			CLogger::LogDebug( DEBUG_ODBC_EXPECTED_PARAMETERS + StringUtils::ToString( count ) );
		}

		for ( auto && parameter : DoGetParameters() )
		{
			std::static_pointer_cast< CDatabaseStatementParameterOdbc >( parameter )->Initialise( _statementHandle );
		}

		return errorType;
	}