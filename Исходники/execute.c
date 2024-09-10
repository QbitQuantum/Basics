/*
---------------------------------------------------------
   TestSQLExecute
---------------------------------------------------------
*/
PassFail TestSQLExecute(TestInfo *pTestInfo, int MX_MP_SPECIFIC)
{                  
	TEST_DECLARE;

 	RETCODE			returncode;
 	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt;
	TCHAR			*ExecStr[15];
	TCHAR			*szInput[] = {_T("Inst char"),_T("Inst vchar"),_T("1234.56789"),_T("1234.56789"),_T("1200"),_T("12000"),_T("123.45"),_T("123.45"),_T("123.45"),_T("1993-07-01"),_T("09:45:30"),_T("1993-08-02 08:44:31.001"),_T("120000"),_T("1234567890.56789"),_T("1234567890.456789"),_T("1234567890.456789"),_T("0.01234567890123456789"),_T("1234.56789"),_T("1234567890.56789"),_T("12345678901234567890.0123456789"),_T("Inst char"),_T("Inst vchar")};
	SQLLEN			cbInput = SQL_NTS;
	SQLUSMALLINT	i = 0;
	SQLSMALLINT		Type[] = {SQL_WCHAR,SQL_WVARCHAR,SQL_DECIMAL,SQL_NUMERIC,SQL_SMALLINT,SQL_INTEGER,SQL_REAL,SQL_FLOAT,SQL_DOUBLE,SQL_DATE,SQL_TIME,SQL_TIMESTAMP,SQL_BIGINT,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_WCHAR,SQL_WVARCHAR};
	SQLUINTEGER		ColPrec[] = {254,254,10,10,5,10,7,15,15,10,8,26,19,19,19,128,128,10,18,30,254,254};
	SQLSMALLINT		ColScale[]= {0,0,5,5,0,0,0,0,0,0,0,0,0,0,6,0,128,5,5,10,0,0};
	short			CCharOutput1,CCharOutput2;
	SQLLEN			OutputLen1,OutputLen2;
	int				actual_insert=0,num_insert=0;
	SWORD			param = 0;

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars(_T("SQLExecute"), charset_file);
	if (var_list == NULL) return FAILED;

	//print_list(var_list);
	ExecStr[0] = var_mapping(_T("SQLExecute_ExecStr_0"), var_list);
	ExecStr[1] = var_mapping(_T("SQLExecute_ExecStr_1"), var_list);
	ExecStr[2] = var_mapping(_T("SQLExecute_ExecStr_2"), var_list);
	ExecStr[3] = var_mapping(_T("SQLExecute_ExecStr_3"), var_list);

	ExecStr[4] = var_mapping(_T("SQLExecute_ExecStr_4"), var_list);
	ExecStr[5] = var_mapping(_T("SQLExecute_ExecStr_5"), var_list);
	ExecStr[6] = var_mapping(_T("SQLExecute_ExecStr_6"), var_list); 
	ExecStr[7] = var_mapping(_T("SQLExecute_ExecStr_7"), var_list);
	ExecStr[8] = var_mapping(_T("SQLExecute_ExecStr_8"), var_list);
	ExecStr[9] = var_mapping(_T("SQLExecute_ExecStr_9"), var_list);
	ExecStr[10] = var_mapping(_T("SQLExecute_ExecStr_10"), var_list);
	ExecStr[11] = var_mapping(_T("SQLExecute_ExecStr_11"), var_list);
	ExecStr[12] = var_mapping(_T("SQLExecute_ExecStr_12"), var_list);
	ExecStr[13] = var_mapping(_T("SQLExecute_ExecStr_13"), var_list);
	ExecStr[14] = var_mapping(_T("SQLExecute_ExecStr_14"), var_list);

//=================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing API => SQLExecute.\n"));

	TEST_INIT;

	TESTCASE_BEGIN("Setup for SQLExecute tests\n");

	if(!FullConnect(pTestInfo)){
		LogMsg(NONE,_T("Unable to connect\n"));
		TEST_FAILED;
		TEST_RETURN;
	}

	henv = pTestInfo->henv;
 	hdbc = pTestInfo->hdbc;
 	hstmt = (SQLHANDLE)pTestInfo->hstmt;
   	
	returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt);	
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
		}

	returncode=SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[4],SQL_NTS);

	returncode=SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[5],SQL_NTS); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
		}

	returncode=SQLExecDirect(hstmt,(SQLTCHAR *)ExecStr[6],SQL_NTS); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
		}

	returncode=SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[7],SQL_NTS); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
		}
	returncode=SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[8],SQL_NTS); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
		}

	TESTCASE_END;  // end of setup

	TESTCASE_BEGIN("Test #1: Positive Functionality of SQLExecute\n");

	returncode = SQLPrepare(hstmt,(SQLTCHAR *)ExecStr[9],SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLExecute(hstmt); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLBindCol(hstmt,1,SQL_C_SHORT,&CCharOutput1,0,&OutputLen1);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLBindCol(hstmt,2,SQL_C_SHORT,&CCharOutput2,0,&OutputLen2);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	while (returncode != SQL_NO_DATA_FOUND)
	{
		returncode = SQLFetch(hstmt);
		if (returncode != SQL_NO_DATA_FOUND)
		{
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt);
			}
		}
	}
	SQLFreeStmt(hstmt,SQL_CLOSE);
	returncode = SQLPrepare(hstmt,(SQLTCHAR *)ExecStr[10],SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLExecute(hstmt); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	SQLFreeStmt(hstmt,SQL_CLOSE);
	SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[4],SQL_NTS); 
	TESTCASE_END;

	TESTCASE_BEGIN("Test #2: Positive Functionality of SQLExecute\n");
	returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[0],_tcslen(ExecStr[0])); /* cleanup */

	returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[1],_tcslen(ExecStr[1]));
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLExecute(hstmt); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}
	TESTCASE_END;
	
	TESTCASE_BEGIN("Test #3: Positive Functionality of SQLExecute with SQL_NTS\n");
	returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[2],SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLExecute(hstmt); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}
	TESTCASE_END;

	TESTCASE_BEGIN("Test #4: Positive Functionality of SQLPrepare then SQLExecute twice\n");
	returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[2],_tcslen(ExecStr[2]));
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLExecute(hstmt); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	returncode = SQLExecute(hstmt); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}

	TESTCASE_END;

	SQLFreeStmt(hstmt,SQL_CLOSE);
	SQLFreeStmt(hstmt,SQL_UNBIND);
	SQLFreeStmt(hstmt,SQL_RESET_PARAMS);
		
	TESTCASE_BEGIN("Test #5: Positive Functionality of SQLExecute with params\n");
	returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[3],SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}
	else{
		for (i = 0; i <= 3; i++){
			    
			if (i==0) Type[0] = 1;	
			returncode = SQLBindParameter(hstmt,(SWORD)(i+1),SQL_PARAM_INPUT,SQL_C_TCHAR,Type[i],EXEC_LEN,0,szInput[i],0,&cbInput);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter")){
				LogMsg(NONE,_T("Type[i]: %d  \n"),Type[i]);
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				}
			
			}
		returncode = SQLExecute(hstmt); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			}
		}
	TESTCASE_END;
		
	TESTCASE_BEGIN("Test #6: Negative Functionality of SQLExecute with less params\n");
	returncode = SQLFreeStmt(hstmt,SQL_DROP);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeStmt")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}
	else{
		returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt")){
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			}
		else{
			returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[3],SQL_NTS);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				}
			else{
				returncode = SQLBindParameter(hstmt,1,SQL_PARAM_INPUT,SQL_C_TCHAR,Type[0],EXEC_LEN,0,szInput[0],0,&cbInput);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter")){
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
					}
				else{
					returncode = SQLExecute(hstmt); 
					if(!CHECKRC(SQL_ERROR,returncode,"SQLExecute")){
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
						}
					}
				}	
			}
		}
	TESTCASE_END;

	TESTCASE_BEGIN("Test #7: Negative Functionality of SQLExecute with not prepared stmt\n");
	returncode = SQLFreeStmt(hstmt,SQL_DROP);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeStmt")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}
	else{
		returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt")){
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			}
		else{
			returncode = SQLExecute(hstmt);
			if(!CHECKRC(SQL_ERROR,returncode,"SQLExecute")){
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				}
			}
		}
	TESTCASE_END;

	TESTCASE_BEGIN("Test #8: Negative Functionality of SQLExecute with invalid handle\n");
	returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[2],_tcslen(ExecStr[2]));
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")){
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		}
	else{
		returncode = SQLExecute((SQLHANDLE)NULL); 
		if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLExecute")){
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			}
		}
	TESTCASE_END;

	returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[0],_tcslen(ExecStr[0])); /* cleanup */
 
	TESTCASE_BEGIN("Test #9: Stress Positive Functionality of SQLExecute.\n");
	returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[11],SQL_NTS);

	returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[12],SQL_NTS); 
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	else
	{
		returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[13],SQL_NTS); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		else
		{
			actual_insert = 0;
			for (num_insert = 0; num_insert < MAX_INSERTED_ROWS; num_insert++)
			{
				returncode = SQLExecute(hstmt);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt);
				}
				else
					actual_insert++;
			}
			if (actual_insert != MAX_INSERTED_ROWS)
			{
				TEST_FAILED;
				LogMsg(ERRMSG,_T("failed to insert rows actual => %d & excepted => %d.\n"),actual_insert,MAX_INSERTED_ROWS);
			}
		}
	}

	SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[11],SQL_NTS); 
	TESTCASE_END;
 
	TESTCASE_BEGIN("Test #10: Stress Positive Functionality of SQLExecute with Params.\n");
	returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[11],SQL_NTS); 

	returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[12],SQL_NTS); 
	LogMsg(NONE,_T("ExecStr[12]: %s\n"), ExecStr[12]);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	else
	{
		returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[14],SQL_NTS); 
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		else
		{
			actual_insert = 0;
			returncode = SQLNumParams(hstmt, &param);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNumParams"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			for (num_insert = 0; num_insert < MAX_INSERTED_ROWS; num_insert++)
			{
				for (i = 0; i < param; i++)
				{
					if (i==0) Type[0] = 1;

					if (MX_MP_SPECIFIC == MX_SPECIFIC)
					{
						returncode = SQLBindParameter(hstmt,(SWORD)(i+1),SQL_PARAM_INPUT,SQL_C_TCHAR,Type[i],ColPrec[i],ColScale[i],szInput[i],0,&cbInput);
					}
					else
					{
						returncode = SQLBindParameter(hstmt,(SWORD)(i+1),SQL_PARAM_INPUT,SQL_C_TCHAR,Type[i],ColPrec[i],ColScale[i],szInput[i],300,&cbInput);
					}
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
				}
				returncode = SQLExecute(hstmt);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt);
				}
				else
					actual_insert++;
			}
			if (actual_insert != MAX_INSERTED_ROWS)
			{
				TEST_FAILED;
				LogMsg(ERRMSG,_T("failed to insert rows actual => %d & excepted => %d.\n"),actual_insert,MAX_INSERTED_ROWS);
			}
		}
	}

	SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[11],SQL_NTS); 
	TESTCASE_END;

	TESTCASE_BEGIN("Test #11: Negative Functionality of SQLExecute with already existing table\n");
	returncode = SQLFreeStmt(hstmt,SQL_DROP);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeStmt"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
	}
	else
	{
		returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
		}
		else
		{
			SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[0],_tcslen(ExecStr[0])); /* cleanup */
			returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecStr[1],_tcslen(ExecStr[1]));
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			else
			{
				returncode = SQLExecute(hstmt); 
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				else
				{
					returncode = SQLExecute(hstmt); 
					if(!CHECKRC(SQL_ERROR,returncode,"SQLExecute"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
				}
			}
			SQLExecDirect(hstmt,(SQLTCHAR*)ExecStr[0],_tcslen(ExecStr[0])); /* cleanup */
		}
	}
	TESTCASE_END;

//=================================================================================================
	
	FullDisconnect(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing API => SQLExecute.\n"));
	free_list(var_list);
	TEST_RETURN;
}