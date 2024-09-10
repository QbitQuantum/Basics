/*
---------------------------------------------------------
   TestSQLDataSources
	No negative tests since this functionality is done at
	driver manager level.
---------------------------------------------------------
*/
PassFail TestSQLDataSources(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;
	RETCODE		returncode;
 	SQLHANDLE 	henv;
	char		szDSN[DSRC_LEN], szDESC[DSRC_LEN];
	SWORD		cbDSN, pcbDESC;

 	LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => SQLDataSources | SQLDataSources | datasrc.c\n");

  TEST_INIT;

	//==========================================================================================
	   
  TESTCASE_BEGIN("Test the positive functionality of SQLDataSources\n");
 	returncode = SQLAllocEnv(&henv);                 /* Environment handle */
	if (returncode == SQL_SUCCESS)
	{
		returncode = SQLDataSources(henv, SQL_FETCH_FIRST, (SQLCHAR*)szDSN, DSRC_LEN, &cbDSN, (SQLCHAR*)szDESC, DSRC_LEN, &pcbDESC); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLDataSources"))
		{
			TEST_FAILED;
			LogMsg(ERRMSG,"Test SQLDataSources => SQL_FETCH_FIRST #1 failed.\n");
		}
		while (returncode == SQL_SUCCESS)
		{
			returncode = SQLDataSources(henv, SQL_FETCH_NEXT, (SQLCHAR*)szDSN, DSRC_LEN, &cbDSN, (SQLCHAR*)szDESC, DSRC_LEN, &pcbDESC); 
			if((returncode != SQL_SUCCESS) && (returncode != SQL_NO_DATA_FOUND))
			{
				TEST_FAILED;
				LogMsg(ERRMSG,"Test SQLDataSources => SQL_FETCH_NEXT failed.\n");
			}
		}
		returncode = SQLDataSources(henv, SQL_FETCH_FIRST, (SQLCHAR*)szDSN, DSRC_LEN, &cbDSN, (SQLCHAR*)szDESC, DSRC_LEN, &pcbDESC); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLDataSources"))
		{
			TEST_FAILED;
			LogMsg(ERRMSG,"Test SQLDataSources => SQL_FETCH_FIRST #2 failed.\n");
		}
	}
	SQLFreeEnv(henv);
   TESTCASE_END;

	//==========================================================================================
      
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => SQLDataSources.\n");
   TEST_RETURN;
}