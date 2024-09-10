bool OdbcOutput::Write( const mr_utils::mr_string& str ) {
#if defined (_WIN32)
	mr_utils::mr_exception::assertCondition(this->m_odbcEnv != SQL_NULL_HENV, _FL_, _L_("No DB Connection"));

	SQLHSTMT stmt;
	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, this->m_odbcHdbc, &stmt); 

	mr_utils::mr_exception::assertCondition( 
		ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO, 
		_FL_, 
		_L_("Failed to allocate ODBC statement handle") 
	);


	ret = SQLExecDirect(stmt, const_cast<SQLTCHAR*>(str.c_str()), SQL_NTS);

	if (ret == SQL_ERROR) {
		//assert(ret == SQL_SUCCESS);
		SQLTCHAR    buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR    sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER	sqlcode;
		SQLSMALLINT length;
  
		while (SQLError(this->m_odbcEnv, this->m_odbcHdbc, stmt, sqlstate, &sqlcode, buffer,
						 SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS) {
			mr_cout << std::endl << L("**** ERROR *****") << std::endl;
			mr_cout << L("SQLSTATE:") << sqlstate << std::endl;
			mr_cout << L("Native Error Code:") << sqlcode << std::endl;
			mr_cout << buffer << std::endl;
		};
	}

	/// @todo if SQL_SUCCESS_WITH_INFO or SQL_ERROR we can get the error info before closing handle.
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);

	return ret == SQL_SUCCESS;
#else
    return false;
#endif
}