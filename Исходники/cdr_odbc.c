static int odbc_log(struct ast_cdr *cdr)
{
    struct odbc_obj *obj = ast_odbc_request_obj(dsn, 0);
    SQLHSTMT stmt;

    if (!obj) {
        ast_log(LOG_ERROR, "Unable to retrieve database handle.  CDR failed.\n");
        return -1;
    }

    stmt = ast_odbc_direct_execute(obj, execute_cb, cdr);
    if (stmt) {
        SQLLEN rows = 0;

        SQLRowCount(stmt, &rows);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);

        if (rows == 0)
            ast_log(LOG_WARNING, "CDR successfully ran, but inserted 0 rows?\n");
    } else
        ast_log(LOG_ERROR, "CDR direct execute failed\n");
    ast_odbc_release_obj(obj);
    return 0;
}