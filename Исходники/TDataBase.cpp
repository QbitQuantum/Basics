bool CDataBase::Connect(const char * szHost, const char * szDataBase, const char * szUser, const char * szPassword)
{
	bool bReturn						= false;
	int	iRecored						= 1;
    SQLSMALLINT cbOutCon				= 0;
	// ----
	SQLCHAR InCon[255]					= {0};
	SQLCHAR OutCon[255]					= {0};
	SQLWCHAR szSQLState[MAX_DB_TEXT_LEN]	= {0};
	SQLWCHAR szSQLMsg[MAX_DB_TEXT_LEN]		= {0};
	// ----
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, & m_hDbc);
	// ----
	wsprintf((char *)InCon, "DRIVER=SQL Server;Server=%s;DATABASE=%s;UID=%s;PWD=%s;", szHost,
		szDataBase, szUser, szPassword);
	// ----
	OnMessage((char *)InCon);
	// ----
	m_Return = SQLDriverConnect(m_hDbc, NULL, InCon, sizeof(InCon), OutCon,
		sizeof(OutCon), & cbOutCon, SQL_DRIVER_NOPROMPT);
	// ----
	if((m_Return == SQL_SUCCESS) || (m_Return == SQL_SUCCESS_WITH_INFO))
	{
		m_Return = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, & m_hStmt);
		// ----
		if((m_Return == SQL_SUCCESS) || (m_Return == SQL_SUCCESS_WITH_INFO))
		{
			m_strHost = szHost;
			m_strDataBase = szDataBase;
			m_strUser = szUser;
			m_strPassword = szPassword;
			// ----
			bReturn  = true;
		}
		else
		{
			m_hStmt = 0;
		}
	}
	// ----
	return bReturn;
}