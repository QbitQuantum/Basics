// -------------------------------------------------------------------------------------
SQLRETURN  SQL_API SQLAllocHandle(SQLSMALLINT HandleType,
																	SQLHANDLE InputHandle, 
																	_Out_ SQLHANDLE *OutputHandle)
{
	AQ_ODBC_LOG("%s called\n", __FUNCTION__);

	switch ( HandleType ) 
	{
	case SQL_HANDLE_ENV:
		return SQLAllocEnv ( OutputHandle );

	case SQL_HANDLE_DBC:
		return SQLAllocConnect ( InputHandle, OutputHandle );

	case SQL_HANDLE_STMT:
		return SQLAllocStmt ( InputHandle, OutputHandle );

	case SQL_HANDLE_DESC:
		AQ_ODBC_LOG("SQLAllocHandle - Explicit descriptor requested - not supported\n");
		return SQL_SUCCESS;
	}
	
	return SQL_ERROR;
}