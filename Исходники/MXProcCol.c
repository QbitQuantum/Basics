/*
---------------------------------------------------------
   TestSQLProcedureColumns
---------------------------------------------------------
*/
PassFail TestMXSQLProcedureColumns(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;
 	TCHAR			Heading[MAX_HEADING_SIZE];
 	RETCODE			returncode;
 	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt;
	TCHAR			*ProcStr;
  	TCHAR			ProcCatalog[NAME_LEN],ProcSchema[NAME_LEN],ProcName[NAME_LEN];
    TCHAR           ColName[NAME_LEN];
/* SEAQUEST */
char                    tmpbuf[1024];
TCHAR                   *myTestSch;
TCHAR                   *createSchStr;
TCHAR                   *setSchStr;
TCHAR                   *dropSchStr;
/* end of SEAQUEST */
	TCHAR			oProcCatalog[NAME_LEN];
	TCHAR			oProcSchema[NAME_LEN];
	TCHAR			oProcName[NAME_LEN];
	TCHAR			oColName[NAME_LEN];
	SWORD			oColType;
	SWORD			oColDataType;
	TCHAR			oColTypeName[NAME_LEN];
	SDWORD			oColSize;
	SDWORD			oBufferLen;
	SWORD			oDecDigits;
	SWORD			oColRadix;
	SWORD			oColNullable;
	TCHAR			oRemark[REM_LEN];
	TCHAR			oColDef[NAME_LEN];
	SWORD			oSQLDataType;
	SWORD			oSQLDateTimeSub;
	SDWORD			oCharOctetLen;
	SDWORD			oOrdinalPos;
	TCHAR			oIsNullable[NAME_LEN];
	SQLLEN		oProcCataloglen; // sushil
	SQLLEN		oProcSchemalen;
	SQLLEN		oProcNamelen;
	SQLLEN		oColNamelen;
	SQLLEN		oColTypelen;
	SQLLEN		oColDataTypelen;
	SQLLEN		oColTypeNamelen;
	SQLLEN		oColSizelen;
	SQLLEN		oBufferLenlen;
	SQLLEN		oDecDigitslen;
	SQLLEN		oColRadixlen;
	SQLLEN		oColNullablelen;
	SQLLEN		oRemarklen;
	SQLLEN		oColDeflen;
	SQLLEN		oSQLDataTypelen;
	SQLLEN		oSQLDateTimeSublen;
	SQLLEN		oCharOctetLenlen;
	SQLLEN		oOrdinalPoslen;
	SQLLEN		oIsNullablelen;

	struct	
	{
		TCHAR		*DropProc;
		TCHAR		*CrtProc;
	} CreateProc[] = {
							{_T("DROP PROCEDURE N4210"),
							 _T("CREATE PROCEDURE N4210 (IN IN1 TIME) EXTERNAL NAME 'Procs.N4210' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},
							{_T("DROP PROCEDURE N4260"),
							 _T("CREATE PROCEDURE N4260 (IN IN1 REAL, INOUT INOUT1 INTEGER) EXTERNAL NAME 'Procs.N4260' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},
							{_T("DROP PROCEDURE N4261"),
 							 _T("CREATE PROCEDURE N4261 (IN IN1 NUMERIC, INOUT INOUT1 REAL) EXTERNAL NAME 'Procs.N4261' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},
							{_T("DROP PROCEDURE N4264"),
 							 _T("CREATE PROCEDURE N4264 (IN IN1 VARCHAR(30) CHARACTER SET ISO88591, OUT OUT1 VARCHAR(45) CHARACTER SET ISO88591) EXTERNAL NAME 'Procs.N4264' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},	
							{_T("DROP PROCEDURE N4264A"),
 							 _T("CREATE PROCEDURE N4264A (IN IN1 CHAR(30) CHARACTER SET ISO88591, OUT OUT1 CHAR(45) CHARACTER SET ISO88591) EXTERNAL NAME 'Procs.N4264' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},	
							{_T("DROP PROCEDURE N4264B"),
 							 _T("CREATE PROCEDURE N4264B (IN IN1 VARCHAR(2000) CHARACTER SET ISO88591, OUT OUT1 VARCHAR(2000) CHARACTER SET ISO88591) EXTERNAL NAME 'Procs.N4264' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},	
							{_T("DROP PROCEDURE N4264C"),
 							 _T("CREATE PROCEDURE N4264C (IN IN1 VARCHAR(30) CHARACTER SET UCS2, OUT OUT1 VARCHAR(45) CHARACTER SET UCS2) EXTERNAL NAME 'Procs.N4264' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},	
							{_T("DROP PROCEDURE N4264D"),
 							 _T("CREATE PROCEDURE N4264D (IN IN1 CHAR(30) CHARACTER SET UCS2, OUT OUT1 CHAR(45) CHARACTER SET UCS2) EXTERNAL NAME 'Procs.N4264' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},	
							{_T("DROP PROCEDURE N4264E"),
 							 _T("CREATE PROCEDURE N4264E (IN IN1 VARCHAR(2000) CHARACTER SET UCS2, OUT OUT1 VARCHAR(2000) CHARACTER SET UCS2) EXTERNAL NAME 'Procs.N4264' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},	
							{_T("DROP PROCEDURE N4267"),
 							 _T("CREATE PROCEDURE N4267 (IN IN1 NUMERIC, INOUT INOUT1 REAL) EXTERNAL NAME 'Procs.N4267' EXTERNAL PATH '/home/SQFQA/SPJRoot/spjrs/nci/spjrs.jar' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE")},
							{_T("endloop"),_T("endloop")}
					};

	struct
	{
		TCHAR       *ProcName;
		TCHAR		*ColName;
		SWORD		ColType;
		SWORD		ColDataType;
		TCHAR		*ColTypeName;
		SDWORD		ColSize;
		SDWORD		BufferLen;
		SWORD		DecDigits;
		SWORD		ColRadix;
		SWORD		ColNullable;
		TCHAR		*Remark;
		TCHAR       *ColDef;
		SWORD       SQLDataType;
		SWORD       SQLDateTimeSub;
		SDWORD		CharOctetLen;
		SDWORD		OrdinalPos;
		TCHAR		*IsNullable;
	} ProcCol[] = {
/*		{"N4210", "IN1",	SQL_PARAM_INPUT,		SQL_TYPE_TIME,	"TIME",			8,	 6, 0, <Null>,	SQL_NULLABLE, <Null>, <Null>, 9,	  2, <Null>, 1, "YES"},
		{"N4260", "IN1",	SQL_PARAM_INPUT,		SQL_REAL,		"REAL",			22,  4, 0, 2,		SQL_NULLABLE, <Null>, <Null>, 7, <Null>, <Null>, 1, "YES"},
		{"N4260", "INOUT1", SQL_PARAM_INPUT_OUTPUT, SQL_INTEGER, "INTEGER SIGNED",	10,  4, 0, 10,		SQL_NULLABLE, <Null>, <Null>, 4, <Null>, <Null>, 2, "YES"},
		{"N4261", "IN1",	SQL_PARAM_INPUT,		SQL_NUMERIC, "NUMERIC",			9,  11, 0, 10,		SQL_NULLABLE, <Null>, <Null>, 2, <Null>, <Null>, 1, "YES"},
		{"N4261", "INOUT1", SQL_PARAM_INPUT_OUTPUT, SQL_REAL,	 "REAL",			22,  4, 0, 2,		SQL_NULLABLE, <Null>, <Null>, 7, <Null>, <Null>, 2, "YES"},
		{"N4264", "IN1",	SQL_PARAM_INPUT,		SQL_WVARCHAR, "VARCHAR",			30, 30, 0, <Null>,	SQL_NULLABLE, <Null>, <Null>, 12,<Null>,     30, 1, "YES"},
		{"N4264", "OUT1",	SQL_PARAM_OUTPUT,		SQL_WVARCHAR, "VARCHAR",			45, 45, 0, <Null>,	SQL_NULLABLE, <Null>, <Null>, 12,<Null>,     45, 2, "YES"},
		{"N4267", "IN1",	SQL_PARAM_INPUT,		SQL_NUMERIC, "NUMERIC",			9,  11, 0, 10,		SQL_NULLABLE, <Null>, <Null>, 2, <Null>, <Null>, 1, "YES"},
		{"N4267", "INOUT1", SQL_PARAM_INPUT_OUTPUT, SQL_REAL,	 "REAL",			22,	 4, 0, 2,		SQL_NULLABLE, <Null>, <Null>, 7, <Null>, <Null>, 2, "YES"},
*/
		{_T("N4210"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_TYPE_TIME,	_T("TIME"),			8,	 6, 0, 0,	SQL_NULLABLE, _T(""), _T(""), 9, 2, 0, 1, _T("YES")},
		{_T("N4260"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_REAL,		_T("REAL"),			22,  4, 0, 2,	SQL_NULLABLE, _T(""), _T(""), 7, 0, 0, 1, _T("YES")},
		{_T("N4260"), _T("INOUT1"), SQL_PARAM_INPUT_OUTPUT, SQL_INTEGER,	_T("INTEGER SIGNED"),10,  4, 0, 10,	SQL_NULLABLE, _T(""), _T(""), 4, 0, 0, 2, _T("YES")},
		{_T("N4261"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_NUMERIC,	_T("NUMERIC SIGNED"),9,  11, 0, 10,	SQL_NULLABLE, _T(""), _T(""), 2, 0, 0, 1, _T("YES")},
		{_T("N4261"), _T("INOUT1"), SQL_PARAM_INPUT_OUTPUT, SQL_REAL,		_T("REAL"),			22,  4, 0, 2,	SQL_NULLABLE, _T(""), _T(""), 7, 0, 0, 2, _T("YES")},
		{_T("N4264"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_VARCHAR,	_T("VARCHAR"),		30, 30, 0, 0,	SQL_NULLABLE, _T(""), _T(""), 12,0, 30,1, _T("YES")},
		{_T("N4264"), _T("OUT1"),	SQL_PARAM_OUTPUT,		SQL_VARCHAR,	_T("VARCHAR"),		45, 45, 0, 0,	SQL_NULLABLE, _T(""), _T(""), 12,0, 45,2, _T("YES")},
		{_T("N4264A"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_CHAR,		_T("CHAR"),			30, 30, 0, 0,	SQL_NULLABLE, _T(""), _T(""),  1,0, 30,1, _T("YES")},
		{_T("N4264A"), _T("OUT1"),	SQL_PARAM_OUTPUT,		SQL_CHAR,		_T("CHAR"),			45, 45, 0, 0,	SQL_NULLABLE, _T(""), _T(""),  1,0, 45,2, _T("YES")},
		{_T("N4264B"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_VARCHAR, _T("VARCHAR"),2000,2000,0,0,	SQL_NULLABLE, _T(""), _T(""), 12,0,2000,1, _T("YES")},
		{_T("N4264B"), _T("OUT1"),	SQL_PARAM_OUTPUT,		SQL_VARCHAR, _T("VARCHAR"),2000,2000,0,0,	SQL_NULLABLE, _T(""), _T(""), 12,0,2000,2, _T("YES")},
		{_T("N4264C"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_WVARCHAR,	_T("NCHAR VARYING"),30, 60, 0, 0,	SQL_NULLABLE, _T(""), _T(""), -9,0, 60,1, _T("YES")},
		{_T("N4264C"), _T("OUT1"),	SQL_PARAM_OUTPUT,		SQL_WVARCHAR,	_T("NCHAR VARYING"),45, 90, 0, 0,	SQL_NULLABLE, _T(""), _T(""), -9,0, 90,2, _T("YES")},
		{_T("N4264D"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_WCHAR,		_T("NCHAR"),		30, 60, 0, 0,	SQL_NULLABLE, _T(""), _T(""), -8,0, 60,1, _T("YES")},
		{_T("N4264D"), _T("OUT1"),	SQL_PARAM_OUTPUT,		SQL_WCHAR,		_T("NCHAR"),		45, 90, 0, 0,	SQL_NULLABLE, _T(""), _T(""), -8,0, 90,2, _T("YES")},
		{_T("N4264E"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_WVARCHAR,_T("NCHAR VARYING"),2000,4000,0,0,	SQL_NULLABLE, _T(""), _T(""),-9,0,4000,1, _T("YES")},
		{_T("N4264E"), _T("OUT1"),	SQL_PARAM_OUTPUT,		SQL_WVARCHAR,_T("NCHAR VARYING"),2000,4000,0,0,	SQL_NULLABLE, _T(""), _T(""),-9,0,4000,2, _T("YES")},
		{_T("N4267"), _T("IN1"),	SQL_PARAM_INPUT,		SQL_NUMERIC,	_T("NUMERIC SIGNED"),9,  11, 0, 10,	SQL_NULLABLE, _T(""), _T(""), 2, 0, 0, 1, _T("YES")},
		{_T("N4267"), _T("INOUT1"), SQL_PARAM_INPUT_OUTPUT, SQL_REAL,		_T("REAL"),			22,	 4, 0, 2,	SQL_NULLABLE, _T(""), _T(""), 7, 0, 0, 2, _T("YES")},
		{_T("endloop"),}
	};

	
	int	i = 0, k = 0;
	TCHAR	State[STATE_SIZE];
	SDWORD	NativeError;
	TCHAR	buf[MAX_STRING_SIZE];
	//TCHAR	*charNameUCS2 = _T("NCHAR");
	//TCHAR	*varcharNameUCS2 = _T("NCHAR VARYING");
	
	LogMsg(SHORTTIMESTAMP,_T("Begin testing API => MX Specific SQLProcedureColumns.\n"));

//=================================================================================================
	//if(isUCS2) {
	//	LogMsg(LINEBEFORE,_T("Setup for UCS2 mode testing: ColSize,BufferLen and CharOctetlen has to be doubled\n"));

	//	k = sizeof(ProcCol)/sizeof(ProcCol[0]);
	//	while(i < k) {
	//		if(ProcCol[i].ColDataType == SQL_WCHAR)
	//		{
	//			ProcCol[i].ColDataType = SQL_WCHAR;
	//			ProcCol[i].SQLDataType = SQL_WCHAR;
	//			ProcCol[i].ColTypeName = charNameUCS2;
	//			//ProcCol[i].ColSize *= 2;  --> This is in character, no need to double
	//			ProcCol[i].BufferLen *= 2;
	//			ProcCol[i].CharOctetLen *= 2;
	//		}
	//		else if (ProcCol[i].ColDataType == SQL_WVARCHAR)
	//		{
	//			ProcCol[i].ColDataType = SQL_WVARCHAR;
	//			ProcCol[i].SQLDataType = SQL_WVARCHAR;
	//			ProcCol[i].ColTypeName = varcharNameUCS2;
	//			//ProcCol[i].ColSize *= 2; --> This is in character, no need to double
	//			ProcCol[i].BufferLen *= 2;
	//			ProcCol[i].CharOctetLen *= 2;
	//		}
	//		else if (ProcCol[i].ColDataType == SQL_WLONGVARCHAR)
	//		{
	//			ProcCol[i].ColDataType = SQL_WLONGVARCHAR;
	//			ProcCol[i].SQLDataType = SQL_WLONGVARCHAR;
	//			ProcCol[i].ColTypeName = varcharNameUCS2;
	//			//ProcCol[i].ColSize *= 2; --> This is in character, no need to double
	//			ProcCol[i].BufferLen *= 2;
	//			ProcCol[i].CharOctetLen *= 2;
	//		}
	//		else {}

	//		i++;
	//	}
	//	i = 0;
	//	k = 0;
	//}
//=================================================================================================

	
	TEST_INIT;

	TESTCASE_BEGIN("Setup for SQLProcedureColumns tests\n");

	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
		LogMsg(NONE,_T("Unable to connect\n"));
		//TEST_FAILED;
		TEST_RETURN;
	}

	henv = pTestInfo->henv;
 	hdbc = pTestInfo->hdbc;
 	hstmt = (SQLHANDLE)pTestInfo->hstmt;
   	
 	returncode = SQLAllocHandle(SQL_HANDLE_STMT, (SQLHANDLE)hdbc, &hstmt);	
 	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		FullDisconnect3(pTestInfo);
		//TEST_FAILED;
		TEST_RETURN;
	}
	//TESTCASE_END; 

	ProcStr = (TCHAR *)malloc(MAX_NOS_SIZE);
/* SEAQUEST */
        myTestSch = (TCHAR *)malloc(MAX_NOS_SIZE);
        createSchStr = (TCHAR *)malloc(MAX_NOS_SIZE);
        setSchStr = (TCHAR *)malloc(MAX_NOS_SIZE);
        dropSchStr = (TCHAR *)malloc(MAX_NOS_SIZE);
        _tcscpy (myTestSch, _T("ODBC_PROCCOL_TEST"));
        _tcscpy (createSchStr, _T("create schema "));
        _tcscat (createSchStr, pTestInfo->Catalog);
        _tcscat (createSchStr, _T("."));
        _tcscat (createSchStr, myTestSch);
        _tcscpy (setSchStr, _T("set schema "));
        _tcscat (setSchStr, pTestInfo->Catalog);
        _tcscat (setSchStr, _T("."));
        _tcscat (setSchStr, myTestSch);
        _tcscpy (dropSchStr, _T("drop schema "));
        _tcscat (dropSchStr, pTestInfo->Catalog);
        _tcscat (dropSchStr, _T("."));
        _tcscat (dropSchStr, myTestSch);
        _tcscat (dropSchStr, _T(" cascade"));
        returncode = SQLExecDirect(hstmt,(SQLTCHAR*) dropSchStr,SQL_NTS);
        // if(!CHECKRC(SQL_SUCCESS,returncode,"Drop Schema"))
        // {
        //      TEST_FAILED;
        //      LogAllErrors(henv,hdbc,hstmt);
        // }
        returncode = SQLExecDirect(hstmt,(SQLTCHAR*) createSchStr,SQL_NTS);
        if(!CHECKRC(SQL_SUCCESS,returncode,"Create Schema"))
        {
                TEST_FAILED;
                LogAllErrors(henv,hdbc,hstmt);
        }
        returncode = SQLExecDirect(hstmt,(SQLTCHAR*) setSchStr,SQL_NTS);
        if(!CHECKRC(SQL_SUCCESS,returncode,"Set Schema"))
        {
                TEST_FAILED;
                LogAllErrors(henv,hdbc,hstmt);
        }
/* end of SEAQUEST */

	while (_tcsicmp(CreateProc[i].DropProc,_T("endloop")) != 0)
	{
		_tcscpy(ProcStr,_T(""));
		_tcscat(ProcStr,CreateProc[i].DropProc);
		SQLExecDirect(hstmt,(SQLTCHAR*) ProcStr,SQL_NTS); // cleanup
		_tcscpy(ProcStr,_T(""));
		_tcscat(ProcStr,CreateProc[i].CrtProc);
		_stprintf(Heading,_T("Adding Procedure => "));
		_tcscat(Heading,ProcStr);
		_tcscat(Heading,_T("\n"));
		TESTCASE_BEGINW(Heading);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ProcStr,SQL_NTS);
		if(returncode != SQL_SUCCESS)
		{
			returncode = SQLError((SQLHANDLE)NULL, (SQLHANDLE)NULL, hstmt, (SQLTCHAR*)State, &NativeError, (SQLTCHAR*)buf, MAX_STRING_SIZE, NULL);
			if (NativeError == -2013)
			{
				LogMsg(NONE, _T("Stored Procedures not supported\n"));
				_gTestCount--;
				free(ProcStr);
				FullDisconnect(pTestInfo);
				LogMsg(SHORTTIMESTAMP,_T("End testing API => MX Specific SQLProcedureColumns.\n"));
				TEST_RETURN;
			}
			else
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt);
			}
		}
		TESTCASE_END;
		i++;
	}

	_tcscpy(ProcCatalog, pTestInfo->Catalog);
	_tcscpy(ProcSchema, myTestSch /*SEAQUEST pTestInfo->Schema*/);
	
	_stprintf(Heading,_T("Test Positive Functionality of SQLProcedureColumns \n"));
	TESTCASE_BEGINW(Heading);
	returncode = SQLProcedureColumns(hstmt,(SQLTCHAR*)pTestInfo->Catalog,(SWORD)_tcslen(pTestInfo->Catalog),(SQLTCHAR*)myTestSch/* SEAQUEST pTestInfo->Schema*/,(SWORD)_tcslen(myTestSch/* SEAQUEST pTestInfo->Schema*/),(SQLTCHAR *)_T("%"),(SWORD)1,(SQLTCHAR *)_T("%"),(SWORD)1);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLProcedureColumns"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	if (returncode == SQL_SUCCESS)
	{
		_tcscpy(oProcCatalog,_T(""));
		_tcscpy(oProcSchema,_T(""));
		_tcscpy(oProcName,_T(""));
		_tcscpy(oColName,_T(""));
		oColType = 0;
		oColDataType = 0;
		_tcscpy(oColTypeName,_T(""));
		oColSize = 0;
		oBufferLen = 0;
		oDecDigits = 0;
		oColRadix = 0;
		oColNullable = 0;
		_tcscpy(oRemark,_T(""));
		_tcscpy(oColDef,_T(""));
		oSQLDataType = 0;
		oSQLDateTimeSub = 0;
		oCharOctetLen = 0;
		oOrdinalPos = 0;
		_tcscpy(oIsNullable,_T(""));
		SQLBindCol(hstmt,1,SQL_C_TCHAR,oProcCatalog,NAME_LEN,&oProcCataloglen);
		SQLBindCol(hstmt,2,SQL_C_TCHAR,oProcSchema,NAME_LEN,&oProcSchemalen);
		SQLBindCol(hstmt,3,SQL_C_TCHAR,oProcName,NAME_LEN,&oProcNamelen);
		SQLBindCol(hstmt,4,SQL_C_TCHAR,oColName,NAME_LEN,&oColNamelen);
		SQLBindCol(hstmt,5,SQL_C_SHORT,&oColType,0,&oColTypelen);
		SQLBindCol(hstmt,6,SQL_C_SHORT,&oColDataType,0,&oColDataTypelen);
		SQLBindCol(hstmt,7,SQL_C_TCHAR,oColTypeName,NAME_LEN,&oColTypeNamelen);
		SQLBindCol(hstmt,8,SQL_C_LONG,&oColSize,0,&oColSizelen);
		SQLBindCol(hstmt,9,SQL_C_LONG,&oBufferLen,0,&oBufferLenlen);
		SQLBindCol(hstmt,10,SQL_C_SHORT,&oDecDigits,0,&oDecDigitslen);
		SQLBindCol(hstmt,11,SQL_C_SHORT,&oColRadix,0,&oColRadixlen);
		SQLBindCol(hstmt,12,SQL_C_SHORT,&oColNullable,0,&oColNullablelen);
		SQLBindCol(hstmt,13,SQL_C_TCHAR,oRemark,REM_LEN,&oRemarklen);
		SQLBindCol(hstmt,14,SQL_C_TCHAR,oColDef,NAME_LEN,&oColDeflen);
		SQLBindCol(hstmt,15,SQL_C_SHORT,&oSQLDataType,0,&oSQLDataTypelen);
		SQLBindCol(hstmt,16,SQL_C_SHORT,&oSQLDateTimeSub,0,&oSQLDateTimeSublen);
		SQLBindCol(hstmt,17,SQL_C_LONG,&oCharOctetLen,0,&oCharOctetLenlen);
		SQLBindCol(hstmt,18,SQL_C_LONG,&oOrdinalPos,0,&oOrdinalPoslen);
		SQLBindCol(hstmt,19,SQL_C_TCHAR,oIsNullable,NAME_LEN,&oIsNullablelen);
		k = 0;
		i = 0;
		while (returncode == SQL_SUCCESS)
		{
			if(_tcscmp(ProcCol[i].ProcName,_T("endloop")) == 0)
				break;
			returncode = SQLFetch(hstmt);
			if((returncode!=SQL_NO_DATA_FOUND) &&(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch")))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			else
			{
				if (returncode == SQL_SUCCESS)
				{
					k++;
					_stprintf(Heading,_T("SQLProcedureColumns: Comparing Results\n"));
					TESTCASE_BEGINW(Heading);
					if ((_tcsicmp(ProcCatalog,oProcCatalog) == 0) 
					&& (_tcsicmp(ProcSchema,oProcSchema) == 0) 
					&& (_tcsicmp(ProcCol[i].ProcName,oProcName) == 0) 
					&& (_tcsicmp(ProcCol[i].ColName,oColName) == 0) 
					&& (ProcCol[i].ColType == oColType) 
					&& (ProcCol[i].ColDataType == oColDataType) 
					&& (_tcsicmp(ProcCol[i].ColTypeName,oColTypeName) == 0) 
					&& (ProcCol[i].ColSize == oColSize)
					&& (ProcCol[i].BufferLen == oBufferLen)
					&& (ProcCol[i].DecDigits == oDecDigits)
					&& (ProcCol[i].ColRadix == oColRadix)
					&& (ProcCol[i].ColNullable == oColNullable)
					&& (_tcsicmp(ProcCol[i].Remark,oRemark) == 0)
					&& (_tcsicmp(ProcCol[i].ColDef,oColDef) == 0)
					&& (ProcCol[i].SQLDataType == oSQLDataType)
					&& (ProcCol[i].SQLDateTimeSub == oSQLDateTimeSub)
					&& (ProcCol[i].CharOctetLen == oCharOctetLen)
					&& (ProcCol[i].OrdinalPos == oOrdinalPos)
					&& (_tcsicmp(ProcCol[i].IsNullable,oIsNullable) == 0)){
						LogMsg(NONE,_T("ProcCatalog expect: %s and actual: %s are matched\n"),ProcCatalog,oProcCatalog);
						LogMsg(NONE,_T("ProcSchema expect: %s and actual: %s are matched\n"),ProcSchema,oProcSchema);
						LogMsg(NONE,_T("ProcName expect: %s and actual: %s are matched\n"),ProcCol[i].ProcName,oProcName);
						LogMsg(NONE,_T("ColName expect: %s and actual: %s are matched\n"),ProcCol[i].ColName,oColName);
						LogMsg(NONE,_T("ColType expect: %d and actual: %d are matched\n"),ProcCol[i].ColType,oColType);
						LogMsg(NONE,_T("ColDataType expect: %d and actual: %d are matched\n"),ProcCol[i].ColDataType,oColDataType);
						LogMsg(NONE,_T("ColTypeName expect: %s and actual: %s are matched\n"),ProcCol[i].ColTypeName,oColTypeName);
						LogMsg(NONE,_T("ColSize expect: %d and actual: %d are matched\n"),ProcCol[i].ColSize,oColSize);
						LogMsg(NONE,_T("BufferLen expect: %d and actual: %d are matched\n"),ProcCol[i].BufferLen,oBufferLen);
						LogMsg(NONE,_T("DecDigits expect: %d and actual: %d are matched\n"),ProcCol[i].DecDigits,oDecDigits);
						LogMsg(NONE,_T("ColRadix expect: %d and actual: %d are matched\n"),ProcCol[i].ColRadix,oColRadix);
						LogMsg(NONE,_T("ColNullable expect: %d and actual: %d are matched\n"),ProcCol[i].ColNullable,oColNullable);
						LogMsg(NONE,_T("Remark expect: %s and actual: %s are matched\n"),ProcCol[i].Remark,oRemark);
						LogMsg(NONE,_T("ColDef expect: %s and actual: %s are matched\n"),ProcCol[i].ColDef,oColDef);
						LogMsg(NONE,_T("SQLDataType expect: %d and actual: %d are matched\n"),ProcCol[i].SQLDataType,oSQLDataType);
						LogMsg(NONE,_T("SQLDateTimeSub expect: %d and actual: %d are matched\n"),ProcCol[i].SQLDateTimeSub,oSQLDateTimeSub);
						LogMsg(NONE,_T("CharOctetLen expect: %d and actual: %d are matched\n"),ProcCol[i].CharOctetLen,oCharOctetLen);
						LogMsg(NONE,_T("OrdinalPos expect: %d and actual: %d are matched\n"),ProcCol[i].OrdinalPos,oOrdinalPos);
						LogMsg(NONE,_T("IsNullable expect: %s and actual: %s are matched\n"),ProcCol[i].IsNullable,oIsNullable);
					}	
					else
					{
						TEST_FAILED;	
						if (_tcsicmp(ProcCatalog,oProcCatalog) != 0)
							LogMsg(ERRMSG,_T("ProcCatalog expect: %s and actual: %s are not matched\n"),ProcCatalog,oProcCatalog);
						else
							LogMsg(NONE,_T("ProcCatalog expect: %s and actual: %s are matched\n"),ProcCatalog,oProcCatalog);
						if (_tcsicmp(ProcSchema,oProcSchema) != 0) 
							LogMsg(ERRMSG,_T("ProcSchema expect: %s and actual: %s are not matched\n"),ProcSchema,oProcSchema);
						else
							LogMsg(NONE,_T("ProcSchema expect: %s and actual: %s are matched\n"),ProcSchema,oProcSchema);
						if (_tcsicmp(ProcCol[i].ProcName,oProcName) != 0) 
							LogMsg(ERRMSG,_T("ProcName expect: %s and actual: %s are not matched\n"),ProcCol[i].ProcName,oProcName);
						else
							LogMsg(NONE,_T("ProcName expect: %s and actual: %s are matched\n"),ProcCol[i].ProcName,oProcName);							
						if (_tcsicmp(ProcCol[i].ColName,oColName) != 0) 
							LogMsg(ERRMSG,_T("ColName expect: %s and actual: %s are not matched\n"),ProcCol[i].ColName,oColName);
						else
							LogMsg(NONE,_T("ColName expect: %s and actual: %s are matched\n"),ProcCol[i].ColName,oColName);
						if (ProcCol[i].ColType != oColType) 
							LogMsg(ERRMSG,_T("ColType expect: %d and actual: %d are not matched\n"),ProcCol[i].ColType,oColType);
						else	
							LogMsg(NONE,_T("ColType expect: %d and actual: %d are matched\n"),ProcCol[i].ColType,oColType);
						if (ProcCol[i].ColDataType != oColDataType) 
							LogMsg(ERRMSG,_T("ColDataType expect: %d and actual: %d are not matched\n"),ProcCol[i].ColDataType,oColDataType);
						else	
							LogMsg(NONE,_T("ColDataType expect: %d and actual: %d are matched\n"),ProcCol[i].ColDataType,oColDataType);
						if (_tcsicmp(ProcCol[i].ColTypeName,oColTypeName) != 0) 
							LogMsg(ERRMSG,_T("ColTypeName expect: %s and actual: %s are not matched\n"),ProcCol[i].ColTypeName,oColTypeName);
						else							
							LogMsg(NONE,_T("ColTypeName expect: %s and actual: %s are matched\n"),ProcCol[i].ColTypeName,oColTypeName);
						if (ProcCol[i].ColSize != oColSize)
							LogMsg(ERRMSG,_T("ColSize expect: %d and actual: %d are not matched\n"),ProcCol[i].ColSize,oColSize);
						else	
							LogMsg(NONE,_T("ColSize expect: %d and actual: %d are matched\n"),ProcCol[i].ColSize,oColSize);
						if (ProcCol[i].BufferLen != oBufferLen)
							LogMsg(ERRMSG,_T("BufferLen expect: %d and actual: %d are not matched\n"),ProcCol[i].BufferLen,oBufferLen);
						else	
							LogMsg(NONE,_T("BufferLen expect: %d and actual: %d are matched\n"),ProcCol[i].BufferLen,oBufferLen);							
						if (ProcCol[i].DecDigits != oDecDigits)
							LogMsg(ERRMSG,_T("DecDigits expect: %d and actual: %d are not matched\n"),ProcCol[i].DecDigits,oDecDigits);
						else	
							LogMsg(NONE,_T("DecDigits expect: %d and actual: %d are matched\n"),ProcCol[i].DecDigits,oDecDigits);					
						if (ProcCol[i].ColRadix != oColRadix)
							LogMsg(ERRMSG,_T("ColRadix expect: %d and actual: %d are not matched\n"),ProcCol[i].ColRadix,oColRadix);
						else	
							LogMsg(NONE,_T("ColRadix expect: %d and actual: %d are matched\n"),ProcCol[i].ColRadix,oColRadix);						
						if (ProcCol[i].ColNullable != oColNullable)
							LogMsg(ERRMSG,_T("ColNullable expect: %d and actual: %d are not matched\n"),ProcCol[i].ColNullable,oColNullable);
						else	
							LogMsg(NONE,_T("ColNullable expect: %d and actual: %d are matched\n"),ProcCol[i].ColNullable,oColNullable);						
						if (_tcsicmp(ProcCol[i].Remark,oRemark) != 0)
							LogMsg(ERRMSG,_T("Remark expect: %s and actual: %s are not matched\n"),ProcCol[i].Remark,oRemark);
						else	
							LogMsg(NONE,_T("Remark expect: %s and actual: %s are matched\n"),ProcCol[i].Remark,oRemark);
						if (_tcsicmp(ProcCol[i].ColDef,oColDef) != 0)
							LogMsg(ERRMSG,_T("Remark expect: %s and actual: %s are not matched\n"),ProcCol[i].ColDef,oColDef);
						else	
							LogMsg(NONE,_T("Remark expect: %s and actual: %s are matched\n"),ProcCol[i].ColDef,oColDef);
						if (ProcCol[i].SQLDataType != oSQLDataType)
							LogMsg(ERRMSG,_T("SQLDataType expect: %d and actual: %d are not matched\n"),ProcCol[i].SQLDataType,oSQLDataType);
						else	
							LogMsg(NONE,_T("SQLDataType expect: %d and actual: %d are matched\n"),ProcCol[i].SQLDataType,oSQLDataType);
						if (ProcCol[i].SQLDateTimeSub != oSQLDateTimeSub)
							LogMsg(ERRMSG,_T("SQLDateTimeSub expect: %d and actual: %d are not matched\n"),ProcCol[i].SQLDateTimeSub,oSQLDateTimeSub);
						else	
							LogMsg(NONE,_T("SQLDateTimeSub expect: %d and actual: %d are matched\n"),ProcCol[i].SQLDateTimeSub,oSQLDateTimeSub);
						if (ProcCol[i].CharOctetLen != oCharOctetLen)
							LogMsg(ERRMSG,_T("CharOctetLen expect: %d and actual: %d are not matched\n"),ProcCol[i].CharOctetLen,oCharOctetLen);
						else	
							LogMsg(NONE,_T("CharOctetLen expect: %d and actual: %d are matched\n"),ProcCol[i].CharOctetLen,oCharOctetLen);
						if (ProcCol[i].OrdinalPos != oOrdinalPos)
							LogMsg(ERRMSG,_T("OrdinalPos expect: %d and actual: %d are not matched\n"),ProcCol[i].OrdinalPos,oOrdinalPos);
						else	
							LogMsg(NONE,_T("OrdinalPos expect: %d and actual: %d are matched\n"),ProcCol[i].OrdinalPos,oOrdinalPos);
						if (_tcsicmp(ProcCol[i].IsNullable,oIsNullable) != 0)
							LogMsg(ERRMSG,_T("IsNullable expect: %s and actual: %s are not matched\n"),ProcCol[i].IsNullable,oIsNullable);
						else	
							LogMsg(NONE,_T("IsNullable expect: %s and actual: %s are matched\n"),ProcCol[i].IsNullable,oIsNullable);
					}
				}
			}
			if(k == 0)
			{
				TEST_FAILED;
				LogMsg(ERRMSG,_T("No Data Found => Atleast one row should be fetched\n"));
			}

			TESTCASE_END;
			_tcscpy(oProcCatalog,_T(""));
			_tcscpy(oProcSchema,_T(""));
			_tcscpy(oProcName,_T(""));
			_tcscpy(oColName,_T(""));
			oColType = 0;
			oColDataType = 0;
			_tcscpy(oColTypeName,_T(""));
			oColSize = 0;
			oBufferLen = 0;
			oDecDigits = 0;
			oColRadix = 0;
			oColNullable = 0;
			_tcscpy(oRemark,_T(""));
			_tcscpy(oColDef,_T(""));
			oSQLDataType = 0;
			oSQLDateTimeSub = 0;
			oCharOctetLen = 0;
			oOrdinalPos = 0;
			_tcscpy(oIsNullable,_T(""));
			i++;
		} // while
	}

	SQLFreeStmt(hstmt,SQL_UNBIND);
	SQLFreeStmt(hstmt,SQL_CLOSE);

	i=0;
	while (_tcsicmp(CreateProc[i].DropProc,_T("endloop")) != 0)
	{
		_tcscpy(ProcStr,_T(""));
		_tcscat(ProcStr,CreateProc[i].DropProc);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*) ProcStr,SQL_NTS); // cleanup
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
		}
		i++;
	}

	SQLFreeStmt(hstmt,SQL_UNBIND);
	SQLFreeStmt(hstmt,SQL_CLOSE);
	
	//========================================================================================================

	_stprintf(Heading,_T("SQLProcedureColumns: Negative test with NULL handle\n"));
	TESTCASE_BEGINW(Heading);

	hstmt = (SQLHANDLE)NULL;
	_tcscpy(ProcName,_T("junkproc"));
	_tcscpy(ColName,_T("C1"));

	returncode = SQLProcedureColumns(hstmt,(SQLTCHAR*)pTestInfo->Catalog,(SWORD)_tcslen(pTestInfo->Catalog),(SQLTCHAR*)myTestSch /* SEAQUEST pTestInfo->Schema */,(SWORD)_tcslen(myTestSch /* SEAQUEST pTestInfo->Schema*/),(SQLTCHAR*)ProcName,(SWORD)_tcslen(ProcName),(SQLTCHAR*)ColName,(SWORD)_tcslen(ColName));
	if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLProcedureColumns"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	TESTCASE_END;

	//========================================================================================================

returncode = SQLExecDirect(hstmt,(SQLTCHAR*) dropSchStr,SQL_NTS);

	free(ProcStr);
	FullDisconnect3(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing API => MX Specific SQLProcedureColumns.\n"));
	TEST_RETURN;
}