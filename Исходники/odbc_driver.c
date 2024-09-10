static int odbc_handle_preparer(pdo_dbh_t *dbh, const char *sql, size_t sql_len, pdo_stmt_t *stmt, zval *driver_options)
{
	RETCODE rc;
	pdo_odbc_db_handle *H = (pdo_odbc_db_handle *)dbh->driver_data;
	pdo_odbc_stmt *S = ecalloc(1, sizeof(*S));
	enum pdo_cursor_type cursor_type = PDO_CURSOR_FWDONLY;
	int ret;
	char *nsql = NULL;
	size_t nsql_len = 0;

	S->H = H;
	S->assume_utf8 = H->assume_utf8;

	/* before we prepare, we need to peek at the query; if it uses named parameters,
	 * we want PDO to rewrite them for us */
	stmt->supports_placeholders = PDO_PLACEHOLDER_POSITIONAL;
	ret = pdo_parse_params(stmt, (char*)sql, sql_len, &nsql, &nsql_len);

	if (ret == 1) {
		/* query was re-written */
		sql = nsql;
	} else if (ret == -1) {
		/* couldn't grok it */
		strcpy(dbh->error_code, stmt->error_code);
		efree(S);
		return 0;
	}

	rc = SQLAllocHandle(SQL_HANDLE_STMT, H->dbc, &S->stmt);

	if (rc == SQL_INVALID_HANDLE || rc == SQL_ERROR) {
		efree(S);
		if (nsql) {
			efree(nsql);
		}
		pdo_odbc_drv_error("SQLAllocStmt");
		return 0;
	}

	cursor_type = pdo_attr_lval(driver_options, PDO_ATTR_CURSOR, PDO_CURSOR_FWDONLY);
	if (cursor_type != PDO_CURSOR_FWDONLY) {
		rc = SQLSetStmtAttr(S->stmt, SQL_ATTR_CURSOR_SCROLLABLE, (void*)SQL_SCROLLABLE, 0);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
			pdo_odbc_stmt_error("SQLSetStmtAttr: SQL_ATTR_CURSOR_SCROLLABLE");
			SQLFreeHandle(SQL_HANDLE_STMT, S->stmt);
			if (nsql) {
				efree(nsql);
			}
			return 0;
		}
	}

	rc = SQLPrepare(S->stmt, (char*)sql, SQL_NTS);
	if (nsql) {
		efree(nsql);
	}

	stmt->driver_data = S;
	stmt->methods = &odbc_stmt_methods;

	if (rc != SQL_SUCCESS) {
		pdo_odbc_stmt_error("SQLPrepare");
        if (rc != SQL_SUCCESS_WITH_INFO) {
            /* clone error information into the db handle */
            strcpy(H->einfo.last_err_msg, S->einfo.last_err_msg);
            H->einfo.file = S->einfo.file;
            H->einfo.line = S->einfo.line;
            H->einfo.what = S->einfo.what;
            strcpy(dbh->error_code, stmt->error_code);
        }
	}

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		return 0;
	}
	return 1;
}