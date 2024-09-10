PassFail TestMXSQLTables (TestInfo *pTestInfo)
{
	TEST_DECLARE;
 	TCHAR			Heading[MAX_HEADING_SIZE];
 	RETCODE			returncode;
 	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt, hstmt1;
	TCHAR			TableQualifier[NAME_LEN],TableOwner[NAME_LEN],Remark[REM_LEN],*TableStr;
	TCHAR			oTableQualifier[NAME_LEN];
	TCHAR			oTableOwner[NAME_LEN];
	TCHAR			oTableName[NAME_LEN];
	TCHAR			oTableType[NAME_LEN];
	TCHAR			oRemark[REM_LEN];
	SQLLEN			oTableQualifierlen,oTableOwnerlen,oTableNamelen,oTableTypelen,oRemarklen;

	int				cols, iatt;
	SWORD numOfCols = 0;
	SWORD pcbDesc;
	SQLLEN pfDesc;
	TCHAR cn[TabType_LEN];
	SWORD cl;
	SWORD st;
	SQLULEN cp;
	SWORD cs, cnull;
	TCHAR rgbDesc[RGB_MAX_LEN];
	TCHAR *CharOutput[12];
	SQLLEN stringlength;
	struct
	{
		TCHAR		*TableName;
		TCHAR		*TableType;
		TCHAR		*TableTypeIn;
	} Table[] = {
							{_T("--")	,_T("TABLE")	,_T("")},
							{_T("--")	,_T("TABLE")	,_T("TABLE")},
							{_T("--")	,_T("TABLE")	,_T("TABLE,VIEW,SYSTEM TABLE")}, 
							{_T("--")	,_T("TABLE")	,_T("TABLE,SYSTEM TABLE,VIEW")},
							{_T("--")	,_T("TABLE")	,_T("TABLE,VIEW,SYSTEM TABLE,SYNONYM,MV,MVG")},
							{_T("--")	,_T("VIEW"),_T("VIEW")},
							{_T("--")	,_T("VIEW"),_T("TABLE,VIEW,SYSTEM TABLE")},
							{_T("--")	,_T("MATERIALIZED VIEW"),_T("")}, 
							{_T("--")	,_T("MATERIALIZED VIEW"),_T("MV")},
							{_T("--")	,_T("SYNONYM"),_T("")}, 
							{_T("--")	,_T("SYNONYM"),_T("SYNONYM")},
							{_T("endloop"),}
					};

	struct
	{
		TCHAR		*TabQua;
		TCHAR		*TabOwner;
		TCHAR		*TabName;
		TCHAR		*TabType;
		int			changedSchema;
	} TableWC[] = 
						{		
							{_T(SQL_ALL_CATALOGS),_T("")			,_T("--")	,_T("")						,-1},		//0
							{_T("")				,_T(SQL_ALL_SCHEMAS),_T("--")	,_T("")						,-1},		//1
							{_T("")				,_T("")				,_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//2
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//3
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//4
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//5
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T("TABLE")				,-1},		//6
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//7
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//8
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T("TABLE")				,-1},		//9
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T("TABLE")				,1},		//10
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T("TABLE")				,1},		//11
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//12
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//13
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//14
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//15
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//16
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//17
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//18
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//19
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T("TABLE")				,-1},		//20
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T("TABLE")				,-1},		//21
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T("TABLE")				,1},		//22
							{pTestInfo->Catalog	,_T(SQL_ALL_SCHEMAS),_T("--")	,_T("TABLE")				,-1},		//23
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T("TABLE")				,1},		//24
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//25
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T("TABLE")				,1},		//26
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("VIEW")					,-1},		//27
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//28
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,-1},		//29
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//30
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("VIEW")					,-1},		//31
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//32
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//33
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//34
							{_T("NULL")			,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//35
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//36
							{pTestInfo->Catalog	,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//37
							{_T("NULL")			,_T("--")			,_T("--")	,_T("TABLE")				,0},		//38
							{_T("NULL")			,pTestInfo->Schema	,_T("--")	,_T("TABLE")				,-1},		//39
							{_T("NULL")			,_T("NULL")			,_T("--")	,_T("TABLE")				,-1},		//40
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,0},		//41
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,0},		//42
							{pTestInfo->Catalog	,_T("--")			,_T("--")	,_T(SQL_ALL_TABLE_TYPES)	,2},		//43
							{_T("endloop"),}
						};	

	struct
	{
		TCHAR		*TabQua;
		SWORD		TabQuaLen;
		TCHAR		*TabOwner;
		SWORD		TabOwnerLen;
		TCHAR		*TabName;
		SWORD		TabNameLen;
		TCHAR		*TabType;
		SWORD		TabTypeLen;
	} TableWC2[] = {		// wild cards from here
							{pTestInfo->Catalog, (SWORD)-1, pTestInfo->Schema,(SWORD)-1, _T("--"),(SWORD)-1, _T(""), (SWORD)-1},
							//{pTestInfo->Catalog, (SWORD)4, pTestInfo->Schema,(SWORD)2, "OBJECTS",(SWORD)2, _T(""), (SWORD)2},
							//{pTestInfo->Catalog, (SWORD)3, pTestInfo->Schema,(SWORD)7, "OBJECTS",(SWORD)3, _T(""), (SWORD)0},
							{_T("endloop"),}
						};
	//attributes for columns added for negative testing
	UWORD DescrType[] = 
				{
					SQL_COLUMN_AUTO_INCREMENT,SQL_COLUMN_CASE_SENSITIVE,SQL_COLUMN_COUNT,
					SQL_COLUMN_DISPLAY_SIZE,SQL_COLUMN_LENGTH,SQL_COLUMN_MONEY,
					SQL_COLUMN_NULLABLE,SQL_COLUMN_PRECISION,SQL_COLUMN_SCALE,
					SQL_COLUMN_SEARCHABLE,SQL_COLUMN_TYPE,SQL_COLUMN_UNSIGNED,
					SQL_COLUMN_UPDATABLE,SQL_COLUMN_NAME,SQL_COLUMN_TYPE_NAME,
					SQL_COLUMN_OWNER_NAME,SQL_COLUMN_QUALIFIER_NAME,SQL_COLUMN_TABLE_NAME,
					SQL_COLUMN_LABEL
				};

    struct {
        TCHAR cat[STR_LEN];
        TCHAR sch[STR_LEN];
        TCHAR tab[STR_LEN];
        TCHAR typ[STR_LEN];
    } displayBuf;
	
	int	i = 0, k = 0, NullValue = 0;
	TCHAR tmpSchema[129];
	TCHAR schemaList[3][256];
	int myInd=1;
	int len = _tcslen(pTestInfo->Schema);

	TCHAR *CrtCol[] = { _T("--"), _T("--") };
	TCHAR *DrpTab[] = { _T("--"), _T("--"), _T("--")};
	TCHAR *CrtTab[] = { _T("--"), _T("--"), _T("--")};

//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars(_T("SQLTables"), charset_file);
	if (var_list == NULL) return FAILED;

	Table[0].TableName = var_mapping(_T("SQLTables_Table_TableName_0"), var_list);
	Table[1].TableName = var_mapping(_T("SQLTables_Table_TableName_1"), var_list);
	Table[2].TableName = var_mapping(_T("SQLTables_Table_TableName_2"), var_list);
	Table[3].TableName = var_mapping(_T("SQLTables_Table_TableName_3"), var_list);
	Table[4].TableName = var_mapping(_T("SQLTables_Table_TableName_4"), var_list);
	Table[5].TableName = var_mapping(_T("SQLTables_Table_TableName_5"), var_list);
	Table[6].TableName = var_mapping(_T("SQLTables_Table_TableName_6"), var_list);
	Table[7].TableName = var_mapping(_T("SQLTables_Table_TableName_7"), var_list);
	Table[8].TableName = var_mapping(_T("SQLTables_Table_TableName_8"), var_list);
	Table[9].TableName = var_mapping(_T("SQLTables_Table_TableName_9"), var_list);
	Table[10].TableName = var_mapping(_T("SQLTables_Table_TableName_10"), var_list);
	
	TableWC[10].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_10"), var_list);
	TableWC[11].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_11"), var_list);
	TableWC[22].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_22"), var_list);
	TableWC[24].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_24"), var_list);
	TableWC[26].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_26"), var_list);
	TableWC[38].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_38"), var_list);
	TableWC[41].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_10"), var_list);
	TableWC[42].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_41"), var_list);
	TableWC[43].TabOwner = var_mapping(_T("SQLTables_TableWC_TabOwner_43"), var_list);

	TableWC[0].TabName = var_mapping(_T("SQLTables_TableWC_TabName_0"), var_list);
	TableWC[1].TabName = var_mapping(_T("SQLTables_TableWC_TabName_1"), var_list);
	TableWC[2].TabName = var_mapping(_T("SQLTables_TableWC_TabName_2"), var_list);
	TableWC[3].TabName = var_mapping(_T("SQLTables_TableWC_TabName_3"), var_list);
	TableWC[4].TabName = var_mapping(_T("SQLTables_TableWC_TabName_4"), var_list);
	TableWC[5].TabName = var_mapping(_T("SQLTables_TableWC_TabName_5"), var_list);
	TableWC[6].TabName = var_mapping(_T("SQLTables_TableWC_TabName_6"), var_list);
	TableWC[7].TabName = var_mapping(_T("SQLTables_TableWC_TabName_7"), var_list);
	TableWC[8].TabName = var_mapping(_T("SQLTables_TableWC_TabName_8"), var_list);
	TableWC[9].TabName = var_mapping(_T("SQLTables_TableWC_TabName_9"), var_list);
	TableWC[10].TabName = var_mapping(_T("SQLTables_TableWC_TabName_10"), var_list);
	TableWC[11].TabName = var_mapping(_T("SQLTables_TableWC_TabName_11"), var_list);
	TableWC[12].TabName = var_mapping(_T("SQLTables_TableWC_TabName_12"), var_list);
	TableWC[13].TabName = var_mapping(_T("SQLTables_TableWC_TabName_13"), var_list);
	TableWC[14].TabName = var_mapping(_T("SQLTables_TableWC_TabName_14"), var_list);
	TableWC[15].TabName = var_mapping(_T("SQLTables_TableWC_TabName_15"), var_list);
	TableWC[16].TabName = var_mapping(_T("SQLTables_TableWC_TabName_16"), var_list);
	TableWC[17].TabName = var_mapping(_T("SQLTables_TableWC_TabName_17"), var_list);
	TableWC[18].TabName = var_mapping(_T("SQLTables_TableWC_TabName_18"), var_list);
	TableWC[19].TabName = var_mapping(_T("SQLTables_TableWC_TabName_19"), var_list);
	TableWC[20].TabName = var_mapping(_T("SQLTables_TableWC_TabName_20"), var_list);
	TableWC[21].TabName = var_mapping(_T("SQLTables_TableWC_TabName_21"), var_list);
	TableWC[22].TabName = var_mapping(_T("SQLTables_TableWC_TabName_22"), var_list);
	TableWC[23].TabName = var_mapping(_T("SQLTables_TableWC_TabName_23"), var_list);
	TableWC[24].TabName = var_mapping(_T("SQLTables_TableWC_TabName_24"), var_list);
	TableWC[25].TabName = var_mapping(_T("SQLTables_TableWC_TabName_25"), var_list);
	TableWC[26].TabName = var_mapping(_T("SQLTables_TableWC_TabName_26"), var_list);
	TableWC[27].TabName = var_mapping(_T("SQLTables_TableWC_TabName_27"), var_list);
	TableWC[28].TabName = var_mapping(_T("SQLTables_TableWC_TabName_28"), var_list);
	TableWC[29].TabName = var_mapping(_T("SQLTables_TableWC_TabName_29"), var_list);
	TableWC[30].TabName = var_mapping(_T("SQLTables_TableWC_TabName_30"), var_list);
	TableWC[31].TabName = var_mapping(_T("SQLTables_TableWC_TabName_31"), var_list);
	TableWC[32].TabName = var_mapping(_T("SQLTables_TableWC_TabName_32"), var_list);
	TableWC[33].TabName = var_mapping(_T("SQLTables_TableWC_TabName_33"), var_list);
	TableWC[34].TabName = var_mapping(_T("SQLTables_TableWC_TabName_34"), var_list);
	TableWC[35].TabName = var_mapping(_T("SQLTables_TableWC_TabName_35"), var_list);
	TableWC[36].TabName = var_mapping(_T("SQLTables_TableWC_TabName_36"), var_list);
	TableWC[37].TabName = var_mapping(_T("SQLTables_TableWC_TabName_37"), var_list);
	TableWC[38].TabName = var_mapping(_T("SQLTables_TableWC_TabName_38"), var_list);
	TableWC[39].TabName = var_mapping(_T("SQLTables_TableWC_TabName_39"), var_list);
	TableWC[40].TabName = var_mapping(_T("SQLTables_TableWC_TabName_40"), var_list);
	TableWC[41].TabName = var_mapping(_T("SQLTables_TableWC_TabName_41"), var_list);
	TableWC[42].TabName = var_mapping(_T("SQLTables_TableWC_TabName_42"), var_list);
	TableWC[43].TabName = var_mapping(_T("SQLTables_TableWC_TabName_43"), var_list);

	TableWC2[0].TabName = var_mapping(_T("SQLTables_TableWC2_TabName_0"), var_list);

	CrtCol[0] = var_mapping(_T("SQLTables_CrtCol_0"), var_list);
	CrtCol[1] = var_mapping(_T("SQLTables_CrtCol_1"), var_list);

	DrpTab[0] = var_mapping(_T("SQLTables_DrpTab_0"), var_list);
	DrpTab[1] = var_mapping(_T("SQLTables_DrpTab_1"), var_list);
	DrpTab[2] = var_mapping(_T("SQLTables_DrpTab_2"), var_list);

	CrtTab[0] = var_mapping(_T("SQLTables_CrtTab_0"), var_list);
	CrtTab[1] = var_mapping(_T("SQLTables_CrtTab_1"), var_list);
	CrtTab[2] = var_mapping(_T("SQLTables_CrtTab_2"), var_list);
//===========================================================================================================

	memset(schemaList[0],'\0', 256*sizeof(TCHAR));
	memset(schemaList[1],'\0', 256*sizeof(TCHAR));
	memset(schemaList[2],'\0', 256*sizeof(TCHAR));

	myInd = len - 2;
	if (len>5) myInd=4;

/*
#ifndef UNICODE
	if (_tcscmp("English", _tsetlocale(LC_ALL, _T(""))) != 0) {
		_mbsncpy(schemaList[0],pTestInfo->Schema,myInd);
		_mbscat(schemaList[0], "%");

		_mbsncpy(schemaList[1],pTestInfo->Schema,myInd+1);
		_mbscat(schemaList[1], "%");
	}
	else {
#endif
*/
		_tcsncpy(schemaList[0],pTestInfo->Schema,myInd);
		_tcscat(schemaList[0], _T("%"));

		_tcsncpy(schemaList[1],pTestInfo->Schema,myInd+1);
		_tcscat(schemaList[1], _T("%"));
/*
#ifndef UNICODE
	}
#endif
*/

	len = 0; myInd = 0;
	do {
		if (pTestInfo->Schema[myInd] == '_')
			schemaList[2][len++] = '\\';
		schemaList[2][len++] = pTestInfo->Schema[myInd];
	} while (pTestInfo->Schema[myInd++] != '\0');

    LogMsg(NONE,_T("%s %s %s\n"), schemaList[0], schemaList[1], schemaList[2]);

	if (isCharSet) {
		_stprintf(tmpSchema, _T("\"SQLTABLES_%s\""), pTestInfo->Schema);
	}
	else {
		_stprintf(tmpSchema, _T("SQLTABLES_%s"), pTestInfo->Schema);
	}
	_tcsupr(tmpSchema);
//======================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,_T("Begin testing API => MX SPECIFIC SQLTables.\n"));

	TEST_INIT;

	TESTCASE_BEGIN("Setup for SQLTables tests\n");
	// for ODBC 3.0
	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
		LogMsg(NONE,_T("Unable to connect as ODBC3.0 application.\n"));
		TEST_FAILED;
		TEST_RETURN;
	}

	henv = pTestInfo->henv;
 	hdbc = pTestInfo->hdbc;
 	hstmt = (SQLHANDLE)pTestInfo->hstmt;
	returncode = SQLAllocStmt((SQLHANDLE)hdbc, &hstmt);	
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLAllocStmt"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	else
	{
		LogMsg(NONE,_T("Allocate a stmt handle successfully.\n"));
	}

   TESTCASE_END;

   _tcscpy(pTestInfo->Catalog, _T("TRAFODION"));
	if (returncode == SQL_SUCCESS)
	{
        _stprintf(Heading,_T("drop schema %s.%s cascade"),pTestInfo->Catalog,tmpSchema);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)Heading, SQL_NTS);
        _stprintf(Heading,_T("create schema %s.%s"),pTestInfo->Catalog,tmpSchema);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)Heading, SQL_NTS);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			TEST_RETURN;
		}

        _stprintf(Heading,_T("set schema %s.%s"),pTestInfo->Catalog,tmpSchema);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)Heading, SQL_NTS);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			TEST_RETURN;
		}

		_tcscpy(TableQualifier,pTestInfo->Catalog);
		_tcscpy(TableOwner, tmpSchema);
		_tcscpy(Remark,_T(""));
		TableStr = (TCHAR *)malloc(MAX_NOS_SIZE);

		i = 0;
		while (_tcsicmp(Table[i].TableName,_T("endloop")) != 0) // cleanup 
		{
			_tcscpy(TableStr,_T(""));
			_tcscat(TableStr,_T("drop "));
			_tcscat(TableStr,Table[i].TableType);
			_tcscat(TableStr,_T(" "));
			_tcscat(TableStr,Table[i].TableName);
			_tcscat(TableStr,_T(" cascade"));
			LogMsg(NONE,_T("Cleanup: %s\n"),TableStr);
			returncode = SQLExecDirect(hstmt,(SQLTCHAR*) TableStr,SQL_NTS);
			i++;
		}
		
		i = 0;
		while (_tcsicmp(Table[i].TableName,_T("endloop")) != 0)
		{
			_tcscpy(TableStr,_T(""));
			_tcscat(TableStr,_T("create "));
			_tcscat(TableStr,Table[i].TableType);
			_tcscat(TableStr,_T(" "));
			_tcscat(TableStr,Table[i].TableName);
			if (_tcsicmp(Table[i].TableType,_T("VIEW")) == 0) {
				_tcscat(TableStr,CrtCol[1]);
				_tcscat(TableStr, Table[0].TableName);
			}
			else if (_tcsicmp(Table[i].TableType,_T("MATERIALIZED VIEW")) == 0) {
				_tcscat(TableStr, _T(" REFRESH ON REQUEST INITIALIZE ON REFRESH "));
				_tcscat(TableStr,CrtCol[1]);
				_tcscat(TableStr, Table[0].TableName); 
			}
			else if (_tcsicmp(Table[i].TableType,_T("SYNONYM")) == 0) {
				_tcscat(TableStr, _T(" FOR "));
				_tcscat(TableStr, Table[0].TableName);
			}
			else
			{
				_tcscat(TableStr,CrtCol[0]);
			}
		
			_stprintf(Heading,_T("SQLTables: Test %d: using the following table create command=> \n"),i);
			_tcscat(Heading,TableStr);
			_tcscat(Heading,_T("\n"));
			TESTCASE_BEGINW(Heading);
			
			returncode = SQLExecDirect(hstmt,(SQLTCHAR*)TableStr,SQL_NTS);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			else
			{
				LogMsg(NONE,_T("Created table successfully.\n"));
			}

			if(isCharSet) {
				returncode = SQLSetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,(SQLPOINTER)SQL_TRUE,0);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtAttr(SQL_ATTR_METADATA_ID"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt);
				}
			}
			
			if (returncode == SQL_SUCCESS)
			{
				if (_tcslen(TableQualifier) > 0)
					returncode = SQLTables(hstmt,(SQLTCHAR*)TableQualifier,(SWORD)_tcslen(TableQualifier),(SQLTCHAR*)TableOwner,(SWORD)_tcslen(TableOwner),(SQLTCHAR*)Table[i].TableName,(SWORD)_tcslen(Table[i].TableName),(SQLTCHAR*)Table[i].TableTypeIn,(SWORD)_tcslen(Table[i].TableTypeIn));
				else
					returncode = SQLTables(hstmt,NULL,(SWORD)_tcslen(TableQualifier),(SQLTCHAR*)TableOwner,(SWORD)_tcslen(TableOwner),(SQLTCHAR*)Table[i].TableName,(SWORD)_tcslen(Table[i].TableName),(SQLTCHAR*)Table[i].TableTypeIn,(SWORD)_tcslen(Table[i].TableTypeIn));
				
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLTables"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt);
				}
				else
				{
					LogMsg(NONE,_T("Call to SQLTables() executed successfully.\n"));
					
					_tcscpy(oTableQualifier,_T(""));
					_tcscpy(oTableOwner,_T(""));
					_tcscpy(oTableName,_T(""));
					_tcscpy(oTableType,_T(""));
					_tcscpy(oRemark,_T(""));
					returncode=SQLBindCol(hstmt,1,SQL_C_TCHAR,oTableQualifier,NAME_LEN,&oTableQualifierlen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")){
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
						}
				   returncode=SQLBindCol(hstmt,2,SQL_C_TCHAR,oTableOwner,NAME_LEN,&oTableOwnerlen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")){
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
						}
					returncode=SQLBindCol(hstmt,3,SQL_C_TCHAR,oTableName,NAME_LEN,&oTableNamelen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")){
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
						}
				   returncode=SQLBindCol(hstmt,4,SQL_C_TCHAR,oTableType,NAME_LEN,&oTableTypelen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")){
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
						}
					returncode=SQLBindCol(hstmt,5,SQL_C_TCHAR,oRemark,NAME_LEN,&oRemarklen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol")){
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
						}

					k = 0;
					while (returncode == SQL_SUCCESS)
					{
						returncode = SQLFetch(hstmt);
						if((returncode != SQL_NO_DATA_FOUND)&&(!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch")))
						{
							LogAllErrors(henv,hdbc,hstmt);
							TEST_FAILED;
						}
						else if (returncode == SQL_SUCCESS)
						{
							if (_tcslen(TableQualifier) == 0)
							{
								//_tcscpy(TableQualifier, _T("TRAFODION"));
								_tcscpy(TableQualifier, _T("TRAFODION"));
							}
							if ((_tcsicmp(TableQualifier,oTableQualifier) == 0) 
								&& (cwcscmp(TableOwner,oTableOwner,TRUE) == 0) 
								&& (cwcscmp(Table[i].TableName,oTableName,TRUE) == 0) 
								&& (_tcsnicmp(Table[i].TableType,oTableType,_tcslen(Table[i].TableType)) == 0) 
								&& (_tcsicmp(Remark,oRemark) == 0))
							{
								LogMsg(NONE,_T("TableQualifier expect: '%s' and actual: '%s' are matched\n"),(SQLTCHAR*)TableQualifier,oTableQualifier);
								LogMsg(NONE,_T("TableOwner expect: '%s' and actual: '%s' are matched\n"),(SQLTCHAR*)TableOwner,oTableOwner);
								LogMsg(NONE,_T("TableName expect: '%s' and actual: '%s' are matched\n"),(SQLTCHAR*)Table[i].TableName,oTableName);
								LogMsg(NONE,_T("TableType expect: '%s' and actual: '%s' are matched\n"),Table[i].TableType,oTableType);
								LogMsg(NONE,_T("Remark expect: '%s' and actual: '%s' are matched\n"),Remark,oRemark);
							}	
							else
							{
								TEST_FAILED;	
								if (_tcsicmp(TableQualifier,oTableQualifier) != 0)
									LogMsg(ERRMSG,_T("TableQualifier expect: '%s' and actual: '%s' are not matched\n"),(SQLTCHAR*)TableQualifier,oTableQualifier);
								if (cwcscmp(TableOwner,oTableOwner,TRUE) != 0) 
									LogMsg(ERRMSG,_T("TableOwner expect: '%s' and actual: '%s' are not matched\n"),(SQLTCHAR*)TableOwner,oTableOwner);
								if (cwcscmp(Table[i].TableName,oTableName,TRUE) != 0) 
									LogMsg(ERRMSG,_T("TableName expect: '%s' and actual: '%s' are not matched\n"),(SQLTCHAR*)Table[i].TableName,oTableName);
								if (_tcsnicmp(Table[i].TableType,oTableType,10) != 0) 
									LogMsg(ERRMSG,_T("TableType expect: '%s' and actual: '%s' are not matched\n"),Table[i].TableType,oTableType);
								if (_tcsicmp(Remark,oRemark) != 0) 
									LogMsg(ERRMSG,_T("Remark expect: '%s' and actual: '%s' are not matched\n"),Remark,oRemark);
							}

							k++;
						}
					}//End while loop

					if(k != 1)
					{
						TEST_FAILED;
						LogMsg(ERRMSG,_T("Only one row should be fetched, the actual number of rows fetched: %d\n"), k);
					} else {
						LogMsg(NONE, _T("Number of rows fetched: %d\n"), k);
					}
				}
				SQLFreeStmt(hstmt,SQL_UNBIND);
				SQLFreeStmt(hstmt,SQL_CLOSE);
			}
			TESTCASE_END;
			i++;
		}
//		i = 0;
//		while (_tcsicmp(Table[i].TableName,"endloop") != 0) // cleanup
//		{
//			_tcscpy(TableStr,_T(""));
//			_tcscat(TableStr,"drop ");
//			_tcscat(TableStr,Table[i].TableType);
//			_tcscat(TableStr," ");
//			_tcscat(TableStr,Table[i].TableName);
//			SQLExecDirect(hstmt,(SQLTCHAR*) TableStr,SQL_NTS);
//			i++;
//		}

        _stprintf(Heading,_T("drop schema %s.%s cascade"),pTestInfo->Catalog,tmpSchema);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)Heading, SQL_NTS);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			TEST_RETURN;
		}

		if (isCharSet) {
			_stprintf(Heading,_T("set schema %s.\"%s\""),pTestInfo->Catalog,pTestInfo->Schema);
		}
		else {
			_stprintf(Heading,_T("set schema %s.%s"),pTestInfo->Catalog,pTestInfo->Schema);
		}
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)Heading, SQL_NTS);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
			TEST_RETURN;
		}

//======================================================================================================
		_stprintf(Heading,_T("Setting up Table & view to test SQLTables for wildcard options => \n"));
		_tcscat(Heading,_T("\n"));
		TESTCASE_BEGINW(Heading);
		SQLExecDirect(hstmt,(SQLTCHAR*)DrpTab[0],SQL_NTS);
		SQLExecDirect(hstmt,(SQLTCHAR*)DrpTab[1],SQL_NTS);
		SQLExecDirect(hstmt,(SQLTCHAR*)DrpTab[2],SQL_NTS);
		LogMsg(NONE,_T("%s\n"), CrtTab[0]);
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)CrtTab[0],SQL_NTS);

		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
		}
		else
		{
			returncode = SQLExecDirect(hstmt,(SQLTCHAR*)CrtTab[1],SQL_NTS);
			LogMsg(NONE,_T("%s\n"), CrtTab[1]);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			else
			{
				LogMsg(NONE,_T("setting up tables & views executed successfully.\n"));
				TESTCASE_END;
			}
		}
		returncode = SQLExecDirect(hstmt,(SQLTCHAR*)CrtTab[2],SQL_NTS);
		LogMsg(NONE,_T("%s\n"), CrtTab[2]);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
		}
		i = 0;
		while (_tcsicmp(TableWC[i].TabQua,_T("endloop")) != 0)
		{
			if(TableWC[i].changedSchema == -1) {
				printSymbol(TableWC[i].TabQua,displayBuf.cat);
                printSymbol(TableWC[i].TabOwner,displayBuf.sch);
				printSymbol(TableWC[i].TabName,displayBuf.tab);
                printSymbol(TableWC[i].TabType,displayBuf.typ);

				_stprintf(Heading,_T("Test Positive Functionality of SQLTables for following wildcard options => \n TableQualifier: %s\n TableOwner: %s\n TableName: %s\n TableType: %s\n"),
				displayBuf.cat, displayBuf.sch,	displayBuf.tab, displayBuf.typ);
			}
			else {
				printSymbol(TableWC[i].TabQua,displayBuf.cat);
                printSymbol(schemaList[TableWC[i].changedSchema],displayBuf.sch);
				printSymbol(TableWC[i].TabName,displayBuf.tab);
                printSymbol(TableWC[i].TabType,displayBuf.typ);

				_stprintf(Heading,_T("Test Positive Functionality of SQLTables for following wildcard options => \n TableQualifier: %s\n TableOwner: %s\n TableName: %s\n TableType: %s\n"),
				displayBuf.cat, displayBuf.sch, displayBuf.tab, displayBuf.typ);
			}

			TESTCASE_BEGINW(Heading);
			NullValue = 0;

			returncode = SQLSetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,(SQLPOINTER)SQL_FALSE,0);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtAttr(SQL_ATTR_METADATA_ID"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt);
			}

			if (_tcsicmp(TableWC[i].TabType,_T("NULL")) == 0)
			{
				TableWC[i].TabType = NULL;
				NullValue = 1;
				returncode = SQLTables(hstmt,NULL,0,NULL,0,NULL,0,NULL,0);
			}
			else if (_tcsicmp(TableWC[i].TabName,_T("NULL")) == 0)
			{
				TableWC[i].TabName = NULL;
				NullValue = 1;
				returncode = SQLTables(hstmt,NULL,0,NULL,0,NULL,0,(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
			}
			else if (_tcsicmp(TableWC[i].TabOwner,_T("NULL")) == 0)
			{
				TableWC[i].TabOwner = NULL;
				NullValue = 1;
				returncode = SQLTables(hstmt,NULL,0,NULL,0,(SQLTCHAR*)removeQuotes(TableWC[i].TabName,displayBuf.tab),(SWORD)_tcslen(displayBuf.tab),(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
			}
			else if (_tcsicmp(TableWC[i].TabQua,_T("NULL")) == 0)
			{
				TableWC[i].TabQua = NULL;
				NullValue = 1;
				if (TableWC[i].changedSchema == -1)
					returncode = SQLTables(hstmt,NULL,0,(SQLTCHAR*)TableWC[i].TabOwner,(SWORD)_tcslen(TableWC[i].TabOwner),(SQLTCHAR*)removeQuotes(TableWC[i].TabName,displayBuf.tab),(SWORD)_tcslen(displayBuf.tab),(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
				else
					returncode = SQLTables(hstmt,NULL,0,(SQLTCHAR*)schemaList[TableWC[i].changedSchema],(SWORD)_tcslen(schemaList[TableWC[i].changedSchema]),(SQLTCHAR*)removeQuotes(TableWC[i].TabName,displayBuf.tab),(SWORD)_tcslen(displayBuf.tab),(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
			}
			else
			{
				if (TableWC[i].changedSchema == -1)
					returncode = SQLTables(hstmt,(SQLTCHAR*)TableWC[i].TabQua,(SWORD)_tcslen(TableWC[i].TabQua),(SQLTCHAR*)TableWC[i].TabOwner,(SWORD)_tcslen(TableWC[i].TabOwner),(SQLTCHAR*)removeQuotes(TableWC[i].TabName,displayBuf.tab),(SWORD)_tcslen(displayBuf.tab),(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
				else
					returncode = SQLTables(hstmt,(SQLTCHAR*)TableWC[i].TabQua,(SWORD)_tcslen(TableWC[i].TabQua),(SQLTCHAR*)schemaList[TableWC[i].changedSchema],(SWORD)_tcslen(schemaList[TableWC[i].changedSchema]),(SQLTCHAR*)removeQuotes(TableWC[i].TabName,displayBuf.tab),(SWORD)_tcslen(displayBuf.tab),(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
			}

			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLTables"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt);
			}
			else
			{
				LogMsg(NONE,_T("Call to SQLTables() executed successfully.\n"));
				_tcscpy(oTableQualifier,_T(""));
				_tcscpy(oTableOwner,_T(""));
				_tcscpy(oTableName,_T(""));
				_tcscpy(oTableType,_T(""));
				_tcscpy(oRemark,_T(""));
				returncode=SQLBindCol(hstmt,1,SQL_C_TCHAR,oTableQualifier,NAME_LEN,&oTableQualifierlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				returncode=SQLBindCol(hstmt,2,SQL_C_TCHAR,oTableOwner,NAME_LEN,&oTableOwnerlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				returncode=SQLBindCol(hstmt,3,SQL_C_TCHAR,oTableName,NAME_LEN,&oTableNamelen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				returncode=SQLBindCol(hstmt,4,SQL_C_TCHAR,oTableType,NAME_LEN,&oTableTypelen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				returncode=SQLBindCol(hstmt,5,SQL_C_TCHAR,oRemark,NAME_LEN,&oRemarklen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				k = 0;
				while (returncode == SQL_SUCCESS)
				{
					returncode = SQLFetch(hstmt);
					if((returncode!=SQL_NO_DATA_FOUND) && (!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch")))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					if (returncode == SQL_SUCCESS)
						k++;
				}
				if(k == 0)
				{
					TEST_FAILED;
					LogMsg(ERRMSG,_T("No Data Found => Atleast one row should be fetched\n"));
                } else {
                    LogMsg(NONE, _T("Number of rows fetched: %d\n"), k);
                }
			}
			SQLFreeStmt(hstmt,SQL_CLOSE);
			i++;
			TESTCASE_END;
		}
		free(TableStr);
	}

//=========================================================================================

	TESTCASE_BEGIN("SQLTables: Negative test with NULL handle.\n");

	hstmt1 = (SQLHANDLE)NULL;
	i = 0;
	returncode = SQLTables(hstmt1,(SQLTCHAR*)TableWC[i].TabQua,(SWORD)_tcslen(TableWC[i].TabQua),(SQLTCHAR*)TableWC[i].TabOwner,(SWORD)_tcslen(TableWC[i].TabOwner),(SQLTCHAR*)TableWC[i].TabName,(SWORD)_tcslen(TableWC[i].TabName),(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
	if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLTables"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	TESTCASE_END;

//=========================================================================================

	TESTCASE_BEGIN("SQLTables: Negative test with invalid arg lengths.\n");
	i = 0;
	while (_tcsicmp(TableWC2[i].TabQua,_T("endloop")) != 0)
	{
		returncode = SQLTables(hstmt,(SQLTCHAR*)TableWC2[i].TabQua,TableWC2[i].TabQuaLen,(SQLTCHAR*)TableWC2[i].TabOwner,TableWC2[i].TabOwnerLen,(SQLTCHAR*)TableWC2[i].TabName,TableWC2[i].TabNameLen,(SQLTCHAR*)TableWC2[i].TabType,TableWC2[i].TabTypeLen);
		if(!CHECKRC(SQL_ERROR,returncode,"SQLTables"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		i++;
	}
	TESTCASE_END;

//=========================================================================================

	TESTCASE_BEGIN("Testing SQLColAttribute, SQLDescribeCol, SQLBindCol and SQLFetch functions for catalog names.\n");

    if(isCharSet) {
		returncode = SQLSetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,(SQLPOINTER)SQL_FALSE,0);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtAttr(SQL_ATTR_METADATA_ID"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
	}

	for(i = 0; i < 5; i++)
	{
		returncode = SQLTables(hstmt,(SQLTCHAR*)TableWC[i].TabQua,(SWORD)_tcslen(TableWC[i].TabQua),(SQLTCHAR*)TableWC[i].TabOwner,(SWORD)_tcslen(TableWC[i].TabOwner),(SQLTCHAR*)TableWC[i].TabName,(SWORD)_tcslen(TableWC[i].TabName),(SQLTCHAR*)TableWC[i].TabType,(SWORD)_tcslen(TableWC[i].TabType));
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLColumns"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		returncode = SQLNumResultCols(hstmt, &numOfCols);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNumResultsCol"))
		{
			TEST_FAILED;
			LogMsg(ERRMSG,_T("Test failed while executing call for SQLNUMRESULTSCOL"));
			LogAllErrors(henv,hdbc,hstmt);
		}
		for(cols = 0; cols < numOfCols; cols++)
		{
			returncode = SQLDescribeCol(hstmt,(SWORD)(cols+1),(SQLTCHAR*)cn,TabType_LEN,&cl,&st,&cp,&cs,&cnull);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLDescribeCol"))
			{
				TEST_FAILED;
				LogMsg(ERRMSG,_T("Test failed while executing call for SQLDESCRIBECOL of column"));
				LogAllErrors(henv,hdbc,hstmt);
			}
			CharOutput[cols] = (TCHAR *)malloc(STR_LEN);
			for (iatt = 0; iatt <= TOTALATTRIBS; iatt++)
			{
				_tcscpy(rgbDesc,_T(""));
				pcbDesc = 0;
				pfDesc = 0;
				returncode = SQLColAttributes(hstmt,(SWORD)(cols+1),DescrType[iatt],(SQLTCHAR*)rgbDesc,STR_LEN,&pcbDesc,&pfDesc);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLColAttribute"))
				{
					TEST_FAILED;
					LogAllErrors(henv,hdbc,hstmt);
				}
			}
			returncode = SQLBindCol(hstmt,(SWORD)(cols+1),SQL_C_TCHAR,(SQLTCHAR*)CharOutput[cols],STR_LEN,&stringlength);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
			{
				TEST_FAILED;
				LogMsg(ERRMSG,_T("Test failed while executing call for SQLBindCols of column : %d.\n"),cols);
				LogAllErrors(henv,hdbc,hstmt);
			}
		}

		k = 0;
		while (returncode == SQL_SUCCESS)
		{
			returncode = SQLFetch(hstmt);
			if((returncode!=SQL_NO_DATA_FOUND) && (!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch")))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			if (returncode == SQL_SUCCESS)
				k++;
		}
		if(k == 0)
		{
            _stprintf(Heading,_T("\n TableQualifier: %s\n TableOwner: %s\n TableName: %s\n TableType: %s\n"),
				printSymbol(TableWC[i].TabQua,displayBuf.cat),
                printSymbol(TableWC[i].TabOwner,displayBuf.sch),
				printSymbol(TableWC[i].TabName,displayBuf.tab),
                printSymbol(TableWC[i].TabType,displayBuf.typ));
            LogMsg(NONE,Heading);
			TEST_FAILED;
			LogMsg(ERRMSG,_T("No Data Found => Atleast one row should be fetched\n"));
		} else {
            LogMsg(NONE, _T("Number of rows fetched: %d\n"), k);
        }

		for(cols = 0; cols < numOfCols; cols++)
		{
			free(CharOutput[cols]);
		}
		TESTCASE_END;
	}

	// Clean up
	SQLExecDirect(hstmt,(SQLTCHAR*)DrpTab[0],SQL_NTS);
	SQLExecDirect(hstmt,(SQLTCHAR*)DrpTab[1],SQL_NTS);
	SQLExecDirect(hstmt,(SQLTCHAR*)DrpTab[2],SQL_NTS);

//=========================================================================================

	FullDisconnect(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,_T("End testing API => SQLTables.\n"));
	free_list(var_list);
	TEST_RETURN;
}