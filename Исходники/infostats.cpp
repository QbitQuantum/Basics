/*
---------------------------------------------------------
  TestSQLDrivers
	No negative tests since this functionality is done at
	driver manager level.
---------------------------------------------------------
*/
PassFail TestInfoStats(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;

    SQLHANDLE	secHandle;
    SQLSMALLINT outLen = SQL_NTS;
    char		tempStr[MAX_STR_LEN*2];
	int			i,j;
	char		cursorName[MAX_STR_LEN] = "";
    RETCODE		returncode;

	char* strs[5];

    struct _test_data {
        char        front[2];
        char        back[MAX_SIZE];
        RETCODE     retcode;
        BOOL        cursor;
        char        *stmt;
    } testData[] = {{"", "",          SQL_SUCCESS,    TRUE,  ""},
                    {"", "",          SQL_SUCCESS,    TRUE,  ""},
                    {"", "",          SQL_SUCCESS,    TRUE,  ""},
                    {"", "SQL_CUR_2", SQL_ERROR,      FALSE, ""},
                    {"", "",          SQL_ERROR,      FALSE, ""},    // empty statement
                    {"'", "'",        SQL_SUCCESS,    TRUE,  ""},
                    {"\"", "\"",      SQL_SUCCESS,    TRUE,  ""},
                    {"", "SQL_CUR_9 ",SQL_ERROR,      FALSE, ""},
                    {"\"", "",        SQL_ERROR,      TRUE,  ""},
                    {"\"", "\"",      SQL_SUCCESS,    FALSE, ""},     // strs[3].txt
                    {"'", "'",        SQL_SUCCESS,    FALSE, ""},     // strs[3].txt
                    {"'", "",         SQL_ERROR,      FALSE, ""},     // strs[3].txt
                    {"\"", "",        SQL_ERROR,      FALSE, ""},     // strs[3].txt
                    {"", "\"",        SQL_ERROR,      FALSE, ""},     // strs[3].txt
                    {"", "'",         SQL_ERROR,      FALSE, ""},     // strs[3].txt
                    {"'", "'",        SQL_ERROR,      FALSE, ""},     // strs[4].txt
                    {"\"", "\"",      SQL_ERROR,      FALSE, ""},     // strs[4].txt
                    {"", "end"}
     };

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars("InfoStats", charset_file);
	if (var_list == NULL) return FAILED;

    strs[0] = var_mapping("InfoStats_strs_0", var_list);
    strs[1] = var_mapping("InfoStats_strs_1", var_list);
    strs[2] = var_mapping("InfoStats_strs_2", var_list);
    strs[3] = var_mapping("InfoStats_strs_3", var_list);
    strs[4] = var_mapping("InfoStats_strs_4", var_list);
    strs[5] = var_mapping("InfoStats_strs_5", var_list);

	testData[9].stmt  = strs[3];
    testData[10].stmt = strs[3];
    testData[11].stmt = strs[3];
    testData[12].stmt = strs[3];
    testData[13].stmt = strs[3];
    testData[14].stmt = strs[3];

    testData[15].stmt = strs[4];
    testData[16].stmt = strs[4];

//===========================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing => InfoStats | InfoStats | infostats.cpp\n");
    TEST_INIT;

	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
		LogMsg(NONE,"Unable to connect\n");
		TEST_FAILED;
		TEST_RETURN;
	}

    returncode = SQLAllocStmt((SQLHANDLE)pTestInfo->hdbc, &(pTestInfo->hstmt));	
    if (returncode != SQL_SUCCESS) {
        TEST_FAILED;
        TEST_RETURN;
    }

    returncode = SQLAllocStmt((SQLHANDLE)pTestInfo->hdbc, &secHandle);
    if(returncode != SQL_SUCCESS) {
        TEST_FAILED;
        TEST_RETURN;
    }

    for(j = 0; j < 2; j++) {
        i = 0;
        while (strcmp(testData[i].back,"end")!=0) {

            if((j == 0) || (i==0)) {    // setup table and data
                LogMsg(NONE,"Setting up table and data\n");
                returncode = SQLExecDirect(pTestInfo->hstmt, (SQLCHAR*)strs[0], SQL_NTS);
	            returncode = SQLExecDirect(pTestInfo->hstmt, (SQLCHAR*)strs[1], SQL_NTS);
	            returncode = SQLExecDirect(pTestInfo->hstmt, (SQLCHAR*)strs[2], SQL_NTS);
	            returncode = SQLEndTran(SQL_HANDLE_DBC, pTestInfo->hdbc, SQL_COMMIT);
	            returncode = SQLFreeStmt(pTestInfo->hstmt, SQL_CLOSE);
            }
     
	        returncode = SQLPrepare(pTestInfo->hstmt, (SQLCHAR*)strs[3], SQL_NTS);

            strcpy(cursorName, "");

	        returncode = SQLGetCursorName(pTestInfo->hstmt, (SQLCHAR*)cursorName, sizeof(cursorName), &outLen);
            if(returncode != SQL_SUCCESS)
                LogAllErrors(pTestInfo->henv, pTestInfo->hdbc, pTestInfo->hstmt);

	        returncode = SQLExecute(pTestInfo->hstmt);

            sprintf(tempStr, "Starting test number %d\n", i);
            TESTCASE_BEGIN(tempStr);

            if(testData[i].cursor == TRUE)
                sprintf(tempStr, "INFOSTATS %s%s%s", testData[i].front, cursorName, testData[i].back);
            else
                sprintf(tempStr, "INFOSTATS %s%s%s", testData[i].front, testData[i].stmt, testData[i].back);

            returncode = execute(pTestInfo, secHandle, tempStr, testData[i].retcode);
            if(returncode == FALSE)
                TEST_FAILED;
			returncode = SQLFreeStmt(secHandle, SQL_CLOSE);
	        returncode = SQLFreeStmt(pTestInfo->hstmt,SQL_CLOSE);

            TESTCASE_END;
            i++;
        }

        returncode = SQLExecDirect(pTestInfo->hstmt, (SQLCHAR*)strs[0], SQL_NTS);
    }

	//==========================================================================================
      
	FullDisconnect3(pTestInfo);
	free_list(var_list);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing => InfoStats.\n");
    TEST_RETURN;
}