/*
------------------------------------------------------------------
   TestSQLGetTypeInfo: Tests SQLGetTypeInfo                      
------------------------------------------------------------------
*/
PassFail TestSQLGetTypeInfoR18(TestInfo *pTestInfo)
{   
	TEST_DECLARE;
	char				Heading[MAX_STRING_SIZE];
  RETCODE			returncode;
  SQLHANDLE 			henv;
  SQLHANDLE 			hdbc;
  SQLHANDLE			hstmt;				  
  char				TempBuf[MAX_STRING_SIZE];	
  int				j = 0,END_LOOP;

	struct
	{
		char		*TYPE_NAME;
		SWORD		DATA_TYPE;
		SDWORD		PRECISION;
		char		*LITERAL_PREFIX;
		char		*LITERAL_SUFFIX;
		char		*CREATE_PARAMS;
		SWORD		NULLABLE;
		SWORD		CASE_SENSITIVE;
		SWORD		SEARCHABLE;
		SWORD		UNSIGNED_ATTRIBUTE;
		SWORD		MONEY;
		SWORD		AUTO_INCREMENT;
		char		*LOCAL_TYPE_NAME;
		SWORD		MINIMUM_SCALE;
		SWORD		MAXIMUM_SCALE;
	}	TypeInfo[] = 
		{//TYPENAME,DATATYPE,PREC,LITPRE,LITSUF,PARAM,NULL,CASE,SRCH,ATTR,MON,INC,LOC,MIN,MAX
			{"",SQL_ALL_TYPES,0,"","","",0,0,0,0,0,0,"",0,0},	// this is for get all types
			{"CHAR", SQL_CHAR, 254, "'", "'", "max length", SQL_NULLABLE, 1, SQL_SEARCHABLE, 0, 0, 0, "CHARACTER", 0, 0},
			{"VARCHAR", SQL_VARCHAR, 254, "'", "'", "max length", SQL_NULLABLE, 1, SQL_SEARCHABLE, 0, 0, 0, "VARCHAR", 0, 0},
			{"DECIMAL", SQL_DECIMAL, 18, "", "", "precision,scale", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "DECIMAL", 0, 18},
			{"NUMERIC", SQL_NUMERIC, 128, "", "", "precision,scale", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "NUMERIC", 0, 128},
			{"SMALLINT", SQL_SMALLINT, 5, "", "", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "SMALLINT", 0, 0},
			{"INTEGER", SQL_INTEGER, 10, "", "", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTEGER", 0, 0},
			{"REAL", SQL_REAL, 7, "", "", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "REAL", 0, 0},
			{"FLOAT", SQL_FLOAT, 15, "", "", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "FLOAT", 0, 0},
			{"DOUBLE PRECISION", SQL_DOUBLE, 15, "", "", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "DOUBLE", 0, 0},
//			{"DATE", SQL_DATE,  10,  "{d '",  "'}","", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "DATE", 0, 0},
//			{"TIME", SQL_TIME, 8, "{t '", "'}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "TIME", 0, 0},
//			{"TIMESTAMP", SQL_TIMESTAMP, 23, "{ts '", "'}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "TIMESTAMP", 0, 6},
			{"DATE", SQL_TYPE_DATE,  10,  "{d '",  "'}","", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "DATE", 0, 0},
			{"TIME", SQL_TYPE_TIME, 8, "{t '", "'}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "TIME", 0, 0},
			{"TIMESTAMP", SQL_TYPE_TIMESTAMP, 26, "{ts '", "'}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "TIMESTAMP", 0, 6},
			{"BIGINT", SQL_BIGINT, 19, "", "", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "LARGEINT", 0, 0},
			{"LONG VARCHAR", SQL_LONGVARCHAR, 4018, "'", "'", "", SQL_NULLABLE, 1, SQL_SEARCHABLE, 0, 0, 0, "LONG VARCHAR", 0, 0},
//			{"BINARY", SQL_BINARY, 4059, "'", "'", "max length", 1, 0, 0, 0, 0, 0, "", 0, 0},
//			{"VARBINARY", -3, 4059, "'", "'", "max length", 1, 0, 0, 0, 0, 0, "", 0, 0},
//			{"LONG VARBINARY", -4, 4059, "'", "'", "max length", 1, 0, 0, 0, 0, 0, "", 0, 0},
//			{"TINYINT", -6, 3, "", "", "", 1, 0, SQL_ALL_EXCEPT_LIKE, 1, 0, 0, "", 0, 0},
//			{"BIT", -7, 1, "", "", "", 1, 0, SQL_UNSEARCHABLE, 0, 0, 0, "", 0, 0},
			{"INTERVAL", SQL_INTERVAL_YEAR, 0, "{INTERVAL '", "' YEAR}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_MONTH, 0, "{INTERVAL '", "' MONTH}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_DAY, 0, "{INTERVAL '", "' DAY}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_HOUR, 0, "{INTERVAL '", "' HOUR}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_MINUTE, 0, "{INTERVAL '", "' MINUTE}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_SECOND, 0, "{INTERVAL '", "' SECOND}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_YEAR_TO_MONTH, 0, "{INTERVAL '", "' YEAR TO MONTH}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_DAY_TO_HOUR, 0, "{INTERVAL '", "' DAY TO HOUR}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_DAY_TO_MINUTE, 0, "{INTERVAL '", "' DAY TO MINUTE}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_DAY_TO_SECOND, 0, "{INTERVAL '", "' DAY TO SECOND}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_HOUR_TO_MINUTE, 0, "{INTERVAL '", "' HOUR TO MINUTE}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_HOUR_TO_SECOND, 0, "{INTERVAL '", "' HOUR TO SECOND}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"INTERVAL", SQL_INTERVAL_MINUTE_TO_SECOND, 0, "{INTERVAL '", "' MINUTE TO SECOND}", "", SQL_NULLABLE, 0, SQL_ALL_EXCEPT_LIKE, 0, 0, 0, "INTERVAL", 0, 0},
			{"",999,}	
	};



		char		oTYPE_NAME[TYPE_LEN];
		SWORD		oDATA_TYPE, fSqlType1;
		SDWORD		oPRECISION;
		char		oLITERAL_PREFIX[TYPE_LEN];
		char		oLITERAL_SUFFIX[TYPE_LEN];
		char		oCREATE_PARAMS[TYPE_LEN];
		SWORD		oNULLABLE;
		SWORD		oCASE_SENSITIVE;
		SWORD		oSEARCHABLE;
		SWORD		oUNSIGNED_ATTRIBUTE;
		SWORD		oMONEY;
		SWORD		oAUTO_INCREMENT;
		char		oLOCAL_TYPE_NAME[TYPE_LEN];
		SWORD		oMINIMUM_SCALE;
		SWORD		oMAXIMUM_SCALE;

		SQLLEN	oTYPE_NAMElen;	
		SQLLEN	oDATA_TYPElen;
		SQLLEN	oPRECISIONlen;
		SQLLEN	oLITERAL_PREFIXlen;
		SQLLEN	oLITERAL_SUFFIXlen;
		SQLLEN	oCREATE_PARAMSlen;
		SQLLEN	oNULLABLElen;
		SQLLEN	oCASE_SENSITIVElen;
		SQLLEN	oSEARCHABLElen;
		SQLLEN	oUNSIGNED_ATTRIBUTElen;
		SQLLEN	oMONEYlen;
		SQLLEN	oAUTO_INCREMENTlen;
		SQLLEN	oLOCAL_TYPE_NAMElen;
		SQLLEN	oMINIMUM_SCALElen;
		SQLLEN	oMAXIMUM_SCALElen;

   	/* Set up some local variables to save on typing in longer ones */
    /* This previously was R1.8 */
//================Modified for Longvarchar Changes===========================================================
if(!pTestInfo->bLongOn)
{
	char *TYPE_NAME = "VARCHAR";
	SWORD DATA_TYPE = SQL_VARCHAR;
    SDWORD	PRECISION = 32000;
	char *CREATE_PARAMS = "max length";
	char *LOCAL_TYPE_NAME = "VARCHAR";


	TypeInfo[1].PRECISION = PRECISION;
	TypeInfo[2].PRECISION = PRECISION;

	TypeInfo[14].TYPE_NAME = TYPE_NAME;
	TypeInfo[14].DATA_TYPE = DATA_TYPE;
	TypeInfo[14].PRECISION = PRECISION;
	TypeInfo[14].CREATE_PARAMS = CREATE_PARAMS;
	TypeInfo[14].LOCAL_TYPE_NAME = LOCAL_TYPE_NAME;
}

//================Modified for Longvarhcar Changes===========================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API =>SQLGetTypeInfo30 | SQLGetTypeInfo3 | gettypeiR18.c\n");

	TEST_INIT;
	TESTCASE_BEGIN("Setup for SQLGetTypeInfo tests for ODBC 3.0\n");

	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
		LogMsg(NONE,"Unable to connect\n");
		TEST_FAILED;
		TEST_RETURN;
	}

  	/* Set up some local variables to save on typing in longer ones */
	henv = pTestInfo->henv;
	hdbc = pTestInfo->hdbc;
 	hstmt = (SQLHANDLE)pTestInfo->hstmt;
   	
	returncode = SQLAllocHandle(SQL_HANDLE_STMT, (SQLHANDLE)hdbc, &hstmt);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle")){
		LogAllErrorsVer3(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
	
	TESTCASE_END; // end of setup

//=========================================================================================
					 
/*	if (MX_MP_SPECIFIC == MX_SPECIFIC)
		END_LOOP = SQL_BINARY;
	else if (MX_MP_SPECIFIC == MP_SPECIFIC)
		END_LOOP = 999;
	else
	{
		LogMsg(ERRMSG,"gettypeinfo test failed.\n");
		TEST_RETURN;
	}
*/	
	END_LOOP = 999;
	j = 0;
	while (TypeInfo[j].DATA_TYPE != END_LOOP) 
	{
		sprintf(Heading,"Test Positive functionality of SQLGetTypeInfo for data type: %s\n",
									SQLTypeToChar(TypeInfo[j].DATA_TYPE,TempBuf));
		TESTCASE_BEGIN(Heading);

		returncode = SQLGetTypeInfo(hstmt,TypeInfo[j].DATA_TYPE);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetTypeInfo"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		else
		{
			if (TypeInfo[j].DATA_TYPE != 0) 
			{ 
				strcpy(oTYPE_NAME,"");
				oDATA_TYPE = 0; 
				oPRECISION = 0;
				strcpy(oLITERAL_PREFIX,"");
				strcpy(oLITERAL_SUFFIX,"");
				strcpy(oCREATE_PARAMS,"");
				oNULLABLE = 0;
				oCASE_SENSITIVE = 0;
				oSEARCHABLE = 0;
				oUNSIGNED_ATTRIBUTE = 0;
				oMONEY = 0;
				oAUTO_INCREMENT = 0;
				strcpy(oLOCAL_TYPE_NAME,"");
				oMINIMUM_SCALE = 0;
				oMAXIMUM_SCALE = 0;
				returncode = SQLBindCol(hstmt,1,SQL_C_CHAR,oTYPE_NAME,TYPE_LEN,&oTYPE_NAMElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,2,SQL_C_SHORT,&oDATA_TYPE,0,&oDATA_TYPElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,3,SQL_C_LONG,&oPRECISION,0,&oPRECISIONlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,4,SQL_C_CHAR,oLITERAL_PREFIX,TYPE_LEN,&oLITERAL_PREFIXlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,5,SQL_C_CHAR,oLITERAL_SUFFIX,TYPE_LEN,&oLITERAL_SUFFIXlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,6,SQL_C_CHAR,oCREATE_PARAMS,TYPE_LEN,&oCREATE_PARAMSlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,7,SQL_C_SHORT,&oNULLABLE,0,&oNULLABLElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,8,SQL_C_SHORT,&oCASE_SENSITIVE,0,&oCASE_SENSITIVElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,9,SQL_C_SHORT,&oSEARCHABLE,0,&oSEARCHABLElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,10,SQL_C_SHORT,&oUNSIGNED_ATTRIBUTE,0,&oUNSIGNED_ATTRIBUTElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,11,SQL_C_SHORT,&oMONEY,0,&oMONEYlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,12,SQL_C_SHORT,&oAUTO_INCREMENT,0,&oAUTO_INCREMENTlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,13,SQL_C_CHAR,oLOCAL_TYPE_NAME,TYPE_LEN,&oLOCAL_TYPE_NAMElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,14,SQL_C_SHORT,&oMINIMUM_SCALE,0,&oMINIMUM_SCALElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,15,SQL_C_SHORT,&oMAXIMUM_SCALE,0,&oMAXIMUM_SCALElen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLFetch(hstmt);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt);
				}
				else
				{
					LogMsg(NONE,"Comparing results\n");
					if ((_stricmp(TypeInfo[j].TYPE_NAME,oTYPE_NAME) == 0)
							&& (TypeInfo[j].DATA_TYPE == oDATA_TYPE)
							&& (TypeInfo[j].PRECISION == oPRECISION)
							&& (_stricmp(TypeInfo[j].LITERAL_PREFIX,oLITERAL_PREFIX) == 0)
							&& (_stricmp(TypeInfo[j].LITERAL_SUFFIX,oLITERAL_SUFFIX) == 0)
							&& (_stricmp(TypeInfo[j].CREATE_PARAMS,oCREATE_PARAMS) == 0)
							&& (TypeInfo[j].NULLABLE == oNULLABLE)
							&& (TypeInfo[j].CASE_SENSITIVE == oCASE_SENSITIVE)
							&& (TypeInfo[j].SEARCHABLE == oSEARCHABLE)
							&& (TypeInfo[j].UNSIGNED_ATTRIBUTE == oUNSIGNED_ATTRIBUTE)
							&& (TypeInfo[j].MONEY == oMONEY)
							&& (TypeInfo[j].AUTO_INCREMENT == oAUTO_INCREMENT)
							&& (_stricmp(TypeInfo[j].LOCAL_TYPE_NAME,oLOCAL_TYPE_NAME) == 0)
							&& (TypeInfo[j].MINIMUM_SCALE == oMINIMUM_SCALE)
							&& (TypeInfo[j].MAXIMUM_SCALE == oMAXIMUM_SCALE))
					{
						//LogMsg(NONE,"Data Type Name actual: %s and expected: %s are matched\n",oTYPE_NAME,TypeInfo[j].TYPE_NAME);
						//LogMsg(NONE,"Data Type actual: %d and expected: %d are matched\n",oDATA_TYPE,TypeInfo[j].DATA_TYPE);
						//LogMsg(NONE,"Precision actual: %d and expected: %d are matched\n",oPRECISION,TypeInfo[j].PRECISION);
						//LogMsg(NONE,"Literal Prefix actual: %s and expected: %s are matched\n",oLITERAL_PREFIX,TypeInfo[j].LITERAL_PREFIX);
						//LogMsg(NONE,"Literal Suffix actual: %s and expected: %s are matched\n",oLITERAL_SUFFIX,TypeInfo[j].LITERAL_SUFFIX);
						//LogMsg(NONE,"Create Params actual: %s and expected: %s are matched\n",oCREATE_PARAMS,TypeInfo[j].CREATE_PARAMS);
						//LogMsg(NONE,"Nullable actual: %d and expected: %d are matched\n",oNULLABLE,TypeInfo[j].NULLABLE);
						//LogMsg(NONE,"Case sensitive actual: %d and expected: %d are matched\n",oCASE_SENSITIVE,TypeInfo[j].CASE_SENSITIVE);
						//LogMsg(NONE,"Searchable actual: %d and expected: %d are matched\n",oSEARCHABLE,TypeInfo[j].SEARCHABLE);
						//LogMsg(NONE,"Unsigned attribute actual: %d and expected: %d are matched\n",oUNSIGNED_ATTRIBUTE,TypeInfo[j].UNSIGNED_ATTRIBUTE);
						//LogMsg(NONE,"Money actual: %d and expected: %d are matched\n",oMONEY,TypeInfo[j].MONEY);
						//LogMsg(NONE,"Auto Increment actual: %d and expected: %d are matched\n",oAUTO_INCREMENT,TypeInfo[j].AUTO_INCREMENT);
						//LogMsg(NONE,"Local Type name actual: %s and expected: %s are matched\n",oLOCAL_TYPE_NAME,TypeInfo[j].LOCAL_TYPE_NAME);
						//LogMsg(NONE,"Minimum Scale actual: %d and expected: %d are matched\n",oMINIMUM_SCALE,TypeInfo[j].MINIMUM_SCALE);
						//LogMsg(NONE,"Maximum Scale actual: %d and expected: %d are matched\n",oMAXIMUM_SCALE,TypeInfo[j].MAXIMUM_SCALE);
					}	
					else
					{
						TEST_FAILED;	
						if (_stricmp(TypeInfo[j].TYPE_NAME,oTYPE_NAME) != 0)
							LogMsg(ERRMSG,"Data Type Name actual: %s and expected: %s are not matched\n",oTYPE_NAME,TypeInfo[j].TYPE_NAME);
						if (TypeInfo[j].DATA_TYPE != oDATA_TYPE)
							LogMsg(ERRMSG,"Data Type actual: %d and expected: %d are not matched\n",oDATA_TYPE,TypeInfo[j].DATA_TYPE);
						if (TypeInfo[j].PRECISION != oPRECISION)
							LogMsg(ERRMSG,"Precision actual: %d and expected: %d are not matched\n",oPRECISION,TypeInfo[j].PRECISION);
						if (_stricmp(TypeInfo[j].LITERAL_PREFIX,oLITERAL_PREFIX) != 0)
							LogMsg(ERRMSG,"Literal Prefix actual: %s and expected: %s are not matched\n",oLITERAL_PREFIX,TypeInfo[j].LITERAL_PREFIX);
						if (_stricmp(TypeInfo[j].LITERAL_SUFFIX,oLITERAL_SUFFIX) != 0)
							LogMsg(ERRMSG,"Literal Suffix actual: %s and expected: %s are not matched\n",oLITERAL_SUFFIX,TypeInfo[j].LITERAL_SUFFIX);
						if (_stricmp(TypeInfo[j].CREATE_PARAMS,oCREATE_PARAMS) != 0)
							LogMsg(ERRMSG,"Create Params actual: %s and expected: %s are not matched\n",oCREATE_PARAMS,TypeInfo[j].CREATE_PARAMS);
						if (TypeInfo[j].NULLABLE != oNULLABLE)
							LogMsg(ERRMSG,"Nullable actual: %d and expected: %d are not matched\n",oNULLABLE,TypeInfo[j].NULLABLE);
						if (TypeInfo[j].CASE_SENSITIVE != oCASE_SENSITIVE)
							LogMsg(ERRMSG,"Case sensitive actual: %d and expected: %d are not matched\n",oCASE_SENSITIVE,TypeInfo[j].CASE_SENSITIVE);
						if (TypeInfo[j].SEARCHABLE != oSEARCHABLE)
							LogMsg(ERRMSG,"Searchable actual: %d and expected: %d are not matched\n",oSEARCHABLE,TypeInfo[j].SEARCHABLE);
						if (TypeInfo[j].UNSIGNED_ATTRIBUTE != oUNSIGNED_ATTRIBUTE)
							LogMsg(ERRMSG,"Unsigned attribute actual: %d and expected: %d are not matched\n",oUNSIGNED_ATTRIBUTE,TypeInfo[j].UNSIGNED_ATTRIBUTE);
						if (TypeInfo[j].MONEY != oMONEY)
							LogMsg(ERRMSG,"Money actual: %d and expected: %d are not matched\n",oMONEY,TypeInfo[j].MONEY);
						if (TypeInfo[j].AUTO_INCREMENT != oAUTO_INCREMENT)
							LogMsg(ERRMSG,"Auto Increment actual: %d and expected: %d are not matched\n",oAUTO_INCREMENT,TypeInfo[j].AUTO_INCREMENT);
						if (_stricmp(TypeInfo[j].LOCAL_TYPE_NAME,oLOCAL_TYPE_NAME) != 0)
							LogMsg(ERRMSG,"Local Type name actual: %s and expected: %s are not matched\n",oLOCAL_TYPE_NAME,TypeInfo[j].LOCAL_TYPE_NAME);
						if (TypeInfo[j].MINIMUM_SCALE != oMINIMUM_SCALE)
							LogMsg(ERRMSG,"Minimum Scale actual: %d and expected: %d are not matched\n",oMINIMUM_SCALE,TypeInfo[j].MINIMUM_SCALE);
						if (TypeInfo[j].MAXIMUM_SCALE != oMAXIMUM_SCALE)
							LogMsg(ERRMSG,"Maximum Scale actual: %d and expected: %d are not matched\n",oMAXIMUM_SCALE,TypeInfo[j].MAXIMUM_SCALE);
					}
				} 					
			}
		}
		TESTCASE_END;
		SQLFreeStmt(hstmt,SQL_CLOSE);	// This is a bug this should be after the inner for loop.
		j++;
	} 															
	
//==========================================================================================
	
	TESTCASE_BEGIN("SQLGetTypeInfo: Negative test for invalid data type\n");

	fSqlType1 = 50;
	returncode = SQLGetTypeInfo(hstmt,fSqlType1);
	if(!CHECKRC(SQL_ERROR,returncode,"SQLGetTypeInfo"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	TESTCASE_END;

//=========================================================================================

	sprintf(Heading,"SQLGetTypeInfo: Negative test with invalid handle\n");
	TESTCASE_BEGIN(Heading);

	hstmt = (SQLHANDLE)NULL;
	fSqlType1 = 1;
	returncode = SQLGetTypeInfo(hstmt,fSqlType1);
	if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLGetTypeInfo"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	TESTCASE_END;

//=========================================================================================

	FullDisconnect3(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => SQLGetTypeInfo.\n");
	TEST_RETURN;
}