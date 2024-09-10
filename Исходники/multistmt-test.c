static void print_all_results(HSTMT hstmt)
{
	int i;
	int rc = SQL_SUCCESS;
	for (i = 1; rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO; i++)
	{
		printf("--%d ", i);
		print_result(hstmt);

		rc = SQLMoreResults(hstmt);
	}
	if (rc != SQL_NO_DATA)
		CHECK_STMT_RESULT(rc, "SQLMoreResults failed", hstmt);
}