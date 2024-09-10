static int odbc_stmt_next_rowset(pdo_stmt_t *stmt)
{
	SQLRETURN rc;
	SQLSMALLINT colcount;
	pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;

	/* NOTE: can't guarantee that output or input/output parameters
	 * are set until this fella returns SQL_NO_DATA, according to
	 * MSDN ODBC docs */
	rc = SQLMoreResults(S->stmt);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		return 0;
	}

	free_cols(stmt, S);
	/* how many columns do we have ? */
	SQLNumResultCols(S->stmt, &colcount);
	stmt->column_count = (int)colcount;
	S->cols = ecalloc(colcount, sizeof(pdo_odbc_column));
	S->going_long = 0;

	return 1;
}