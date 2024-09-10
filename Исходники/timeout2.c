int
main(int argc, char *argv[])
{
	SQLRETURN ret;
	int i;

	Connect();

	Command(Statement, "create table #timeout(i int)");
	Command(Statement, "insert into #timeout values(1)");

	for (i = 0; i < 2; ++i) {

		printf("Loop %d\n", i);

		CHK(SQLSetStmtAttr, (Statement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER) 10, SQL_IS_UINTEGER));

		CHK(SQLPrepare, (Statement, (SQLCHAR*) "select * from #timeout", SQL_NTS));
		CHK(SQLExecute, (Statement));

		do {
			while ((ret=SQLFetch(Statement)) == SQL_SUCCESS)
				;
			assert(ret == SQL_NO_DATA);
		} while ((ret = SQLMoreResults(Statement)) == SQL_SUCCESS);
		assert(ret == SQL_NO_DATA);

		if (i == 0) {
			printf("Sleep 15 seconds to test if timeout occurs\n");
			sleep(15);
		}

		SQLFreeStmt(Statement, SQL_CLOSE);
		SQLFreeStmt(Statement, SQL_UNBIND);
		SQLFreeStmt(Statement, SQL_RESET_PARAMS);
		SQLCloseCursor(Statement);
	}

	Disconnect();

	return 0;
}