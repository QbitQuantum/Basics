static SQLRETURN doSql(SQLHENV henv, SQLHDBC hdbc, SQLHSTMT shdl, SQLCHAR sql[])
{
	SQLRETURN rc;

	btlogger_debug("doSql %s\n", sql);
	rc = SQLPrepare(shdl, sql, SQL_NTS);
	CHECK_HANDLE(SQL_HANDLE_STMT, shdl, rc, "SQLPrepare", sql);
	
	SQLExecDirect(shdl, sql, SQL_NTS);
	CHECK_HANDLE(SQL_HANDLE_STMT, shdl, rc, "SQLExecDirect", sql);

	return SQL_SUCCESS;
}