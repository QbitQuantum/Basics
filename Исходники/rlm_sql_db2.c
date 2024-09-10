/*************************************************************************
 *
 *	Function: sql_affected_rows
 *
 *	Purpose: Return the number of rows affected by the last query.
 *
 *************************************************************************/
static int sql_affected_rows(rlm_sql_handle_t *handle, UNUSED rlm_sql_config_t *config)
{
	SQLINTEGER c;
	rlm_sql_db2_conn_t *conn = handle->conn;

	SQLRowCount(conn->stmt, &c);
	
	return c;
}