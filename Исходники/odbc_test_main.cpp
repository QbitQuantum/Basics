int test_fun_odbc_api_Mysql__DBPOOL_DYN()
{
	int nFunRes = 0;

	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	// Drop and re-create a Msorcl10.dll (version 1.0) data source.
	SQLConfigDataSource(NULL, ODBC_ADD_DSN, "MySQL ODBC 5.2 Unicode Driver",
		"DSN=Mysql12343DYN;UID=IT271350_5;PWD=IT271350_5;SERVER=192.168.123.43;DATABASE=tra_occ");


	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	////http://support.microsoft.com/kb/164221/en-us

	////http://www.informixchina.net/club/thread-5924-1-1.html

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}
	// set the ODBC behavior version.
	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	if (!SQL_SUCCEEDED(retcode))  
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	// make process level cursor pooling
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_CONNECTION_POOLING,	(SQLPOINTER)SQL_CP_ONE_PER_DRIVER, SQL_IS_UINTEGER);
	if (!SQL_SUCCEEDED(retcode)) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}




	//set the matching condition for using an existing connection in the pool
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_CP_MATCH, (SQLPOINTER)SQL_CP_RELAXED_MATCH, 0);//SQL_IS_INTEGER
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLSetEnvAttr/SQL_ATTR_CP_MATCH error\n");
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	int nIndex = 0;
	while (nIndex < 10) 
	{
		/* Allocate connection handle */
		retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLAllocHandle error\n");
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}



		/* Set login timeout to 5 seconds. */
		//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

		/* Connect to data source */
		retcode = SQLConnect(m_hDatabaseConnection, 
			(SQLCHAR*) "Mysql12343DYN", SQL_NTS,
			(SQLCHAR*) "IT271350_5", SQL_NTS,
			(SQLCHAR*) "IT271350_5", SQL_NTS);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLConnect error\n");
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}
		else
		{
			printf("Connect successfully %d times\n", nIndex);
		}


		//////////////////////////////////////////////////////////////////////////

		/* Allocate statement handle */
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		{
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}

		retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}


		/* get return data Row count */
		SQLINTEGER l_siIdCount = 0;
		retcode = SQLRowCount(m_hStatement, &l_siIdCount);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}

		while (true)
		{
			//fecth data use SQLFetch() return SQL_SUCCESS  then no data
			retcode = SQLFetch(m_hStatement);
			if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
			{
				break;
			}

			SQLINTEGER l_siID;
			SQLINTEGER l_siIDLength = 0;

			retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
			if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
			{
				break;
			}
		}//while (true)


		//the first time, the application calls SQLDisconenct, it will return
		//the connection to the //pool
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);

		//////////////////////////////////////////////////////////////////////////

		nIndex++;
	}//while (nIndex < 10) 

	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);


	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	return nFunRes;
}