BOOL CODBC::WriteScorcoData(char* SQL, BYTE* pData, int Length)
{
	SQLRETURN retcode;
	SQLINTEGER cbObjectParam;
	SQLPOINTER pToken;

	char* pSQL = new char[strlen(SQL)];
	sprintf(pSQL, SQL, "?");

	SQLFreeStmt(hstmt,SQL_CLOSE);
	retcode = SQLPrepare(hstmt, (unsigned char *)pSQL, SQL_NTS);
	if (MYSQLSUCCESS(rc))
	{
		SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_LONGVARBINARY, 
			0, 0, (SQLPOINTER) 2, 0, &cbObjectParam);

		cbObjectParam = SQL_LEN_DATA_AT_EXEC(0);
		retcode = SQLExecute(hstmt);

		while (retcode == SQL_NEED_DATA)
		{
			retcode = SQLParamData(hstmt, &pToken);
			if (retcode == SQL_NEED_DATA)
				SQLPutData(hstmt, pData, Length);
		}
		return TRUE;
	}
	else
	{
		SaveSQLError();
		return FALSE;
	}
}