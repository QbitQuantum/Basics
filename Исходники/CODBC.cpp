BOOL CODBCDatabase::Open(CHAR* szDSN,CHAR* szUser, CHAR* szPass)
{
	SQLRETURN ret;
	
	if(m_lConnectionTimeout > 0)
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lConnectionTimeout, 0);
		
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);

	ret = SQLConnectA(m_hDbc, (SQLCHAR *)szDSN, SQL_NTS, (SQLCHAR *)szUser, SQL_NTS, (SQLCHAR *)szPass, SQL_NTS);

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	return m_bIsConnected;
}