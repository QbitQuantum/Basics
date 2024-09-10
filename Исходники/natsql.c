/*
---------------------------------------------------------
   TestSQLNativeSql
---------------------------------------------------------
*/
PassFail TestSQLNativeSql(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;
	RETCODE		returncode;
 	SQLHANDLE 	henv;
 	SQLHANDLE 	hdbc;
 	SQLHANDLE	hstmt;
	CHAR		*szSqlStrIn[3];
	CHAR		szSqlStrOut[SQLSTR_LEN];
	SDWORD	pcbSqlStr;
   
//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars("SQLNativeSql", charset_file);
	if (var_list == NULL) return FAILED;

	//print_list(var_list);
	szSqlStrIn[0] = var_mapping("SQLNativeSql_szSqlStrIn_1", var_list);
	szSqlStrIn[1] = var_mapping("SQLNativeSql_szSqlStrIn_2", var_list);
	szSqlStrIn[2] = var_mapping("SQLNativeSql_szSqlStrIn_3", var_list);
//===========================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API =>SQLNativeSql | SQLNativeSQL | natsql.c\n");

	TEST_INIT;

	returncode=FullConnect(pTestInfo);
   if (pTestInfo->hdbc == (SQLHANDLE)NULL)
	{
		TEST_FAILED;
		TEST_RETURN;
	}

	henv = pTestInfo->henv;
 	hdbc = pTestInfo->hdbc;
 	hstmt = (SQLHANDLE)pTestInfo->hstmt;
	returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt);	
	if (returncode == SQL_SUCCESS)
	{
	//==================================================================================================

		TESTCASE_BEGIN("Test the positive functionality of SQLNativeSql with null terminated string\n");
		returncode = SQLNativeSql((SQLHANDLE)hdbc, (SQLCHAR*)szSqlStrIn[0], SQL_NTS, (SQLCHAR*)szSqlStrOut, SQLSTR_LEN, &pcbSqlStr); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNativeSql"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		if (strcmp(szSqlStrOut,szSqlStrIn[0]) == 0)
		{
			LogMsg(NONE,"expect: %s and actual: %s are matched\n", szSqlStrIn[0], szSqlStrOut);
		}	
		else
		{
			TEST_FAILED;	
			LogMsg(NONE,"expect: %s and actual: %s are not matched\n", szSqlStrIn[0], szSqlStrOut);
		}
		TESTCASE_END;

		//==================================================================================================

		TESTCASE_BEGIN("Test the positive functionality of SQLNativeSql with string length as input\n");
		returncode = SQLNativeSql((SQLHANDLE)hdbc, (SQLCHAR*)szSqlStrIn[1], strlen(szSqlStrIn[1]), (SQLCHAR*)szSqlStrOut, SQLSTR_LEN, &pcbSqlStr); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNativeSql"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		if (strcmp(szSqlStrOut,szSqlStrIn[1]) == 0)
		{
			LogMsg(NONE,"expect: %s and actual: %s are matched\n", szSqlStrIn[1], szSqlStrOut);
		}	
		else
		{
			TEST_FAILED;	
			LogMsg(NONE,"expect: %s and actual: %s are not matched\n", szSqlStrIn[1], szSqlStrOut);
		}
		TESTCASE_END;

		//==================================================================================================
		TESTCASE_BEGIN("Test the positive functionality of SQLNativeSql with max length same as string length\n");
		returncode = SQLNativeSql((SQLHANDLE)hdbc, (SQLCHAR*)szSqlStrIn[2], strlen(szSqlStrIn[2]), (SQLCHAR*)szSqlStrOut, strlen(szSqlStrIn[2])+1, &pcbSqlStr); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNativeSql"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		if (strcmp(szSqlStrOut,szSqlStrIn[2]) == 0)
		{
			LogMsg(NONE,"expect: %s and actual: %s are matched\n", szSqlStrIn[2], szSqlStrOut);
		}	
		else
		{
			TEST_FAILED;	
			LogMsg(NONE,"expect: %s and actual: %s are not matched\n", szSqlStrIn[2], szSqlStrOut);
		}
		TESTCASE_END;
	}
//==================================================================================================

	FullDisconnect(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => SQLNativeSql.\n");
	free_list(var_list);
	TEST_RETURN;
}