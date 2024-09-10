PassFail TestSQLDescribeParam(TestInfo *pTestInfo, int MX_MP_SPECIFIC)
{                  
	TEST_DECLARE;
 	char			Heading[MAX_STRING_SIZE];
	RETCODE			returncode;
	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt;
	SWORD			numparam;
	UWORD			icol;

	SWORD		st, SQLType[] = 
							{
								SQL_CHAR,SQL_VARCHAR,SQL_DECIMAL,SQL_NUMERIC,SQL_SMALLINT,SQL_INTEGER,SQL_REAL,
								SQL_DOUBLE,SQL_DOUBLE,SQL_DATE,SQL_TIME,SQL_TIMESTAMP,SQL_BIGINT,SQL_LONGVARCHAR,
								SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC
																												
							};										// SQL_DOUBLE for SQL_FLOAT MX limitation
																	//SQL_BIGINT replaced by SQL_NUMERIC in MX
	SWORD		MPSQLType[] = 
							{
								SQL_CHAR,SQL_VARCHAR,SQL_DECIMAL,SQL_NUMERIC,SQL_SMALLINT,SQL_INTEGER,SQL_REAL,
								SQL_FLOAT,SQL_FLOAT,SQL_DATE,SQL_TIME,SQL_TIMESTAMP,SQL_BIGINT,SQL_LONGVARCHAR,
								SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC,SQL_NUMERIC
							};						
    SQLULEN cp; 
	SQLULEN		ColPrec[] = {10,10,10,10,5,10,7,15,15,10,8,26,19,2000,19,19,128,128,128,10,18,30};
    SQLULEN		MPColPrec[] = {10,10,10,10,5,10,7,15,15,10,8,26,19,10,19,19,128,128,128,10,18,30};	
	SWORD		cs, cnull, ColScale[] = {0,0,5,5,0,0,0,0,0,0,0,6,0,0,0,6,0,128,64,5,5,10};

	CHAR		*DropStr[] = {"--","--","endloop"};
	CHAR		*CrtStr[] = {"--", "--", "endloop"};
	CHAR		*MPCrtStr[] = {"--", "--", "endloop"};
	CHAR		*ExecDirStr[] = {"--","--","--","--","--","--","--","--","--","--","endloop"};

	char		TempType1[50],TempType2[50];
	SWORD		ColNullable[] = {SQL_NULLABLE,SQL_NO_NULLS,SQL_NULLABLE,SQL_NO_NULLS,SQL_NULLABLE,SQL_NO_NULLS,SQL_NULLABLE,SQL_NO_NULLS,SQL_NULLABLE,SQL_NO_NULLS};

	CHAR		*TestCase[] = 
						{
							"before preparing stmt ",
							"endloop"
						};

	SQLUSMALLINT i = 0, l = 0;

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars("SQLDescribeParam", charset_file);
	if (var_list == NULL) return FAILED;

//=====================Modified for Longvarchar Changes========================================================
	if(!pTestInfo->bLongOn)
	{
		int i = 0;
		char *noLong = "SQL_VARCHAR"; 
		SWORD iNoLong = SQL_VARCHAR;

		SQLType[13] = iNoLong;
		MPSQLType[13] = iNoLong;
	}
//=====================Modified for Longvarchar Changes========================================================


	//print_list(var_list);
	DropStr[0] = var_mapping("SQLDescribeParam_DropStr_1", var_list);
	DropStr[1] = var_mapping("SQLDescribeParam_DropStr_2", var_list);

	CrtStr[0] = var_mapping("SQLDescribeParam_CrtStr_1", var_list);
	CrtStr[1] = var_mapping("SQLDescribeParam_CrtStr_2", var_list);

	MPCrtStr[0] = var_mapping("SQLDescribeParam_MPCrtStr_1", var_list);
	MPCrtStr[1] = var_mapping("SQLDescribeParam_MPCrtStr_2", var_list);

	ExecDirStr[0] = var_mapping("SQLDescribeParam_ExecDirStr_1", var_list);
	ExecDirStr[1] = var_mapping("SQLDescribeParam_ExecDirStr_2", var_list);
	ExecDirStr[2] = var_mapping("SQLDescribeParam_ExecDirStr_3", var_list);
	ExecDirStr[3] = var_mapping("SQLDescribeParam_ExecDirStr_4", var_list);
	ExecDirStr[4] = var_mapping("SQLDescribeParam_ExecDirStr_5", var_list);
	ExecDirStr[5] = var_mapping("SQLDescribeParam_ExecDirStr_6", var_list);
	ExecDirStr[6] = var_mapping("SQLDescribeParam_ExecDirStr_7", var_list);
	ExecDirStr[7] = var_mapping("SQLDescribeParam_ExecDirStr_8", var_list);
	ExecDirStr[8] = var_mapping("SQLDescribeParam_ExecDirStr_9", var_list);
	ExecDirStr[9] = var_mapping("SQLDescribeParam_ExecDirStr_10", var_list);

//=================================================================================================

	if(isUCS2) {
		LogMsg(NONE,"Setup for UCS2 mode testing: ColPrec has to be doubled\n");

		l = sizeof(SQLType)/sizeof(SQLType[0]);
		while(i < l) {
			if(SQLType[i] == SQL_CHAR) {
				//SQLType[i] = SQL_WCHAR;
				ColPrec[i] *= 2;  //--> This is in character, so no need to double
			}
			else if (SQLType[i] == SQL_VARCHAR) {
				//SQLType[i] = SQL_WVARCHAR;
				ColPrec[i] *= 2;  //--> This is in character, so no need to double
			}
			else if (SQLType[i] == SQL_LONGVARCHAR)	{
				//SQLType[i] = SQL_WLONGVARCHAR;
				ColPrec[i] *= 2;  //--> This is in character, so no need to double
			}
			else {
			}

			i++;
		}
		i = 0;

		l = sizeof(MPSQLType)/sizeof(MPSQLType[0]);
		while(i < l) {
			if(MPSQLType[i] == SQL_CHAR) {
		        //MPSQLType[i] = SQL_WCHAR;
				MPColPrec[i] *= 2;  //--> This is in character, so no need to double
			}
			else if (MPSQLType[i] == SQL_VARCHAR) {
				//MPSQLType[i] = SQL_WVARCHAR;
				MPColPrec[i] *= 2;  //--> This is in character, so no need to double
			}
			else if (MPSQLType[i] == SQL_LONGVARCHAR)	{
				//MPSQLType[i] = SQL_WLONGVARCHAR;
				MPColPrec[i] *= 2;  //--> This is in character, so no need to double
			}
			else {
			}
			i++;
		}
		i = 0;
		l = 0;
	}

//===========================================================================================================

    if (MX_MP_SPECIFIC == MX_SPECIFIC)
        LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => MX Specific SQLDescribeParam | SQLDescribeParam | desparam.c\n");
    else
        LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => MP Specific SQLDescribeParam | SQLDescribeParam | desparam.c\n");

	TEST_INIT;
	   
	TESTCASE_BEGIN("Setup for SQLDescribeParam tests\n");

	if(!FullConnect(pTestInfo)){
		LogMsg(NONE,"Unable to connect\n");
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

	i = 0;
	while (_stricmp(DropStr[i],"endloop") != 0)
	{
		SQLExecDirect(hstmt,(SQLCHAR*)DropStr[i],SQL_NTS); /* cleanup */
		i++;
	}
	i = 0;
	if (MX_MP_SPECIFIC == MX_SPECIFIC)
	{
		while (_stricmp(CrtStr[i],"endloop") != 0)
		{
			returncode = SQLExecDirect(hstmt,(SQLCHAR*)CrtStr[i],SQL_NTS); /* create table */
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				TEST_RETURN;
			}
			//LogMsg(NONE,"%s\n",	CrtStr[i]);
			i++;
		}
	}
	else
	{
		while (_stricmp(MPCrtStr[i],"endloop") != 0)
		{
			returncode = SQLExecDirect(hstmt,(SQLCHAR*)MPCrtStr[i],SQL_NTS); /* create table */
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
				TEST_RETURN;
			}
			//LogMsg(NONE,"%s\n",	MPCrtStr[i]);
			i++;
		}
	}
	TESTCASE_END;  // end of setup

	l = 0;
	while (_stricmp(TestCase[l],"endloop") != 0)
	{
		i = 0;
		while (_stricmp(ExecDirStr[i],"endloop") != 0)
		{
			//==================================================================================
			sprintf(Heading,"SQLDescribeParam: Test #%d.%d\n",l,i);
			TESTCASE_BEGIN(Heading);
			returncode = SQLPrepare(hstmt,(SQLCHAR*)ExecDirStr[i], SQL_NTS);
			//LogMsg(NONE,"%s\n", ExecDirStr[i]);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLPrepare"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			else
			{
				returncode=SQLNumParams(hstmt, &numparam);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNumResultCols"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				//LogMsg(NONE,"SQLNumParams returns %d\n", numparam);
				for (icol = 1; icol <= numparam; icol++)
				{
					LogMsg(LINEBEFORE,"SQLDescribeParam: checking Column #%d\n",icol);
					returncode = SQLDescribeParam(hstmt,icol,&st,&cp,&cs,&cnull);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLDescribeParam"))
					{
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt);
					}
					if (MX_MP_SPECIFIC == MX_SPECIFIC)
					{
						if ((st==SQLType[icol-1]) && (cp==ColPrec[icol-1]) && (cs==ColScale[icol-1]) && (cnull==ColNullable[i]))
						{
							//LogMsg(NONE,"SQLType expect: %s and actual: %s are matched\n",
							//	SQLTypeToChar(SQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2));
							//LogMsg(NONE,"ColPrec expect: %d and actual: %d are matched\n",ColPrec[icol-1],cp);
							//LogMsg(NONE,"ColScale expect: %d and actual: %d are matched\n",ColScale[icol-1],cs);
							//LogMsg(NONE,"ColNullable expect: %s and actual: %s are matched\n\n",
							//	SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2));
						}	
						else
						{
							TEST_FAILED;	
							if (st != SQLType[icol-1])
								LogMsg(ERRMSG,"SQLType expect: %s and actual: %s are not matched\n",SQLTypeToChar(SQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2));
							if (cp != ColPrec[icol-1])
								LogMsg(ERRMSG,"ColPrec expect: %d and actual: %d are not matched\n",ColPrec[icol-1],cp);
							if (cs != ColScale[icol-1])
								LogMsg(ERRMSG,"ColScale expect: %d and actual: %d are not matched\n",ColScale[icol-1],cs);
							if (cnull != ColNullable[i])
								LogMsg(ERRMSG,"ColNullable expect: %s and actual: %s are not matched\n\n",SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2));
						}
					}
					else
					{
						if ((st==MPSQLType[icol-1]) && (cp==MPColPrec[icol-1]) && (cs==ColScale[icol-1]) && (cnull==ColNullable[i]))
						{
							//LogMsg(NONE,"SQLType expect: %s and actual: %s are matched\n",
							//	SQLTypeToChar(MPSQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2));
							//LogMsg(NONE,"ColPrec expect: %d and actual: %d are matched\n",MPColPrec[icol-1],cp);
							//LogMsg(NONE,"ColScale expect: %d and actual: %d are matched\n",ColScale[icol-1],cs);
							//LogMsg(NONE,"ColNullable expect: %s and actual: %s are matched\n\n",
							//	SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2));
						}	
						else
						{
							TEST_FAILED;	
							if (st != MPSQLType[icol-1])
								LogMsg(ERRMSG,"SQLType expect: %s and actual: %s are not matched\n",SQLTypeToChar(MPSQLType[icol-1],TempType1),SQLTypeToChar(st,TempType2));
							if (cp != MPColPrec[icol-1])
								LogMsg(ERRMSG,"ColPrec expect: %d and actual: %d are not matched\n",MPColPrec[icol-1],cp);
							if (cs != ColScale[icol-1])
								LogMsg(ERRMSG,"ColScale expect: %d and actual: %d are not matched\n",ColScale[icol-1],cs);
							if (cnull != ColNullable[i])
								LogMsg(ERRMSG,"ColNullable expect: %s and actual: %s are not matched\n\n",SQLNullToChar(ColNullable[i],TempType1),SQLNullToChar(cnull,TempType2));
						}
					}
				} /* end icol loop */
			}
			SQLFreeStmt(hstmt,SQL_CLOSE);
			i++;
			TESTCASE_END;
		}
		l++;
	}

	i = 0;
	while (_stricmp(DropStr[i],"endloop") != 0)
	{
		SQLExecDirect(hstmt,(SQLCHAR*)DropStr[i],SQL_NTS); /* cleanup */
		i++;
	}

	FullDisconnect(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => MX Specific SQLDescribeParam.\n");
	free_list(var_list);
	TEST_RETURN;
}