/*************************************************************************
 *
 *	Function: sql_affected_rows
 *
 *	Purpose: Return the number of rows affected by the last query.
 *
 *************************************************************************/
static int sql_affected_rows(SQLSOCK * sqlsocket, SQL_CONFIG *config)
{
    SQLINTEGER c;
    rlm_sql_db2_sock *sock;

    sock = sqlsocket->conn;

    SQLRowCount(sock->stmt, &c);
    return c;
}