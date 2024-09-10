PassFail TestSQLSpecialColumns(TestInfo *pTestInfo, int MX_MP_SPECIFIC)
{                  
	TEST_DECLARE;
 	TCHAR			Heading[MAX_HEADING_SIZE];
 	RETCODE			returncode;
 	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt;
	TCHAR			TQualifier[NAME_LEN],TOwner[NAME_LEN],TName[NAME_LEN];
	UWORD			fColType[NUM_COLTYPE] = {SQL_BEST_ROWID,SQL_ROWVER};
	UWORD			Scope[NUM_SCOPE] = {SQL_SCOPE_CURROW,SQL_SCOPE_TRANSACTION,SQL_SCOPE_SESSION};
	UWORD			Nullable[NUM_NULL] = {SQL_NO_NULLS,SQL_NULLABLE};
	TCHAR			ocname[MAX_COLUMN_NAME],octype[MAX_COLUMN_NAME];
	SWORD			oscope,ocdatatype,ocsca,ocpc;
	SDWORD			ocprec,oclen;		
	SQLLEN			oscopelen,ocnamelen,ocdatatypelen,octypelen,ocpreclen,oclenlen,ocscalen,ocpclen;

	struct
	{
		TCHAR		*ColName;
		SWORD		ColDataType;
		TCHAR		*ColTypeName;
		TCHAR		*ColTypeOutput;
		TCHAR		*ColTypeLen;
		SDWORD		ColPrec;
		SWORD		ColSca;
		SDWORD		ColLen;
	} Columns[] = {
							{_T("--"),SQL_CHAR,_T("char"),_T("CHAR"),_T("(10) CHARACTER SET ISO88591"),10,0,10},
							{_T("--"),SQL_VARCHAR,_T("varchar"),_T("VARCHAR"),_T("(10) CHARACTER SET ISO88591"),10,0,10},
							{_T("--"),SQL_VARCHAR,_T("varchar"),_T("VARCHAR"),_T("(255) CHARACTER SET ISO88591"),255,0,255},
							{_T("--"),SQL_WCHAR,_T("char"),_T("NCHAR"),_T("(10) CHARACTER SET UCS2"),10,0,20},
							{_T("--"),SQL_WVARCHAR,_T("varchar"),_T("NCHAR VARYING"),_T("(10) CHARACTER SET UCS2"),10,0,20},
							{_T("--"),SQL_WVARCHAR,_T("varchar"),_T("NCHAR VARYING"),_T("(255) CHARACTER SET UCS2"),255,0,510},
							{_T("--"),SQL_DECIMAL,_T("decimal"),_T("DECIMAL SIGNED"),_T("(10,5)"),10,5,12},
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC SIGNED"),_T("(10,5)"),10,5,12},
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC SIGNED"),_T("(19,0)"),19,0,21},				//Bignum
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC SIGNED"),_T("(19,6)"),19,6,21},				//Bignum
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC SIGNED"),_T("(128,0)"),128,0,130},			//Bignum
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC SIGNED"),_T("(128,128)"),128,128,130},		//Bignum
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC SIGNED"),_T("(128,64)"),128,64,130},			//Bignum
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC UNSIGNED"),_T("(10,5) unsigned"),10,5,12},		//Bignum
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC UNSIGNED"),_T("(18,5) unsigned"),18,5,20},		//Bignum
							{_T("--"),SQL_NUMERIC,_T("numeric"),_T("NUMERIC UNSIGNED"),_T("(30,10) unsigned"),30,10,32},	//Bignum
							{_T("--"),SQL_SMALLINT,_T("smallint"),_T("SMALLINT SIGNED"),_T(""),5,0,2},
							{_T("--"),SQL_INTEGER,_T("integer"),_T("INTEGER SIGNED"),_T(""),10,0,4},
							{_T("--"),SQL_BIGINT,_T("bigint"),_T("BIGINT SIGNED"),_T(""),19,0,20},
							{_T("--"),SQL_DATE,_T("date"),_T("DATE"),_T(""),10,0,6},
							{_T("--"),SQL_TIME,_T("time"),_T("TIME"),_T(""),8,0,6},
							{_T("--"),SQL_TIMESTAMP,_T("TIMESTAMP"),_T("timestamp"),_T(""),26,6,16},
							{_T("--"),SQL_BIT,_T("bit"),_T("BIT"),_T(""),1,1,0},
							{_T("--"),SQL_TINYINT,_T("tinyint"),_T("TINYINT"),_T(""),3,0,2},
							{_T("--"),SQL_BINARY,_T("binary"),_T("BINARY"),_T("(10)"),10,0,10},
							{_T("--"),SQL_VARBINARY,_T("varbinary"),_T("VARBINARY"),_T("(10)"),10,0,10},
							{_T("--"),SQL_WCHAR,_T("char"),_T("NCHAR"),_T("(10) CHARACTER SET UTF8"),10,0,20},
							{_T("--"),SQL_WVARCHAR,_T("varchar"),_T("NCHAR VARYING"),_T("(10) CHARACTER SET UTF8"),10,0,20},
							{_T("--"),SQL_WVARCHAR,_T("varchar"),_T("NCHAR VARYING"),_T("(255) CHARACTER SET UTF8"),255,0,510},
							{_T("--"),0,_T("endloop"),_T(""),0,0,0,0}
						};

	TCHAR	*TableStr[4];
	TCHAR	ColStr[MAX_NOS_SIZE], KeyStr[MAX_NOS_SIZE], CreateTbl[MAX_NOS_SIZE],END_LOOP[10];
	int		i = 0, k = 0,ct = 0, s = 0, t = 0, n = 0, psc = 1;
    BOOL    found = FALSE;
	//TCHAR *charNameUCS2 = _T("NCHAR");
	//TCHAR *varcharNameUCS2 = _T("NCHAR VARYING");

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars(_T("SQLSpecialColumns"), charset_file);
	if (var_list == NULL) return FAILED;

	//print_list(var_list);
	Columns[0].ColName = var_mapping(_T("SQLSpecialColumns_Columns_1"), var_list);
	Columns[1].ColName = var_mapping(_T("SQLSpecialColumns_Columns_2"), var_list);
	Columns[2].ColName = var_mapping(_T("SQLSpecialColumns_Columns_3"), var_list);
	Columns[3].ColName = var_mapping(_T("SQLSpecialColumns_Columns_4"), var_list);
	Columns[4].ColName = var_mapping(_T("SQLSpecialColumns_Columns_5"), var_list);
	Columns[5].ColName = var_mapping(_T("SQLSpecialColumns_Columns_6"), var_list);
	Columns[6].ColName = var_mapping(_T("SQLSpecialColumns_Columns_7"), var_list);
	Columns[7].ColName = var_mapping(_T("SQLSpecialColumns_Columns_8"), var_list);
	Columns[8].ColName = var_mapping(_T("SQLSpecialColumns_Columns_9"), var_list);
	Columns[9].ColName = var_mapping(_T("SQLSpecialColumns_Columns_10"), var_list);
	Columns[10].ColName = var_mapping(_T("SQLSpecialColumns_Columns_11"), var_list);
	Columns[11].ColName = var_mapping(_T("SQLSpecialColumns_Columns_12"), var_list);
	Columns[12].ColName = var_mapping(_T("SQLSpecialColumns_Columns_13"), var_list);
	Columns[13].ColName = var_mapping(_T("SQLSpecialColumns_Columns_14"), var_list);
	Columns[14].ColName = var_mapping(_T("SQLSpecialColumns_Columns_15"), var_list);
	Columns[15].ColName = var_mapping(_T("SQLSpecialColumns_Columns_16"), var_list);
	Columns[16].ColName = var_mapping(_T("SQLSpecialColumns_Columns_17"), var_list);
	Columns[17].ColName = var_mapping(_T("SQLSpecialColumns_Columns_18"), var_list);
	Columns[18].ColName = var_mapping(_T("SQLSpecialColumns_Columns_19"), var_list);
	Columns[19].ColName = var_mapping(_T("SQLSpecialColumns_Columns_20"), var_list);
	Columns[20].ColName = var_mapping(_T("SQLSpecialColumns_Columns_21"), var_list);
	Columns[21].ColName = var_mapping(_T("SQLSpecialColumns_Columns_22"), var_list);
	Columns[22].ColName = var_mapping(_T("SQLSpecialColumns_Columns_23"), var_list);
	Columns[23].ColName = var_mapping(_T("SQLSpecialColumns_Columns_24"), var_list);
	Columns[24].ColName = var_mapping(_T("SQLSpecialColumns_Columns_25"), var_list);
	Columns[25].ColName = var_mapping(_T("SQLSpecialColumns_Columns_26"), var_list);
	Columns[26].ColName = var_mapping(_T("SQLSpecialColumns_Columns_27"), var_list);
	Columns[27].ColName = var_mapping(_T("SQLSpecialColumns_Columns_28"), var_list);
	Columns[28].ColName = var_mapping(_T("SQLSpecialColumns_Columns_29"), var_list);

	TableStr[0] = var_mapping(_T("SQLSpecialColumns_TableStr_1"), var_list);
	TableStr[1] = var_mapping(_T("SQLSpecialColumns_TableStr_2"), var_list);
	TableStr[2] = var_mapping(_T("SQLSpecialColumns_TableStr_3"), var_list);
	TableStr[3] = var_mapping(_T("SQLSpecialColumns_TableStr_4"), var_list);

//=========================================================================================

	//if(isUCS2) {
	//	LogMsg(NONE,_T("Setup for UCS2 mode testing: ColPrec has to be doubled\n"));

	//	i = 0;
	//	while(_tcsicmp(Columns[i].ColTypeName,_T("endloop")) != 0) {
	//		if (Columns[i].ColDataType == SQL_WCHAR){
	//			Columns[i].ColDataType = SQL_WCHAR;
	//			Columns[i].ColTypeOutput = charNameUCS2;
	//			//Columns[i].ColPrec *= 2;  --> This is in character, no need to double
	//			Columns[i].ColLen *= 2;
	//		}
	//		else if (Columns[i].ColDataType == SQL_WVARCHAR) {
	//			Columns[i].ColDataType = SQL_WVARCHAR;
	//			Columns[i].ColTypeOutput = varcharNameUCS2;
	//			//Columns[i].ColPrec *= 2;  --> This is in character, no need to double
	//			Columns[i].ColLen *= 2;
	//		}
	//		else if (Columns[i].ColDataType == SQL_WLONGVARCHAR)	{
	//			Columns[i].ColDataType = SQL_WLONGVARCHAR;
	//			Columns[i].ColTypeOutput = varcharNameUCS2;
	//			//Columns[i].ColPrec *= 2;  --> This is in character, no need to double
	//			Columns[i].ColLen *= 2;
	//		}
	//		i++;
	//	}
	//	i = 0;
	//}

//=========================================================================================

	if (MX_MP_SPECIFIC == MX_SPECIFIC)
		LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing API => MX Specific SQLSpecialColumns.\n"));
	else
		LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing API => MP Specific SQLSpecialColumns.\n"));
	
	TEST_INIT;
	TESTCASE_BEGIN("Setup for SQLSpecialColumns tests\n");

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
	TESTCASE_END;

	_tcscpy(ColStr,_T(""));
	_tcscpy(KeyStr,_T(""));
	_tcscpy(END_LOOP,_T(""));
	_tcscpy(TName,TableStr[2]);

	if (MX_MP_SPECIFIC == MX_SPECIFIC)
	{
		_tcscpy(TQualifier,pTestInfo->Catalog);
		_tcscpy(TOwner,pTestInfo->Schema);
		_tcscpy(END_LOOP,_T("bit"));
	}
	else
	{
		_tcscpy(TQualifier,_T(""));
		_tcscpy(TOwner,pTestInfo->UserID);
		_tcscpy(END_LOOP,_T("endloop"));
	}

	while (_tcsicmp(Columns[i].ColTypeName,END_LOOP) != 0)
	{
		SQLExecDirect(hstmt,(SQLTCHAR*) (SQLTCHAR *)TableStr[1],SQL_NTS); // cleanup
		if (i > 0)
		{
			_tcscat(ColStr,_T(","));
			_tcscat(KeyStr,_T(","));
		}
		_tcscat(ColStr,Columns[i].ColName);
		_tcscat(ColStr,_T(" "));
		_tcscat(ColStr,Columns[i].ColTypeName);
		_tcscat(ColStr,Columns[i].ColTypeLen);
		_tcscat(ColStr,_T(" not null"));
		_tcscat(KeyStr,Columns[i].ColName);
		_tcscpy(CreateTbl,_T(""));
		_tcscat(CreateTbl,TableStr[0]);
		_tcscat(CreateTbl,_T("("));
		_tcscat(CreateTbl,ColStr);
		_tcscat(CreateTbl,_T(", primary key("));
		_tcscat(CreateTbl,KeyStr);
		_tcscat(CreateTbl,_T("))"));

		_stprintf(Heading,_T("Test Positive Functionality of SQLSpecialColumns for this table:\n"));
		_tcscat(Heading,CreateTbl);
		_tcscat(Heading,_T("\n"));
		TESTCASE_BEGINW(Heading);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)CreateTbl,SQL_NTS);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect")){
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		else{
			if (_tcslen(TQualifier) > 0)
				returncode = SQLSpecialColumns(hstmt,fColType[ct],(SQLTCHAR*)TQualifier,(SWORD)_tcslen(TQualifier),(SQLTCHAR*)TOwner,(SWORD)_tcslen(TOwner),(SQLTCHAR*)TName,(SWORD)_tcslen(TName),Scope[s],Nullable[n]);
			else
				returncode = SQLSpecialColumns(hstmt,fColType[ct],NULL,0,(SQLTCHAR*)TOwner,(SWORD)_tcslen(TOwner),(SQLTCHAR*)TName,(SWORD)_tcslen(TName),Scope[s],Nullable[n]);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSpecialColumns")){
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt);
				}
			else{
				oscope = 0;
				_tcscpy(ocname,_T(""));
				ocdatatype = 0;
				_tcscpy(octype,_T(""));
				ocprec = 0;
				oclen = 0;
				ocsca = 0;
				ocpc = 0;
				SQLBindCol(hstmt,1,SQL_C_SHORT,&oscope,0,&oscopelen);
			    SQLBindCol(hstmt,2,SQL_C_TCHAR,ocname,MAX_COLUMN_NAME,&ocnamelen);
				SQLBindCol(hstmt,3,SQL_C_SHORT,&ocdatatype,0,&ocdatatypelen);
				SQLBindCol(hstmt,4,SQL_C_TCHAR,octype,MAX_COLUMN_NAME,&octypelen);
				SQLBindCol(hstmt,5,SQL_C_LONG,&ocprec,0,&ocpreclen);
				SQLBindCol(hstmt,6,SQL_C_LONG,&oclen,0,&oclenlen);
				SQLBindCol(hstmt,7,SQL_C_SHORT,&ocsca,0,&ocscalen);
				SQLBindCol(hstmt,8,SQL_C_SHORT,&ocpc,0,&ocpclen);

				k = 0;
				while (returncode == SQL_SUCCESS){
					returncode = SQLFetch(hstmt);
					if((returncode!=SQL_NO_DATA_FOUND)
							&&(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch"))){
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt);
						}
					else{
						if (returncode == SQL_SUCCESS){
							if (MX_MP_SPECIFIC == MX_SPECIFIC)
							{
								psc = SQL_PC_NOT_PSEUDO;
							}
							else
							{
								psc = 1;
							}
							LogMsg(NONE,_T("Comparing results for SQLSpecialColumns\n"));
                            t = 0;
                            found = FALSE;
                            while(_tcscmp(Columns[t].ColTypeName,_T("endloop"))!=0) {
                                if(cwcscmp(ocname, Columns[t].ColName,TRUE) == 0) {
							        if ((oscope == Scope[s]) 
								        && (ocdatatype == Columns[t].ColDataType) 
								        && (_tcsicmp(octype,Columns[t].ColTypeOutput) == 0) 
								        && (ocprec == Columns[t].ColPrec) 
								        && (oclen == Columns[t].ColLen) 
								        && (ocsca == Columns[t].ColSca) 
								        && (ocpc == (SWORD)psc)){
								        /*
								        LogMsg(NONE,_T("Scope expect: %d and actual: %d are matched\n"),Scope[s],oscope);
								        LogMsg(NONE,_T("colname expect: %s and actual: %s are matched\n"),Columns[t].ColName,ocname);
								        LogMsg(NONE,_T("ColDataType expect: %d and actual: %d are matched\n"),Columns[t].ColDataType,ocdatatype);
								        LogMsg(NONE,_T("ColTypeOutput expect: %s and actual: %s are matched\n"),Columns[t].ColTypeOutput,octype);
								        LogMsg(NONE,_T("ColPrec expect: %d and actual: %d are matched\n"),Columns[t].ColPrec,ocprec);
								        LogMsg(NONE,_T("ColLen expect: %d and actual: %d are matched\n"),Columns[t].ColLen,oclen);
								        LogMsg(NONE,_T("ColScale expect: %d and actual: %d are matched\n"),Columns[t].ColSca,ocsca);
								        LogMsg(NONE,_T("ColPseudoCol expect: %d and actual: %d are matched\n\n"),(SWORD)psc,ocpc);
								        */
							        } else {
							            TEST_FAILED;	
							            if (oscope != Scope[s]) 
								            LogMsg(ERRMSG,_T("Scope expect: %d and actual: %d are not matched\n"),Scope[t],oscope);
							            if (ocdatatype != Columns[t].ColDataType) 
								            LogMsg(ERRMSG,_T("ColDataType expect: %d and actual: %d are not matched\n"),Columns[t].ColDataType,ocdatatype);
							            if (_tcsicmp(octype,Columns[t].ColTypeOutput) != 0) 
								            LogMsg(ERRMSG,_T("ColTypeName expect: %s and actual: %s are not matched\n"),Columns[t].ColTypeOutput,octype);
							            if (ocprec != Columns[t].ColPrec) 
								            LogMsg(ERRMSG,_T("ColPrec expect: %d and actual: %d are not matched\n"),Columns[t].ColPrec,ocprec);
							            if (oclen != Columns[t].ColLen) 
								            LogMsg(ERRMSG,_T("ColLen expect: %d and actual: %d are not matched\n"),Columns[t].ColLen,oclen);
							            if (ocsca != Columns[t].ColSca) 
								            LogMsg(ERRMSG,_T("ColScale expect: %d and actual: %d are not matched\n"),Columns[t].ColSca,ocsca);
							            if (ocpc != (SWORD)psc)
								            LogMsg(ERRMSG,_T("ColPseudoCol expect: %d and actual: %d are not matched\n\n"),(SWORD)psc,ocpc);
						            }
                                    found = TRUE;
                                    break;
                                } else {
                                    t++;
                                }
                            }
                            if(!found) {
                                TEST_FAILED;
                                LogMsg(ERRMSG,_T("Unexpected returned data: %s\n"), ocname);
                            }
						}
                    }
					if (returncode == SQL_SUCCESS)
						k++;
					} // end while
					if(k == 0)
					{
						TEST_FAILED;
						LogMsg(ERRMSG,_T("No Data Found => Atleast one row should be fetched\n"));
					}
				}
			SQLFreeStmt(hstmt,SQL_UNBIND);
			SQLFreeStmt(hstmt,SQL_CLOSE);
			}
			SQLExecDirect(hstmt,(SQLTCHAR*) (SQLTCHAR *)TableStr[1],SQL_NTS);
		i++;
		TESTCASE_END;
		}  // end while

	//========================================================================================================

	_stprintf(Heading,_T("SQLSpecialColumns: Negative test with NULL handle\n"));
	TESTCASE_BEGINW(Heading);

	hstmt = (SQLHANDLE)NULL;
	_tcscpy(TQualifier,_T(""));
	_tcscpy(TOwner,pTestInfo->UserID);
	_tcscpy(TName,TableStr[3]);
	i = 0;

	returncode = SQLSpecialColumns(hstmt,fColType[i],(SQLTCHAR*)TQualifier,(SWORD)_tcslen(TQualifier),(SQLTCHAR*)TOwner,(SWORD)_tcslen(TOwner),(SQLTCHAR*)TName,(SWORD)_tcslen(TName),Scope[i],Nullable[i]);
	if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLSpecialColumns"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	TESTCASE_END;

	//========================================================================================================

	FullDisconnect(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing API => SQLSpecialColumns.\n"));
	free_list(var_list);
	TEST_RETURN;
}