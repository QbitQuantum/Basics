/*
** Sets the auto commit mode
*/
static int conn_setautocommit (lua_State *L) {
	conn_data *conn = (conn_data *) getconnection (L);
	SQLRETURN ret;
	if (lua_toboolean (L, 2)) {
		ret = SQLSetConnectAttr(conn->hdbc, SQL_ATTR_AUTOCOMMIT,
			(SQLPOINTER) SQL_AUTOCOMMIT_ON, 0);
	} else {
		ret = SQLSetConnectAttr(conn->hdbc, SQL_ATTR_AUTOCOMMIT,
			(SQLPOINTER) SQL_AUTOCOMMIT_OFF, 0);
	}
	if (error(ret))
		return fail(L, hSTMT, conn->hdbc);
	else
		return pass(L);
}