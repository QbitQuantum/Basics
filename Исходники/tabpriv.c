/*
---------------------------------------------------------
   TestSQLTablePrivileges
---------------------------------------------------------
*/
PassFail TestMXSQLTablePrivileges( TestInfo *pTestInfo)
{
	TEST_DECLARE;
 	char			Heading[MAX_HEADING_SIZE];
	/*  */char	ColumnWC4_TabOwner[NAME_LEN];
 	RETCODE			returncode;
 	SQLHANDLE 		henv = (SQLHANDLE)NULL;
 	SQLHANDLE 		hdbc = (SQLHANDLE)NULL;
 	SQLHANDLE		hstmt = (SQLHANDLE)NULL, hstmt1 = (SQLHANDLE)NULL;
	CHAR			TableQualifier[NAME_LEN],TableOwner[NAME_LEN],*TableStr;

	CHAR			*TableName;
	
	// CHAR			*Grantor; //Assume that we log on as role.user
	CHAR            Grantor[SQL_MAX_ROLENAME_LEN+2];

	CHAR			oTableQualifier[NAME_LEN];  
	CHAR			oTableOwner[NAME_LEN];
	CHAR			oTableName[NAME_LEN];
	CHAR			oGrantor[NAME_LEN];
	CHAR			oGrantee[NAME_LEN];
	CHAR			oPrivilege[NAME_LEN];
	CHAR			oIs_Grantable[3];

	SQLLEN		oTableQualifierlen;
	SQLLEN		oTableOwnerlen;
	SQLLEN		oTableNamelen;
	SQLLEN		oGrantorlen = SQL_NTS;
	SQLLEN		oGranteelen;
	SQLLEN		oPrivilegelen;
	SQLLEN		oIs_Grantablelen;

/*  */
	struct
	{
		CHAR		*Col;
		CHAR		*Grantee;
		CHAR		*Is_Grantable;
		CHAR		*Privilege;
	} TableCol[] = {
		{"--",SQ_GRANTEE,"YES","DELETE"},
		{"--",SQ_GRANTEE,"NO","DELETE,SELECT"},
		{"--",SQ_GRANTEE,"YES","SELECT"},
		{"--",SQ_GRANTEE,"NO","DELETE"},
		{"--",SQ_GRANTEE,"YES","INSERT"},
		{"--",SQ_GRANTEE,"NO","UPDATE"},
		{"--",SQ_GRANTEE,"YES","REFERENCES"},
		{"--",SQ_GRANTEE,"NO","SELECT"},
		{"--",SQ_GRANTEE,"YES","INSERT"},
		{"--",SQ_GRANTEE,"NO","REFERENCES"},
		{"--",SQ_GRANTEE,"YES","UPDATE"},
		{"--",SQ_GRANTEE,"NO","REFERENCES"},
		{"--",SQ_GRANTEE,"YES","UPDATE"},
		{"--",SQ_GRANTEE,"NO","INSERT",},
		{"--",SQ_GRANTEE,"YES","SELECT"},
		{"--",SQ_GRANTEE,"NO","REFERENCES,SELECT"},
		{"--",SQ_GRANTEE,"YES","DELETE,INSERT,SELECT"},
		{"--",SQ_GRANTEE,"NO","INSERT,REFERENCES,UPDATE"},
		{"--",SQ_GRANTEE,"YES","SELECT,DELETE,INSERT,UPDATE"},
		{"--",SQ_GRANTEE,"NO","DELETE,INSERT,REFERENCES,UPDATE",},
		{"--",SQ_GRANTEE,"YES","DELETE,INSERT,REFERENCES,SELECT,UPDATE"},
		{"--",SQ_GRANTEE,"NO","DELETE"},						//Bignum
		{"--",SQ_GRANTEE,"YES","SELECT"},					//Bignum
		{"--",SQ_GRANTEE,"NO","INSERT"},						//Bignum
		{"--",SQ_GRANTEE,"YES","UPDATE"},					//Bignum
		{"--",SQ_GRANTEE,"NO","REFERENCES"},					//Bignum
		{"--",SQ_GRANTEE,"YES","SELECT,DELETE,INSERT,UPDATE"},//Bignum
		{"--",SQ_GRANTEE,"NO","INSERT,REFERENCES,UPDATE"},	//Bignum
		{"endloop",}
	};

	struct
	{
		CHAR		*TabQua;
		CHAR		*TabOwner;
		CHAR		*TabName;
		RETCODE		CheckCode;
		int			isEscape;
	} ColumnWC[] = {								// wild cards from here 
							{"--","--","--", SQL_SUCCESS,0},// Have a row with all valid values here so that 
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_ERROR,0},
							{"--","--","--", SQL_ERROR,0},
							{"--","--","--", SQL_ERROR,0},
							{"--","--","--", SQL_ERROR,0},
							{"--","--","--", SQL_ERROR,0}, 
							{"--","--","--", SQL_ERROR,0}, 
							{"--","--","--", SQL_ERROR,0}, 
							{"--","--","--", SQL_ERROR,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							{"--","--","--", SQL_SUCCESS,0},
							//	Testing escape sequences
							{"--","--","--", SQL_SUCCESS,1},
							{"--","--","--", SQL_SUCCESS,1},
							{"--","--","--", SQL_SUCCESS,1},
							{"--","--","--", SQL_SUCCESS,1},
							{"endloop",}
						};

	struct
	{
		CHAR		*TabQua;
		SWORD		TabQuaLen;
		CHAR		*TabOwner;
		SWORD		TabOwnerLen;
		CHAR		*TabName;
		SWORD		TabNameLen;
		CHAR		*ColName;
		SWORD		ColNameLen;
	} ColumnWC2[] = {								//	wild cards from here
							{"--", (SWORD)-1, "--",(SWORD)-1, "--",(SWORD)-1, "", (SWORD)-1},
							{"--", (SWORD)4,  "--",(SWORD)2,  "--",(SWORD)2,  "", (SWORD)2},
//							{"TEST_CATALOG", (SWORD)0, "TEST_SCHEMA",(SWORD)0, "TEST_TABLE",(SWORD)0, "", (SWORD)0},
							{"endloop",}
						};

	int cols;
	int	iatt;
	SWORD numOfCols = 0;
	SWORD pcbDesc;
	SQLLEN pfDesc;
	CHAR cn[COLNAME_LEN];
	SWORD cl;
	SWORD st;
	SQLULEN cp;
	SWORD cs, cnull;
	CHAR rgbDesc[RGB_MAX_LEN];
	CHAR *CharOutput[12];
	SQLLEN stringlength;	//	Attributes for columns added for negative testing
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

	CHAR	*TestColumn;
	int		i = 0, k = 0;

    struct {
        char cat[STR_LEN];
        char sch[STR_LEN];
        char tab[STR_LEN];
    } displayBuf;

//	DWORD	nSize;


//===========================================================================================================
	var_list_t *var_list;
	var_list = load_api_vars("SQLTablePrivileges", charset_file);
	if (var_list == NULL) return FAILED;

	TableName = var_mapping("SQLTablePrivileges_TableName", var_list);

	TestColumn = var_mapping("SQLTablePrivileges_TestColumn", var_list);

	TableCol[0].Col = var_mapping("SQLTablePrivileges_TableCol_Col_0", var_list);
	TableCol[1].Col = var_mapping("SQLTablePrivileges_TableCol_Col_1", var_list);
	TableCol[2].Col = var_mapping("SQLTablePrivileges_TableCol_Col_2", var_list);
	TableCol[3].Col = var_mapping("SQLTablePrivileges_TableCol_Col_3", var_list);
	TableCol[4].Col = var_mapping("SQLTablePrivileges_TableCol_Col_4", var_list);
	TableCol[5].Col = var_mapping("SQLTablePrivileges_TableCol_Col_5", var_list);
	TableCol[6].Col = var_mapping("SQLTablePrivileges_TableCol_Col_6", var_list);
	TableCol[7].Col = var_mapping("SQLTablePrivileges_TableCol_Col_7", var_list);
	TableCol[8].Col = var_mapping("SQLTablePrivileges_TableCol_Col_8", var_list);
	TableCol[9].Col = var_mapping("SQLTablePrivileges_TableCol_Col_9", var_list);
	TableCol[10].Col = var_mapping("SQLTablePrivileges_TableCol_Col_10", var_list);
	TableCol[11].Col = var_mapping("SQLTablePrivileges_TableCol_Col_11", var_list);
	TableCol[12].Col = var_mapping("SQLTablePrivileges_TableCol_Col_12", var_list);
	TableCol[13].Col = var_mapping("SQLTablePrivileges_TableCol_Col_13", var_list);
	TableCol[14].Col = var_mapping("SQLTablePrivileges_TableCol_Col_14", var_list);
	TableCol[15].Col = var_mapping("SQLTablePrivileges_TableCol_Col_15", var_list);
	TableCol[16].Col = var_mapping("SQLTablePrivileges_TableCol_Col_16", var_list);
	TableCol[17].Col = var_mapping("SQLTablePrivileges_TableCol_Col_17", var_list);
	TableCol[18].Col = var_mapping("SQLTablePrivileges_TableCol_Col_18", var_list);
	TableCol[19].Col = var_mapping("SQLTablePrivileges_TableCol_Col_19", var_list);
	TableCol[20].Col = var_mapping("SQLTablePrivileges_TableCol_Col_20", var_list);
	TableCol[21].Col = var_mapping("SQLTablePrivileges_TableCol_Col_21", var_list);
	TableCol[22].Col = var_mapping("SQLTablePrivileges_TableCol_Col_22", var_list);
	TableCol[23].Col = var_mapping("SQLTablePrivileges_TableCol_Col_23", var_list);
	TableCol[24].Col = var_mapping("SQLTablePrivileges_TableCol_Col_24", var_list);
	TableCol[25].Col = var_mapping("SQLTablePrivileges_TableCol_Col_25", var_list);
	TableCol[26].Col = var_mapping("SQLTablePrivileges_TableCol_Col_26", var_list);
	TableCol[27].Col = var_mapping("SQLTablePrivileges_TableCol_Col_27", var_list);

	ColumnWC[0].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_0", var_list);
	ColumnWC[0].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_0", var_list);
	ColumnWC[0].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_0", var_list);

	ColumnWC[1].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_1", var_list);
	ColumnWC[1].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_1", var_list);
	ColumnWC[1].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_1", var_list);

	ColumnWC[2].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_2", var_list);
	ColumnWC[2].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_2", var_list);
	ColumnWC[2].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_2", var_list);

	ColumnWC[3].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_3", var_list);
	ColumnWC[3].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_3", var_list);
	ColumnWC[3].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_3", var_list);

	ColumnWC[4].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_4", var_list);
        ColumnWC[4].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_4", var_list); 
	ColumnWC[4].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_4", var_list);

	ColumnWC[5].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_5", var_list);
	ColumnWC[5].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_5", var_list);
	ColumnWC[5].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_5", var_list);

	ColumnWC[6].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_6", var_list);
	ColumnWC[6].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_6", var_list);
	ColumnWC[6].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_6", var_list);

	ColumnWC[7].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_7", var_list);
	ColumnWC[7].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_7", var_list);
	ColumnWC[7].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_7", var_list);

	ColumnWC[8].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_8", var_list);
	ColumnWC[8].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_8", var_list);
	ColumnWC[8].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_8", var_list);

	ColumnWC[9].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_9", var_list);
	ColumnWC[9].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_9", var_list);
	ColumnWC[9].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_9", var_list);

	ColumnWC[10].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_10", var_list);
	ColumnWC[10].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_10", var_list);
	ColumnWC[10].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_10", var_list);

	ColumnWC[11].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_11", var_list);
	ColumnWC[11].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_11", var_list);
	ColumnWC[11].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_11", var_list);

	ColumnWC[12].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_12", var_list);
	ColumnWC[12].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_12", var_list);
	ColumnWC[12].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_12", var_list);

	ColumnWC[13].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_13", var_list);
	ColumnWC[13].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_13", var_list);
	ColumnWC[13].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_13", var_list);

	ColumnWC[14].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_14", var_list);
	ColumnWC[14].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_14", var_list);
	ColumnWC[14].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_14", var_list);

	ColumnWC[15].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_15", var_list);
	ColumnWC[15].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_15", var_list);
	ColumnWC[15].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_15", var_list);

	ColumnWC[16].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_16", var_list);
	ColumnWC[16].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_16", var_list);
	ColumnWC[16].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_16", var_list);

	ColumnWC[17].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_17", var_list);
	ColumnWC[17].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_17", var_list);
	ColumnWC[17].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_17", var_list);

	ColumnWC[18].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_18", var_list);
	ColumnWC[18].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_18", var_list);
	ColumnWC[18].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_18", var_list);

	ColumnWC[19].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_19", var_list);
	ColumnWC[19].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_19", var_list);
	ColumnWC[19].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_19", var_list);

	ColumnWC[20].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_20", var_list);
	ColumnWC[20].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_20", var_list);
	ColumnWC[20].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_20", var_list);

	ColumnWC[21].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_21", var_list);
	ColumnWC[21].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_21", var_list);
	ColumnWC[21].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_21", var_list);

	ColumnWC[22].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_22", var_list);
	ColumnWC[22].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_22", var_list);
	ColumnWC[22].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_22", var_list);

	ColumnWC[23].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_23", var_list);
	ColumnWC[23].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_23", var_list);
	ColumnWC[23].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_23", var_list);

	ColumnWC[24].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_24", var_list);
	ColumnWC[24].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_24", var_list);
	ColumnWC[24].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_24", var_list);

	ColumnWC[25].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_25", var_list);
	ColumnWC[25].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_25", var_list);
	ColumnWC[25].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_25", var_list);

	ColumnWC[26].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_26", var_list);
	ColumnWC[26].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_26", var_list);
	ColumnWC[26].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_26", var_list);

	ColumnWC[27].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_27", var_list);
	ColumnWC[27].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_27", var_list);
	ColumnWC[27].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_27", var_list);

	ColumnWC[28].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_28", var_list);
	ColumnWC[28].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_28", var_list);
	ColumnWC[28].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_28", var_list);

	ColumnWC[29].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_29", var_list);
	ColumnWC[29].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_29", var_list);
	ColumnWC[29].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_29", var_list);

	ColumnWC[30].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_30", var_list);
	ColumnWC[30].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_30", var_list);
	ColumnWC[30].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_30", var_list);

	ColumnWC[31].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_31", var_list);
	ColumnWC[31].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_31", var_list);
	ColumnWC[31].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_31", var_list);

	ColumnWC[32].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_32", var_list);
	ColumnWC[32].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_32", var_list);
	ColumnWC[32].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_32", var_list);

	ColumnWC[33].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_33", var_list);
	ColumnWC[33].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_33", var_list);
	ColumnWC[33].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_33", var_list);

	ColumnWC[34].TabQua = var_mapping("SQLTablePrivileges_ColumnWC_TabQua_34", var_list);
	ColumnWC[34].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC_TabOwner_34", var_list);
	ColumnWC[34].TabName = var_mapping("SQLTablePrivileges_ColumnWC_TabName_34", var_list);

	ColumnWC2[0].TabQua = var_mapping("SQLTablePrivileges_ColumnWC2_TabQua_0", var_list);
	ColumnWC2[0].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC2_TabOwner_0", var_list);
	ColumnWC2[0].TabName = var_mapping("SQLTablePrivileges_ColumnWC2_TabName_0", var_list);

	ColumnWC2[1].TabQua = var_mapping("SQLTablePrivileges_ColumnWC2_TabQua_1", var_list);
	ColumnWC2[1].TabOwner = var_mapping("SQLTablePrivileges_ColumnWC2_TabOwner_1", var_list);
	ColumnWC2[1].TabName = var_mapping("SQLTablePrivileges_ColumnWC2_TabName_1", var_list);

//=================================================================================================

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => SQLTablePrivileges | SQLTablePriv | tabpriv.c\n");

	TEST_INIT;

	TESTCASE_BEGIN("Setup for SQLTablePrivileges tests\n");

	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
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

#ifdef LDAP
	// Grantor = var_mapping("SQLTablePrivileges_Grantor", var_list);
/*
	returncode = SQLGetConnectAttr(hdbc, (SQLINTEGER)SQL_ATTR_ROLENAME, (SQLCHAR*)Grantor, SQL_MAX_ROLENAME_LEN+2, (SQLINTEGER *) &oGrantorlen);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLGetConnectAttr"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
		TEST_RETURN;
	}
*/
/* hardcode it for now */ strcpy (Grantor, "DB__ROOT");
#else
        sprintf(Grantor, "%s", var_mapping("SQLTablePrivileges_Grantor", var_list)); 
#endif

	LogMsg(NONE,"Grantor is: %s\n", Grantor);

	TESTCASE_END;  // end of setup
 
	strcpy(TableQualifier,pTestInfo->Catalog);
	strcpy(TableOwner,pTestInfo->Schema);

	TableStr = (char *)malloc(MAX_NOS_SIZE);
	i = 0;
	while (_stricmp(TableCol[i].Col,"endloop") != 0)
	{
		sprintf(Heading,"Test #%d\n",i);
		TESTCASE_BEGIN(Heading);

		if (_stricmp(TableCol[i].Privilege,"ALL PRIVILEGES") == 0)
			strcpy(TableCol[i].Privilege,"DELETE");

		// clean up left over table, if any.  We don't care about returncode from SQLExecDirect
		sprintf(TableStr,"drop table %s",TableName);
		SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);
		
		// create table to test against
		sprintf(TableStr,"create table %s (%s) no partition;",TableName,TableCol[i].Col);
		returncode = SQLExecDirect(hstmt,(SQLCHAR*)TableStr,SQL_NTS);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
		}
		else
		{
			// execute GRANT statement to set up some table privileges
			sprintf(TableStr,"GRANT %s ON %s TO \"%s\"",TableCol[i].Privilege,TableName,TableCol[i].Grantee);
			if (_stricmp(TableCol[i].Is_Grantable,"YES") == 0)
				strcat(TableStr, " WITH GRANT OPTION");
			LogMsg(NONE,"%s\n",TableStr);
			returncode = SQLExecDirect(hstmt,(SQLCHAR*)TableStr,SQL_NTS);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			}
			else
			{
				// Execute SQLTablePrivileges for test table
				if (strlen(TableQualifier) == 0)
					returncode = SQLTablePrivileges(hstmt,NULL,0,(SQLCHAR*)TableOwner,(SWORD)strlen(TableOwner),(SQLCHAR*)TableName,(SWORD)strlen(TableName));
				else
					returncode = SQLTablePrivileges(hstmt,(SQLCHAR*)TableQualifier,(SWORD)strlen(TableQualifier),(SQLCHAR*)TableOwner,(SWORD)strlen(TableOwner),(SQLCHAR*)TableName,(SWORD)strlen(TableName));
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLTablePrivileges"))
				{
					LogAllErrors(henv,hdbc,hstmt);
					TEST_FAILED;
				}
				else
				{
					LogMsg(NONE,"SQLTablePrivileges function call executed correctly.\n");

					// clear all buffers
					strcpy(oTableQualifier,"");
					strcpy(oTableOwner,"");
					strcpy(oTableName,"");
					strcpy(oGrantor,"");
					strcpy(oGrantee,"");
					strcpy(oPrivilege,"");
					strcpy(oIs_Grantable,"");

					// Bind all columns to recieve data returned from SQLTablePrivileges
					returncode = SQLBindCol(hstmt,1,SQL_C_CHAR,oTableQualifier,NAME_LEN,&oTableQualifierlen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					} 
					returncode = SQLBindCol(hstmt,2,SQL_C_CHAR,oTableOwner,NAME_LEN,&oTableOwnerlen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					returncode = SQLBindCol(hstmt,3,SQL_C_CHAR,oTableName,NAME_LEN,&oTableNamelen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					returncode = SQLBindCol(hstmt,4,SQL_C_CHAR,oGrantor,NAME_LEN,&oGrantorlen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					returncode = SQLBindCol(hstmt,5,SQL_C_CHAR,oGrantee,NAME_LEN,&oGranteelen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					returncode = SQLBindCol(hstmt,6,SQL_C_CHAR,oPrivilege,NAME_LEN,&oPrivilegelen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					returncode = SQLBindCol(hstmt,7,SQL_C_CHAR,oIs_Grantable,NAME_LEN,&oIs_Grantablelen);
					if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
					{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
					}
					
					
					// Loop, reading and checking all data retuned from SQLTablePrivileges call
					k = 0;
					while (returncode == SQL_SUCCESS)
					{
						returncode = SQLFetch(hstmt);
						if((returncode!=SQL_NO_DATA_FOUND) && (!CHECKRC(SQL_SUCCESS,returncode,"SQLFetch")))
						{
							LogAllErrors(henv,hdbc,hstmt);
							TEST_FAILED;
						}
						else 
						{
							// check for SQL_SUCCESS in case SQL_NO_DATA_FOUND was what was returned
							// compare results for rows where oGrantor is not the same as Grantor (super.super)
							if ((returncode == SQL_SUCCESS) && (_stricmp(Grantor,oGrantor) == 0) && (_stricmp(TableCol[i].Grantee,oGrantee) == 0))
							{
								k++;	// found a match, increment counter
								if ((_stricmp(TableQualifier,oTableQualifier) == 0) 
									&& (cstrcmp(TableOwner,oTableOwner,TRUE,isCharSet) == 0) 
									&& (cstrcmp(TableName,oTableName,TRUE,isCharSet) == 0) 
									//&& (_stricmp(oGrantor,Grantor) == 0) 
									//&& (_stricmp(TableCol[i].Grantee,oGrantee) == 0) // NOT NEEDED
									&& (strstr(TableCol[i].Privilege,oPrivilege) != NULL) 
									&& (_stricmp(TableCol[i].Is_Grantable,oIs_Grantable) == 0) )
								{
									LogMsg(NONE,"SQLTablePrivileges: compare results of rows fetched for following column.\n");
									LogMsg(NONE,"TableQualifier expect: %s and actual: %s are matched\n",TableQualifier,oTableQualifier);
									LogMsg(NONE,"TableOwner expect: %s and actual: %s are matched\n",TableOwner,oTableOwner);
									LogMsg(NONE,"TableName expect: %s and actual: %s are matched\n",TableName,oTableName);
									LogMsg(NONE,"Grantor expect: %s and actual: %s are matched\n",Grantor,oGrantor);
									LogMsg(NONE,"Grantee expect: %s and actual: %s are matched\n",TableCol[i].Grantee,oGrantee);
									LogMsg(NONE,"Privilege expect: %s and actual: %s are matched\n",TableCol[i].Privilege,oPrivilege);
									LogMsg(NONE,"Is_Grantable expect: %s and actual: %s are matched\n",TableCol[i].Is_Grantable,oIs_Grantable);
								}
								else
								{
									TEST_FAILED;	
									LogMsg(NONE,"SQLTablePrivileges: compare results of rows fetched for following column failed line %d.\n", __LINE__);
									if (_stricmp(TableQualifier,oTableQualifier) != 0)
										LogMsg(ERRMSG,"TableQualifier expect: %s and actual: %s are not matched\n",TableQualifier,oTableQualifier);
									if (cstrcmp(TableOwner,oTableOwner,TRUE,isCharSet) != 0) 
										LogMsg(ERRMSG,"TableOwner expect: %s and actual: %s are not matched\n",TableOwner,oTableOwner);
									if (cstrcmp(TableName,oTableName,TRUE,isCharSet) != 0) 
										LogMsg(ERRMSG,"TableName expect: %s and actual: %s are not matched\n",TableName,oTableName);
									//if (_stricmp(oGrantor,Grantor) != 0)
									//	LogMsg(ERRMSG,"Grantor expect: %s and actual: %s are not matched\n",Grantor,oGrantor);
									//if (_stricmp(TableCol[i].Grantee,oGrantee) != 0)
									//	LogMsg(ERRMSG,"Grantee expect: %s and actual: %s are not matched\n",TableCol[i].Grantee,oGrantee);
									if (strstr(TableCol[i].Privilege,oPrivilege) == NULL)
										LogMsg(ERRMSG,"Privilege expect: %s and actual: %s are not matched\n",TableCol[i].Privilege,oPrivilege);
									if (_stricmp(TableCol[i].Is_Grantable,oIs_Grantable) != 0)
										LogMsg(ERRMSG,"Is_Grantable expect: %s and actual: %s are not matched\n",TableCol[i].Is_Grantable,oIs_Grantable);
								}
							}
						}
					}
					if(k == 0){
						TEST_FAILED;
						LogMsg(ERRMSG,"No matching grantee record for '%s' found\n"
										  "   At least one row fetched should have matched\n",
										  TableCol[i].Grantee);
						}
					SQLFreeStmt(hstmt,SQL_UNBIND);
					SQLFreeStmt(hstmt,SQL_CLOSE);
				}
			}
		}
		TESTCASE_END;
		
		// clean up SQL table
		sprintf(TableStr,"drop table %s",TableName);
		SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);
		i++;
	} 

//=======================================================================================

	i = 0;
	sprintf(TableStr,"drop table %s.%s.%s",ColumnWC[i].TabQua, ColumnWC[i].TabOwner, ColumnWC[i].TabName);
	SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);
	LogMsg(NONE,"%s\n",TableStr);
	sprintf(TableStr,"drop schema %s.%s cascade",ColumnWC[i].TabQua, ColumnWC[i].TabOwner);
	SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);
	LogMsg(NONE,"%s\n",TableStr);

	sprintf(TableStr,"create schema %s.%s",ColumnWC[i].TabQua, ColumnWC[i].TabOwner);
	LogMsg(NONE,"%s\n",TableStr);
	returncode = SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
	{
		LogAllErrors(henv,hdbc,hstmt);
		TEST_FAILED;
	}
	else
	{
		sprintf(TableStr,"create table %s.%s.%s(%s char(10)) no partition;",ColumnWC[i].TabQua, ColumnWC[i].TabOwner, ColumnWC[i].TabName, TestColumn);
		returncode = SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLExecDirect"))
		{
			LogAllErrors(henv,hdbc,hstmt);
			TEST_FAILED;
		}
	}
	LogMsg(NONE,"%s\n",TableStr);
	returncode = SQLSetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,(SQLPOINTER)SQL_FALSE,0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtAttr"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}// end of setup
	if (returncode == SQL_SUCCESS) 
	{
		while ((_stricmp(ColumnWC[i].TabQua,"endloop") != 0) && (ColumnWC[i].isEscape == 0))
		{
			sprintf(Heading,"SQLTablePrivileges: wildcard options => \n"
				"Table Qualifier: %s \nTable Owner: %s \nTable Name: %s\n", 
				printSymbol(ColumnWC[i].TabQua,displayBuf.cat), 
				printSymbol(ColumnWC[i].TabOwner,displayBuf.sch), 
				printSymbol(ColumnWC[i].TabName,displayBuf.tab));
			TESTCASE_BEGIN(Heading);
			if (_stricmp(ColumnWC[i].TabQua,"NULL") == 0)
				ColumnWC[i].TabQua = NULL;
			if (_stricmp(ColumnWC[i].TabOwner,"NULL") == 0)
				ColumnWC[i].TabOwner = NULL;
			if (_stricmp(ColumnWC[i].TabName,"NULL") == 0)
				ColumnWC[i].TabName = NULL;

			if (ColumnWC[i].TabQua == NULL || ColumnWC[i].TabOwner == NULL || ColumnWC[i].TabName == NULL)
				returncode = SQLTablePrivileges(hstmt,(SQLCHAR*)ColumnWC[i].TabQua,SQL_NTS,
                                                      (SQLCHAR*)ColumnWC[i].TabOwner,SQL_NTS,
                                                      (SQLCHAR*)removeQuotes(ColumnWC[i].TabName,displayBuf.tab),SQL_NTS);
			else
				returncode = SQLTablePrivileges(hstmt,(SQLCHAR*)ColumnWC[i].TabQua,(SWORD)strlen(ColumnWC[i].TabQua),
                                                      (SQLCHAR*)ColumnWC[i].TabOwner,(SWORD)strlen(ColumnWC[i].TabOwner),
                                                      (SQLCHAR*)removeQuotes(ColumnWC[i].TabName,displayBuf.tab),(SWORD)strlen(displayBuf.tab));
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLTablePrivileges"))
			{
				TEST_FAILED;
				LogAllErrors(henv,hdbc,hstmt);
			}
			else
			{
				LogMsg(NONE,"SQLTablePrivileges: SQLTablePrivileges function call executed correctly.\n");
				strcpy(oTableQualifier,"");
				strcpy(oTableOwner,"");
				strcpy(oTableName,"");
				strcpy(oGrantor,"");
				strcpy(oGrantee,"");
				strcpy(oPrivilege,"");
				strcpy(oIs_Grantable,"");
				returncode = SQLBindCol(hstmt,1,SQL_C_CHAR,oTableQualifier,NAME_LEN,&oTableQualifierlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				} 
				returncode = SQLBindCol(hstmt,2,SQL_C_CHAR,oTableOwner,NAME_LEN,&oTableOwnerlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,3,SQL_C_CHAR,oTableName,NAME_LEN,&oTableNamelen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}

				returncode = SQLBindCol(hstmt,4,SQL_C_CHAR,oGrantor,NAME_LEN,&oGrantorlen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,5,SQL_C_CHAR,oGrantee,NAME_LEN,&oGranteelen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				
				returncode = SQLBindCol(hstmt,6,SQL_C_CHAR,oPrivilege,NAME_LEN,&oPrivilegelen);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
				{
						LogAllErrors(henv,hdbc,hstmt);
						TEST_FAILED;
				}
				returncode = SQLBindCol(hstmt,7,SQL_C_CHAR,oIs_Grantable,NAME_LEN,&oIs_Grantablelen);
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
						TEST_FAILED;
						LogAllErrors(henv,hdbc,hstmt);
					}
					if (returncode == SQL_SUCCESS)
						k++;
				}
				if(k == 0 && ColumnWC[i].CheckCode == SQL_SUCCESS)
				{
					if(ColumnWC[i].isEscape == 1)
						LogMsg(ERRMSG, "Search string pattern in Catalog's Name is not supported\n");
					else {
						TEST_FAILED;
						LogMsg(ERRMSG,"No Data Found => Atleast one row should be fetched\n");
					}
				}
			}
			SQLFreeStmt(hstmt,SQL_CLOSE);
			TESTCASE_END;
			i++;
		}
	}

//======================================================================================================

	TESTCASE_BEGIN("SQLTablePrivileges: Negative test with invalid handle.\n");

	i = 0;
	returncode = SQLTablePrivileges(hstmt1,(SQLCHAR*)ColumnWC[i].TabQua,(SWORD)strlen(ColumnWC[i].TabQua),(SQLCHAR*)ColumnWC[i].TabOwner,(SWORD)strlen(ColumnWC[i].TabOwner),(SQLCHAR*)ColumnWC[i].TabName,(SWORD)strlen(ColumnWC[i].TabName));
	if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLTables"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	TESTCASE_END;

//=========================================================================================

	TESTCASE_BEGIN("SQLTables: Negative test with NULL handle.\n");

	hstmt1 = (SQLHANDLE)NULL;
	i = 0;
	returncode = SQLTablePrivileges(hstmt1,(SQLCHAR*)ColumnWC[i].TabQua,(SWORD)strlen(ColumnWC[i].TabQua),(SQLCHAR*)ColumnWC[i].TabOwner,(SWORD)strlen(ColumnWC[i].TabOwner),(SQLCHAR*)ColumnWC[i].TabName,(SWORD)strlen(ColumnWC[i].TabName));
	if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLTables"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	TESTCASE_END;

//=========================================================================================

	TESTCASE_BEGIN("SQLTablePrivileges: Negative test with invalid arg lengths.\n");

	returncode = SQLTablePrivileges(hstmt,(SQLCHAR*)ColumnWC2[0].TabQua,ColumnWC2[0].TabQuaLen,(SQLCHAR*)ColumnWC2[0].TabOwner,ColumnWC2[0].TabOwnerLen,(SQLCHAR*)ColumnWC2[0].TabName,ColumnWC2[0].TabNameLen);
	LogMsg(NONE, "Input parameters: CatalogLen %d SchemaLen %d TableLen %d\n", ColumnWC2[0].TabQuaLen, ColumnWC2[0].TabOwnerLen, ColumnWC2[0].TabNameLen);
	if(!CHECKRC(SQL_ERROR,returncode,"SQLTablePrivileges"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}

	TESTCASE_END;

//=========================================================================================

	TESTCASE_BEGIN("SQLTablePrivileges: Positive test with invalid arg lengths.\n");

	returncode = SQLTablePrivileges(hstmt,(SQLCHAR*)ColumnWC2[1].TabQua,ColumnWC2[1].TabQuaLen,(SQLCHAR*)ColumnWC2[1].TabOwner,ColumnWC2[1].TabOwnerLen,(SQLCHAR*)ColumnWC2[1].TabName,ColumnWC2[1].TabNameLen);
	LogMsg(NONE, "Input parameters: CatalogLen %d SchemaLen %d TableLen %d\n", ColumnWC2[1].TabQuaLen, ColumnWC2[1].TabOwnerLen, ColumnWC2[1].TabNameLen);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLTablePrivileges"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
	else {
		LogMsg(NONE,"SQLTablePrivileges: SQLTablePrivileges function call executed correctly.\n");
		strcpy(oTableQualifier,"");
		strcpy(oTableOwner,"");
		strcpy(oTableName,"");
		strcpy(oGrantor,"");
		strcpy(oGrantee,"");
		strcpy(oPrivilege,"");
		strcpy(oIs_Grantable,"");
		returncode = SQLBindCol(hstmt,1,SQL_C_CHAR,oTableQualifier,NAME_LEN,&oTableQualifierlen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
		{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
		} 
		returncode = SQLBindCol(hstmt,2,SQL_C_CHAR,oTableOwner,NAME_LEN,&oTableOwnerlen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
		{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
		}
		returncode = SQLBindCol(hstmt,3,SQL_C_CHAR,oTableName,NAME_LEN,&oTableNamelen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
		{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
		}
		returncode = SQLBindCol(hstmt,4,SQL_C_CHAR,oGrantor,NAME_LEN,&oGrantorlen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
		{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
		}
		returncode = SQLBindCol(hstmt,5,SQL_C_CHAR,oGrantee,NAME_LEN,&oGranteelen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
		{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
		}
		
		returncode = SQLBindCol(hstmt,6,SQL_C_CHAR,oPrivilege,NAME_LEN,&oPrivilegelen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
		{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
		}
		returncode = SQLBindCol(hstmt,7,SQL_C_CHAR,oIs_Grantable,NAME_LEN,&oIs_Grantablelen);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
		{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
		}
		k = 0;
		while (returncode == SQL_SUCCESS) 
		{
			returncode = SQLFetch(hstmt);
			if (returncode == SQL_SUCCESS) k++;
		}
		if(k > 0)
		{
			TEST_FAILED;
			LogMsg(ERRMSG,"Should be no data found - check for similar objects unintentionally appear\n");
		}
	}

	TESTCASE_END;

//=========================================================================================

	TESTCASE_BEGIN("Testing SQLColAttribute, SQLDescribeCol, SQLBindCol and SQLFetch functions for catalog names.\n");

	returncode = SQLSetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,(SQLPOINTER)SQL_FALSE,0);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLSetStmtAttr"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}// end of setup

	for(i = 0; i < 5; i++)
	{
		sprintf(Heading,"======================================\n"
						"SQLTablePrivileges: wildcard options => \n"
						"Table Qualifier: %s \nTable Owner: %s \nTable Name: %s\n", 
						printSymbol(ColumnWC[i].TabQua,displayBuf.cat), 
						printSymbol(ColumnWC[i].TabOwner,displayBuf.sch), 
						printSymbol(ColumnWC[i].TabName,displayBuf.tab));
		LogMsg(NONE,Heading);

		returncode = SQLTablePrivileges(hstmt,(SQLCHAR*)ColumnWC[i].TabQua,(SWORD)strlen(ColumnWC[i].TabQua),
											  (SQLCHAR*)removeQuotes(ColumnWC[i].TabOwner, displayBuf.sch),(SWORD)strlen(displayBuf.sch),
											  (SQLCHAR*)removeQuotes(ColumnWC[i].TabName, displayBuf.tab),(SWORD)strlen(displayBuf.tab));
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLColumns"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		LogMsg(NONE,"after the call\n");

		returncode = SQLNumResultCols(hstmt, &numOfCols);
		if(!CHECKRC(SQL_SUCCESS,returncode,"SQLNumResultsCol"))
		{
			TEST_FAILED;
			LogMsg(ERRMSG,"Test failed while executing call for SQLNUMRESULTSCOL");
			LogAllErrors(henv,hdbc,hstmt);
		}
		for(cols = 0; cols < numOfCols; cols++)
		{
			returncode = SQLDescribeCol(hstmt,(SWORD)(cols+1),(SQLCHAR*)cn,COLNAME_LEN,&cl,&st,&cp,&cs,&cnull);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLDescribeCol"))
			{
				TEST_FAILED;
				LogMsg(ERRMSG,"Test failed while executing call for SQLDESCRIBECOL of column");
				LogAllErrors(henv,hdbc,hstmt);
			}
			CharOutput[cols] = (char *)malloc(STR_LEN);
			for (iatt = 0; iatt <= TOTALATTRIBS; iatt++)
			{
				strcpy(rgbDesc,"");
				pcbDesc = 0;
				pfDesc = 0;
				returncode = SQLColAttributes(hstmt,(SWORD)(cols+1),DescrType[iatt],rgbDesc,STR_LEN,&pcbDesc,&pfDesc);
				if(!CHECKRC(SQL_SUCCESS,returncode,"SQLColAttribute"))
				{
					TEST_FAILED;
					LogMsg(ERRMSG,"Test failed while executing call for SQLCOLATTRIBUTES of column : %d.\n",i+1);
					LogAllErrors(henv,hdbc,hstmt);
				}
			}
			returncode = SQLBindCol(hstmt,(SWORD)(cols+1),SQL_C_CHAR,CharOutput[cols],STR_LEN,&stringlength);
			if(!CHECKRC(SQL_SUCCESS,returncode,"SQLBindCol"))
			{
				TEST_FAILED;
				LogMsg(ERRMSG,"Test failed while executing call for SQLBindCols of column : %d.\n",cols);
				LogAllErrors(henv,hdbc,hstmt);
			}
		}

		k = 0;
		while (returncode == SQL_SUCCESS)
		{
			returncode = SQLFetch(hstmt);
			if(returncode == SQL_ERROR)
			{
				LogAllErrors(henv,hdbc,hstmt);
				TEST_FAILED;
			} else if (returncode == SQL_NO_DATA_FOUND) {
				break;
			}
			else {
				if (returncode == SQL_SUCCESS_WITH_INFO)
					LogAllErrors(henv,hdbc,hstmt);
				k++;
			}
		}
		if(k == 0)
		{
			TEST_FAILED;
			LogMsg(ERRMSG,"No Data Found => Atleast one row should be fetched\n");
		}
		
		for(cols = 0; cols < numOfCols; cols++)
		{
			free(CharOutput[cols]);
		}
		TESTCASE_END;
	}

//=========================================================================================
	// Cleanup
	i=0;
	sprintf(TableStr,"drop table %s.%s.%s",ColumnWC[i].TabQua, ColumnWC[i].TabOwner, ColumnWC[i].TabName);
	SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);
	sprintf(TableStr,"drop schema %s.%s cascade",ColumnWC[i].TabQua, ColumnWC[i].TabOwner);
	SQLExecDirect(hstmt,(SQLCHAR*) TableStr,SQL_NTS);

	FullDisconnect3(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => SQLTablePrivileges.\n");
	free(TableStr); 
	free_list(var_list);
	TEST_RETURN;
}