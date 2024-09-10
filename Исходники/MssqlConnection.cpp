bool CMssqlConnection::Open()
{
	CMssqlConnectionInformation *pCI = static_cast<CMssqlConnectionInformation*>(GetConnectionInformation());

	m_lasterror = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&m_hEnv);
	if(!SQL_SUCCEEDED(m_lasterror))
		return false;

	m_lasterror = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	if(!SQL_SUCCEEDED(m_lasterror))
		return false;

	m_lasterror = SQLAllocHandle(SQL_HANDLE_DBC,m_hEnv,&m_hDbc);
	if(!SQL_SUCCEEDED(m_lasterror))
		return false;

	cvs::wstring strConn;
	cvs::swprintf(strConn,80,L"DATABASE={%s};DRIVER={SQL Server};Pwd={%s};Server={%s};Uid={%s};",
		(const wchar_t*)cvs::wide(pCI->database.c_str()),(const wchar_t*)cvs::wide(pCI->password.c_str()),(const wchar_t*)cvs::wide(pCI->hostname.c_str()),(const wchar_t*)cvs::wide(pCI->username.c_str()));
	m_lasterror = SQLDriverConnect(m_hDbc,NULL,(SQLWCHAR*)strConn.c_str(),(SQLSMALLINT)strConn.size(),NULL,0,NULL,SQL_DRIVER_NOPROMPT);
	if(!SQL_SUCCEEDED(m_lasterror))
		return false;

	m_lasterror = SQLSetConnectAttr(m_hDbc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_ON,0);
	if(!SQL_SUCCEEDED(m_lasterror))
		return false;

	return true;
}