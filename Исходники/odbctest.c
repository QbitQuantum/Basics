RETCODE ODBC_connect(                   /* Perform Driver Connection    */
					 HENV henv,         /* ODBC Environment Handle      */
					 HDBC hdbc,         /* ODBC Connection Handle       */
					 UCHAR *driver,     /* Data Source Name             */
					 UCHAR *uid,        /* User ID                      */
					 UCHAR *pwd)        /* User Password                */
{
	RETCODE rc;
	int     retries;
	
#if defined(TRACING)
	rc = SQLSetConnectOption (hdbc, SQL_OPT_TRACE, 1);
	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
		return (rc);
#endif
		/*
		** try connecting up to 3 times
    */
	printf("\nPlease wait . . .\n");
	printf("Establishing a connection to '%s' . . .\n", driver);
	for (retries = 1; retries <= 3; retries++) 
	{
		printf("Attempt connecting %d of 3 . . .\n", retries );
		rc = SQLConnect (hdbc, driver, SQL_NTS, uid, SQL_NTS, pwd, SQL_NTS);
		if ((rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO))
		{
			printf("Successfully, connected to '%s'.\n", driver);
			return (rc);
		}
		else 
		{
			printf("Unable to establish a connection to '%s'.\n", driver);
			ODBC_getErrorInfo (henv, hdbc, SQL_NULL_HSTMT);
			if(retries < 3)
				printf("Retrying connect . . .\n");
		}
	}
	/*
	** Attempt to obtain a meaningful error as to why connect failed.
	*/
	printf("No connection could be established.\n");
	ODBC_getErrorInfo(henv, hdbc, SQL_NULL_HSTMT);
	return (SQL_INVALID_HANDLE);
}