static void
Test(const char *bind1, SQLSMALLINT type1, const char *bind2, SQLSMALLINT type2)
{
	char sql[512];
	char *val = "test";
	SQLLEN ind = 4;
	int id = 1;

	SQLFreeStmt(Statement, SQL_RESET_PARAMS);

	++test_num;
	sprintf(sql, "insert into #test_output values (%s, %s)", bind1, bind2);

	success(2, SQLPrepare(Statement, (SQLCHAR *) sql, strlen(sql)));
	if (bind1[0] == '?')
		success(3, SQLBindParameter(Statement, id++, SQL_PARAM_INPUT, SQL_C_LONG, type1, 3, 0, &test_num, 0, &ind));
	if (bind2[0] == '?')
		success(4,
			SQLBindParameter(Statement, id++, SQL_PARAM_INPUT, SQL_C_CHAR, type2, strlen(val) + 1, 0, (SQLCHAR *) val,
					 0, &ind));
	success(5, SQLExecute(Statement));
}