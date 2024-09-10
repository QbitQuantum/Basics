/*
---------------------------------------------------------
   TestSQLGetDescRec
---------------------------------------------------------
*/
PassFail TestMXSQLGetDescRec(TestInfo *pTestInfo)
{   
	TEST_DECLARE;
	RETCODE				returncode;
	SQLHANDLE 			henv;
	SQLHANDLE 			hdbc;
	SQLHANDLE			hstmt, hstmt1;
	
	//Common input params to the apis
	SQLHDESC			hIrd, hImArd, hImIrd, hImApd, hImIpd, hExArd, hExApd;
	SWORD				RecNumber = 0;

	//SQLGetDescRec: params
	SQLHDESC			getDescRecHandle;				//input
	SWORD				getDescRecNumber;				//input
	TCHAR				getDescName[MAXLEN];		 
	SWORD				getNameMaxLength;				//input; MAXLEN = 100 : defined in Common.h
	SWORD				getDescNameActualLength;
	SQLSMALLINT			getDescType;
	SWORD				getDescIntervalCode;
	SQLLEN				getDescOctectLength; 
	SWORD				getDescPrecision;
	SWORD				getDescScale;
	SWORD				getDescNullable;

	//SQLSetDescRec: params
	SQLHDESC			setDescRecHandle;
	SQLSMALLINT			setDescRecNumber;
	SQLSMALLINT			setDescType;
	SQLSMALLINT			setDescIntervalCode;
	SQLINTEGER			setDescOctetLength;
	SQLSMALLINT			setDescPrecision;
	SQLSMALLINT			setDescScale;
	SQLPOINTER			setDescDataPtr;
	SQLLEN				setDescOctectLengthPtr; 
	SQLLEN				setDescIndicatorPtr; 

	TCHAR				setDescName[1];
	
	SQLINTEGER			setDescNullable = SQL_NULL_DATA;
	short int			i;

	// Template for a Descriptor record
	typedef struct {
	  //	TCHAR				DescName[MAXLEN];
	TCHAR				*DescName;
	short int			DescType;
	short int			DescDatetimeIntervalCode;
	short int			DescOctetLength;
	short int			DescPrecision;
	short int			DescScale;
	void*				DescDataPtr;
	short int			DescOctectLengthPtr;
	short int			DescIndicatorPtr;
	short int			DescNullable;
	}DescRec;

	DescRec TestDataAPD[DATA_ARR_LEN] = 
	{
	//APD
	//	DescName		Type				DatetimeIntervalCode	DescOctetLength		Precision	DescScale	DescDataPtr		OctectLengthPtr		IndicatorPtr				DescNullable
		{_T(""),			SQL_C_DEFAULT,				0,						0,				0,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TCHAR,					0,						80,				0,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TCHAR,					0,						300,			0,			0,			NULL,		SQL_NTS,			SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_NUMERIC,				0,						0,				0,			0,			NULL,		SQL_DATA_AT_EXEC,	SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TYPE_TIMESTAMP,	SQL_CODE_TIMESTAMP,			0,				6,			1,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_INTERVAL_SECOND,	SQL_CODE_SECOND,			0,				2,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN }
	};

	DescRec TestDataARD[DATA_ARR_LEN] =
	{
	//ARD
	//	DescName		Type				DatetimeIntervalCode	DescOctetLength		Precision	DescScale	DescDataPtr		OctectLengthPtr		IndicatorPtr				DescNullable
		{_T(""),			SQL_C_DEFAULT,				0,						0,				0,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TCHAR,					0,						80,				0,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TCHAR,					0,						300,			0,			0,			NULL,		SQL_NTS,			SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_NUMERIC,				0,						0,				0,			0,			NULL,		SQL_DATA_AT_EXEC,	SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TYPE_TIMESTAMP,	SQL_CODE_TIMESTAMP,			0,				6,			1,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_INTERVAL_SECOND,	SQL_CODE_SECOND,			0,				2,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN }
	};

	DescRec TestDataIPD[DATA_ARR_LEN] =
	{
	//IPD
	//	DescName		Type				DatetimeIntervalCode	DescOctetLength		Precision	DescScale	DescDataPtr		OctectLengthPtr		IndicatorPtr				DescNullable
		{_T(""),			SQL_C_DEFAULT,				0,						0,				0,			0,			0,				0,					0,					SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_TCHAR,					0,						80,				0,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_TCHAR,					0,						300,			0,			0,			NULL,		SQL_NTS,			SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_NUMERIC,				0,						0,				0,			0,			NULL,		SQL_DATA_AT_EXEC,	SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_TYPE_TIMESTAMP,		SQL_CODE_TIMESTAMP,			0,				6,			1,			0,				0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_INTERVAL_SECOND,	SQL_CODE_SECOND,			0,				2,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN }
	};

	DescRec TestDataIRD[DATA_ARR_LEN] =
	{
	//IRD can only be read
	//	DescName		Type				DatetimeIntervalCode	DescOctetLength		Precision	DescScale	DescDataPtr		OctectLengthPtr		IndicatorPtr				DescNullable
		{_T(""),			SQL_C_DEFAULT,				0,						0,				0,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TCHAR,					0,						80,				0,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TCHAR,					0,						300,			0,			0,			NULL,		SQL_NTS,			SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_NUMERIC,				0,						0,				0,			0,			NULL,		SQL_DATA_AT_EXEC,	SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_TIMESTAMP,		SQL_CODE_TIMESTAMP,			0,				6,			1,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN },
		{_T(""),			SQL_C_INTERVAL_SECOND,	SQL_CODE_SECOND,			0,				2,			0,			NULL,			0,				SQL_NULL_DATA,			SQL_NULLABLE_UNKNOWN }
	};
	_tcscpy(setDescName, _T(""));
// ================================================================================================================
//		begin common test setup 
//==================================================================================================================
	LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing API => SQLSetDescRec and SQLGetDescRec.\n"));
	TEST_INIT;

	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
		LogMsg(NONE,_T("Unable to connect\n"));
		TEST_FAILED;
		TEST_RETURN;
	}
	
	henv = pTestInfo->henv;
 	hdbc = pTestInfo->hdbc;

	returncode = SQLAllocHandle(SQL_HANDLE_STMT, (SQLHANDLE)hdbc, &hstmt);	
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		FullDisconnect(pTestInfo);
		TEST_FAILED;
		TEST_RETURN;
	}

	//Explicit APD
	//allocate an Explicit APD desc
	returncode = SQLAllocHandle(SQL_HANDLE_DESC, (SQLHANDLE)hdbc, &hExApd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle to get explicit APD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		FullDisconnect(pTestInfo);
		TEST_FAILED;
		TEST_RETURN;
	}	

	//Explicit ARD
	returncode = SQLAllocHandle(SQL_HANDLE_DESC, (SQLHANDLE)hdbc, &hExArd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle to get explicit ARD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		FullDisconnect(pTestInfo);
		TEST_FAILED;
		TEST_RETURN;
	}

//===============================================================================================================
//			Begin Testing:Positive Test for Implicit APD 
//===============================================================================================================	
	//Get Implicit APD handle
	returncode = SQLGetStmtAttr(hstmt, SQL_ATTR_APP_PARAM_DESC, &hImApd, 0, NULL);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetStmtAttr: get APD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG,_T("Cannot allocate descriptor: Aborting Implicit APD tests.\n"));
		TEST_FAILED;
		goto ExAPDtests;		// transfers control to the next set of tests
	}

	for (i = 0;i < DATA_ARR_LEN; i++)		// i = index to TestDataAPD
	{
		TESTCASE_BEGIN("Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Implicit APD.\n");


		//set multiple Fields
		RecNumber = i + 1;		//increment the recnumber and thus set the next rec (change SQL_DESC_COUNT)
		
		setDescRecHandle		= hImApd ;
		setDescRecNumber		= RecNumber;
		setDescType				= TestDataAPD[i].DescType; 
		setDescIntervalCode		= TestDataAPD[i].DescDatetimeIntervalCode;
		setDescOctetLength		= TestDataAPD[i].DescOctetLength;	
		setDescPrecision		= TestDataAPD[i].DescPrecision;	
		setDescScale			= TestDataAPD[i].DescScale;	
		setDescDataPtr			= TestDataAPD[i].DescDataPtr;			
		setDescOctectLengthPtr	= TestDataAPD[i].DescOctectLengthPtr;			
		setDescIndicatorPtr		= TestDataAPD[i].DescIndicatorPtr;	

		/*LogMsg(NONE,_T("SQLSetDescRec(handle,%d,%d,%d,%d,%d,%d,%s,%d,%d)\n"),
											setDescRecNumber, 
											setDescType, 
											setDescIntervalCode, 
											setDescOctetLength , 
											setDescPrecision, 
											setDescScale, 
											setDescDataPtr,
											setDescOctectLengthPtr, 
											setDescIndicatorPtr);  */

		returncode = SQLSetDescRec(setDescRecHandle, setDescRecNumber, setDescType, setDescIntervalCode, setDescOctetLength , setDescPrecision, setDescScale, setDescDataPtr,&setDescOctectLengthPtr, &setDescIndicatorPtr);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetDescRec "))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLSetDescRec: positive tests for Implicit APD: TestDataAPD['%d'].\n"),i);
			//FullDisconnect(pTestInfo);
			TEST_FAILED;
			//TEST_RETURN;
			continue;
		}
		
		//Get the Implicit APD Descriptor 
		//LogMsg(SHORTTIMESTAMP,"SQLGetDescRec: test for Implicit APD.\n");
		LogMsg(NONE,_T("SQLSetDescRec / SQLGetDescRec: positive tests for Implicit APD.\n"));


		getDescRecHandle		= hImApd;					
		getDescRecNumber		= RecNumber;				
		getNameMaxLength		= MAXLEN;
		_tcscpy(getDescName	,_T(""));	//initialize
		setDescNullable			= TestDataAPD[i].DescNullable;

		returncode = SQLGetDescRec(getDescRecHandle, getDescRecNumber, (SQLTCHAR*)getDescName, getNameMaxLength, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLGetDescRec: positive tests for Implicit APD: TestDataAPD['%d'].\n"),i);
			//FullDisconnect(pTestInfo);
			TEST_FAILED;
			//TEST_RETURN;
			continue;
		}

		//begin checking  APD values ----------
		
		//check  SQL_DESC_NAME
		if (!(_tcscmp(getDescName, setDescName)))
		{
			LogMsg(NONE,_T("SQL_DESC_NAME value returned is '%s'\n"),getDescName);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NAME: '%s' and actual: '%s' are not matched\n"), setDescName,getDescName);
		}
		
		//check SQL_DESC_TYPE
		if (getDescType == setDescType)
		{
			LogMsg(NONE,_T("SQL_DESC_TYPE value returned is '%d'\n"),getDescType);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_TYPE: '%d' and actual: '%d' are not matched\n"), setDescType, getDescType);
		}

		//check SQL_DESC_DATETIME_INTERVAL_CODE
		if (getDescIntervalCode == setDescIntervalCode)
		{
			LogMsg(NONE,_T("SQL_DESC_DATETIME_INTERVAL_CODE value returned is '%d'\n"),getDescIntervalCode);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_DATETIME_INTERVAL_CODE: '%d' and actual: '%d' are not matched\n"), setDescIntervalCode, getDescIntervalCode);
		}
		//check SQL_DESC_OCTECT_LENGTH
		if (getDescOctectLength == setDescOctetLength)
		{
			LogMsg(NONE,_T("SQL_DESC_OCTECT_LENGTH value returned is '%d'\n"),getDescOctectLength);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_OCTECT_LENGTH: '%d' and actual: '%d' are not matched\n"), setDescOctetLength,getDescOctectLength);
		}

		//check SQL_DESC_PRECISION
		if (getDescPrecision == setDescPrecision)
		{
			LogMsg(NONE,_T("SQL_DESC_PRECISION value returned is '%d'\n"),getDescPrecision);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_PRECISION: '%d' and actual: '%d' are not matched\n"), setDescPrecision,getDescPrecision);
		}

		//check SQL_DESC_SCALE
		if (getDescScale == setDescScale)
		{
			LogMsg(NONE,_T("SQL_DESC_SCALE value returned is '%d'\n"),getDescScale);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_SCALE: '%d' and actual: '%d' are not matched\n"), setDescScale,getDescScale);
		}

		//check SQL_DESCNULLABLE
		if (getDescNullable == setDescNullable)
		{
			LogMsg(NONE,_T("SQL_DESC_NULLABLE value returned is '%d'\n"),getDescNullable);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NULLABLE: '%d' and actual: '%d' are not matched\n"), setDescNullable, getDescNullable);
		}
		// end of checks 
		TESTCASE_END;

	} //end for loop; end of positive tests for APD
	 

//===============================================================================================================
//			Begin Testing:Positive Test for Explicit APD 
//===============================================================================================================
	ExAPDtests: ;		// beginning next set of tests
	
	//mark the beginning of tests in log file
	//LogMsg(SHORTTIMESTAMP, "Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Explicit APD.\n");
	
	//Get Explicit APD handle
	returncode = SQLAllocHandle(SQL_HANDLE_DESC, (SQLHANDLE)hdbc, &hExApd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle: get Explicit APD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG,_T("Cannot allocate descriptor: Aborting Explicit APD tests.\n"));
		TEST_FAILED;
		//TEST_RETURN;
		goto ARDtests;		// transfers control to the next set of tests
	}

	//associate with a statement
	returncode = SQLSetStmtAttr(hstmt, SQL_ATTR_APP_PARAM_DESC, (SQLPOINTER)hExApd, SQL_IS_POINTER);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtAttr: explicit APD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG, _T("Cannot set Explicit APD for statement.\n"));
		TEST_FAILED;
	}

	setDescRecHandle = hExApd ;

	for (i = 0;i < DATA_ARR_LEN; i++)		// i = index to TestDataAPD
	{
		TESTCASE_BEGIN("Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Explicit APD.\n");


		//set multiple Fields
		RecNumber = i + 1;		//increment the recnumber and thus set the next rec (change SQL_DESC_COUNT)
		

		setDescRecNumber		= RecNumber;
		setDescType				= TestDataAPD[i].DescType; 
		setDescIntervalCode		= TestDataAPD[i].DescDatetimeIntervalCode;
		setDescOctetLength		= TestDataAPD[i].DescOctetLength;	
		setDescPrecision		= TestDataAPD[i].DescPrecision;	
		setDescScale			= TestDataAPD[i].DescScale;	
		setDescDataPtr			= TestDataAPD[i].DescDataPtr;			
		setDescOctectLengthPtr	= TestDataAPD[i].DescOctectLengthPtr;			
		setDescIndicatorPtr		= TestDataAPD[i].DescIndicatorPtr;	


		/*LogMsg(NONE,_T("SQLSetDescRect(handle,%d,%d,%d,%d,%d,%d,%s,%d,%d)\n"),
									setDescRecNumber, 
									setDescType, 
									setDescIntervalCode, 
									setDescOctetLength , 
									setDescPrecision, 
									setDescScale, 
									setDescDataPtr,
									setDescOctectLengthPtr, 
									setDescIndicatorPtr);*/

		returncode = SQLSetDescRec(setDescRecHandle, setDescRecNumber, setDescType, setDescIntervalCode, setDescOctetLength , setDescPrecision, setDescScale, setDescDataPtr,&setDescOctectLengthPtr, &setDescIndicatorPtr);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLSetDescRec: positive tests for Explicit APD: TestDataAPD['%d'].\n"),i);
			TEST_FAILED;
			//TEST_RETURN;
			continue;
		}
		
			
		//Get the Explicit APD Descriptor 
		//LogMsg(SHORTTIMESTAMP,"SQLGetDescRec: test for Implicit APD.\n");
		LogMsg(NONE,_T("SQLSetDescRec / SQLGetDescRec: positive tests for Explicit APD.\n"));


		getDescRecHandle		= 	setDescRecHandle;					
		getDescRecNumber		= RecNumber;				
		getNameMaxLength		= MAXLEN;
		_tcscpy(getDescName	,_T(""));	//initialize		
		setDescNullable			= TestDataAPD[i].DescNullable;

		returncode = SQLGetDescRec(getDescRecHandle, getDescRecNumber, (SQLTCHAR*)getDescName, getNameMaxLength, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetDescRec and SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLGetDescRec: positive tests for Explicit APD: TestDataAPD['%d'].\n"),i);
			TEST_FAILED;
			continue;
		}

		//begin checking  APD values 
		
		//check  SQL_DESC_NAME
		if (!(_tcscmp(getDescName, setDescName)))
		{
			LogMsg(NONE,_T("SQL_DESC_NAME value returned is '%s'\n"),getDescName);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NAME: '%s' and actual: '%s' are not matched\n"), setDescName,getDescName);
		}
		
		//check SQL_DESC_TYPE
		if (getDescType == setDescType)
		{
			LogMsg(NONE,_T("SQL_DESC_TYPE value returned is '%d'\n"),getDescType);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_TYPE: '%d' and actual: '%d' are not matched\n"), setDescType, getDescType);
		}

		//check SQL_DESC_DATETIME_INTERVAL_CODE
		if (getDescIntervalCode == setDescIntervalCode)
		{
			LogMsg(NONE,_T("SQL_DESC_DATETIME_INTERVAL_CODE value returned is '%d'\n"),getDescIntervalCode);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_DATETIME_INTERVAL_CODE: '%d' and actual: '%d' are not matched\n"), setDescIntervalCode, getDescIntervalCode);
		}
		//check SQL_DESC_OCTECT_LENGTH
		if (getDescOctectLength == setDescOctetLength)
		{
			LogMsg(NONE,_T("SQL_DESC_OCTECT_LENGTH value returned is '%d'\n"),getDescOctectLength);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_OCTECT_LENGTH: '%d' and actual: '%d' are not matched\n"), setDescOctetLength,getDescOctectLength);
		}

		//check SQL_DESC_PRECISION
		if (getDescPrecision == setDescPrecision)
		{
			LogMsg(NONE,_T("SQL_DESC_PRECISION value returned is '%d'\n"),getDescPrecision);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_PRECISION: '%d' and actual: '%d' are not matched\n"), setDescPrecision,getDescPrecision);
		}

		//check SQL_DESC_SCALE
		if (getDescScale == setDescScale)
		{
			LogMsg(NONE,_T("SQL_DESC_SCALE value returned is '%d'\n"),getDescScale);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_SCALE: '%d' and actual: '%d' are not matched\n"), setDescScale,getDescScale);
		}

		//check SQL_DESCNULLABLE
		if (getDescNullable == setDescNullable)
		{
			LogMsg(NONE,_T("SQL_DESC_NULLABLE value returned is '%d'\n"),getDescNullable);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NULLABLE: '%d' and actual: '%d' are not matched\n"), setDescNullable, getDescNullable);
		}
		// end of checks 


		
		TESTCASE_END;

	} //end for loop; end of positive tests for Explicit APD


	 
//===============================================================================================================
//			Begin Testing: Statement reverts to Implicit APD after freeing Explicit Descriptor
//===============================================================================================================
	
	//mark the beginning of tests in log file
	//LogMsg(SHORTTIMESTAMP, "SQLGetDescRec for Explicit-Implicit APD: statement reverts to implicit descriptor after explicit descriptor has been freed.\n");
	
	//free Explicit APD
	returncode = SQLFreeHandle(SQL_HANDLE_DESC, hExApd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeHandle (for APD)"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG,_T("Cannot free explicit descriptor: Aborting Explicit-Implicit Descriptor tests.\n"));
		TEST_FAILED;
		goto ARDtests;		// transfers control to the next set of tests
	}

	//Use the previously allocated Implicit APD handle
	getDescRecHandle		= hImApd;

		TESTCASE_BEGIN("Test that the implicit descriptor get associated with statement after explicit descriptor has been freed.\n");


		//set multiple Fields
		i			= 0;
		RecNumber = i + 1;		//increment the recnumber and thus set the next rec (change SQL_DESC_COUNT)
		
		
		setDescRecNumber		= RecNumber;
		setDescType				= TestDataAPD[i].DescType; 
		setDescIntervalCode		= TestDataAPD[i].DescDatetimeIntervalCode;
		setDescOctetLength		= TestDataAPD[i].DescOctetLength;	
		setDescPrecision		= TestDataAPD[i].DescPrecision;	
		setDescScale			= TestDataAPD[i].DescScale;	
		setDescDataPtr			= TestDataAPD[i].DescDataPtr;			
		setDescOctectLengthPtr	= TestDataAPD[i].DescOctectLengthPtr;			
		setDescIndicatorPtr		= TestDataAPD[i].DescIndicatorPtr;	

			
		//Get the Implicit APD Descriptor 
		LogMsg(NONE,_T("SQLGetDescRec: tests for Explicit-Implicit Descriptor.\n"));
			
		getDescRecNumber		= RecNumber;				
		getNameMaxLength		= MAXLEN;
		_tcscpy(getDescName	,_T(""));	//initialize		
		setDescNullable			= TestDataAPD[i].DescNullable;

		returncode = SQLGetDescRec(getDescRecHandle, getDescRecNumber, (SQLTCHAR*)getDescName, getNameMaxLength, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLGetDescRec: tests for Explicit-Implicit APD: TestDataAPD['%d'].\n"),i);
			TEST_FAILED;
			//continue;
		}

		//begin checking  APD values ----------
		
		//check  SQL_DESC_NAME
		if (!(_tcscmp(getDescName, setDescName)))
		{
			LogMsg(NONE,_T("SQL_DESC_NAME value returned is '%s'\n"),getDescName);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NAME: '%s' and actual: '%s' are not matched\n"), setDescName,getDescName);
		}
		
		//check SQL_DESC_TYPE
		if (getDescType == setDescType)
		{
			LogMsg(NONE,_T("SQL_DESC_TYPE value returned is '%d'\n"),getDescType);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_TYPE: '%d' and actual: '%d' are not matched\n"), setDescType, getDescType);
		}

		//check SQL_DESC_DATETIME_INTERVAL_CODE
		if (getDescIntervalCode == setDescIntervalCode)
		{
			LogMsg(NONE,_T("SQL_DESC_DATETIME_INTERVAL_CODE value returned is '%d'\n"),getDescIntervalCode);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_DATETIME_INTERVAL_CODE: '%d' and actual: '%d' are not matched\n"), setDescIntervalCode, getDescIntervalCode);
		}
		//check SQL_DESC_OCTECT_LENGTH
		if (getDescOctectLength == setDescOctetLength)
		{
			LogMsg(NONE,_T("SQL_DESC_OCTECT_LENGTH value returned is '%d'\n"),getDescOctectLength);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_OCTECT_LENGTH: '%d' and actual: '%d' are not matched\n"), setDescOctetLength,getDescOctectLength);
		}

		//check SQL_DESC_PRECISION
		if (getDescPrecision == setDescPrecision)
		{
			LogMsg(NONE,_T("SQL_DESC_PRECISION value returned is '%d'\n"),getDescPrecision);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_PRECISION: '%d' and actual: '%d' are not matched\n"), setDescPrecision,getDescPrecision);
		}

		//check SQL_DESC_SCALE
		if (getDescScale == setDescScale)
		{
			LogMsg(NONE,_T("SQL_DESC_SCALE value returned is '%d'\n"),getDescScale);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_SCALE: '%d' and actual: '%d' are not matched\n"), setDescScale,getDescScale);
		}

		//check SQL_DESCNULLABLE
		if (getDescNullable == setDescNullable)
		{
			LogMsg(NONE,_T("SQL_DESC_NULLABLE value returned is '%d'\n"),getDescNullable);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NULLABLE: '%d' and actual: '%d' are not matched\n"), setDescNullable, getDescNullable);
		}
		// end of checks 
		TESTCASE_END;




//==================================================================================================================
//		Begin Testing: Positive Test for Implicit ARD 
//===================================================================================================================
	ARDtests:	;
	
	//mark the beginning of tests in log file
	//LogMsg(SHORTTIMESTAMP, "Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Implicit ARD.\n");
	

	//Get Implicit ARD handle
	returncode = SQLGetStmtAttr(hstmt, SQL_ATTR_APP_ROW_DESC, &hImArd, 0, NULL);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetStmtAttr: get ARD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG, _T("Cannot get ARD: Aborting Implicit ARD tests.\n"));
		TEST_FAILED;
		goto ExARDtests;		//go to next set of tests
	}
				
	for (i = 0;i < DATA_ARR_LEN; i++)		// i = index to TestDataARD
	{
		TESTCASE_BEGIN("Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Implicit ARD.\n");


		
		//set multiple Fields
		RecNumber = i + 1;		//increment the recnumber and thus set the next rec (change SQL_DESC_COUNT)
		
		setDescRecHandle		= hImArd ;
		setDescRecNumber		= RecNumber;
		setDescType				= TestDataARD[i].DescType; 
		setDescIntervalCode		= TestDataARD[i].DescDatetimeIntervalCode;	
		setDescOctetLength		= TestDataARD[i].DescOctetLength;	
		setDescPrecision		= TestDataARD[i].DescPrecision;	
		setDescScale			= TestDataARD[i].DescScale;		
		setDescDataPtr			= TestDataARD[i].DescDataPtr;			
		setDescOctectLengthPtr	= TestDataARD[i].DescOctectLengthPtr;			
		setDescIndicatorPtr		= TestDataARD[i].DescIndicatorPtr;				


		returncode = SQLSetDescRec(setDescRecHandle, setDescRecNumber, setDescType, setDescIntervalCode, setDescOctetLength , setDescPrecision, setDescScale, setDescDataPtr,&setDescOctectLengthPtr, &setDescIndicatorPtr);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetDescRec and SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLSetDescRec: positive tests for Implicit ARD: TestDataARD['%d'].\n"),i);
			//FullDisconnect(pTestInfo);
			TEST_FAILED;
			//TEST_RETURN;
			continue;
		}
		
			
		//Get the Implicit ARD Descriptor 
		LogMsg(NONE,_T("SQLSetDescRec / SQLGetDescRec: positive tests for Implicit ARD.\n"));

		getDescRecHandle		= hImApd;					
		getDescRecNumber		= RecNumber;				
		getNameMaxLength		= MAXLEN;
		_tcscpy(getDescName	,_T(""));	//initialize		
		setDescNullable			= TestDataARD[i].DescNullable;

		returncode = SQLGetDescRec(getDescRecHandle, getDescRecNumber, (SQLTCHAR*)getDescName, getNameMaxLength, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetDescRec and SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLGetDescRec: positive tests for Implicit ARD: TestDataARD['%d'].\n"),i);
			//FullDisconnect(pTestInfo);
			TEST_FAILED;
			//TEST_RETURN;
			break;
		}

		//begin checking  ARD values 
		
		//check  SQL_DESC_NAME
		if (!(_tcscmp(getDescName, setDescName)))
		{
			LogMsg(NONE,_T("SQL_DESC_NAME value returned is '%s'\n"),getDescName);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NAME: '%s' and actual: '%s' are not matched\n"), setDescName,getDescName);
		}
		
		//check SQL_DESC_TYPE
		if (getDescType == setDescType)
		{
			LogMsg(NONE,_T("SQL_DESC_TYPE value returned is '%d'\n"),getDescType);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_TYPE: '%d' and actual: '%d' are not matched\n"), setDescType, getDescType);
		}

		//check SQL_DESC_DATETIME_INTERVAL_CODE
		if (getDescIntervalCode == setDescIntervalCode)
		{
			LogMsg(NONE,_T("SQL_DESC_DATETIME_INTERVAL_CODE value returned is '%d'\n"),getDescIntervalCode);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_DATETIME_INTERVAL_CODE: '%d' and actual: '%d' are not matched\n"), setDescIntervalCode, getDescIntervalCode);
		}
		//check SQL_DESC_OCTECT_LENGTH
		if (getDescOctectLength == setDescOctetLength)
		{
			LogMsg(NONE,_T("SQL_DESC_OCTECT_LENGTH value returned is '%d'\n"),getDescOctectLength);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_OCTECT_LENGTH: '%d' and actual: '%d' are not matched\n"), setDescOctetLength,getDescOctectLength);
		}

		//check SQL_DESC_PRECISION
		if (getDescPrecision == setDescPrecision)
		{
			LogMsg(NONE,_T("SQL_DESC_PRECISION value returned is '%d'\n"),getDescPrecision);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_PRECISION: '%d' and actual: '%d' are not matched\n"), setDescPrecision,getDescPrecision);
		}

		//check SQL_DESC_SCALE
		if (getDescScale == setDescScale)
		{
			LogMsg(NONE,_T("SQL_DESC_SCALE value returned is '%d'\n"),getDescScale);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_SCALE: '%d' and actual: '%d' are not matched\n"), setDescScale,getDescScale);
		}

		//check SQL_DESCNULLABLE
		if (getDescNullable == setDescNullable)
		{
			LogMsg(NONE,_T("SQL_DESC_NULLABLE value returned is '%d'\n"),getDescNullable);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NULLABLE: '%d' and actual: '%d' are not matched\n"), setDescNullable, getDescNullable);
		}
		// end of checks
		TESTCASE_END;

	} //end for loop; end of positive tests for ARD
	


//==================================================================================================================
//		Begin Testing: Positive Test for Explicit ARD 
//===================================================================================================================
	ExARDtests:	;
	
	//mark the beginning of tests in log file
	//LogMsg(SHORTTIMESTAMP, "Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Explicit ARD.\n");
	

	//Get Explicit ARD handle
	returncode = SQLAllocHandle(SQL_HANDLE_DESC, (SQLHANDLE)hdbc, &hExArd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle: get explicit ARD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG, _T("Cannot get ARD: Aborting Implicit ARD tests.\n"));
		TEST_FAILED;
		goto IPDtests;		//go to next set of tests
	}

	//associate with a statement
	returncode = SQLSetStmtAttr(hstmt, SQL_ATTR_APP_ROW_DESC, (SQLPOINTER)hExArd, SQL_IS_POINTER);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtAttr: explicit ARD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG, _T("Cannot set Explicit ARD for statement.\n"));
		TEST_FAILED;
	}

				
	for (i = 0;i < DATA_ARR_LEN; i++)		// i = index to TestDataARD
	{
		TESTCASE_BEGIN("Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Explicit ARD.\n");


		
		//set multiple Fields
		RecNumber = i + 1;		//increment the recnumber and thus set the next rec (change SQL_DESC_COUNT)
		
		setDescRecHandle		= hExArd ;
		setDescRecNumber		= RecNumber;
		setDescType				= TestDataARD[i].DescType; 
		setDescIntervalCode		= TestDataARD[i].DescDatetimeIntervalCode;	
		setDescOctetLength		= TestDataARD[i].DescOctetLength;	
		setDescPrecision		= TestDataARD[i].DescPrecision;	
		setDescScale			= TestDataARD[i].DescScale;		
		setDescDataPtr			= TestDataARD[i].DescDataPtr;			
		setDescOctectLengthPtr	= TestDataARD[i].DescOctectLengthPtr;			
		setDescIndicatorPtr		= TestDataARD[i].DescIndicatorPtr;				


		returncode = SQLSetDescRec(setDescRecHandle, setDescRecNumber, setDescType, setDescIntervalCode, setDescOctetLength , setDescPrecision, setDescScale, setDescDataPtr,&setDescOctectLengthPtr, &setDescIndicatorPtr);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLSetDescRec: positive tests for Explicit ARD: TestDataARD['%d'].\n"),i);
			TEST_FAILED;
			continue;
		}
		
			
		//Get the Explicit ARD Descriptor 
		LogMsg(NONE,_T("SQLSetDescRec and SQLGetDescRec: positive tests for Explicit ARD.\n"));

		getDescRecHandle		= hExArd;					
		getDescRecNumber		= RecNumber;				
		getNameMaxLength		= MAXLEN;
		_tcscpy(getDescName	,_T(""));	//initialize		
		setDescNullable			= TestDataARD[i].DescNullable;

		returncode = SQLGetDescRec(getDescRecHandle, getDescRecNumber, (SQLTCHAR*)getDescName, getNameMaxLength, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLGetDescRec: positive tests for Explicit ARD: TestDataARD['%d'].\n"),i);
			TEST_FAILED;
			break;
		}

		//begin checking  ARD values 
		
		//check  SQL_DESC_NAME
		if (!(_tcscmp(getDescName, setDescName)))
		{
			LogMsg(NONE,_T("SQL_DESC_NAME value returned is '%s'\n"),getDescName);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NAME: '%s' and actual: '%s' are not matched\n"), setDescName,getDescName);
		}
		
		//check SQL_DESC_TYPE
		if (getDescType == setDescType)
		{
			LogMsg(NONE,_T("SQL_DESC_TYPE value returned is '%d'\n"),getDescType);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_TYPE: '%d' and actual: '%d' are not matched\n"), setDescType, getDescType);
		}

		//check SQL_DESC_DATETIME_INTERVAL_CODE
		if (getDescIntervalCode == setDescIntervalCode)
		{
			LogMsg(NONE,_T("SQL_DESC_DATETIME_INTERVAL_CODE value returned is '%d'\n"),getDescIntervalCode);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_DATETIME_INTERVAL_CODE: '%d' and actual: '%d' are not matched\n"), setDescIntervalCode, getDescIntervalCode);
		}
		//check SQL_DESC_OCTECT_LENGTH
		if (getDescOctectLength == setDescOctetLength)
		{
			LogMsg(NONE,_T("SQL_DESC_OCTECT_LENGTH value returned is '%d'\n"),getDescOctectLength);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_OCTECT_LENGTH: '%d' and actual: '%d' are not matched\n"), setDescOctetLength,getDescOctectLength);
		}

		//check SQL_DESC_PRECISION
		if (getDescPrecision == setDescPrecision)
		{
			LogMsg(NONE,_T("SQL_DESC_PRECISION value returned is '%d'\n"), getDescPrecision);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_PRECISION: '%d' and actual: '%d' are not matched\n"), setDescPrecision,getDescPrecision);
		}

		//check SQL_DESC_SCALE
		if (getDescScale == setDescScale)
		{
			LogMsg(NONE,_T("SQL_DESC_SCALE value returned is '%d'\n"),getDescScale);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_SCALE: '%d' and actual: '%d' are not matched\n"), setDescScale,getDescScale);
		}

		//check SQL_DESCNULLABLE
		if (getDescNullable == setDescNullable)
		{
			LogMsg(NONE,_T("SQL_DESC_NULLABLE value returned is '%d'\n"),getDescNullable);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NULLABLE: '%d' and actual: '%d' are not matched\n"), setDescNullable, getDescNullable);
		}
		// end of checks
		TESTCASE_END;

	} //end for loop; end of positive tests for Explicit ARD

	//free explicit ARD
	returncode = SQLFreeHandle(SQL_HANDLE_DESC, hExArd);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeHandle (for ARD)"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		TEST_FAILED;
	}
	

//======================================================================================================================
//		 Begin Testing: Positive Test for Implicit IPD 
//=====================================================================================================================	

	IPDtests:	;
	
	//mark the beginning of tests in log file
	//LogMsg(SHORTTIMESTAMP, "Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Implicit IPD.\n");
	

	//Get Implicit IPD handle
	returncode = SQLGetStmtAttr(hstmt, SQL_ATTR_APP_ROW_DESC, &hImIpd, 0, NULL);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetStmtAttr: get IPD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		LogMsg(ERRMSG, _T("Cannot get IPD: Aborting Implicit IPD tests.\n"));
		TEST_FAILED;
		goto IRDtests;		//go to next set of tests
	}	
	
	
	
	for (i = 0;i < DATA_ARR_LEN; i++)		// i = index to TestDataIPD
	{
		TESTCASE_BEGIN("Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Implicit IPD.\n");
		

		
		//set multiple Fields
		RecNumber = i + 1;		//increment the recnumber and thus set the next rec (change SQL_DESC_COUNT)
		
		setDescRecHandle		= hImIpd ;
		setDescRecNumber		= RecNumber;
		setDescType				= TestDataIPD[i].DescType; 
		setDescIntervalCode		= TestDataIPD[i].DescDatetimeIntervalCode;
		setDescOctetLength		= TestDataIPD[i].DescOctetLength;
		setDescPrecision		= TestDataIPD[i].DescPrecision;	
		setDescScale			= TestDataIPD[i].DescScale;		
		setDescDataPtr			= TestDataIPD[i].DescDataPtr;			
		setDescOctectLengthPtr	= TestDataIPD[i].DescOctectLengthPtr;			
		setDescIndicatorPtr		= TestDataIPD[i].DescIndicatorPtr;				

		returncode = SQLSetDescRec(setDescRecHandle, setDescRecNumber, setDescType, setDescIntervalCode, setDescOctetLength , setDescPrecision, setDescScale, setDescDataPtr,&setDescOctectLengthPtr, &setDescIndicatorPtr);
		if(!CHECKRC(SQL_SUCCESS,returncode, "SQLSetDescRec and SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLSetDescRec: positive tests for Implicit IPD: TestDataIPD['%d'].\n"),i);
			//FullDisconnect(pTestInfo);
			TEST_FAILED;
			//TEST_RETURN;
			continue;
		}
		
			
		//Get the Implicit IPD Descriptor 
		LogMsg(NONE,_T("SQLSetDescRec and SQLGetDescRec: positive tests for Implicit IPD.\n"));


		getDescRecHandle		= hImApd;					
		getDescRecNumber		= RecNumber;				
		getNameMaxLength		= MAXLEN;
		_tcscpy(getDescName	,_T(""));	//initialize	
		setDescNullable			= TestDataIPD[i].DescNullable;

		returncode = SQLGetDescRec(getDescRecHandle, getDescRecNumber, (SQLTCHAR*)getDescName, getNameMaxLength, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG,_T("SQLGetDescRec: positive tests for Implicit IPD: TestDataIPD['%d'].\n"),i);
			//FullDisconnect(pTestInfo);
			TEST_FAILED;
			//TEST_RETURN;
			continue;
		}

		//begin checking  IPD values 
		
		//check  SQL_DESC_NAME
		if (!(_tcscmp(getDescName, setDescName)))
		{
			LogMsg(NONE,_T("SQL_DESC_NAME value returned is '%s'\n"),getDescName);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NAME: '%s' and actual: '%s' are not matched\n"), setDescName,getDescName);
		}
		
		//check SQL_DESC_TYPE
		if (getDescType == setDescType)
		{
			LogMsg(NONE,_T("SQL_DESC_TYPE value returned is '%d'\n"), getDescType);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_TYPE: '%d' and actual: '%d' are not matched\n"), setDescType, getDescType);
		}

		//check SQL_DESC_DATETIME_INTERVAL_CODE
		if (getDescIntervalCode == setDescIntervalCode)
		{
			LogMsg(NONE,_T("SQL_DESC_DATETIME_INTERVAL_CODE value returned is '%d'\n"),getDescIntervalCode);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_DATETIME_INTERVAL_CODE: '%d' and actual: '%d' are not matched\n"), setDescIntervalCode, getDescIntervalCode);
		}
		//check SQL_DESC_OCTECT_LENGTH
		if (getDescOctectLength == setDescOctetLength)
		{
			LogMsg(NONE,_T("SQL_DESC_OCTECT_LENGTH value returned is '%d'\n"),getDescOctectLength);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_OCTECT_LENGTH: '%d' and actual: '%d' are not matched\n"), setDescOctetLength,getDescOctectLength);
		}

		//check SQL_DESC_PRECISION
		if (getDescPrecision == setDescPrecision)
		{
			LogMsg(NONE,_T("SQL_DESC_PRECISION value returned is '%d'\n"),getDescPrecision);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_PRECISION: '%d' and actual: '%d' are not matched\n"), setDescPrecision,getDescPrecision);
		}

		//check SQL_DESC_SCALE
		if (getDescScale == setDescScale)
		{
			LogMsg(NONE,_T("SQL_DESC_SCALE value returned is '%d'\n"),getDescScale);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_SCALE: '%d' and actual: '%d' are not matched\n"), setDescScale,getDescScale);
		}

		//check SQL_DESCNULLABLE
		if (getDescNullable == setDescNullable)
		{
			LogMsg(NONE,_T("SQL_DESC_NULLABLE value returned is '%d'\n"),getDescNullable);
		}
		else
		{
			TEST_FAILED;					
			LogMsg(ERRMSG, _T("expect SQL_DESC_NULLABLE: '%d' and actual: '%d' are not matched\n"), setDescNullable, getDescNullable);
		}
		// end of checks 
		TESTCASE_END;

	} //end for loop; end of positive tests for IPD


//==================================================================================================================
//		 Begin Testing: Posituve Tests for IRD (IRD Desc Fields are read only) 
//==================================================================================================================
		IRDtests: ;

		//mark the beginning of tests in log file
		//LogMsg(SHORTTIMESTAMP, "Test the positive functionality of SQLSetDescRec and SQLGetDescRec for Implicit IRD.\n");
	
		//Get Implicit IRD handle
		returncode = SQLGetStmtAttr(hstmt, SQL_ATTR_IMP_ROW_DESC, &hImIrd, 0, NULL);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetStmtAttr"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			LogMsg(ERRMSG, _T("Cannot get IRD: Aborting Implicit IRD tests.\n"));
			TEST_FAILED;
		//	TEST_RETURN;		//this will abort tests and perform a full disconnect.
		}

		//---------------------------------------------------------------------------------------------------------
		
		TESTCASE_BEGIN("Test SQLSetDescRec for Implicit IRD: IRD Descriptor Fields cannot be set by the application.\n");
		
		//set multiple Fields
		RecNumber = i + 1;		//increment the recnumber and thus set the next rec (change SQL_DESC_COUNT)
		
		setDescRecHandle		= hImIrd ;
		setDescRecNumber		= RecNumber;
		setDescType				= TestDataIRD[i].DescType; 
		setDescIntervalCode		= TestDataIRD[i].DescDatetimeIntervalCode;	
		setDescOctetLength		= TestDataIRD[i].DescOctetLength;	
		setDescPrecision		= TestDataIRD[i].DescPrecision;	
		setDescScale			= TestDataIRD[i].DescScale;		
		setDescDataPtr			= TestDataIRD[i].DescDataPtr;			
		setDescOctectLengthPtr	= TestDataIRD[i].DescOctectLengthPtr;			
		setDescIndicatorPtr		= TestDataIRD[i].DescIndicatorPtr;				

		returncode = SQLSetDescRec(setDescRecHandle, setDescRecNumber, setDescType, setDescIntervalCode, setDescOctetLength , setDescPrecision, setDescScale, setDescDataPtr,&setDescOctectLengthPtr, &setDescIndicatorPtr);
		if(!CHECKRC(SQL_ERROR,returncode,"SQLSetDescRec"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			TEST_FAILED;

		}
		TESTCASE_END;
		
		//-------------------------------------------------------------------------------------------------------------
		
		TESTCASE_BEGIN("Test SQLGetDescRec for Implicit IRD: IRD Descriptor Fields not populated before call to DB.\n");
		
		//This testcases use the Implicit IRD handle obtained in previous testcase

		returncode = SQLGetDescRec(hImIrd, 1, (SQLTCHAR*)getDescName, MAXLEN, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
		if(!CHECKRC(SQL_NO_DATA_FOUND,returncode,"SQLGetDescField"))
		{
			LogAllErrorsVer3(henv,hdbc,hstmt);
			TEST_FAILED;
			//TEST_RETURN;	//last test: valid to use TEST_RETURN when the test suite must be exited.
		}

		TESTCASE_END;

//===============================================================================================================
//			Begin Testing:Positive Test for populated Implicit IRD 
//===============================================================================================================

	TESTCASE_BEGIN("Test SQLGetDescRec for populated Implicit IRD.\n");

	//mark the beginning of tests in log file
	//LogMsg(SHORTTIMESTAMP, "Test the positive functionality of (SQLSetDescRec) and SQLGetDescRec for Implicit IRD.\n");
	
	//alloc new handle
	returncode = SQLAllocHandle(SQL_HANDLE_STMT, (SQLHANDLE)hdbc, &hstmt1);	
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocHandle"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt1);
		LogMsg(ERRMSG,_T("Cannot allocate statement: Aborting populated Implicit IRD tests.\n"));
		FullDisconnect(pTestInfo);
		TEST_FAILED;
		goto Cleanup;		// transfers control to the next set 
	}

	//Get Implicit IRD handle
	returncode = SQLGetStmtAttr(hstmt, SQL_ATTR_APP_PARAM_DESC, &hIrd, 0, NULL);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetStmtAttr: get IRD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt1);
		LogMsg(ERRMSG,_T("Cannot allocate descriptor: Aborting populated Implicit IRD tests.\n"));
		TEST_FAILED;
		goto Cleanup;		// transfers control to the next set 
	}

	//populate the IRD by executing an catalog api
	returncode = SQLGetTypeInfo(hstmt1, SQL_ALL_TYPES);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetTypeInfo: population of IRD"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt1);
		LogMsg(ERRMSG,_T("Cannot execute statement: Aborting populated Implicit IRD tests.\n"));
		TEST_FAILED;
		goto Cleanup;		// transfers control to the next set 
	}	

	//check IRD
	returncode = SQLGetDescRec(hIrd, 1, (SQLTCHAR*)getDescName, MAXLEN, &getDescNameActualLength, &getDescType, &getDescIntervalCode, &getDescOctectLength, &getDescPrecision, &getDescScale, &getDescNullable);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetDescField"))
	{
			LogAllErrorsVer3(henv,hdbc,hstmt1);
			TEST_FAILED;
			//TEST_RETURN;	//last test: valid to use TEST_RETURN when the test suite must be exited.
	}
	
	TESTCASE_END;

	// free implicitly allocated descriptors by freeing statement
	returncode = SQLFreeHandle(SQL_HANDLE_STMT,hstmt1);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeHandle"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt1);
		TEST_FAILED;
	}

//===========================================================================================================
//		begin cleanup 
//==============================================================================================================
Cleanup: ;
		
	// free implicitly allocated descriptors by freeing statement
	returncode = SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFreeHandle"))
	{
		LogAllErrorsVer3(henv,hdbc,hstmt);
		TEST_FAILED;
	}
	

	
	FullDisconnect3(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing API => SQLSetDescRec and SQLGetDescRec.\n"));
    TEST_RETURN;
} //end of test ****************