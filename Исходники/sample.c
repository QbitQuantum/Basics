/**
 * Displays error message and prepare for program exit.
 */
int barf(SQLHENV c, char* failMsg) {
    char sqlhmsg[200], sqlhstat[10];
    SQLSMALLINT junksmall;
    SQLINTEGER errint;

    SQLGetDiagRec(SQL_HANDLE_DBC, c, 1, sqlhstat, &errint,
            sqlhmsg, 100, &junksmall);
    return print2_ret(failMsg, sqlhmsg, 1);
}