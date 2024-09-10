/*************************************************************************
 *
 *	Function: sql_select_query
 *
 *	Purpose: Issue a select query to the database
 *
 *************************************************************************/
static sql_rcode_t sql_select_query(rlm_sql_handle_t *handle, rlm_sql_config_t *config, char const *query) {

	int numfields = 0;
	int i = 0;
	char **row = NULL;
	long len = 0;
	rlm_sql_iodbc_conn_t *conn = handle->conn;

	if(sql_query(handle, config, query) < 0) {
		return -1;
	}

	numfields = sql_num_fields(handle, config);

	row = (char **) rad_malloc(sizeof(char *) * (numfields+1));
	memset(row, 0, (sizeof(char *) * (numfields)));
	row[numfields] = NULL;

	for(i=1; i<=numfields; i++) {
		SQLColAttributes(conn->stmt_handle, ((SQLUSMALLINT) i), SQL_COLUMN_LENGTH, NULL, 0, NULL, &len);
		len++;

		/*
		 * Allocate space for each column
		 */
		row[i - 1] = rad_malloc((size_t) len);

		/*
		 * This makes me feel dirty, but, according to Microsoft, it works.
		 * Any ODBC datatype can be converted to a 'char *' according to
		 * the following:
		 *
		 * http://msdn.microsoft.com/library/psdk/dasdk/odap4o4z.htm
		 */
		SQLBindCol(conn->stmt_handle, i, SQL_C_CHAR, (SQLCHAR *)row[i-1], len, 0);
	}

	conn->row = row;

	return 0;
}