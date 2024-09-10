/*************************************************************************
 *
 *	Function: sql_select_query
 *
 *	Purpose: Issue a select query to the database
 *
 *************************************************************************/
static int sql_select_query(rlm_sql_handle_t *handle, rlm_sql_config_t *config, char *querystr) {
	rlm_sql_unixodbc_conn_t *conn = handle->conn;
	SQLINTEGER column;
	SQLLEN len;
	int numfields;
	int state;

	/* Only state = 0 means success */
	if ((state = sql_query(handle, config, querystr))) {
		return state;
	}

	numfields=sql_num_fields(handle, config);
	if (numfields < 0) {
		return -1;
	}

	/* Reserving memory for result */
	conn->row = (char **) rad_malloc((numfields+1)*sizeof(char *));
	conn->row[numfields] = NULL;

	for(column = 1; column <= numfields; column++) {
		SQLColAttributes(conn->statement,((SQLUSMALLINT) column),SQL_COLUMN_LENGTH,NULL,0,NULL,&len);
		conn->row[column-1] = (char*)rad_malloc((int)++len);
		SQLBindCol(conn->statement, column, SQL_C_CHAR, (SQLCHAR *)conn->row[column-1], len, NULL);
	}
	return 0;
}