/* Open an ODBC connection to the database. */
int _connect_to_db(struct db_context_t *odbcc)
{
	SQLRETURN rc;

	/* Allocate connection handles. */
	pthread_mutex_lock(&db_source_mutex);
	rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, &odbcc->hdbc);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		LOG_ODBC_ERROR(SQL_HANDLE_DBC, odbcc->hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, odbcc->hdbc);
		return ERROR;
	}

	/* Open connection to the database. */
	rc = SQLConnect(odbcc->hdbc, servername, SQL_NTS,
			username, SQL_NTS, authentication, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		LOG_ODBC_ERROR(SQL_HANDLE_DBC, odbcc->hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, odbcc->hdbc);
		return ERROR;
	}

	rc = SQLSetConnectAttr(odbcc->hdbc, SQL_ATTR_AUTOCOMMIT,
			SQL_AUTOCOMMIT_OFF, 0);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return ERROR;
	}

	rc = SQLSetConnectAttr(odbcc->hdbc, SQL_ATTR_TXN_ISOLATION,
			(SQLPOINTER *) SQL_TXN_REPEATABLE_READ, 0);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return ERROR;
	}

	/* allocate statement handle */
	rc = SQLAllocHandle(SQL_HANDLE_STMT, odbcc->hdbc, &odbcc->hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return ERROR;
	}
	pthread_mutex_unlock(&db_source_mutex);

	return OK;
}