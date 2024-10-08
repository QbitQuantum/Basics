int main(int argc, char **argv)
{
	int rc;
	HSTMT hstmt = SQL_NULL_HSTMT;
	int			i;
	SQLINTEGER	colvalue;
	SQLLEN		indColvalue;

	test_connect();

	rc = SQLAllocHandle(SQL_HANDLE_STMT, conn, &hstmt);
	if (!SQL_SUCCEEDED(rc))
	{
		print_diag("failed to allocate stmt handle", SQL_HANDLE_DBC, conn);
		exit(1);
	}

	/*
	 * Initialize a table with some test data.
	 */
	printf("Creating test table pos_update_test\n");
	rc = SQLExecDirect(hstmt, (SQLCHAR *) "CREATE TEMPORARY TABLE pos_update_test(i int4, orig int4)", SQL_NTS);
	CHECK_STMT_RESULT(rc, "SQLExecDirect failed", hstmt);
	rc = SQLExecDirect(hstmt, (SQLCHAR *) "INSERT INTO pos_update_test SELECT g, g FROM generate_series(1, 10) g", SQL_NTS);
	CHECK_STMT_RESULT(rc, "SQLExecDirect failed", hstmt);

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	CHECK_STMT_RESULT(rc, "SQLFreeStmt failed", hstmt);

	printf("Opening a cursor for update, and fetching 10 rows\n");

	rc  = SQLSetStmtAttr(hstmt, SQL_ATTR_CONCURRENCY,
						 (SQLPOINTER) SQL_CONCUR_ROWVER, 0);
	CHECK_STMT_RESULT(rc, "SQLSetStmtAttr failed", hstmt);
	rc = SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_TYPE,
						(SQLPOINTER) SQL_CURSOR_KEYSET_DRIVEN, 0);
	CHECK_STMT_RESULT(rc, "SQLSetStmtAttr failed", hstmt);

	rc = SQLBindCol(hstmt, 1, SQL_C_LONG, &colvalue, 0, &indColvalue);
	CHECK_STMT_RESULT(rc, "SQLBindCol failed", hstmt);

	rc = SQLExecDirect(hstmt, (SQLCHAR *) "SELECT * FROM pos_update_test ORDER BY orig", SQL_NTS);
	CHECK_STMT_RESULT(rc, "SQLExecDirect failed", hstmt);

	for (i = 0; i < 5; i++)
	{
		rc = SQLFetch(hstmt);
		if (rc == SQL_NO_DATA)
			break;
		if (rc == SQL_SUCCESS)
		{
			char buf[40];
			int col;
			SQLLEN ind;

			for (col = 1; col <= 2; col++)
			{
				rc = SQLGetData(hstmt, col, SQL_C_CHAR, buf, sizeof(buf), &ind);
				if (!SQL_SUCCEEDED(rc))
				{
					print_diag("SQLGetData failed", SQL_HANDLE_STMT, hstmt);
					exit(1);
				}
				if (ind == SQL_NULL_DATA)
					strcpy(buf, "NULL");
				printf("%s%s", (col > 1) ? "\t" : "", buf);
			}
			printf("\n");
		}
		else
		{
			print_diag("SQLFetch failed", SQL_HANDLE_STMT, hstmt);
			exit(1);
		}
	}

	/* Do a positioned update and delete */
	printf("Updating result set\n");
	colvalue += 100;
	rc = SQLSetPos(hstmt, 1, SQL_UPDATE, SQL_LOCK_NO_CHANGE);
	CHECK_STMT_RESULT(rc, "SQLSetPos failed", hstmt);

	rc = SQLFetch(hstmt);
	CHECK_STMT_RESULT(rc, "SQLFetch failed", hstmt);

	rc = SQLSetPos(hstmt, 1, SQL_DELETE, SQL_LOCK_NO_CHANGE);
	CHECK_STMT_RESULT(rc, "SQLSetPos failed", hstmt);

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	CHECK_STMT_RESULT(rc, "SQLFreeStmt failed", hstmt);

	/* See if the update took effect */
	rc = SQLExecDirect(hstmt, (SQLCHAR *) "SELECT * FROM pos_update_test ORDER BY orig", SQL_NTS);
	CHECK_STMT_RESULT(rc, "SQLExecDirect failed", hstmt);
	print_result(hstmt);

	/* Clean up */
	test_disconnect();

	return 0;
}