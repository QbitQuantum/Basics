/*
---------------------------------------------------------
   TestSQLProcedures
---------------------------------------------------------
*/
PassFail TestMXSQLProcedures(TestInfo *pTestInfo)
{                  
	TEST_DECLARE;
 	char			Heading[MAX_HEADING_SIZE];
 	RETCODE			returncode;
 	SQLHANDLE 		henv;
 	SQLHANDLE 		hdbc;
 	SQLHANDLE		hstmt;
  	CHAR			*ProcStr;
	CHAR			*myTestSch = "ODBC_PROC_TEST";
 	CHAR 			createSchStr[128];
	CHAR			setSchStr[128];
	CHAR			dropSchStr[128];
 	CHAR            ProcName[NAME_LEN];
    CHAR            ServerName[NAME_LEN];
    char            SerName[4];
    SQLSMALLINT     serLen;
	SWORD			ProcType = SQL_PT_PROCEDURE;
	CHAR			opqua[NAME_LEN],opowner[NAME_LEN],opname[NAME_LEN],oremark[REM_LEN];
	SWORD			onuminpar,onumoutpar,onumresset,optype;
	SQLLEN			opqualen,opownerlen,opnamelen,onuminparlen,onumoutparlen,onumressetlen,oremarklen,optypelen;

	struct	
	{
		CHAR		*DropProc;
		CHAR		*CrtProc;
	} CreateProc[] = {
							{"DROP PROCEDURE N4210_REG",
							 "CREATE PROCEDURE N4210_REG (IN IN1 TIME) EXTERNAL NAME 'Procs.N4210' EXTERNAL PATH '/home/SQFQA/SPJRoot/odbctest_spjs' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE"},
							{"DROP PROCEDURE N4260_REG",
							 "CREATE PROCEDURE N4260_REG (IN IN1 REAL, INOUT INOUT1 INTEGER) EXTERNAL NAME 'Procs.N4260' EXTERNAL PATH '/home/SQFQA/SPJRoot/odbctest_spjs' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE"},
							{"DROP PROCEDURE N4261_REG",
 							 "CREATE PROCEDURE N4261_REG (IN IN1 NUMERIC, INOUT INOUT1 REAL) EXTERNAL NAME 'Procs.N4261' EXTERNAL PATH '/home/SQFQA/SPJRoot/odbctest_spjs' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE"},
							{"DROP PROCEDURE N4264_REG",
 							 "CREATE PROCEDURE N4264_REG (IN IN1 VARCHAR(30), OUT OUT1 VARCHAR(45)) EXTERNAL NAME 'Procs.N4264' EXTERNAL PATH '/home/SQFQA/SPJRoot/odbctest_spjs' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE"},	
							{"DROP PROCEDURE N4267_REG",
 							 "CREATE PROCEDURE N4267_REG (IN IN1 NUMERIC, INOUT INOUT1 REAL) EXTERNAL NAME 'Procs.N4267' EXTERNAL PATH '/home/SQFQA/SPJRoot/odbctest_spjs' LANGUAGE JAVA PARAMETER STYLE JAVA NO SQL NO ISOLATE"},
							{"endloop","endloop"}
					};
	struct	
	{
		CHAR		*ProcName;
		SDWORD	NumInParams;
		SDWORD	NumOutParams;
		SDWORD	NumResSet;
		CHAR		*Remark;
	} Procedure[] = {
							{"N4210_REG",0,0,0,""},
							{"N4260_REG",0,0,0,""},
							{"N4261_REG",0,0,0,""},
							{"N4264_REG",0,0,0,""},
							{"N4267_REG",0,0,0,""},
							{"endloop",0,0,0,""}
						};
	int	i = 0, k = 0;

//===========================================================================================================
// Initialization Test Case

	LogMsg(LINEBEFORE+SHORTTIMESTAMP,"Begin testing API => MX Specific SQLProcedures | SQLProcedures | MXProc.c\n");
	
	TEST_INIT;

	TESTCASE_BEGIN("Setup for SQLProcedures tests\n");

	if(!FullConnectWithOptions(pTestInfo, CONNECT_ODBC_VERSION_3))
	{
		LogMsg(NONE,"Unable to connect\n");
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
		TEST_RETURN;
	}

    returncode = SQLGetInfo(hdbc, SQL_SERVER_NAME, (SQLPOINTER)&ServerName, NAME_LEN, &serLen);

    strncpy(SerName, ServerName+1, 3);
    SerName[3] = '\0';

   /* sq: This test calls SQLProcedures() with wildcard characters.  It 
    * needs its own empty schema to create the procedures,  Otherwise the 
    * standard schema that everybody uses may already have other procedures 
    * created and will be returned by SQLProcedures() to confuse the test.
    */
   sprintf (createSchStr, "CREATE SCHEMA %s.%s", pTestInfo->Catalog, myTestSch);
   sprintf (setSchStr, "SET SCHEMA %s.%s", pTestInfo->Catalog, myTestSch);
   sprintf (dropSchStr, "DROP SCHEMA %s.%s cascade", pTestInfo->Catalog, myTestSch);
   returncode = SQLExecDirect(hstmt,(SQLCHAR*) dropSchStr,SQL_NTS);
   returncode = SQLExecDirect(hstmt,(SQLCHAR*) createSchStr,SQL_NTS);
   returncode = SQLExecDirect(hstmt,(SQLCHAR*) setSchStr,SQL_NTS);

	ProcStr = (char *)malloc(MAX_NOS_SIZE);

	while (_stricmp(CreateProc[i].DropProc,"endloop") != 0)
	{
        sprintf(ProcStr,"%s",CreateProc[i].DropProc);
		returncode = SQLExecDirect(hstmt,(SQLCHAR*) ProcStr,SQL_NTS); // cleanup
        sprintf(ProcStr,"%s",CreateProc[i].CrtProc);
        replace_str(ProcStr,"$$$",SerName);
		sprintf(Heading,"Procedure => %s\n",ProcStr);
		TESTCASE_BEGIN(Heading);
		
		returncode = SQLExecDirect(hstmt,(SQLCHAR*)ProcStr,SQL_NTS);
		if(returncode != SQL_SUCCESS)
		{
            TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
		TESTCASE_END;
		i++;
	}
	
	sprintf(Heading,"Test Positive Functionality of SQLProcedures \n");
	TESTCASE_BEGIN(Heading);
	returncode = SQLProcedures(hstmt,(SQLCHAR*)pTestInfo->Catalog,(SWORD)strlen(pTestInfo->Catalog),(SQLCHAR*)myTestSch/*pTestInfo->Schema*/,(SWORD)strlen(myTestSch/*pTestInfo->Schema*/),(SQLCHAR *)"%",(SWORD)1);
	if(!CHECKRC(SQL_SUCCESS,returncode,"SQLProcedures"))
		{
			TEST_FAILED;
			LogAllErrors(henv,hdbc,hstmt);
		}
	if (returncode == SQL_SUCCESS)
		{
			strcpy(opqua,"");
			strcpy(opowner,"");
			strcpy(opname,"");
			onuminpar = 0;
			onumoutpar = 0;
			onumresset = 0;
			strcpy(oremark,"");
			optype = 0;
			SQLBindCol(hstmt,1,SQL_C_CHAR,opqua,NAME_LEN,&opqualen);
			SQLBindCol(hstmt,2,SQL_C_CHAR,opowner,NAME_LEN,&opownerlen);
			SQLBindCol(hstmt,3,SQL_C_CHAR,opname,NAME_LEN,&opnamelen);
			SQLBindCol(hstmt,4,SQL_C_SHORT,&onuminpar,0,&onuminparlen);
			SQLBindCol(hstmt,5,SQL_C_SHORT,&onumoutpar,0,&onumoutparlen);
			SQLBindCol(hstmt,6,SQL_C_SHORT,&onumresset,0,&onumressetlen);
			SQLBindCol(hstmt,7,SQL_C_CHAR,oremark,NAME_LEN,&oremarklen);
			SQLBindCol(hstmt,8,SQL_C_SHORT,&optype,0,&optypelen);
			k = 0;
			i = 0;
			while (returncode == SQL_SUCCESS)
			{
				if(strcmp(Procedure[i].ProcName,"endloop") == 0)
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
						sprintf(Heading,"SQLProcedures: Comparing Results\n");
						TESTCASE_BEGIN(Heading);
						if ((_stricmp(pTestInfo->Catalog,opqua) == 0) 
							&& (_stricmp(myTestSch/*pTestInfo->Schema*/,opowner) == 0) 
							&& (_stricmp(Procedure[i].ProcName,opname) == 0) 
							&& (Procedure[i].NumInParams == onuminpar) 
							&& (Procedure[i].NumOutParams == onumoutpar) 
							&& (Procedure[i].NumResSet == onumresset) 
							&& (_stricmp(Procedure[i].Remark,oremark) == 0) 
							&& (ProcType == optype))
							{
								//LogMsg(NONE,"Catalog Name expect: %s and actual: %s are matched\n",pTestInfo->Catalog,opqua);
								//LogMsg(NONE,"Schema Name expect: %s and actual: %s are matched\n",pTestInfo->Schema,opowner);
								//LogMsg(NONE,"ProcName expect: %s and actual: %s are matched\n",Procedure[i].ProcName,opname);
								//LogMsg(NONE,"NumInParams expect: %d and actual: %d are matched\n",Procedure[i].NumInParams,onuminpar);
								//LogMsg(NONE,"NumOutParams expect: %d and actual: %d are matched\n",Procedure[i].NumOutParams,onumoutpar);
								//LogMsg(NONE,"NumResSet expect: %d and actual: %d are matched\n",Procedure[i].NumResSet, onumresset);
								//LogMsg(NONE,"Remark expect: %s and actual: %s are matched\n",Procedure[i].Remark,oremark);
								//LogMsg(NONE,"ProcType expect: %d and actual: %d are matched\n",ProcType,optype);
							}	
						else
							{
								TEST_FAILED;	
								if (_stricmp(pTestInfo->Catalog,opqua) != 0)
									LogMsg(ERRMSG,"Catalog Name expect: %s and actual: %s are not matched\n",pTestInfo->Catalog,opqua);
								if (_stricmp(myTestSch/*pTestInfo->Schema*/,opowner) != 0) 
									LogMsg(ERRMSG,"Schema Name expect: %s and actual: %s are not matched\n",myTestSch/*pTestInfo->Schema*/,opowner);
								if (_stricmp(Procedure[i].ProcName,opname) != 0) 
									LogMsg(ERRMSG,"ProcName expect: %s and actual: %s are not matched\n",Procedure[i].ProcName,opname);
								if (Procedure[i].NumInParams != onuminpar) 
									LogMsg(ERRMSG,"NumInParams expect: %d and actual: %d are not matched\n",Procedure[i].NumInParams,onuminpar);
								if (Procedure[i].NumOutParams != onumoutpar) 
									LogMsg(ERRMSG,"NumOutParams expect: %d and actual: %d are not matched\n",Procedure[i].NumOutParams,onumoutpar);
								if (Procedure[i].NumResSet != onumresset) 
									LogMsg(ERRMSG,"NumResSet expect: %d and actual: %d are not matched\n",Procedure[i].NumResSet, onumresset);
								if (_stricmp(Procedure[i].Remark,oremark) != 0) 
									LogMsg(ERRMSG,"Remark expect: %s and actual: %s are not matched\n",Procedure[i].Remark,oremark);
								if (ProcType != optype)
									LogMsg(ERRMSG,"ProcType expect: %d and actual: %d are not matched\n",ProcType,optype);
							}
						}
					}
					if(k == 0)
					{
						TEST_FAILED;
						LogMsg(ERRMSG,"No Data Found => Atleast one row should be fetched\n");
					}
			TESTCASE_END;
			i++;
			} // while
		}
	SQLFreeStmt(hstmt,SQL_UNBIND);
	SQLFreeStmt(hstmt,SQL_CLOSE);

	//========================================================================================================

	sprintf(Heading,"SQLProcedures: Negative test with NULL handle\n");
	TESTCASE_BEGIN(Heading);

	hstmt = (SQLHANDLE)NULL;
	strcpy(ProcName,"junkproc");

	returncode = SQLProcedures(hstmt,(SQLCHAR*)pTestInfo->Catalog,(SWORD)strlen(pTestInfo->Catalog),(SQLCHAR*)myTestSch/*pTestInfo->Schema*/,(SWORD)strlen(myTestSch/*pTestInfo->Schema*/),(SQLCHAR*)ProcName,(SWORD)strlen(ProcName));
	if(!CHECKRC(SQL_INVALID_HANDLE,returncode,"SQLProcedures"))
	{
		TEST_FAILED;
		LogAllErrors(henv,hdbc,hstmt);
	}
       returncode = SQLExecDirect(hstmt,(SQLCHAR*) dropSchStr,SQL_NTS);
	TESTCASE_END;

	//========================================================================================================

	free(ProcStr);
	FullDisconnect3(pTestInfo);
	LogMsg(SHORTTIMESTAMP+LINEAFTER,"End testing API => MX Specific SQLProcedures.\n");
	TEST_RETURN;
}