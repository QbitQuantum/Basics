CDBConnection::CDBConnection()
{
    RETCODE rc;
    hdbc = SQL_NULL_HDBC;
    rc = SQLAllocConnect (henv, &hdbc);
    if (rc != SQL_SUCCESS)
    {
	ReportODBCError (SQL_NULL_HSTMT, "SQLAllocConnect error");
	throw rc;
    }
    rc = SQLConnect (hdbc, (SQLCHAR *)szDSN, SQL_NTS, (SQLCHAR *)szUID, SQL_NTS,
	(SQLCHAR *)szPWD, SQL_NTS);
    if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
    {
	ReportODBCError (SQL_NULL_HSTMT, "SQLConnect error");
	SQLFreeConnect (hdbc);
	hdbc = SQL_NULL_HDBC;
	throw rc;
    }
}