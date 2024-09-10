/*-------------------------------------------------------------------------
 * InitSql
 *-------------------------------------------------------------------------
 * Purpose:
 *    Set up the odbc stuff
 * 
 * Returns:
 *    0. Returns a value only so we can call it during global initialization,
 *        before any code blocks execute.
 */
int InitSql(char * szRegKey, ISQLSite * pSQLSite)
{
  g_pSQLSite = pSQLSite;
  
  // Setup odbc stuff
  SQLRETURN sqlret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hSqlEnv);
  if (SQL_SUCCESS != sqlret)
    SQLWhatsWrong(SQL_HANDLE_ENV, hSqlEnv);
  
  sqlret = SQLSetEnvAttr(hSqlEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC2, 0);
  if (SQL_SUCCESS != sqlret)
    SQLWhatsWrong(SQL_HANDLE_ENV, hSqlEnv);
  
  sqlret = SQLAllocHandle(SQL_HANDLE_DBC, hSqlEnv, &hSqlDbc);
  if (SQL_SUCCESS != sqlret)
    SQLWhatsWrong(SQL_HANDLE_DBC, hSqlDbc);

  // BT - 7/15 CSS Integration.
  char szCssIntegration[8];
  strcpy(szCssIntegration, ParseCommandLine(szRegKey, "CssIntegration", "0"));
  bool useCssIntegration = atoi(szCssIntegration) > 0;

  SQLCHAR StrConnectionOut[1<<10];
  SQLSMALLINT cbStrConnectionOut;

  // BT - 7/15 CSS Integration - Making Club Server actually obey the registry for settings.
  if (useCssIntegration == false)
  {
	  sqlret = SQLDriverConnectA(hSqlDbc, NULL, (SQLCHAR*)
		  "DRIVER={SQL Server};PWD=AllegFed@2014!NotSecret;UID=club;DATABASE=AZFederation;SERVER=tqhlsg1ad6.database.windows.net", SQL_NTS,
		  StrConnectionOut, sizeof(StrConnectionOut),
		  &cbStrConnectionOut, SQL_DRIVER_NOPROMPT);
  }
  else
  {
	  char szUser[64];
	  char szPW[64];
	  char szDatabase[64];
	  char szServer[128];
	  strcpy(szUser, ParseCommandLine(szRegKey, "SQLUser", "club"));
	  strcpy(szPW, ParseCommandLine(szRegKey, "SQLPW", "AllegFed@2014!NotSecret"));
	  strcpy(szDatabase, ParseCommandLine(szRegKey, "SQLDatabase", "AZFederation"));
	  strcpy(szServer, ParseCommandLine(szRegKey, "SQLServer", "localhost"));

	  char sqlDsn[2048];
	  sprintf(sqlDsn, "DRIVER={SQL Server};PWD={%s};UID=%s;DATABASE=%s;SERVER=%s;", szPW, szUser, szDatabase, szServer);

	  printf("  Connecting with DSN: %s...\n", sqlDsn);
	 
	  sqlret = SQLDriverConnectA(hSqlDbc, NULL, (SQLCHAR*)
		  sqlDsn, SQL_NTS,
		  StrConnectionOut, sizeof(StrConnectionOut),
		  &cbStrConnectionOut, SQL_DRIVER_NOPROMPT);
  }
  
  if (SQL_SUCCESS != sqlret && SQL_SUCCESS_WITH_INFO != sqlret)
    SQLWhatsWrong(SQL_HANDLE_DBC, hSqlDbc);
  
   SQLCHAR scODBCver[6];
  SQLSMALLINT cbODBCver;
  sqlret = SQLGetInfoA(hSqlDbc, SQL_DRIVER_ODBC_VER, scODBCver, sizeof(scODBCver), &cbODBCver);
  if (SQL_SUCCESS != sqlret)
    SQLWhatsWrong(SQL_HANDLE_DBC, hSqlDbc);

  return 0;
}