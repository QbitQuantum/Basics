static SQLHSTMT generic_prepare(struct odbc_obj *obj, void *data)
{
	struct generic_prepare_struct *gps = data;
	SQLHSTMT stmt;
	int res;

	res = SQLAllocHandle(SQL_HANDLE_STMT, obj->con, &stmt);
	if ((res != SQL_SUCCESS) && (res != SQL_SUCCESS_WITH_INFO)) {
		ast_log(LOG_WARNING, "SQL Alloc Handle failed!\n");
		return NULL;
	}

	res = SQLPrepare(stmt, (unsigned char *)gps->sql, SQL_NTS);
	if ((res != SQL_SUCCESS) && (res != SQL_SUCCESS_WITH_INFO)) {
		ast_log(LOG_WARNING, "SQL Prepare failed![%s]\n", (char *)gps->sql);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return NULL;
	}

	if (!ast_strlen_zero(gps->param))
		SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(gps->param), 0, (void *)gps->param, 0, NULL);

	return stmt;
}