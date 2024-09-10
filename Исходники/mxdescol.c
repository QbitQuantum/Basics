/*
---------------------------------------------------------
   TestSQLDescribeCol for MP Specific
---------------------------------------------------------
*/
PassFail TestMXSQLDescribeCol(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;
 	TCHAR			Heading[MAX_STRING_SIZE];
	RETCODE			returncode;
	SQLHANDLE 		henv, hdbc, hstmt;
	UWORD			icol;
	SWORD			numcol, st, cs, cnull, cl, colsize = 2;
	SQLULEN         cp; 
	TCHAR			cn[COLNAME_LEN];
	TCHAR			*colname[COL_LEN];
	TCHAR			*ExecDirStr[12];
	TCHAR			*colVal[2];

#ifndef _WM 
	#ifdef UNICODE
	SWORD			SQLType[] = {SQL_WCHAR,SQL_WVARCHAR,SQL_DECIMAL,SQL_NUMERIC,SQL_SMALLINT,SQL_INTEGER,
									SQL_REAL,SQL_DOUBLE,SQL_DOUBLE,SQL_DATE,SQL_TIME,SQL_TIMESTAMP,SQL_WVARCHAR,SQL_BIGINT,
									SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,
									SQL_WCHAR,SQL_WVARCHAR,SQL_WVARCHAR,SQL_CHAR,SQL_VARCHAR,SQL_WVARCHAR};
    SQLULEN			ColPrec[] = {254,254,18,18,5,10,7,15,15,10,8,26,2000,19,19,19,128,128,10,18,30,254,254,2000,1016,1016,2000};

	SWORD			ColScale[]= {0,0,6,6,0,0,0,0,0,0,0,6,0,0,0,6,0,128,5,5,10,0,0,0,0,0,0};
	#else
	SWORD			SQLType[] = {SQL_CHAR,SQL_VARCHAR,SQL_DECIMAL,SQL_NUMERIC,SQL_SMALLINT,SQL_INTEGER,
									SQL_REAL,SQL_DOUBLE,SQL_DOUBLE,SQL_DATE,SQL_TIME,SQL_TIMESTAMP,SQL_VARCHAR,SQL_BIGINT,
									SQL_WCHAR,SQL_WVARCHAR,SQL_WVARCHAR,
									SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC	};
    SQLULEN			ColPrec[] = {254,254,18,18,5,10,7,15,15,10,8,26,2000,19,254,127,2000,19,19,128,128,10,18,30};

	SWORD			ColScale[]= {0,  0,  6, 6, 0,0, 0,0, 0, 0, 0,6, 0,   0, 0,  0,  0,   0, 6, 0,  128,5, 5, 10};
	#endif
#else
    SWORD			SQLType[] = {SQL_CHAR,SQL_VARCHAR,SQL_DECIMAL,SQL_NUMERIC,SQL_SMALLINT,SQL_INTEGER,
									SQL_REAL,SQL_DOUBLE,SQL_DOUBLE,SQL_CHAR,SQL_TIME,SQL_TIMESTAMP,SQL_LONGVARCHAR,SQL_BIGINT,
									SQL_WCHAR,SQL_WVARCHAR,SQL_WLONGVARCHAR,
									SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC};
    SQLULEN			ColPrec[] = {254,127,18,18,5,10,7,15,15,8,8,26,2000,19,254,127,2000,19,19,128,128,10,18,30};

	SWORD			ColScale[]= {0,0,6,6,0,0,0,0,0,0,0,6,0,0,0,6,0,128,5,5,10,0,0,0,0,0,0};
#endif
	

	TCHAR			TempType1[50],TempType2[50];
	SWORD			ColNullable[] = {SQL_NULLABLE,SQL_NO_NULLS,SQL_NULLABLE};

	TCHAR			*TestCase[] = {
					_T("before preparing stmt "),
					_T("before preparing & executing stmt "),
					_T("before preparing, executing & fetching stmt "),
					_T("before execdirect stmt "),
					_T("before execdirect & fetching stmt "),
					_T("before preparing param stmt "),
					_T("before preparing & binding stmt "),
					_T("before preparing, binding & executing stmt "),
					_T("before preparing, binding, executing & fetching stmt ")
					};

	int				lend = 9, iend = 3;
	SQLUSMALLINT	i = 0, l = 0;
	SQLLEN			cbIn = SQL_NTS;

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars(_T("SQLDescribeColumns"), charset_file);
	if (var_list == NULL) return FAILED;

	//print_list(var_list);
	colname[0] = var_mapping(_T("SQLDescribeColumns_colname_1"), var_list);
	colname[1] = var_mapping(_T("SQLDescribeColumns_colname_2"), var_list);
	colname[2] = var_mapping(_T("SQLDescribeColumns_colname_3"), var_list);
	colname[3] = var_mapping(_T("SQLDescribeColumns_colname_4"), var_list);
	colname[4] = var_mapping(_T("SQLDescribeColumns_colname_5"), var_list);
	colname[5] = var_mapping(_T("SQLDescribeColumns_colname_6"), var_list);
	colname[6] = var_mapping(_T("SQLDescribeColumns_colname_7"), var_list);
	colname[7] = var_mapping(_T("SQLDescribeColumns_colname_8"), var_list);
	colname[8] = var_mapping(_T("SQLDescribeColumns_colname_9"), var_list);
	colname[9] = var_mapping(_T("SQLDescribeColumns_colname_10"), var_list);
	colname[10] = var_mapping(_T("SQLDescribeColumns_colname_11"), var_list);
	colname[11] = var_mapping(_T("SQLDescribeColumns_colname_12"), var_list);
	colname[12] = var_mapping(_T("SQLDescribeColumns_colname_13"), var_list);
	colname[13] = var_mapping(_T("SQLDescribeColumns_colname_14"), var_list);
	colname[14] = var_mapping(_T("SQLDescribeColumns_colname_15"), var_list);
	colname[15] = var_mapping(_T("SQLDescribeColumns_colname_16"), var_list);
	colname[16] = var_mapping(_T("SQLDescribeColumns_colname_17"), var_list);
	colname[17] = var_mapping(_T("SQLDescribeColumns_colname_18"), var_list);
	colname[18] = var_mapping(_T("SQLDescribeColumns_colname_19"), var_list);
	colname[19] = var_mapping(_T("SQLDescribeColumns_colname_20"), var_list);
	colname[20] = var_mapping(_T("SQLDescribeColumns_colname_21"), var_list);
	colname[21] = var_mapping(_T("SQLDescribeColumns_colname_22"), var_list);
	colname[22] = var_mapping(_T("SQLDescribeColumns_colname_23"), var_list);
	colname[23] = var_mapping(_T("SQLDescribeColumns_colname_24"), var_list);

#ifdef UNICODE 
	colname[24] = var_mapping(_T("SQLDescribeColumns_colname_25"), var_list);
	colname[25] = var_mapping(_T("SQLDescribeColumns_colname_26"), var_list);
	colname[26] = var_mapping(_T("SQLDescribeColumns_colname_27"), var_list);
#endif

	ExecDirStr[0] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_1"), var_list);
	ExecDirStr[1] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_2"), var_list);
	ExecDirStr[2] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_3"), var_list);
	ExecDirStr[3] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_4"), var_list);
	ExecDirStr[4] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_5"), var_list);
	ExecDirStr[5] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_6"), var_list);
	ExecDirStr[6] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_7"), var_list);
	ExecDirStr[7] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_8"), var_list);
	ExecDirStr[8] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_9"), var_list);
	ExecDirStr[9] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_10"), var_list);
	ExecDirStr[10] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_11"), var_list);
	ExecDirStr[11] = var_mapping(_T("SQLDescribeColumns_ExecDirStr_12"), var_list);

	colVal[0] = var_mapping(_T("SQLDescribeColumns_colVal_1"), var_list);
	colVal[1] = var_mapping(_T("SQLDescribeColumns_colVal_2"), var_list);
//===========================================================================================================

	//if(isUCS2) {
	//	LogMsg(NONE,_T("Setup for UCS2 mode testing: ColPrec has to be doubled\n"));

	//	l = sizeof(SQLType)/sizeof(SQLType[0]);
	//	while(i < l) {
	//		if(SQLType[i] == SQL_WCHAR) {
	//			SQLType[i] = SQL_WCHAR;
	//			//ColPrec[i] *= 2;  --> This is in character, so no need to double
	//		}
	//		else if (SQLType[i] == SQL_WVARCHAR) {
	//			SQLType[i] = SQL_WVARCHAR;
	//			//ColPrec[i] *= 2;  --> This is in character, so no need to double
	//		}
	//		else if (SQLType[i] == SQL_WLONGVARCHAR)	{
	//			SQLType[i] = SQL_WLONGVARCHAR;
	//			//ColPrec[i] *= 2;  --> This is in character, so no need to double
	//		}
	//		else {
	//		}
	//		i++;
	//	}
	//	i = 0;
	//	l = 0;
	//}

//===========================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing API => MX Specific SQLDescribeColumns.\n"));
	TEST_INIT;
	   
	TESTCASE_BEGIN("Setup for SQLDescribCol tests\n");

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
		TEST_FAILED;
		TEST_RETURN;
	}
	TESTCASE_END;  // end of setup
	for (l = 0; l < lend; l++)
	{
		for (i = 0; i < iend; i++)
		{
			//==================================================================================
			_stprintf(Heading,_T("SQLDescribeCol: Test #%d.%d\n"),l,i);
			TESTCASE_BEGINW(Heading);
			if ((i != (iend-1)) && (l < 5))
			{
				SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i],SQL_NTS); /* cleanup */
				returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i+iend],SQL_NTS); /* create table */
				LogMsg(NONE,_T("%s\n"), ExecDirStr[i+iend]);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				else
				{
					returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend],SQL_NTS); /* insert into table */
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					else
					{
						LogMsg(NONE,_T("SQLDescribeCol: %s\n"),TestCase[l]);
						LogMsg(NONE,_T("     %s\n"),ExecDirStr[i+iend+iend+iend]);
						switch( l )
						{
							case 0:
								returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								break;
							case 1 :
								returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
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
								}
								break;
							case 2 :
								returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
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
										returncode = SQLFetch(hstmt);
										if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))
										{
											LogAllErrors(henv,hdbc,hstmt);
											TEST_FAILED;
										}
									}
								}
								break;
							case 3 :
								returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								break;
							case 4 :
								returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								else
								{
									returncode = SQLFetch(hstmt);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
								}
								break;
						}
						if (returncode == SQL_SUCCESS)
						{
							returncode=SQLNumResultCols(hstmt, &numcol);
							if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNumResultCols"))
							{
								LogAllErrors(henv,hdbc,hstmt);
								TEST_FAILED;
							}
							for (icol = 1; icol <= numcol; icol++)
							{
								LogMsg(LINEBEFORE,_T("SQLDescribeCol: checking Column #%d\n"),icol);
								returncode = SQLDescribeCol(hstmt,icol,(SQLTCHAR*)cn,COLNAME_LEN,&cl,&st,&cp,&cs,&cnull);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLDescribeCol"))
								{
									TEST_FAILED;
									LogAllErrors(henv,hdbc,hstmt);
								}
								colsize=_tcslen(colname[icol-1]);
								if(isCharSet == TRUE)
									colsize -= 2;
								if ((cwcscmp(cn,colname[icol-1],FALSE) == 0) 
									 && (cl == colsize) 
									 && (st == SQLType[icol-1]) 
									 && (cp == ColPrec[icol-1]) 
									 && (cs == ColScale[icol-1]) 
									 && (cnull == ColNullable[i]))
								{
									LogMsg(NONE,_T("colname expect: %s and actual: %s are matched\n"),colname[icol-1],cn);
									LogMsg(NONE,_T("ColNameLen expect: %d and actual: %d are matched\n"),colsize,cl);
									LogMsg(NONE,_T("SQLType expect: %s and actual: %s are matched\n"),
									SQLTypeToChar(SQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2));
									LogMsg(NONE,_T("ColPrec expect: %d and actual: %d are matched\n"),ColPrec[icol-1],cp);
									LogMsg(NONE,_T("ColScale expect: %d and actual: %d are matched\n"),ColScale[icol-1],cs);
									LogMsg(NONE,_T("ColNullable expect: %s and actual: %s are matched\n\n"),
									SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2));
								}
								else
								{
									TEST_FAILED;	
									if (cwcscmp(cn,colname[icol-1],FALSE) != 0)
										LogMsg(ERRMSG,_T("colname expect: %s and actual: %s are not matched line %d\n"),colname[icol-1],cn,__LINE__);
									if (cl != colsize)
										LogMsg(ERRMSG,_T("ColNameLen expect: %d and actual: %d are not matched line %d\n"),colsize,cl,__LINE__);
									if (st != SQLType[icol-1])
										LogMsg(ERRMSG,_T("SQLType expect: %s and actual: %s are not matched line %d\n"),
											SQLTypeToChar(SQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2),__LINE__);
									if (cp != ColPrec[icol-1])
										LogMsg(ERRMSG,_T("ColPrec expect: %d and actual: %d are not matched line %d\n"),ColPrec[icol-1],cp,__LINE__);
									if (cs != ColScale[icol-1])
										LogMsg(ERRMSG,_T("ColScale expect: %d and actual: %d are not matched line %d\n"),ColScale[icol-1],cs,__LINE__);
									if (cnull != ColNullable[i])
										LogMsg(ERRMSG,_T("ColNullable expect: %s and actual: %s are not matched line %d\n\n"),
											SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2),__LINE__);
								}
							} /* end icol loop */
						}
						else
						{
							TEST_FAILED;
							LogAllErrors(henv,hdbc,hstmt);
						}
						SQLFreeStmt(hstmt,SQL_CLOSE);
						SQLExecDirect(hstmt,(SQLTCHAR*) ExecDirStr[i],SQL_NTS); /* cleanup */
					}
				}
			}
			else if ((i == (iend-1)) && (l >= 5))
			{
				SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i],SQL_NTS); /* cleanup */ 
				returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i+iend],SQL_NTS); /* create table */
				LogMsg(NONE,_T("%s\n"), ExecDirStr[i+iend]);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				else
				{
					returncode = SQLExecDirect(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend],SQL_NTS); /* insert into table */
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					else
					{
						LogMsg(NONE,_T("SQLDescribeCol: %s\n"),TestCase[l]);
						LogMsg(NONE,_T("     %s\n"),ExecDirStr[i+iend+iend+iend]);
						switch( l ) 
						{
							case 5 :
								returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								break;
							case 6 :
								returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								else
								{
									returncode = SQLBindParameter(hstmt,1,SQL_PARAM_INPUT,SQL_C_TCHAR,SQL_WCHAR,2000,0,(SQLPOINTER)colVal[0],300,&cbIn);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
									returncode = SQLBindParameter(hstmt,2,SQL_PARAM_INPUT,SQL_C_TCHAR,SQL_WCHAR,2000,0,(SQLPOINTER)colVal[1],300,&cbIn);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
								}
								break;
							case 7 :
								returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								else
								{
									returncode = SQLBindParameter(hstmt,1,SQL_PARAM_INPUT,SQL_C_TCHAR,SQL_WCHAR,2000,0,(SQLPOINTER)colVal[0],300,&cbIn);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
									returncode = SQLBindParameter(hstmt,2,SQL_PARAM_INPUT,SQL_C_TCHAR,SQL_WCHAR,2000,0,(SQLPOINTER)colVal[1],300,&cbIn);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
									returncode = SQLExecute(hstmt);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
								}
								break;
							  case 8 :
								returncode = SQLPrepare(hstmt,(SQLTCHAR*)ExecDirStr[i+iend+iend+iend], SQL_NTS);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
								{
									LogAllErrors(henv,hdbc,hstmt);
									TEST_FAILED;
								}
								else
								{
									returncode = SQLBindParameter(hstmt,1,SQL_PARAM_INPUT,SQL_C_TCHAR,SQL_WCHAR,2000,0,(SQLPOINTER)colVal[0],300,&cbIn);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
									returncode = SQLBindParameter(hstmt,2,SQL_PARAM_INPUT,SQL_C_TCHAR,SQL_WCHAR,2000,0,(SQLPOINTER)colVal[1],300,&cbIn);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindParameter"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
									returncode = SQLExecute(hstmt);
									if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecute"))
									{
										LogAllErrors(henv,hdbc,hstmt);
										TEST_FAILED;
									}
									else
									{
										returncode = SQLFetch(hstmt);
										if(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))
										{
											LogAllErrors(henv,hdbc,hstmt);
											TEST_FAILED;
										}
									}
								}
								break;
						}
						if (returncode == SQL_SUCCESS)
						{
							SQLNumResultCols(hstmt, &numcol);
							if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNumResultCols"))
							{
								LogAllErrors(henv,hdbc,hstmt);
								TEST_FAILED;
							}
							for (icol = 1; icol <= numcol; icol++)
							{
								LogMsg(LINEBEFORE,_T("SQLDescribeCol: checking Column #%d\n"),icol);
								returncode = SQLDescribeCol(hstmt,icol,(SQLTCHAR*)cn,COLNAME_LEN,&cl,&st,&cp,&cs,&cnull);
								if(!CHECKRC(SQL_SUCCESS,returncode,"SQLDescribeCol"))
								{
									TEST_FAILED;
									LogAllErrors(henv,hdbc,hstmt);
								}
								colsize=_tcslen(colname[icol-1]);
								if(isCharSet == TRUE)
									colsize -= 2;
								if ((cwcscmp(cn,colname[icol-1],FALSE) == 0) 
									 && (cl == colsize) 
									 && (st == SQLType[icol-1]) 
									 && (cp == ColPrec[icol-1]) 
									 && (cs == ColScale[icol-1]) 
									 && (cnull == ColNullable[i]))
								{
									LogMsg(NONE,_T("colname expect: %s and actual: %s are matched\n"),colname[icol-1],cn);
									LogMsg(NONE,_T("ColNameLen expect: %d and actual: %d are matched\n"),colsize,cl);
									LogMsg(NONE,_T("SQLType expect: %s and actual: %s are matched\n"),
										SQLTypeToChar(SQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2));
									LogMsg(NONE,_T("ColPrec expect: %d and actual: %d are matched\n"),ColPrec[icol-1],cp);
									LogMsg(NONE,_T("ColScale expect: %d and actual: %d are matched\n"),ColScale[icol-1],cs);
									LogMsg(NONE,_T("ColNullable expect: %s and actual: %s are matched\n\n"),
										SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2));
								}
								else
								{
									TEST_FAILED;	
									if (cwcscmp(cn,colname[icol-1],FALSE) != 0)
										LogMsg(ERRMSG,_T("colname expect: %s and actual: %s are not matched at line %d\n"),colname[icol-1],cn,__LINE__);
									if (cl != colsize)
										LogMsg(ERRMSG,_T("ColNameLen expect: %d and actual: %d are not matched at line %d\n"),colsize,cl,__LINE__);
									if (st != SQLType[icol-1])
										LogMsg(ERRMSG,_T("SQLType expect: %s and actual: %s are not matched at line %d\n"),
											SQLTypeToChar(SQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2),__LINE__);
									if (cp != ColPrec[icol-1])
										LogMsg(ERRMSG,_T("ColPrec expect: %d and actual: %d are not matched at line %d\n"),ColPrec[icol-1],cp,__LINE__);
									if (cs != ColScale[icol-1])
										LogMsg(ERRMSG,_T("ColScale expect: %d and actual: %d are not matched at line %d\n"),ColScale[icol-1],cs,__LINE__);
									if (cnull != ColNullable[i])
										LogMsg(ERRMSG,_T("ColNullable expect: %s and actual: %s are not matched at line %d\n\n"),
											SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2),__LINE__);
								}
							}
						}
					}
					SQLFreeStmt(hstmt,SQL_CLOSE);
					SQLExecDirect(hstmt,(SQLTCHAR*) ExecDirStr[i],SQL_NTS); 
				}
			}
			TESTCASE_END;
		} /* iend loop */
	} /* lend loop */
	FullDisconnect(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing API => MX Specific SQLDescribeColumns.\n"));
	free_list(var_list);
	TEST_RETURN;
}