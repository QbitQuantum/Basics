static void acf_odbc_error(SQLHSTMT stmt, int res)
{
	char state[10] = "", diagnostic[256] = "";
	SQLINTEGER nativeerror = 0;
	SQLSMALLINT diagbytes = 0;
	SQLGetDiagRec(SQL_HANDLE_STMT, stmt, 1, state, &nativeerror, diagnostic, sizeof(diagnostic), &diagbytes);
	ast_log(LOG_WARNING, "SQL return value %d: error %s: %s (len %d)\n", res, state, diagnostic, diagbytes);
}