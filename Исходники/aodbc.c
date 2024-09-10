TF EXPFUNC p_db_connect(ENGid eid)
{
   HDBC hdbc;
   char szDataSource[80];
   char szUserID[40];
   char szPassword[40];

   if (pVAR != lsGetParmType(eid, 1))
   {
      lsErrRaise(eid, "db_connect instantiation error: arg 1 must be var");
      return FALSE;
   }
   g_lsRC = lsGetParm(eid, 2, cSTR, szDataSource);
   if (g_lsRC != OK) goto LS_ERROR;
   g_lsRC = lsGetParm(eid, 3, cSTR, szUserID);
   if (g_lsRC != OK) goto LS_ERROR;
   g_lsRC = lsGetParm(eid, 4, cSTR, szPassword);
   if (g_lsRC != OK) goto LS_ERROR;

   g_RC = SQLAllocConnect(g_hEnv, &hdbc);
   /* set up error handler */
   g_hDBC = hdbc;
   g_hSTMT = SQL_NULL_HSTMT;
   g_eid = eid;
   ERROR_CHK("SQLAllocConnect");

   // Added this line to get around erroneous messages:
   // S1010:[Microsoft][ODBC SQL Server Driver]Function sequence error 
   // Fix from MS Knowledge Article 179226
   // SQL_PRESERVE_CURSORS - note new name in actual call
   // This only applies to SQL Server, so hopefully, nothing bad will
   // happen if it fails.

   g_RC = SQLSetConnectOption(hdbc, SQL_COPT_SS_PRESERVE_CURSORS, NULL);

   g_RC = SQLConnect(hdbc,
         (UCHAR*)szDataSource, SQL_NTS,
         (UCHAR*)szUserID, SQL_NTS,
         (UCHAR*)szPassword, SQL_NTS);
   ERROR_CHK("SQLConnect");

   lsUnifyParm(eid, 1, cADDR, &hdbc);
   return TRUE;
LS_ERROR:
   return(lserror());
ODBC_ERROR:
   return FALSE;
}