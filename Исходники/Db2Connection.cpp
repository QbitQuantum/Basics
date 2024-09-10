bool CDb2Connection::CommitTrans()
{
	m_lasterror = SQLEndTran(SQL_HANDLE_DBC,m_hDbc,SQL_COMMIT);

	if(!SQL_SUCCEEDED(m_lasterror))
		return false;

	m_lasterror = SQLSetConnectAttr(m_hDbc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_ON,0);
	if(!SQL_SUCCEEDED(m_lasterror))
		return false;

	return true;
}