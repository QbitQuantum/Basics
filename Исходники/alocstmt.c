//---------------------------------------------------------
//   TestSQLAllocStmt()
//---------------------------------------------------------
PassFail TestSQLAllocStmt (TestInfo *pTestInfo, int MX_MP_SPECIFIC)
{
	TEST_DECLARE;
 	char			Heading[MAX_STRING_SIZE];
 	RETCODE			returncode;
 	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt[NUM_STMT];
	//RETCODE		AsyncStmt[NUM_ASYNC_STMT];
	char			*StmtHndlStr;
	int				i = 0, j = 0, k = 0;
	int				AnyAsync;
	int				AsyncOper[] = {CREATE_TABLE,INSERT_TABLE,SELECT_TABLE,DROP_TABLE,999};

	char			*teststmthndl[21];

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars("SQLAllocateStatement", charset_file);
	if (var_list == NULL) return FAILED;

	teststmthndl[0] = var_mapping("TestStmtHndl_0", var_list);
	teststmthndl[1] = var_mapping("TestStmtHndl_1", var_list);
	teststmthndl[2] = var_mapping("TestStmtHndl_2", var_list);
	teststmthndl[3] = var_mapping("TestStmtHndl_3", var_list);
	teststmthndl[4] = var_mapping("TestStmtHndl_4", var_list);
	teststmthndl[5] = var_mapping("TestStmtHndl_5", var_list);
	teststmthndl[6] = var_mapping("TestStmtHndl_6", var_list);
	teststmthndl[7] = var_mapping("TestStmtHndl_7", var_list);
	teststmthndl[8] = var_mapping("TestStmtHndl_8", var_list);
	teststmthndl[9] = var_mapping("TestStmtHndl_9", var_list);
	teststmthndl[10] = var_mapping("TestStmtHndl_10", var_list);
	teststmthndl[11] = var_mapping("TestStmtHndl_11", var_list);
	teststmthndl[12] = var_mapping("TestStmtHndl_12", var_list);
	teststmthndl[13] = var_mapping("TestStmtHndl_13", var_list);
	teststmthndl[14] = var_mapping("TestStmtHndl_14", var_list);
	teststmthndl[15] = var_mapping("TestStmtHndl_15", var_list);
	teststmthndl[16] = var_mapping("TestStmtHndl_16", var_list);
	teststmthndl[17] = var_mapping("TestStmtHndl_17", var_list);
	teststmthndl[18] = var_mapping("TestStmtHndl_18", var_list);
	teststmthndl[19] = var_mapping("TestStmtHndl_19", var_list);
	teststmthndl[20] = var_mapping("TestStmtHndl_20", var_list);
//======================================================================================

	if (MX_MP_SPECIFIC == MX_SPECIFIC)
		LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => MX specific SQLAllocStmt | SQLAllocStmt | alocstmt.c\n");
	else
		LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => MP specific SQLAllocStmt | SQLAllocStmt | alocstmt.c\n");

	TEST_INIT;

	TESTCASE_BEGIN("Setup for SQLAllocStmt/SQLFreeStmt tests\n");

	/* 6-5-00:
	Need to turn Autocommit off since MX will close all open cursors that are
	open if the end of ANY of the cursors is reached. */
	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_2))
	{
		LogMsg(NONE,"Unable to connect\n");
		TEST_FAILED;
		TEST_RETURN;
	}

	henv = pTestInfo->henv;
 	hdbc = pTestInfo->hdbc;
	//set the connection attribute to SQL_AUTOCOMMIT_OFF to enable use of multiple stmt  without errors 
	SQLSetConnectAttr((SQLHANDLE)hdbc, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, SQL_IS_UINTEGER);

	TESTCASE_END;  // end of setup

	StmtHndlStr = (char *)malloc(MAX_NOS_SIZE);

//====================================================================================================
// General statement handle exercise testcases.

	for (k = 0; k < 2; k++)
	{
		for (i = 0; i < NUM_STMT; i++)
		{
			hstmt[i] = (SQLHANDLE)pTestInfo->hstmt;

			sprintf(Heading,"SQLAllocstmt: Test #%d\n",i);
			TESTCASE_BEGIN(Heading);
			returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt[i]);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}
			TESTCASE_END;
			if (returncode == SQL_SUCCESS)
			{
		 		if (i == 0)									// cleanup 
				{
					for (j = 0; j < NUM_STMT; j++)
					{
						SQLExecDirect(hstmt[0],StmtQueries(DROP_TABLE,teststmthndl[j],StmtHndlStr),SQL_NTS); 
					}
				}
				sprintf(Heading,"SQLAllocStmt: create table teststmthndl%d\n",i+1);
				TESTCASE_BEGIN(Heading);
				if (k == 0)	// prepare & execute 
				{
					returncode = SQLPrepare(hstmt[i],StmtQueries(CREATE_TABLE,teststmthndl[i],StmtHndlStr),SQL_NTS); 
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
					else{
						returncode = SQLExecute(hstmt[i]);
						if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
							TEST_FAILED;
							LogAllErrors(henv,hdbc,hstmt[i]);
							}
						}
					}
				else	// execdirect 
				{
					returncode = SQLExecDirect(hstmt[i],StmtQueries(CREATE_TABLE,teststmthndl[i],StmtHndlStr),SQL_NTS);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
				}
				}
				if (returncode == SQL_SUCCESS) TESTCASE_END;
			}

		for (i = 0; i < NUM_STMT; i++)
		{
			sprintf(Heading,"SQLAllocStmt: inserts on Stmt Handle(%d)\n",i);
			TESTCASE_BEGIN(Heading);
			if (k == 0)	// prepare & execute 
			{
				returncode = SQLPrepare(hstmt[i],StmtQueries(INSERT_TABLE,teststmthndl[i],StmtHndlStr),SQL_NTS); 
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt[i]);
				}
				else
				{
					returncode = SQLExecute(hstmt[i]);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
				}
			}
			else	// execdirect 
			{
				returncode = SQLExecDirect(hstmt[i],StmtQueries(INSERT_TABLE,teststmthndl[i],StmtHndlStr),SQL_NTS); 
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt[i]);
				}
			}
			if (returncode == SQL_SUCCESS)TESTCASE_END;
		}

		for (i = 0; i < NUM_STMT; i++)
		{
			sprintf(Heading,"SQLAllocStmt: selects on Stmt Handle(%d)\n",i);
			TESTCASE_BEGIN(Heading);
			if (k == 0)	// prepare & execute 
			{
				returncode = SQLPrepare(hstmt[i],StmtQueries(SELECT_TABLE,teststmthndl[i],StmtHndlStr),SQL_NTS); 
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt[i]);
				}
				else{
					returncode = SQLExecute(hstmt[i]);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute")){
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
						}
					}
			}
			else	// execdirect 
			{
				returncode = SQLExecDirect(hstmt[i],StmtQueries(SELECT_TABLE,teststmthndl[i],StmtHndlStr),SQL_NTS); 
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt[i]);
				}
			}
			if (returncode == SQL_SUCCESS) TESTCASE_END;
		}

		for (i = (NUM_STMT-1); i > -1; i--)
		{
			sprintf(Heading,"SQLAllocStmt: fetches on selects on Stmt Handle(%d)\n",i);
			TESTCASE_BEGIN(Heading);
			returncode = SQLFetch(hstmt[i]);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}			
			if (returncode == SQL_SUCCESS) TESTCASE_END;
		}

		for (i = 0; i < NUM_STMT; i++)
		{
			sprintf(Heading,"SQLAllocStmt: SQLFreeStmt(%d) with SQL_CLOSE\n",i);
			TESTCASE_BEGIN(Heading);
			returncode = SQLFreeStmt(hstmt[i],SQL_CLOSE);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeStmt"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}
			else{
				TESTCASE_END;
				}

			if (i == (NUM_STMT-1))					// cleanup 
			{
				for (j = 0; j < NUM_STMT; j++)
				{
					SQLExecDirect(hstmt[0],StmtQueries(DROP_TABLE,teststmthndl[j],StmtHndlStr),SQL_NTS); 
				}
			}
		}

		for (i = 0; i < NUM_STMT; i++)
		{
			sprintf(Heading,"SQLAllocStmt: SQLFreeStmt(%d) with SQL_DROP\n",i);
			TESTCASE_BEGIN(Heading);
			returncode = SQLFreeStmt(hstmt[i],SQL_DROP);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeStmt"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}
			else{
				TESTCASE_END;
				}
		}

		sprintf(Heading,"SLQAllocStmt: same sql operations on different of SQLAllocstmt(%d)s\n",i);
		TESTCASE_BEGIN(Heading);
 		for (i = 0; i < NUM_STMT; i++)
		{
			hstmt[i] = (SQLHANDLE)pTestInfo->hstmt;
			returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt[i]);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}
			if (returncode == SQL_SUCCESS)
			{
		 		if (i == 0)									// cleanup
				{
					SQLExecDirect(hstmt[0],StmtQueries(DROP_TABLE,teststmthndl[20],StmtHndlStr),SQL_NTS); 
					returncode = SQLExecDirect(hstmt[0],StmtQueries(CREATE_TABLE,teststmthndl[20],StmtHndlStr),SQL_NTS); 
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[0]);
					}			
				}
				if (k == 0)	// prepare & execute 
				{
					returncode = SQLPrepare(hstmt[i],StmtQueries(INSERT_TABLE,teststmthndl[20],StmtHndlStr),SQL_NTS);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}			
					returncode = SQLExecute(hstmt[i]);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
				}
				else	// execdirect
				{
					returncode = SQLExecDirect(hstmt[i],StmtQueries(INSERT_TABLE,teststmthndl[20],StmtHndlStr),SQL_NTS);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
				}
				if (k == 0)	// prepare & execute 
				{
					returncode = SQLPrepare(hstmt[i],StmtQueries(SELECT_TABLE,teststmthndl[20],StmtHndlStr),SQL_NTS);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}			
					returncode = SQLExecute(hstmt[i]);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
				}
				else
				{
					returncode = SQLExecDirect(hstmt[i],StmtQueries(SELECT_TABLE,teststmthndl[20],StmtHndlStr),SQL_NTS);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
				}
				returncode = SQLFetch(hstmt[i]); 
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt[i]);
				}
			}
		}
 		for (i = 0; i < NUM_STMT; i++)
		{
			returncode = SQLFreeStmt(hstmt[i],SQL_CLOSE);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}
			if (i == 0)
			{
				SQLExecDirect(hstmt[0],StmtQueries(DROP_TABLE,teststmthndl[20],StmtHndlStr),SQL_NTS); 
			}
			returncode = SQLFreeStmt(hstmt[i],SQL_DROP);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeStmt"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}
		}
		TESTCASE_END;
	}

//====================================================================================================
// Asynchronus Testcases

	if (MX_MP_SPECIFIC == MX_SPECIFIC)
	{
		for (i = 0; i < NUM_ASYNC_STMT; i++)
		{
			hstmt[i] = (SQLHANDLE)pTestInfo->hstmt;
			// Creating statement handles
			sprintf(Heading,"SQLAllocstmt: Test #%d and Enable the ASYNC MODE ON.\n",i);
			TESTCASE_BEGIN(Heading);
			returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt[i]);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt[i]);
			}
			else
			{
		 		if (i == 0)									// cleanup 
				{
					// Creating tables to be used by each of the stmt handles
					for (j = 0; j < NUM_ASYNC_STMT; j++)
					{
						SQLExecDirect(hstmt[0],StmtQueries(DROP_TABLE,teststmthndl[j],StmtHndlStr),SQL_NTS); 
					}
				}
				// Putting each stmthandle into Asynchronus mode
				returncode = SQLSetStmtOption(hstmt[i],SQL_ASYNC_ENABLE,SQL_ASYNC_ENABLE_ON);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtOptions"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt[i]);
				}
			}
			TESTCASE_END;
		}

		// Running the Asynchronus tests
		// WHAT IS GOING ON
		//   Two tests cases are being checked:
		//     1. That the status of an asynchronus stmt handle CAN be checked.
		//     2. That the stmt handle completes correctly.
		//
		// HOW IT'S BEING RUN
		//   Steps being performed until all handles are no longer executing:
		//     1. Prepare the async test data structure.
		//     2. Generate table name based on statement handle being used.
		//     3. If handle's status has not been checked already, check as test case 1.
		//        Else, check it's status NOT as a test case.
		//     4. Run the statement (also used to check the status of the handle).
		//     5. If the stmt completes, verify that it does so successfully. Test case 2.
		//
		//   Once all of the handles have completed, perform the next Async Operation
		//   until the terminating operation (a.k.a "999") is reached.
		k = 0;
		while (AsyncOper[k] != 999)
		{
			// 1. Preparing the async test data structure
			for (i = 0; i < NUM_ASYNC_STMT; i++)
			{
				AsyncStmt[i].status = SQL_STILL_EXECUTING;
				AsyncStmt[i].checked = FALSE;
			}
			AnyAsync = 1;
			// Testing begins
			while (AnyAsync > 0)
			{
				for (i = 0; i < NUM_ASYNC_STMT; i++)
				{
					if (AsyncStmt[i].status == SQL_STILL_EXECUTING)
					{
						// 3. Has the handle been checked for its status?
						if (AsyncStmt[i].checked)
						{
							// 4. Run the statement.
							returncode = SQLExecDirect(hstmt[i],StmtQueries(AsyncOper[k],teststmthndl[i],StmtHndlStr),SQL_NTS);
							AsyncStmt[i].status = returncode;
							// 5. Result Test: Verifying that the statement completes correctly.
							if (returncode != SQL_STILL_EXECUTING)
							{
								sprintf(Heading,"SQLAllocStmt: Result Test: %d; SQLStmt: %s.\n",i,StmtQueries(AsyncOper[k],teststmthndl[i],StmtHndlStr));
								TESTCASE_BEGIN(Heading);
								if (returncode != SQL_SUCCESS)
								{
									TEST_FAILED;
									LogAllErrors(henv,hdbc,hstmt[i]);
								}
								TESTCASE_END;
							}
						}
						else
						{
							// Status Test (Test case 1):
							// Only EXECUTING and SUCCESS are acceptable, others are errors.
							//   This test is only run once!
							sprintf(Heading,"SQLAllocStmt: Status Test: %d; SQLStmt: %s.\n",i,StmtQueries(AsyncOper[k],teststmthndl[i],StmtHndlStr));
							TESTCASE_BEGIN(Heading);
							
							// 4. Run the statement.
							returncode = SQLExecDirect(hstmt[i],StmtQueries(AsyncOper[k],teststmthndl[i],StmtHndlStr),SQL_NTS);
							AsyncStmt[i].status = returncode;
							AsyncStmt[i].checked = TRUE;
							if ((returncode != SQL_STILL_EXECUTING) && (returncode != SQL_SUCCESS))
							{
								TEST_FAILED;
								LogAllErrors(henv,hdbc,hstmt[i]);
							}
							TESTCASE_END;
							
							// 5. If the stmt completes, verify that it does so successfully.
							if (returncode != SQL_STILL_EXECUTING)
							{
								// Result Test: Verifying that the stmt completes successfully.
								sprintf(Heading,"SQLAllocStmt: Result Test: %d; SQLStmt: %s.\n",i,StmtQueries(AsyncOper[k],teststmthndl[i],StmtHndlStr));
								TESTCASE_BEGIN(Heading);
								if (returncode != SQL_SUCCESS)
								{
									TEST_FAILED;
									LogAllErrors(henv,hdbc,hstmt[i]);
								}
								TESTCASE_END;
							}
							//Sleep (500);
						}
					}
				}
				AnyAsync = 0;
				for (i = 0; i < NUM_ASYNC_STMT; i++)
				{
					if (AsyncStmt[i].status == SQL_STILL_EXECUTING)
					{
						AnyAsync = AnyAsync + 1;
					}
				}
			}

			// Special tests for Fetching after doing a SELECT
			// Steps are identical to the above steps.
			if (AsyncOper[k] == SELECT_TABLE)
			{
				// Preparing data structure
				for (i = 0; i < NUM_ASYNC_STMT; i++)
				{
					AsyncStmt[i].status = SQL_STILL_EXECUTING;
					AsyncStmt[i].checked = FALSE;
				}
				AnyAsync = 1;
				// Select testing begins
				while (AnyAsync > 0)
				{
					for (i = 0; i < NUM_ASYNC_STMT; i++)
					{
						if (AsyncStmt[i].status == SQL_STILL_EXECUTING)
						{
							if (AsyncStmt[i].checked)
							{
								returncode = SQLFetch(hstmt[i]);
								AsyncStmt[i].status = returncode;									
								if (returncode != SQL_STILL_EXECUTING)
								{
									// Result Test
									sprintf(Heading,"SQLAllocStmt: Result Test:%d; performing SQLFetch.\n",i);
									TESTCASE_BEGIN(Heading);
									if (returncode != SQL_SUCCESS)
									{
										TEST_FAILED;
										LogAllErrors(henv,hdbc,hstmt[i]);
									}
									TESTCASE_END;
								}
							}
							else
							{
								// Status Test
								sprintf(Heading,"SQLAllocStmt: Status Test:%d; performing SQLFetch.\n",i);
								TESTCASE_BEGIN(Heading);
								returncode = SQLFetch(hstmt[i]);
								AsyncStmt[i].status = returncode;
								AsyncStmt[i].checked = TRUE;
								if ((returncode != SQL_STILL_EXECUTING) && (returncode != SQL_SUCCESS))
								{
									TEST_FAILED;
									LogAllErrors(henv,hdbc,hstmt[i]);
								}
								TESTCASE_END;

								// Result Test
								if (returncode != SQL_STILL_EXECUTING)
								{
									sprintf(Heading,"SQLAllocStmt: Result Test:%d; performing SQLFetch.\n",i);
									TESTCASE_BEGIN(Heading);
									if (returncode != SQL_SUCCESS)
									{
										TEST_FAILED;
										LogAllErrors(henv,hdbc,hstmt[i]);
									}
									TESTCASE_END;
								}
							}
						}
					}
					AnyAsync = 0;
					for (i = 0; i < NUM_ASYNC_STMT; i++)
					{
						if (AsyncStmt[i].status == SQL_STILL_EXECUTING)
						{
							AnyAsync = AnyAsync + 1;
						}
					}
				}
				// Closing the cursor from the SELECT stmt result set.
				for (i = 0; i < NUM_ASYNC_STMT; i++)
				{
					sprintf(Heading,"SQLFreeStmt: %d.\n",i);
					TESTCASE_BEGIN(Heading);
					returncode = SQLFreeStmt(hstmt[i],SQL_CLOSE);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeStmt"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt[i]);
					}
					TESTCASE_END;
				}
			} // End of async SELECT test.

			// Resetting the checked status for the next operation.
			for (i = 0; i < NUM_ASYNC_STMT; i++)
			{
				AsyncStmt[i].checked = FALSE;
			}

			k++;
		}
	}
//====================================================================================================

	free(StmtHndlStr);
	returncode = SQLDisconnect((SQLHANDLE)hdbc);
    if(!CHECKRC(SQL_ERROR,returncode,"SQLDisconnect")) 
	{
		TEST_FAILED;	
		LogAllErrorsVer3(henv,hdbc,hstmt[0]);
	}	
	
	// Free the open transactions.
	returncode=SQLTransact((SQLHANDLE)henv,(SQLHANDLE)hdbc,SQL_ROLLBACK);
	Sleep(2);	

	returncode=FullDisconnect(pTestInfo);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFullDisconnect"))
	{
		TEST_FAILED;
		LogAllErrorsVer3(henv,hdbc,hstmt[0]);
	}
	
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => SQLAllocStmt.\n");

	free_list(var_list);

	TEST_RETURN;
}