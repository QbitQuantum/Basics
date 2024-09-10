/*
---------------------------------------------------------
   TestSQLTransact
---------------------------------------------------------
*/
PassFail TestSQLTransact(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;
	RETCODE			returncode;
	TCHAR			Heading[MAX_STRING_SIZE];
	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt;
	TCHAR			*ExecDirStr[6];
	UWORD			fType[] = { SQL_ROLLBACK,SQL_COMMIT };
	TCHAR			*TypeDesc[] = { _T("SQL_ROLLBACK"),_T("SQL_COMMIT") };
	TCHAR			*Output;
	SQLLEN			OutputLen;
	struct
	{
		SWORD	ExeRes[2];
		SWORD	FetchRes[2];
		TCHAR	*DataRes[2];
	} CheckRes[] =	
		{
			{SQL_ERROR,SQL_SUCCESS,SQL_NO_DATA_FOUND,SQL_NO_DATA_FOUND,_T(""),_T("")},
			{SQL_SUCCESS,SQL_SUCCESS,SQL_NO_DATA_FOUND,SQL_SUCCESS,_T(""),_T("--")},
			{SQL_SUCCESS,SQL_SUCCESS,SQL_SUCCESS,SQL_SUCCESS,_T("--"),_T("--")},
			{SQL_SUCCESS,SQL_SUCCESS,SQL_SUCCESS,SQL_NO_DATA_FOUND,_T("--"),_T("")},
			{SQL_SUCCESS,SQL_ERROR,SQL_NO_DATA_FOUND,SQL_NO_DATA_FOUND,_T(""),_T("")}
		};
	int	i = 0, j = 0, iend = 5, jend = 1, commit_on_off = 0;

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars(_T("SQLTransact"), charset_file);
	if (var_list == NULL) return FAILED;

	ExecDirStr[0] = var_mapping(_T("SQLTransact_ExecDirStr_0"), var_list);
	ExecDirStr[1] = var_mapping(_T("SQLTransact_ExecDirStr_1"), var_list);
	ExecDirStr[2] = var_mapping(_T("SQLTransact_ExecDirStr_2"), var_list);
	ExecDirStr[3] = var_mapping(_T("SQLTransact_ExecDirStr_3"), var_list);
	ExecDirStr[4] = var_mapping(_T("SQLTransact_ExecDirStr_4"), var_list);
	ExecDirStr[5] = var_mapping(_T("SQLTransact_ExecDirStr_5"), var_list);

	CheckRes[1].DataRes[1] = var_mapping(_T("SQLTransact_Insert"), var_list);
	CheckRes[2].DataRes[0] = var_mapping(_T("SQLTransact_Insert"), var_list);
	CheckRes[2].DataRes[1] = var_mapping(_T("SQLTransact_Update"), var_list);
	CheckRes[3].DataRes[0] = var_mapping(_T("SQLTransact_Update"), var_list);

//========================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing API => SQLTransact.\n"));
	TEST_INIT;

	TESTCASE_BEGIN("Initializing SQLTransact test environment\n");
//	
	if(!FullConnect(pTestInfo))
	{
		LogMsg(NONE,_T("Unable to connect\n"));
		TEST_FAILED;
		TEST_RETURN;
	}
	henv = pTestInfo->henv;
 	hdbc = pTestInfo->hdbc;
 	hstmt = (SQLHANDLE)pTestInfo->hstmt;
	returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt);	
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		FullDisconnect(pTestInfo);
		TEST_FAILED;
		TEST_RETURN;
	}
	
	for (commit_on_off = 0; commit_on_off < 10; commit_on_off++)
	{
		returncode = SQLSetConnectOption((SQLHANDLE)hdbc,SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetConnectOption"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			FullDisconnect(pTestInfo);
			TEST_FAILED;
			TEST_RETURN;
		}
		TESTCASE_END;
		SQLExecDirect(hstmt, (SQLTCHAR*)ExecDirStr[4], SQL_NTS); /* CLEANUP */
		for (i = 0; i <= (iend-1); i++)
		{
			_stprintf(Heading,_T("Test Positive Functionality of SQLTransact while Autocommit is ON and executing\n"));
			_tcscat(Heading, ExecDirStr[i]);
			_tcscat(Heading, _T("\n"));
			TESTCASE_BEGINW(Heading);
			
			returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i],SQL_NTS);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
		}
		SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[4],SQL_NTS); /* CLEANUP */
		returncode = SQLSetConnectOption((SQLHANDLE)hdbc,SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_OFF);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetConnectOption"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			FullDisconnect(pTestInfo);
			TEST_FAILED;
			TEST_RETURN;
		}
		TESTCASE_END;
		
		for (i = 0; i <= (iend-1); i++)
		{
			for (j = 0; j <= jend; j++)
			{
				_stprintf(Heading,_T("Test Positive Functionality of SQLTransact while Autocommit is OFF and executing\n"));
				_tcscat(Heading, ExecDirStr[i]);
				_tcscat(Heading, _T(" & "));
				_tcscat(Heading, TypeDesc[j]);
				_tcscat(Heading, _T("\n"));
				TESTCASE_BEGINW(Heading);
				
				//MAY 9, 2014 - TURNING AUTOCOMMIT ON FOR DDLs FOR TRAF, AS DDLs ARE NOT SUPPORTED WITH AUTOCOMMIT OFF
				if (i == 4 || i == 0)
					SQLSetConnectOption((SQLHANDLE)hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
				returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i],SQL_NTS);
				SQLSetConnectOption((SQLHANDLE)hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
				if (!CHECKRC(SQL_SUCCESS, returncode, "SQLExecDirect"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				else
				{
					returncode=SQLTransact((SQLHANDLE)henv,(SQLHANDLE)hdbc,fType[j]);
					Sleep(2);																// tmf rollback is slower.
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLTransact"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}

					returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[iend],SQL_NTS);
					if(!CHECKRC(CheckRes[i].ExeRes[j],returncode,"SQLExecDirect"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					else
					{
						if (returncode == SQL_SUCCESS || returncode == SQL_SUCCESS_WITH_INFO)
						{
							Output = (TCHAR *)malloc(NAME_LEN);
							returncode=SQLBindCol(hstmt,1,SQL_C_TCHAR,Output,NAME_LEN,&OutputLen);
							if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
							{
								LogAllErrors(henv,hdbc,hstmt);
								TEST_FAILED;
							}
							else
							{
								returncode = SQLFetch(hstmt);
								if(!CHECKRC(CheckRes[i].FetchRes[j],returncode,"SQLFetch"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								else
								{
									if (returncode != SQL_NO_DATA_FOUND && returncode != SQL_ERROR)
									{
										if (_tcscspn(CheckRes[i].DataRes[j],Output) == 0)
										{
											LogMsg(NONE,_T("expect: %s and actual: %s are matched\n"),Output,CheckRes[i].DataRes[j]);
										}	
										else
										{
											LogMsg(NONE,_T("expect: %s and actual: %s are not matched\n"),Output,CheckRes[i].DataRes[j]);
											TEST_FAILED;	
										}
									}
								}
								free(Output);
								SQLFreeStmt(hstmt,SQL_CLOSE);
							}
						}
					}
				}
				TESTCASE_END;
			}/* end j loop */
		}/* end i loop */
	}

//========================================================================================================

	SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[4],SQL_NTS); /* CLEANUP */
	returncode = SQLDisconnect((SQLHANDLE)hdbc);
    if(!CHECKRC(SQL_ERROR,returncode,"SQLDisconnect")) 
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		TEST_FAILED;	
	}	
	
	// Free the open transactions.
	returncode=SQLTransact((SQLHANDLE)henv,(SQLHANDLE)hdbc,SQL_ROLLBACK);
	Sleep(2);	

	returncode=FullDisconnect(pTestInfo);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFullDisconnect"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		TEST_FAILED;
	}

	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing API => SQLTransact.\n"));

	free_list(var_list);

	TEST_RETURN;
}