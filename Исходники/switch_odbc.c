static int db_is_up(switch_odbc_handle_t *handle)
{
	int ret = 0;
	SQLHSTMT stmt = NULL;
	SQLLEN m = 0;
	int result;
	switch_event_t *event;
	switch_odbc_status_t recon = 0;
	char *err_str = NULL;
	SQLCHAR sql[255] = "";
	int max_tries = DEFAULT_ODBC_RETRIES;
	int code = 0;
	SQLRETURN rc;
	SQLSMALLINT nresultcols;


	if (handle) {
		max_tries = handle->num_retries;
		if (max_tries < 1)
			max_tries = DEFAULT_ODBC_RETRIES;
	}

  top:

	if (!handle) {
		switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_CRIT, "No DB Handle\n");
		goto done;
	}

	if (handle->is_oracle) {
		strcpy((char *) sql, "select 1 from dual");
	} else if (handle->is_firebird) {
		strcpy((char *) sql, "select first 1 * from RDB$RELATIONS");
	} else {
		strcpy((char *) sql, "select 1");
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, handle->con, &stmt) != SQL_SUCCESS) {
		code = __LINE__;
		goto error;
	}

	SQLSetStmtAttr(stmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)30, 0);

	if (SQLPrepare(stmt, sql, SQL_NTS) != SQL_SUCCESS) {
		code = __LINE__;
		goto error;
	}

	result = SQLExecute(stmt);

	if (result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO) {
		code = __LINE__;
		goto error;
	}

	SQLRowCount(stmt, &m);
	rc = SQLNumResultCols(stmt, &nresultcols);
	if (rc != SQL_SUCCESS) {
		code = __LINE__;
		goto error;
	}
	ret = (int) nresultcols;
	/* determine statement type */
	if (nresultcols <= 0) {
		/* statement is not a select statement */
		code = __LINE__;
		goto error;
	}

	goto done;

  error:
	err_str = switch_odbc_handle_get_error(handle, stmt);

	/* Make sure to free the handle before we try to reconnect */
	if (stmt) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		stmt = NULL;
	}

	recon = switch_odbc_handle_connect(handle);

	max_tries--;

	if (switch_event_create(&event, SWITCH_EVENT_TRAP) == SWITCH_STATUS_SUCCESS) {
		switch_event_add_header(event, SWITCH_STACK_BOTTOM, "Failure-Message", "The sql server is not responding for DSN %s [%s][%d]",
								switch_str_nil(handle->dsn), switch_str_nil(err_str), code);
		switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_CRIT, "The sql server is not responding for DSN %s [%s][%d]\n",
						  switch_str_nil(handle->dsn), switch_str_nil(err_str), code);

		if (recon == SWITCH_ODBC_SUCCESS) {
			switch_event_add_header(event, SWITCH_STACK_BOTTOM, "Additional-Info", "The connection has been re-established");
			switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "The connection has been re-established\n");
		} else {
			switch_event_add_header(event, SWITCH_STACK_BOTTOM, "Additional-Info", "The connection could not be re-established");
			switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_CRIT, "The connection could not be re-established\n");
		}
		if (!max_tries) {
			switch_event_add_header(event, SWITCH_STACK_BOTTOM, "Additional-Info", "Giving up!");
			switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_CRIT, "Giving up!\n");
		}

		switch_event_fire(&event);
	}

	if (!max_tries) {
		goto done;
	}

	switch_safe_free(err_str);
	switch_yield(1000000);
	goto top;

  done:

	switch_safe_free(err_str);

	if (stmt) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	}

	return ret;
}