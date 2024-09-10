/*
---------------------------------------------------------
   TestHash2
---------------------------------------------------------
*/
PassFail TestHash2(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;
	SQLRETURN		returncode;      
	SQLHENV			henv = 0;
	SQLHDBC			hdbc = 0;
	SQLHSTMT		hstmt= 0;
	SQLUSMALLINT	ParamStatusArray[ARRAY_SIZE];
	SQLUSMALLINT	expParamStatusArray[ARRAY_SIZE];
	SQLUSMALLINT	lastExpParamStatusArray[ARRAY_SIZE];
	SQLULEN			lastParamsProcessed=ARRAY_SIZE, ParamsProcessed = 0;
	SQLLEN			rowcount = 0, expRowcount = 0, lastExpRowcount = 0;
	int				i,j,k,counter = 1, loopcount = 0;
	TCHAR			buffer[256];

	typedef struct {
    		TCHAR	num[15];	SQLLEN numLenOrInd;
    		TCHAR	val[15];	SQLLEN valLenOrInd;
	}nameStruct;
	nameStruct  nameArray1[ARRAY_SIZE];

	SQLUINTEGER mode = 1; 
	SQLUINTEGER startnode = 2;
	SQLUINTEGER streams_per_node = 4;
	SQLUINTEGER delay_error = 1;
	SQLUINTEGER suggested_rowset_size=0;

	SQLTCHAR *sqlDrvInsert = (SQLTCHAR*)_T("PLANLOADTABLE HASH2_TABLE");
	SQLTCHAR *dropTbl = (SQLTCHAR *)_T("DROP TABLE HASH2_TABLE cascade");
	SQLTCHAR *crtTbl = (SQLTCHAR *)_T("CREATE TABLE HASH2_TABLE (A int NOT NULL NOT DROPPABLE, B varchar(10), PRIMARY KEY (A))");
	SQLTCHAR *insTbl = (SQLTCHAR *)_T("INSERT INTO HASH2_TABLE values (?,?)");
//	SQLTCHAR *selTbl = (SQLTCHAR *)_T("SELECT * HASH2_TABLE");

	//==================================================================================================
	LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing feature => Hash2.\n"));
	TEST_INIT;

	returncode = SQLAllocEnv(&henv);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocEnv"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLAllocConnect( henv, &hdbc);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocConnect"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLSetConnectAttr(hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON,0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetConnectAttr"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	//==================================================================================================
	// Set Mode to Loader
	returncode = SQLSetConnectAttr(hdbc, SQL_MODE_LOADER, (void *) mode, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_MODE_LOADER"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	// Set Start mode
	returncode = SQLSetConnectAttr(hdbc,  SQL_START_NODE,  (void *) startnode,  0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_START_NODE"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	// Set Desired Streams Per Node
	returncode = SQLSetConnectAttr(hdbc,  SQL_STREAMS_PER_SEG,  (void *) streams_per_node,  0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_STREAMS_PER_SEG"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	// Set delay_error mode
	returncode = SQLSetConnectAttr(hdbc,  SQL_LOADER_DELAYERROR, (void *) delay_error, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_LOADER_DELAYERROR"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	//==================================================================================================

	returncode = SQLConnect(hdbc,
					   (SQLTCHAR*)pTestInfo->DataSource,(SWORD)_tcslen(pTestInfo->DataSource),
					   (SQLTCHAR*)pTestInfo->UserID,(SWORD)_tcslen(pTestInfo->UserID),
					   (SQLTCHAR*)pTestInfo->Password,(SWORD)_tcslen(pTestInfo->Password)
					   );
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLConnect"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLAllocStmt(hdbc, &hstmt);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLConnect"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLExecDirect(hstmt, dropTbl, SQL_NTS);
	returncode = SQLExecDirect(hstmt, crtTbl, SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLPrepare(hstmt, (SQLTCHAR *) sqlDrvInsert, SQL_NTS);
	if (returncode != SQL_SUCCESS) {
		LogMsg(ERRMSG,_T("PLANLOADTABLE is expected to return SQL_SUCCESS, actual is %d\n"), returncode);
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLGetConnectAttr(hdbc, SQL_ATTR_SUG_ROWSET_SIZE, &suggested_rowset_size, 0, NULL);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_ATTR_SUG_ROWSET_SIZE"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	LogMsg(LINEAFTER,_T("suggested_rowset_size=%d\n"), suggested_rowset_size);

	//==================================================================================================
	// Set the SQL_ATTR_PARAM_BIND_TYPE statement attribute to use row-wise binding.
	returncode = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_BIND_TYPE, (void *)sizeof(nameStruct), 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_ATTR_PARAM_BIND_TYPE"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	// Specify the number of elements in each parameter array.
	returncode = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (void *)ARRAY_SIZE, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_ATTR_PARAMSET_SIZE"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	// Specify an array in which to return the status of each set of parameters.
	returncode = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAM_STATUS_PTR, ParamStatusArray, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_ATTR_PARAM_STATUS_PTR"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	// Specify an SQLUINTEGER value in which to return the number of sets of parameters processed.
	returncode = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_ATTR_PARAMS_PROCESSED_PTR"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLPrepare(hstmt, insTbl, SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_INTEGER, 10, 0,
                 &nameArray1[0].num, 300, &nameArray1[0].numLenOrInd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	returncode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_WCHAR, 10, 0,
                 &nameArray1[0].val, 300, &nameArray1[0].valLenOrInd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	for (j=0; j<ARRAY_SIZE; j++) {
		lastExpParamStatusArray[j] = SQL_PARAM_SUCCESS;
		expParamStatusArray[j] = SQL_PARAM_SUCCESS;
	}

	//==================================================================================================
	TESTCASE_BEGIN("Test the positive functionality of Hash2, with delay_error mode ON.\n");
	loopcount = 4;
	k = 0;
	while ( k < (loopcount+1)) {
		expRowcount = 0;

		if (k==loopcount) { //Send a dummy rowsets to get the status array of the previous rowsets in delay-mode
			LogMsg(LINEAFTER,_T("Insert dummy rowsets with size=0\n"));
			returncode = SQLSetStmtAttr(hstmt, SQL_ATTR_PARAMSET_SIZE, (void *)0, 0);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQL_ATTR_PARAMSET_SIZE"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				TEST_RETURN;
			}
		}
		else {
			_stprintf(buffer, _T("Data inserted: "));
			for (j=0; j<ARRAY_SIZE; j++) {
				if ((j+1)%(3+2*k) == 0) {
					counter--;
					expParamStatusArray[j] = SQL_PARAM_ERROR;
				}
				else {
					expParamStatusArray[j] = SQL_PARAM_SUCCESS;
					expRowcount++;
				}
				_stprintf(nameArray1[j].num,_T("%d"),counter++);
				nameArray1[j].numLenOrInd = SQL_NTS;
				_stprintf(nameArray1[j].val,_T("%s"),_T("chochet"));
				nameArray1[j].valLenOrInd = SQL_NTS;
				_tcscat(buffer,nameArray1[j].num);
				_tcscat(buffer,_T(" "));
			}
			_tcscat(buffer,_T("\n"));
		}
		LogMsg(NONE,_T("%s\n"), buffer);

		returncode = SQLExecute(hstmt);
		if (delay_error == 1 && k != 0) {
			if(returncode != SQL_SUCCESS_WITH_INFO)
			{
				LogMsg(ERRMSG,_T("SQLExecute: returncode expected: SQL_SUCCESS_WITH_INFO, actual: %d at line=%d\n"), returncode, __LINE__);
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				TEST_RETURN;
			}
		}
		else {
			if(returncode != SQL_SUCCESS)
			{
				LogMsg(ERRMSG,_T("SQLExecute: returncode expected: SQL_SUCCESS, actual: %d at line=%d\n"), returncode, __LINE__);
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				TEST_RETURN;
			}
		}

		if ((k == loopcount && ParamsProcessed != 0) || (k != loopcount && ParamsProcessed != ARRAY_SIZE)) {
			LogMsg(ERRMSG,_T("ParamsProcessed is not the same as rowset size from client, at line=%d\n"), __LINE__);
			TEST_FAILED;
		}

		returncode = SQLRowCount(hstmt, &rowcount);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLRowCount"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
		}

		if (delay_error == 1) {
			if (lastExpRowcount != rowcount) {
				TEST_FAILED;
				LogMsg(ERRMSG,_T("Expected Rowcount=%d, Actual Rowcount=%d\n"), expRowcount, rowcount);
			}
			lastExpRowcount = expRowcount;

			LogMsg(NONE,_T("\n%d last rows processed, %d current rows processed, rowcount=%d\n"), lastParamsProcessed, ParamsProcessed, rowcount);
			for (i = 0; i < (int)lastParamsProcessed; i++) {
   				LogMsg(NONE,_T("Parameter Set  Status\n"));
				LogMsg(NONE,_T("-------------  -------------\n"));
				if (ParamStatusArray[i] != lastExpParamStatusArray[i]) {
					TEST_FAILED;
					LogMsg(ERRMSG,_T("Param status array at row #%d is expected: %d, actual %d\n"), i, lastExpParamStatusArray[i], ParamStatusArray[i]);
					continue;
				}
				switch (ParamStatusArray[i]) {
					case SQL_PARAM_SUCCESS:
					case SQL_PARAM_SUCCESS_WITH_INFO:
         					LogMsg(NONE,_T("%13d  Success\n"), i);
         					break;

      					case SQL_PARAM_ERROR:
         					LogMsg(NONE,_T("%13d  Error  <-------\n"), i);
         					break;

      					case SQL_PARAM_UNUSED:
        					LogMsg(NONE,_T("%13d  Not processed\n"), i);
        					break;

     					case SQL_PARAM_DIAG_UNAVAILABLE:
         					LogMsg(NONE,_T("%13d  Unknown\n"), i);
         					break;
   				}
			}
			LogMsg(NONE,_T("\n============================================================\n"));
			lastParamsProcessed = ParamsProcessed;
			for (j=0; j<ARRAY_SIZE; j++) {
				lastExpParamStatusArray[j] = expParamStatusArray[j];
			}
		}
		else {
			if (expRowcount != rowcount) {
				TEST_FAILED;
				LogMsg(ERRMSG,_T("Expected Rowcount=%d, Actual Rowcount=%d\n"), expRowcount, rowcount);
			}

			LogMsg(NONE,_T("\n%d current rows processed, rowcount=%d\n"), ParamsProcessed, rowcount);
			for (i = 0; i < (int)ParamsProcessed; i++) {
   				LogMsg(NONE,_T("Parameter Set  Status\n"));
				LogMsg(NONE,_T("-------------  -------------\n"));
				if (ParamStatusArray[i] != expParamStatusArray[i]) {
					TEST_FAILED;
					LogMsg(ERRMSG,_T("Param status array at row #%d is expected: %d, actual %d\n"), i, expParamStatusArray[i], ParamStatusArray[i]);
					continue;
				}
				switch (ParamStatusArray[i]) {
					case SQL_PARAM_SUCCESS:
					case SQL_PARAM_SUCCESS_WITH_INFO:
         					LogMsg(NONE,_T("%13d  Success\n"), i);
         					break;

      					case SQL_PARAM_ERROR:
         					LogMsg(NONE,_T("%13d  Error  <-------\n"), i);
         					break;

      					case SQL_PARAM_UNUSED:
        					LogMsg(NONE,_T("%13d  Not processed\n"), i);
        					break;

     					case SQL_PARAM_DIAG_UNAVAILABLE:
         					LogMsg(NONE,_T("%13d  Unknown\n"), i);
         					break;
   				}
			}
			LogMsg(NONE,_T("\n============================================================\n"));
		}
		k++;
	}
	TESTCASE_END;

	SQLFreeStmt( hstmt, SQL_CLOSE );
	SQLFreeStmt( hstmt, SQL_UNBIND );
	SQLDisconnect( hdbc );
	SQLFreeConnect( hdbc );
	SQLFreeEnv( henv );

	//==================================================================================================
	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing feature => Hash2.\n"));
	TEST_RETURN;
}