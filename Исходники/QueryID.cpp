PassFail TestQueryID (TestInfo *pTestInfo)
{
	TEST_DECLARE;
 	char			Heading[MAX_STRING_SIZE];
 	RETCODE			returncode;
 	SQLHANDLE 		henv, henv2;
 	SQLHANDLE 		hdbc, hdbc2 = (SQLHANDLE)NULL;
 	SQLHANDLE		hstmt, hstmt2;

	int				loop = 0;
	//char			preparedStmt[1024];
	char			infoStatsStmt[ 1024 ];
	SQLCHAR			cursorName[ 1024 ];
	CHAR			jobid[SQL_MAX_SESSIONNAME_LEN];
	CHAR			queryID[256];
	SQLINTEGER		jobidlen;
	SQLLEN			queryIDPtr;
	CHAR			tempStr[256];
                              
	char *droptab   =  "DROP TABLE JOBID cascade";
  	char *createtab =  "CREATE TABLE JOBID (C int) NO PARTITION";
  	char *inserttab =  "INSERT INTO JOBID VALUES (10)";
  	char *selecttab =  "SELECT * FROM JOBID";

	struct
	{
		RETCODE		returncode;
		CHAR		*jobID;
		CHAR		*jobIDExpected;
	} jobIDMatrix[] = {
        { SQL_SUCCESS, "1"                                                  , "1"},
        { SQL_SUCCESS, "11"                                                  , "11"},
		{ SQL_SUCCESS, ""                                                   , "" },
		{ SQL_SUCCESS, "H"                                                  , "H" },
		{ SQL_SUCCESS, "hh"                                                  , "hh" },
		{ SQL_SUCCESS, "0"                                                  , "0" },
		{ SQL_SUCCESS, "_"                                                  , "_" },
		{ SQL_SUCCESS, "________________________"                           , "________________________" },
		{ SQL_SUCCESS, "odbcqa"                                             , "odbcqa" },
		{ SQL_SUCCESS, "odbcqa00"                                           , "odbcqa00" },
		{ SQL_SUCCESS, "00odbcqa"                                           , "00odbcqa" },
		{ SQL_SUCCESS, "0123_HELLOKITTY"                                    , "0123_HELLOKITTY" },
		{ SQL_SUCCESS, "_Hello_Kitty_123"                                   , "_Hello_Kitty_123" },
		{ SQL_SUCCESS, "Hello_Kitty_Went_To_The_"							, "Hello_Kitty_Went_To_The_" },
		{ SQL_SUCCESS, "Hello_Kitty_Went_To_The_"							, "Hello_Kitty_Went_To_The_" },
		{ SQL_SUCCESS, "1234567890_1234567890"								, "1234567890_1234567890" },
		{ SQL_SUCCESS, "123456789012345678901234"                           , "123456789012345678901234" },
		{ SQL_SUCCESS, "123456789012345678901234"                           , "123456789012345678901234" },
		{ SQL_SUCCESS, "1234567890123456789012345"                          , "123456789012345678901234" },
		{ SQL_SUCCESS, "Hello_Kitty_Went_To_The_Store_To_Buy"				, "Hello_Kitty_Went_To_The_" },
		{ SQL_SUCCESS_WITH_INFO, " "										, "" },
		{ SQL_SUCCESS_WITH_INFO, " HelloKitty"                              , "" },
		{ SQL_SUCCESS_WITH_INFO, "Hello Kitty"                              , "" },
		{ SQL_SUCCESS_WITH_INFO, "HelloKitty "                              , "" },
		{ SQL_SUCCESS_WITH_INFO, "1 2"						                , "" },
		{ SQL_SUCCESS_WITH_INFO, "12345.67890.123456789012"                 , "" },
		{ SQL_SUCCESS_WITH_INFO, "Hello$Kitty"                              , "" },
		{ SQL_SUCCESS_WITH_INFO, "\"HelloKitty\""							, "" },
		{ SQL_SUCCESS_WITH_INFO, "'HelloKitty'"								, "" },
		{ SQL_SUCCESS_WITH_INFO, "\" \""                                    , "" },
		{ SQL_SUCCESS_WITH_INFO, "\"\""                                     , "" },
		{ SQL_SUCCESS_WITH_INFO, "\"#@*()-_=+[]{}|:;'<>,.?\""               , "" },
		{ -101				   , ""                                         , "" }
	};

	//struct
	//{
	//	RETCODE		rtc;
	//	CHAR		*queryID;
	//	CHAR		*queryIDExpected;
	//} queryIDMatrix[] = {
	//	{ SQL_SUCCESS, "HELLOKITTY"	                                        , "HELLOKITTY" },
	//	{ SQL_SUCCESS, "H"                                                  , "H" },
	//	{ SQL_SUCCESS, "HELLOKITTYWENTTOTHESTORETOBUYDRI"                   , "HELLOKITTYWENTTOTHESTORETOBUYDRI" },
	//	{ SQL_SUCCESS, "HELLOKITTYWENTTOTHESTORETOBUYDRINKSFORTHEPARTY"     , "HELLOKITTYWENTTOTHESTORETOBUYDRI" },
	//	{ SQL_SUCCESS, "HelloKitty"                                         , "HELLOKITTY" },
	//	{ SQL_SUCCESS, "h"                                                  , "H" },
	//	{ SQL_SUCCESS, "HelloKittyWentToTheStoreToBuyDri"                   , "HELLOKITTYWENTTOTHESTORETOBUYDRI" },
	//	{ SQL_SUCCESS, "HelloKittyWentToTheStoreToBuyDrinksForTheParty"     , "HELLOKITTYWENTTOTHESTORETOBUYDRI" },
	//	{ SQL_SUCCESS, "H_1"                                                , "H_1" },
	//	{ SQL_SUCCESS, "HELLO_KITTY_1234"                                   , "HELLO_KITTY_1234" },
	//	{ SQL_SUCCESS, "HELLO_KITTY_1234_ABCDEFGHIJKLMNO"                   , "HELLO_KITTY_1234_ABCDEFGHIJKLMNO" },
	//	{ SQL_SUCCESS, "HELLO_KITTY_1234_ABCDEFGHIJKLMNOPQRSTUVWXYZ"        , "HELLO_KITTY_1234_ABCDEFGHIJKLMNO" },
	//	{ SQL_SUCCESS, "Hello_Kitty_1234"                                   , "HELLO_KITTY_1234" },
	//	{ SQL_SUCCESS, "Hello_Kitty_1234_abcdefghijklmno"                   , "HELLO_KITTY_1234_ABCDEFGHIJKLMNO" },
	//	{ SQL_SUCCESS, "Hello_Kitty_1234_abcdefghijklmnopqrstuvwxyz"        , "HELLO_KITTY_1234_ABCDEFGHIJKLMNO" },
	//	{ SQL_SUCCESS, "\"HELLOKITTY\""                                     , "HELLOKITTY" },
	//	{ SQL_SUCCESS, "\"H\""                                              , "H" },
	//	{ SQL_SUCCESS, "\"HELLOKITTYWENTTOTHESTORETOBUYDRI\""               , "HELLOKITTYWENTTOTHESTORETOBUYDRI" },
	//	{ SQL_SUCCESS, "\"HELLOKITTYWENTTOTHESTORETOBUYDRINKSFORTHEPARTY\"" , "HELLOKITTYWENTTOTHESTORETOBUYDRI" },
	//	{ SQL_SUCCESS, "\"HelloKitty\""                                     , "HelloKitty" },
	//	{ SQL_SUCCESS, "\"h\""                                              , "h" },
	//	{ SQL_SUCCESS, "\"HelloKittyWentToTheStoreToBuyDri\""               , "HelloKittyWentToTheStoreToBuyDri" },
	//	{ SQL_SUCCESS, "\"HelloKittyWentToTheStoreToBuyDrinksForTheParty\"" , "HelloKittyWentToTheStoreToBuyDri" },
	//	{ SQL_SUCCESS, "\"H_1\""                                            , "H_1" },
	//	{ SQL_SUCCESS, "\"HELLO_KITTY_1234\""                               , "HELLO_KITTY_1234" },
	//	{ SQL_SUCCESS, "\"HELLO_KITTY_1234_ABCDEFGHIJKLMNO\""               , "HELLO_KITTY_1234_ABCDEFGHIJKLMNO" },
	//	{ SQL_SUCCESS, "\"HELLO_KITTY_1234_ABCDEFGHIJKLMNOPQRSTUVWXYZ\""    , "HELLO_KITTY_1234_ABCDEFGHIJKLMNO" },
	//	{ SQL_SUCCESS, "\"Hello_Kitty_1234\""                               , "Hello_Kitty_1234" },
	//	{ SQL_SUCCESS, "\"Hello_Kitty_1234_abcdefghijklmno\""               , "Hello_Kitty_1234_abcdefghijklmno" },
	//	{ SQL_SUCCESS, "\"Hello_Kitty_1234_abcdefghijklmnopqrstuvwxyz\""    , "Hello_Kitty_1234_abcdefghijklmno" },
	//	{ SQL_SUCCESS, "\"Hello Kitty\""                                    , "Hello Kitty" },
	//	{ SQL_SUCCESS, "\"Hello Kitty says \"\"MEOW!\"\"\""                 , "Hello Kitty says \"MEOW\"" },
	//	{ SQL_SUCCESS, "\"Hello Kitty's Pruse\""                            , "Hello Kitty's Purse" },
	//	{ SQL_SUCCESS, "\"CREATE\""                                         , "CREATE" },
	//	{ SQL_SUCCESS, "\"SELECT * FROM T1\""								, "SELECT * FROM T1" },
	//	{ SQL_ERROR  , ""                                                   , "" },
	//	{ SQL_ERROR  , "	"                                               , "" },
	//	{ SQL_ERROR  , "1HelloKitty"                                        , "" },
	//	{ SQL_ERROR  , "_A"                                                 , "" },
	//	{ SQL_ERROR  , "Hello Kitty"                                        , "" },
	//	{ SQL_ERROR  , "Hello$Kitty"                                        , "" },
	//	{ SQL_ERROR  , "\"\\HelloKitty\""                                   , "" },
	//	{ SQL_ERROR  , "\"$HelloKitty\""                                    , "" },
	//	{ SQL_ERROR  , "\" \""                                              , "" },
	//	{ SQL_ERROR  , "\"\""                                               , "" },
	//	{ SQL_ERROR  , "\"@*()-_=+[]{}|:;'<>,.?\""                          , "" },
	//	{ SQL_ERROR  , "CREATE"												, "" },
	//	{ -101       , ""                                                   , "" }
	//};

	//struct
	//{
	//	char*	sqlStmt;
	//} sqlPrepareMatrix[] = {
	//	{ "CREATE CATALOG STMNT" },
	//	{ "CREATE SCHEMA STMNT.TEST" },
	//	{ "CREATE TABLE T2 ( C1 INTEGER NOT NULL NOT DROPPABLE, C2 INTEGER, PRIMARY KEY( C1 ) )" },
	//	{ "CREATE INDEX T2_INDEX ON T2 ( C1 ) NO POPULATE" },
	//	{ "CREATE PROCEDURE T2_PROC (IN IN1 TIME) EXTERNAL NAME 'Procs.N4210' EXTERNAL PATH '/usr/spjqa/Testware/Class' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE" },
	//	{ "CREATE VIEW T2_VIEW AS SELECT C1 FROM T2" },
	//	{ "INSERT INTO T2 VALUES ( 1 , 1) " },
	//	{ "SELECT C1 FROM T2" },
	//	{ "UPDATE T2 SET C2 = 2 WHERE C1 = 1" },
	//	{ "DELETE FROM T2" },
	//	{ "ALTER INDEX T2_INDEX ON T2 ( C2 ) NO POPULATE" },
	//	{ "ALTER TABLE T2 ( C1 INTEGER NOT NULL NOT DROPPABLE, C2 INTEGER NOT NULL, PRIMARY KEY( C1 ) )" },
	//	{ "ALTER TRIGGER" },
	//	{ "DROP SCHEMA STMT.TEST" },
	//	{ "DROP CATALOG STMT" },
	//	{ "DROP INDEX T2_INDEX" },
	//	{ "DROP VIEW T2_VIEW" },
	//	{ "DROP PROCEDURE T2_PROC" },
	//	{ "DROP TABLE T2" },
	//	{ "STOP" }
	//};

//======================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => JobID | QueryID | QueryID.cpp\n");

	TEST_INIT;

	TESTCASE_BEGIN("Setup for JobID tests\n");

	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
		LogMsg(NONE,"Unable to connect as ODBC3.0 application.\n");
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
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLExecDirect(hstmt, (SQLCHAR*)droptab,SQL_NTS);

	returncode = SQLExecDirect(hstmt, (SQLCHAR*)createtab,SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLExecDirect(hstmt, (SQLCHAR*)inserttab,SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	FullDisconnect(pTestInfo);
	TESTCASE_END;

//======================================================================================================
	sprintf(Heading,"Test positive functionality of SessionName, single connection\n");
	TESTCASE_BEGIN( Heading);

	// Allocate Environment Handle
	returncode = SQLAllocEnv(&henv);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocEnv")) {
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetEnvAttr"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		SQLFreeEnv(henv);
		TEST_FAILED;
		TEST_RETURN;
	}

	// Allocate Connection handle
	returncode = SQLAllocConnect(henv,&hdbc);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocConnect")) {
		LogAllErrors(henv,hdbc,hstmt);
		SQLFreeEnv(henv);
		TEST_FAILED;
		TEST_RETURN;
	}
	TESTCASE_END;
	
	loop = 0;
	while( jobIDMatrix[ loop ].returncode != -101 )
	{
		sprintf(Heading,"Test #%d: Testing for jobID: %s\n", loop, jobIDMatrix[ loop ].jobID);
		TESTCASE_BEGIN( Heading);

		returncode = SQLSetConnectAttr(hdbc, (SQLINTEGER)SQL_ATTR_SESSIONNAME,(SQLCHAR*) jobIDMatrix[ loop ].jobID, SQL_NTS);
		if (jobIDMatrix[ loop ].returncode == SQL_SUCCESS) {
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetConnectAttr")) {
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				loop++;
				continue;
			}

		}
		else {
#ifdef unixcli
			if(returncode != SQL_ERROR) {
#else
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetConnectAttr")) {
#endif
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				loop++;
				continue;
			}
		}
		returncode = SQLGetConnectAttr(hdbc, (SQLINTEGER)SQL_ATTR_SESSIONNAME, jobid, SQL_MAX_SESSIONNAME_LEN, &jobidlen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetConnectAttr")) {
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			loop++;
			continue;
		}
		if (jobIDMatrix[ loop ].returncode == SQL_SUCCESS) {
			if (strcmp(jobIDMatrix[ loop ].jobIDExpected, jobid) == 0) {
				LogMsg(NONE, "JobIDs are matched. Expected: \"%s\", Actual: \"%s\" for SQLGetConnectAttr\n", jobIDMatrix[ loop ].jobIDExpected, jobid);
				TESTCASE_END;
			}
			else {
				LogMsg(ERRMSG, "JobIDs are not matched. Expected: \"%s\", Actual: \"%s\", at line=%d for SQLGetConnectAttr\n", jobIDMatrix[ loop ].jobIDExpected, jobid, __LINE__);
				TEST_FAILED;
			}
		}
		else {
#ifdef unixcli
			if (strcmp(jobIDMatrix[ loop ].jobIDExpected, jobid) == 0) {
#else
			if (strcmp(jobIDMatrix[ loop ].jobID, jobid) == 0) {
#endif
				LogMsg(NONE, "JobIDs are matched. Expected: \"%s\", Actual: \"%s\" for SQLGetConnectAttr\n", jobIDMatrix[ loop ].jobID, jobid);
				TESTCASE_END;
			}
			else {
				LogMsg(ERRMSG, "JobIDs are not matched. Expected: \"%s\", Actual: \"%s\", at line=%d for SQLGetConnectAttr\n", jobIDMatrix[ loop ].jobID, jobid, __LINE__);
				TEST_FAILED;
			}
		}

		returncode = SQLConnect(hdbc,
							   (SQLCHAR*)pTestInfo->DataSource,(SWORD)strlen(pTestInfo->DataSource),
							   (SQLCHAR*)pTestInfo->UserID,(SWORD)strlen(pTestInfo->UserID),
							   (SQLCHAR*)pTestInfo->Password,(SWORD)strlen(pTestInfo->Password)
							   );	
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLConnect")) {
			LogAllErrors(henv,hdbc,hstmt);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

#ifndef unixcli
		if (jobIDMatrix[ loop ].returncode ==  SQL_SUCCESS_WITH_INFO) {
			if (returncode != jobIDMatrix[ loop ].returncode) {
				LogMsg(ERRMSG, "The retcode has to be SQL_SUCCESS_WITH_INFO, with the error message \"Driver's SQLSetConnectAttr failed.\" in it, at line=%d\n", __LINE__);
				SQLFreeConnect(hdbc);
				SQLFreeEnv(henv);
				TEST_FAILED;
				TEST_RETURN;
			}
//			LogAllErrors(henv,hdbc,NULL);
			if (!FindError("IM006",henv,hdbc,NULL)) {
				LogMsg(ERRMSG, "Couldn't find state error IM006, with the error message \"Driver's SQLSetConnectAttr failed.\", at line=%d\n", __LINE__);
				SQLFreeConnect(hdbc);
				SQLFreeEnv(henv);
				TEST_FAILED;
				TEST_RETURN;
			}
		}
#endif

		returncode = SQLAllocStmt(hdbc,&hstmt);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt")) {
			LogAllErrors(henv,hdbc,hstmt);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLAllocStmt(hdbc,&hstmt2);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt")) {
			LogAllErrors(henv,hdbc,hstmt);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLPrepare( hstmt, (SQLCHAR *)selecttab, SQL_NTS );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")) {
			LogAllErrors(henv,hdbc,hstmt);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLGetCursorName(hstmt, cursorName, sizeof(cursorName), NULL );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")) {
			LogAllErrors(henv,hdbc,hstmt);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		//Get queryID
		sprintf( infoStatsStmt, "INFOSTATS %s", (char*)cursorName );
		returncode = SQLBindCol( hstmt2, 1, SQL_C_CHAR, &queryID, 256, &queryIDPtr );
 		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLExecDirect( hstmt2, (SQLCHAR *)infoStatsStmt, SQL_NTS );
 		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLFetch( hstmt2 );
 		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		LogMsg(NONE, "queryID: \"%s\"\n", queryID);
		SQLFreeStmt(hstmt2,SQL_CLOSE);
		SQLFreeStmt(hstmt2,SQL_UNBIND);

		//Get Jobid
		if(isCharSet || isUCS2)
			sprintf( infoStatsStmt, "SELECT queryid_extract( _ISO88591'%s',_ISO88591'SESSIONNAME') FROM JOBID", (char*)queryID );
		else
			sprintf( infoStatsStmt, "SELECT queryid_extract('%s','SESSIONNAME') FROM JOBID", (char*)queryID );

		returncode = SQLBindCol( hstmt2, 1, SQL_C_CHAR, &queryID, 256, &queryIDPtr );
 		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLExecDirect( hstmt2, (SQLCHAR *)infoStatsStmt, SQL_NTS );
 		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLFetch( hstmt2 );
 		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		LogMsg(NONE, "JobID: \"%s\"\n", queryID);
		if (strcmp(jobIDMatrix[ loop ].jobIDExpected, queryID) == 0) {
			LogMsg(NONE, "JobIDs are matched. Expected: \"%s\", Actual: \"%s\" for after queryid_extract\n", jobIDMatrix[ loop ].jobIDExpected, queryID);
			TESTCASE_END;
		}
		else {
			LogMsg(ERRMSG, "JobIDs are not matched. Expected: \"%s\", Actual: \"%s\", at line=%d for after queryid_extract\n", jobIDMatrix[ loop ].jobIDExpected, queryID, __LINE__);
			TEST_FAILED;
		}

		SQLFreeStmt(hstmt,SQL_CLOSE);
		SQLFreeStmt(hstmt,SQL_UNBIND);
		SQLFreeStmt(hstmt2,SQL_CLOSE);
		SQLFreeStmt(hstmt2,SQL_UNBIND);

		returncode = SQLDisconnect(hdbc);
		if (returncode != SQL_SUCCESS)
		{
			LogAllErrors(henv,hdbc,hstmt);
			SQLDisconnect(hdbc);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
		}
   		loop++;
	}

	returncode = SQLFreeConnect(hdbc);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv,hdbc,hstmt);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
	}

	returncode = SQLFreeEnv(henv);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv,hdbc,hstmt);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
	}

//======================================================================================================
	sprintf(Heading,"Test positive functionality of SessionName, mutiple connection using the same session name\n");
	TESTCASE_BEGIN( Heading);

	// Allocate Environment Handle
	returncode = SQLAllocEnv(&henv);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocEnv")) {
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	returncode = SQLAllocEnv(&henv2);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocEnv2")) {
		LogAllErrors(henv2,hdbc2,hstmt2);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetEnvAttr"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		SQLFreeEnv(henv);
		TEST_FAILED;
		TEST_RETURN;
	}
	returncode = SQLSetEnvAttr(henv2, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetEnvAttr2"))
	{
		LogAllErrors(henv2,hdbc2,hstmt2);
		SQLFreeEnv(henv2);
		TEST_FAILED;
		TEST_RETURN;
	}

	// Allocate Connection handle
	returncode = SQLAllocConnect(henv,&hdbc);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocConnect")) {
		LogAllErrors(henv,hdbc,hstmt);
		SQLFreeEnv(henv);
		TEST_FAILED;
		TEST_RETURN;
	}
	returncode = SQLAllocConnect(henv2,&hdbc2);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocConnect2")) {
		LogAllErrors(henv2,hdbc2,hstmt2);
		SQLFreeEnv(henv2);
		TEST_FAILED;
		TEST_RETURN;
	}
	TESTCASE_END;
	

	strcpy(tempStr,"123456789012345678901234");
	sprintf(Heading,"Testing for jobID: %s\n", tempStr);
	TESTCASE_BEGIN( Heading);

	returncode = SQLSetConnectAttr(hdbc, (SQLINTEGER)SQL_ATTR_SESSIONNAME,(SQLCHAR*) tempStr, SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetConnectAttr")) {
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	returncode = SQLSetConnectAttr(hdbc2, (SQLINTEGER)SQL_ATTR_SESSIONNAME,(SQLCHAR*) tempStr, SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetConnectAttr2")) {
		LogAllErrors(henv2,hdbc2,hstmt2);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLGetConnectAttr(hdbc, (SQLINTEGER)SQL_ATTR_SESSIONNAME, jobid, SQL_MAX_SESSIONNAME_LEN, &jobidlen);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetConnectAttr")) {
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
	}
	if (strcmp(tempStr, jobid) == 0) {
		LogMsg(NONE, "JobID1 are matched. Expected: \"%s\", Actual: \"%s\" for hdbc\n", tempStr, jobid);
	}
	else {
		LogMsg(ERRMSG, "JobID1 are not matched. Expected: \"%s\", Actual: \"%s\", at line=%d for hdbc\n", tempStr, jobid, __LINE__);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLGetConnectAttr(hdbc2, (SQLINTEGER)SQL_ATTR_SESSIONNAME, jobid, SQL_MAX_SESSIONNAME_LEN, &jobidlen);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetConnectAttr2")) {
		LogAllErrors(henv2,hdbc2,hstmt2);
		TEST_FAILED;
		TEST_RETURN;
	}
	if (strcmp(tempStr, jobid) == 0) {
		LogMsg(NONE, "JobID2 are matched. Expected: \"%s\", Actual: \"%s\" for hdbc2\n", tempStr, jobid);
	}
	else {
		LogMsg(ERRMSG, "JobID2 are not matched. Expected: \"%s\", Actual: \"%s\", at line=%d for hdbc2\n", tempStr, jobid, __LINE__);
		TEST_FAILED;
		TEST_RETURN;
	}

	returncode = SQLConnect(hdbc,
						   (SQLCHAR*)pTestInfo->DataSource,(SWORD)strlen(pTestInfo->DataSource),
						   (SQLCHAR*)pTestInfo->UserID,(SWORD)strlen(pTestInfo->UserID),
						   (SQLCHAR*)pTestInfo->Password,(SWORD)strlen(pTestInfo->Password)
						   );	
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLConnect")) {
		LogAllErrors(henv,hdbc,hstmt);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
		TEST_FAILED;
		TEST_RETURN;
	}
	returncode = SQLConnect(hdbc2,
						   (SQLCHAR*)pTestInfo->DataSource,(SWORD)strlen(pTestInfo->DataSource),
						   (SQLCHAR*)pTestInfo->UserID,(SWORD)strlen(pTestInfo->UserID),
						   (SQLCHAR*)pTestInfo->Password,(SWORD)strlen(pTestInfo->Password)
						   );	
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLConnect2")) {
		LogAllErrors(henv2,hdbc2,hstmt2);
		SQLFreeConnect(hdbc2);
		SQLFreeEnv(henv2);
		TEST_FAILED;
		TEST_RETURN;
	}

	for (loop=0; loop<2; loop++) {
		if (loop == 0) {
			returncode = SQLAllocStmt(hdbc,&hstmt);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt")) {
				LogAllErrors(henv,hdbc,hstmt);
				SQLFreeConnect(hdbc);
				SQLFreeEnv(henv);
				TEST_FAILED;
				TEST_RETURN;
			}
			returncode = SQLAllocStmt(hdbc,&hstmt2);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt3")) {
				LogAllErrors(henv,hdbc,hstmt2);
				SQLFreeConnect(hdbc);
				SQLFreeEnv(henv);
				TEST_FAILED;
				TEST_RETURN;
			}
		}
		else {
			returncode = SQLAllocStmt(hdbc2,&hstmt);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt")) {
				LogAllErrors(henv2,hdbc2,hstmt);
				SQLFreeConnect(hdbc2);
				SQLFreeEnv(henv2);
				TEST_FAILED;
				TEST_RETURN;
			}
			returncode = SQLAllocStmt(hdbc2,&hstmt2);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt3")) {
				LogAllErrors(henv2,hdbc2,hstmt2);
				SQLFreeConnect(hdbc2);
				SQLFreeEnv(henv2);
				TEST_FAILED;
				TEST_RETURN;
			}
		}

		returncode = SQLPrepare( hstmt, (SQLCHAR *)selecttab, SQL_NTS );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")) {
			LogAllErrors(henv,hdbc,hstmt);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLGetCursorName(hstmt, cursorName, sizeof(cursorName), NULL );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare")) {
			LogAllErrors(henv,hdbc,hstmt);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		//Get queryID
		sprintf( infoStatsStmt, "INFOSTATS %s", (char*)cursorName );
		returncode = SQLBindCol( hstmt2, 1, SQL_C_CHAR, &queryID, 256, &queryIDPtr );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLExecDirect( hstmt2, (SQLCHAR *)infoStatsStmt, SQL_NTS );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLFetch( hstmt2 );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		LogMsg(NONE, "queryID%d: \"%s\"\n", loop, queryID);
		SQLFreeStmt(hstmt2,SQL_CLOSE);
		SQLFreeStmt(hstmt2,SQL_UNBIND);

		//Get Jobid
		if(isCharSet || isUCS2)
			sprintf( infoStatsStmt, "SELECT queryid_extract( _ISO88591'%s', _ISO88591'SESSIONNAME') FROM JOBID", (char*)queryID );
		else
			sprintf( infoStatsStmt, "SELECT queryid_extract('%s','SESSIONNAME') FROM JOBID", (char*)queryID );

		returncode = SQLBindCol( hstmt2, 1, SQL_C_CHAR, &queryID, 256, &queryIDPtr );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLExecDirect( hstmt2, (SQLCHAR *)infoStatsStmt, SQL_NTS );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		returncode = SQLFetch( hstmt2 );
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")) {
			LogAllErrors(henv,hdbc,hstmt2);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			TEST_FAILED;
			TEST_RETURN;
		}

		LogMsg(NONE, "JobID%d: \"%s\"\n", loop, queryID);
		if (strcmp(tempStr, queryID) == 0) {
			LogMsg(NONE, "JobID%d are matched. Expected: \"%s\", Actual: \"%s\" for after queryid_extract\n", loop, tempStr, queryID);
			TESTCASE_END;
		}
		else {
			LogMsg(ERRMSG, "JobID%d are not matched. Expected: \"%s\", Actual: \"%s\", at line=%d for after queryid_extract\n", loop, tempStr, queryID, __LINE__);
			TEST_FAILED;
		}

		SQLFreeStmt(hstmt,SQL_CLOSE);
		SQLFreeStmt(hstmt,SQL_UNBIND);
		SQLFreeStmt(hstmt2,SQL_CLOSE);
		SQLFreeStmt(hstmt2,SQL_UNBIND);
	}

	returncode = SQLDisconnect(hdbc);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv,hdbc,hstmt);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
	}
	returncode = SQLDisconnect(hdbc2);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv2,hdbc2,hstmt2);
		SQLDisconnect(hdbc2);
		SQLFreeConnect(hdbc2);
		SQLFreeEnv(henv2);
	}

	returncode = SQLFreeConnect(hdbc);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv,hdbc,hstmt);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
	}
	returncode = SQLFreeConnect(hdbc2);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv2,hdbc2,hstmt2);
		SQLDisconnect(hdbc2);
		SQLFreeConnect(hdbc2);
		SQLFreeEnv(henv2);
	}

	returncode = SQLFreeEnv(henv);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv,hdbc,hstmt);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
	}
	returncode = SQLFreeEnv(henv2);
	if (returncode != SQL_SUCCESS)
	{
		LogAllErrors(henv2,hdbc2,hstmt2);
		SQLDisconnect(hdbc2);
		SQLFreeConnect(hdbc2);
		SQLFreeEnv(henv2);
	}

	//=========================================================================================

	//FullDisconnect(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => JobID.\n");
	TEST_RETURN;
}