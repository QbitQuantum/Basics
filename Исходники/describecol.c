int
main(int argc, char *argv[])
{
#define TEST_FILE "describecol.in"
    const char *in_file = FREETDS_SRCDIR "/" TEST_FILE;
    FILE *f;
    char buf[256];
    SQLINTEGER i;
    SQLLEN len;
    check_attr_t check_attr_p = check_attr_none;

    odbc_connect();
    odbc_command("SET TEXTSIZE 4096");

    SQLBindCol(odbc_stmt, 1, SQL_C_SLONG, &i, sizeof(i), &len);

    f = fopen(in_file, "r");
    if (!f)
        fopen(TEST_FILE, "r");
    if (!f) {
        fprintf(stderr, "error opening test file\n");
        exit(1);
    }

    line_num = 0;
    while (fgets(buf, sizeof(buf), f)) {
        char *p = buf, *cmd;

        ++line_num;

        while (isspace((unsigned char) *p))
            ++p;
        cmd = strtok(p, SEP);

        /* skip comments */
        if (!cmd || cmd[0] == '#' || cmd[0] == 0 || cmd[0] == '\n')
            continue;

        if (strcmp(cmd, "odbc") == 0) {
            int odbc3 = get_int(strtok(NULL, SEP)) == 3 ? 1 : 0;

            if (odbc_use_version3 != odbc3) {
                odbc_use_version3 = odbc3;
                odbc_disconnect();
                odbc_connect();
                odbc_command("SET TEXTSIZE 4096");
                SQLBindCol(odbc_stmt, 1, SQL_C_SLONG, &i, sizeof(i), &len);
            }
        }

        /* select type */
        if (strcmp(cmd, "select") == 0) {
            const char *type = strtok(NULL, SEP);
            const char *value = strtok(NULL, SEP);
            char sql[sizeof(buf) + 40];

            SQLMoreResults(odbc_stmt);
            odbc_reset_statement();

            sprintf(sql, "SELECT CONVERT(%s, %s) AS col", type, value);

            /* ignore error, we only need precision of known types */
            check_attr_p = check_attr_none;
            if (odbc_command_with_result(odbc_stmt, sql) != SQL_SUCCESS) {
                odbc_reset_statement();
                SQLBindCol(odbc_stmt, 1, SQL_C_SLONG, &i, sizeof(i), &len);
                continue;
            }

            CHKFetch("SI");
            SQLBindCol(odbc_stmt, 1, SQL_C_SLONG, &i, sizeof(i), &len);
            check_attr_p = check_attr_ird;
        }

        /* set attribute */
        if (strcmp(cmd, "set") == 0) {
            const struct attribute *attr = lookup_attr(strtok(NULL, SEP));
            char *value = strtok(NULL, SEP);
            SQLHDESC desc;
            SQLRETURN ret;
            SQLINTEGER ind;

            if (!value)
                fatal("Line %u: value not defined\n", line_num);

            /* get ARD */
            SQLGetStmtAttr(odbc_stmt, SQL_ATTR_APP_ROW_DESC, &desc, sizeof(desc), &ind);

            ret = SQL_ERROR;
            switch (attr->type) {
            case type_INTEGER:
                ret = SQLSetDescField(desc, 1, attr->value, int2ptr(lookup(value, attr->lookup)),
                                      sizeof(SQLINTEGER));
                break;
            case type_SMALLINT:
                ret = SQLSetDescField(desc, 1, attr->value, int2ptr(lookup(value, attr->lookup)),
                                      sizeof(SQLSMALLINT));
                break;
            case type_LEN:
                ret = SQLSetDescField(desc, 1, attr->value, int2ptr(lookup(value, attr->lookup)),
                                      sizeof(SQLLEN));
                break;
            case type_CHARP:
                ret = SQLSetDescField(desc, 1, attr->value, (SQLPOINTER) value, SQL_NTS);
                break;
            }
            if (!SQL_SUCCEEDED(ret))
                fatal("Line %u: failure not expected setting ARD attribute\n", line_num);
            check_attr_p = check_attr_ard;
        }

        /* test attribute */
        if (strcmp(cmd, "attr") == 0) {
            const struct attribute *attr = lookup_attr(strtok(NULL, SEP));
            char *expected = strtok(NULL, SEP);

            if (!expected)
                fatal("Line %u: value not defined\n", line_num);

            check_attr_p(attr, expected);
        }
    }

    fclose(f);
    odbc_disconnect();

    printf("Done.\n");
    return g_result;
}