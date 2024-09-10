int SSmain(int    argc, 
		SSchar* argv[])
{
	HDBC	hdbc;
	HENV	henv;
	HSTMT	hstmt;
	SQLRETURN  return_code;


	UTLDbUtlProgStart (argc, argv, SSText("log.txt"), DB_PD_DDL_EXPORT_PROCNAME);

	/*1. Connect to DB*/
	connectDB(&henv, &hdbc);

    /* HSTMT   hstmt_session;
    return_code = SQLAllocStmt ((SQLHDBC)hdbc, (SQLHSTMT *)&hstmt_session);
	if (return_code != SQL_SUCCESS)
	{
		printf("ERROR: The SQL statement did not execute successfully.\n");
		exit(1);
	}

   return_code = SQLExecDirect(hstmt_session, SSText("alter session set NLS_LANGUAGE='SIMPLIFIED CHINESE'"), -3);
   SQLFreeStmt(hstmt_session, SQL_DROP);*/

	/*3. Execute the SQL statement*/
	return_code = SQLAllocStmt ((SQLHDBC)hdbc, (SQLHSTMT *)&hstmt);
	if (return_code != SQL_SUCCESS)
	{  
		printf("ERROR: The SQL statement did not execute successfully.\n");
		exit(1);
	}
	
	SSchar*     pFilterStmt =  SSText("INSERT INTO TEST_CLOB_COL VALUES (?)");
	//SSchar*     pFilterStmt =  SSText("INSERT INTO test(LOG_DATA_1) VALUES (?)");
	return_code = SQLPrepare(hstmt, (SSuchar*)(pFilterStmt), SQL_NTS);   
	SSchar clobcol[] = {0x3042,0x3044,0x3046,0x3048,0x304A, 0x0000};
   /* test 1:
	LONG        cbRowId = 10;
	//return_code= SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, 4000, 0, clobcol, sizeof(clobcol), &cbRowId); //This is ok!
	return_code= SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_LONGVARCHAR, 40, 0, clobcol, 10, &cbRowId);
    
	return_code = SQLExecute((SQLHSTMT)hstmt); 
   */

   /*test 2*/
   //test a: LONG cbRowId = SQL_DATA_AT_EXEC;
   LONG cbRowId = SQL_LEN_DATA_AT_EXEC(11);
   return_code= SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_LONGVARCHAR, 40, 0, clobcol, 10, &cbRowId);
   return_code = SQLExecute((SQLHSTMT)hstmt);
   SSchar *buf = clobcol;
   return_code = SQLParamData(hstmt, (SQLPOINTER *)&buf);
   return_code = SQLPutData(hstmt, buf, 10);
   return_code = SQLParamData(hstmt, (SQLPOINTER *)&buf);

	if (return_code == SQL_SUCCESS)
	{
		printf("The SQL statement executed successfully.\n");
	}
	else{
		printf("The SQL statement did not execute successfully.\n");
		ODBC_error ((HENV)henv, (HDBC)hdbc, (HSTMT)hstmt) ;
	}

   SSchar*     pSelectStmt =  SSText("select userenv('language') from dual");
	//SSchar*     pFilterStmt =  SSText("INSERT INTO test(LOG_DATA_1) VALUES (?)");
	return_code = SQLPrepare(hstmt, (SSuchar*)(pSelectStmt), SQL_NTS);

	return_code = SQLExecute((SQLHSTMT)hstmt); 
   

	SQLDisconnect ((SQLHDBC)hdbc);
	SQLFreeConnect ((SQLHDBC)hdbc);
	SQLFreeEnv ((SQLHENV)henv);

	return(return_code);
}