int main(int argc, char **argv)
{
	int rc;
	HSTMT hstmt = SQL_NULL_HSTMT;
	SQLUSMALLINT info;

	test_connect();

	rc = SQLAllocHandle(SQL_HANDLE_STMT, conn, &hstmt);
	if (!SQL_SUCCEEDED(rc))
	{
		print_diag("failed to allocate stmt handle", SQL_HANDLE_DBC, conn);
		exit(1);
	}

	/*
	 * Print out the current SQL_CURSOR_COMMIT_BEHAVIOR and
	 * SQL_CURSOR_ROLLBACK settings. The result of this test case depends on
	 * those.
	 */
	rc = SQLGetInfo(conn, SQL_CURSOR_COMMIT_BEHAVIOR, &info, sizeof(info), NULL);
	CHECK_STMT_RESULT(rc, "SQLGetInfo failed", hstmt);
	printf("SQL_CURSOR_COMMIT_BEHAVIOR: %s\n", sql_commit_behavior_str(info));

	rc = SQLGetInfo(conn, SQL_CURSOR_ROLLBACK_BEHAVIOR, &info, sizeof(info), NULL);
	CHECK_STMT_RESULT(rc, "SQLGetInfo failed", hstmt);
	printf("SQL_CURSOR_ROLLBACK_BEHAVIOR: %s\n\n", sql_commit_behavior_str(info));

	/* Run three variations of the test */
	testLargeResult(hstmt, 0);
	testLargeResult(hstmt, 1);
	testLargeResult(hstmt, 2);

	/* Clean up */
	test_disconnect();

	return 0;
}