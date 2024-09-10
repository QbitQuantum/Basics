static int
TestOutput(const char *type, const char *value_to_convert, SQLSMALLINT out_c_type, SQLSMALLINT out_sql_type, const char *expected)
{
    char sbuf[1024];
    unsigned char out_buf[256];
    SQLLEN out_len = 0;
    const char *sep;

    odbc_reset_statement();

    /* build store procedure to test */
    odbc_command("IF OBJECT_ID('spTestProc') IS NOT NULL DROP PROC spTestProc");
    sep = "'";
    if (strncmp(value_to_convert, "0x", 2) == 0)
        sep = "";
    sprintf(sbuf, "CREATE PROC spTestProc @i %s OUTPUT AS SELECT @i = CONVERT(%s, %s%s%s)", type, type, sep, value_to_convert, sep);
    odbc_command(sbuf);
    memset(out_buf, 0, sizeof(out_buf));

    if (use_cursors) {
        odbc_reset_statement();
        CHKSetStmtAttr(SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER) SQL_SCROLLABLE, 0, "S");
        CHKSetStmtAttr(SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) SQL_CURSOR_DYNAMIC, 0, "S");
    }

    /* bind parameter */
    if (exec_direct) {
        CHKBindParameter(1, SQL_PARAM_OUTPUT, out_c_type, out_sql_type, precision, 0, out_buf,
                         sizeof(out_buf), &out_len, "S");

        /* call store procedure */
        CHKExecDirect(T("{call spTestProc(?)}"), SQL_NTS, "S");
    } else {
        if (prepare_before)
            CHKPrepare(T("{call spTestProc(?)}"), SQL_NTS, "S");

        CHKBindParameter(1, SQL_PARAM_OUTPUT, out_c_type, out_sql_type, precision, 0, out_buf,
                         sizeof(out_buf), &out_len, "S");

        if (!prepare_before)
            CHKPrepare(T("{call spTestProc(?)}"), SQL_NTS, "S");

        CHKExecute("S");
    }

    /*
     * MS OBDC requires it cause first recordset is a recordset with a
     * warning caused by the way it execute RPC (via EXEC statement)
     */
    if (use_cursors && !odbc_driver_is_freetds())
        SQLMoreResults(odbc_stmt);

    /* test results */
    odbc_c2string(sbuf, out_c_type, out_buf, out_len);

    if (strcmp(sbuf, expected) != 0) {
        if (only_test) {
            odbc_command("drop proc spTestProc");
            ODBC_FREE();
            return 1;
        }
        fprintf(stderr, "Wrong result\n  Got: %s\n  Expected: %s\n", sbuf, expected);
        exit(1);
    }
    only_test = 0;
    odbc_command("drop proc spTestProc");
    ODBC_FREE();
    return 0;
}