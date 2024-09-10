DatabaseODBC::DatabaseODBC()
{
	m_connected = false;

	char* dns = new char[SQL_MAX_DSN_LENGTH];
	char* user = new char[32];
	char* pass = new char[32];

	strcpy((char*)dns, g_config.getString(ConfigManager::SQL_DB).c_str());
	strcpy((char*)user, g_config.getString(ConfigManager::SQL_USER).c_str());
	strcpy((char*)pass, g_config.getString(ConfigManager::SQL_PASS).c_str());

	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_env);
	if(!RETURN_SUCCESS(ret)){
		std::cout << "Failed to allocate ODBC SQLHENV enviroment handle." << std::endl;
		m_env = NULL;
		return;
	}

	ret = SQLSetEnvAttr(m_env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	if(!RETURN_SUCCESS(ret)){
		std::cout << "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION): Failed to switch to ODBC 3 version." << std::endl;
		SQLFreeHandle(SQL_HANDLE_ENV, m_env);
		m_env = NULL;
	}

	if(m_env == NULL){
		std::cout << "ODBC SQLHENV enviroment not initialized." << std::endl;
		return;
	}

	ret = SQLAllocHandle(SQL_HANDLE_DBC, m_env, &m_handle);
	if(!RETURN_SUCCESS(ret)){
		std::cout << "Failed to allocate ODBC SQLHDBC connection handle." << std::endl;
		m_handle = NULL;
		return;
	}

	ret = SQLSetConnectAttr(m_handle, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER*)5, 0);
	if(!RETURN_SUCCESS(ret)){
		std::cout << "SQLSetConnectAttr(SQL_ATTR_CONNECTION_TIMEOUT): Failed to set connection timeout." << std::endl;
		SQLFreeHandle(SQL_HANDLE_DBC, m_handle);
		m_handle = NULL;
		return;
	}

	ret = SQLConnect(m_handle, (SQLCHAR*)dns, SQL_NTS, (SQLCHAR*)user, SQL_NTS, (SQLCHAR*)pass, SQL_NTS);
	if(!RETURN_SUCCESS(ret)){
		std::cout << "Failed to connect to ODBC via DSN: " << dns << " (user " << user << ")" << std::endl;
		SQLFreeHandle(SQL_HANDLE_DBC, m_handle);
		m_handle = NULL;
		return;
	}

	m_connected = true;
}