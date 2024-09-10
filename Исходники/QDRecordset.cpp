bool 
QDRecordset::Open(const char* szSqlStr)
{
	SQLRETURN ret;
	
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER)SQL_SCROLLABLE, SQL_IS_INTEGER);
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_DYNAMIC, SQL_IS_INTEGER);
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_ROWS_FETCHED_PTR, &m_nNumRowsFetched, 0);
	ret = SQLExecDirect(m_hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);

	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		ret = SQLFetch(m_hStmt);

		if(ret==SQL_NO_DATA_FOUND)
			return FALSE;
		else
			return TRUE;
	}
	else
	{
		return FALSE;
	}
}