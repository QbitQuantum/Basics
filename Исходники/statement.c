int dbd_db2_statement_create(lua_State *L, connection_t *conn, const char *sql_query) { 
    SQLRETURN rc = SQL_SUCCESS;
    statement_t *statement = NULL;
    SQLHANDLE stmt;

    SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
    SQLCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
    SQLINTEGER sqlcode;
    SQLSMALLINT length;	

    rc = SQLAllocHandle(SQL_HANDLE_STMT, conn->db2, &stmt);
    if (rc != SQL_SUCCESS) {
	SQLGetDiagRec(SQL_HANDLE_DBC, conn->db2, 1, sqlstate, &sqlcode, message, SQL_MAX_MESSAGE_LENGTH + 1, &length);

        lua_pushnil(L);
        lua_pushfstring(L, DBI_ERR_ALLOC_STATEMENT, message);
        return 2;
    }

    /*
     * turn off deferred prepare
     * statements will be sent to the server at prepare time,
     * and therefore we can catch errors now rather 
     * than at execute time
     */
    rc = SQLSetStmtAttr(stmt,SQL_ATTR_DEFERRED_PREPARE,(SQLPOINTER)SQL_DEFERRED_PREPARE_OFF,0);

    rc = SQLPrepare(stmt, (SQLCHAR *)sql_query, SQL_NTS);
    if (rc != SQL_SUCCESS) {
	SQLGetDiagRec(SQL_HANDLE_STMT, stmt, 1, sqlstate, &sqlcode, message, SQL_MAX_MESSAGE_LENGTH + 1, &length);

	lua_pushnil(L);
	lua_pushfstring(L, DBI_ERR_PREP_STATEMENT, message);
	return 2;
    }

    statement = (statement_t *)lua_newuserdata(L, sizeof(statement_t));
    statement->stmt = stmt;
    statement->db2 = conn->db2;
    statement->resultset = NULL;
    statement->bind = NULL;

    luaL_getmetatable(L, DBD_DB2_STATEMENT);
    lua_setmetatable(L, -2);

    return 1;
} 