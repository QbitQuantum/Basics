int db__driver_drop_table(dbString * name)
{
    char cmd[200];
    cursor *c;
    SQLRETURN ret;
    char msg[OD_MSG];
    char *emsg = NULL;
    SQLINTEGER err;
    SQLCHAR ttype[50], *tname;
    SQLINTEGER nrow = 0;


    /* allocate cursor */
    c = alloc_cursor();
    if (c == NULL)
	return DB_FAILED;

    tname = db_get_string(name);

    ret = SQLTables(c->stmt, NULL, 0, NULL, 0, tname, sizeof(tname), NULL, 0);
    if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
	report_error("SQLTables()");
	return DB_FAILED;
    }

    /* Get number of rows */
    ret = SQLRowCount(c->stmt, &nrow);
    if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
	report_error("SQLRowCount()");
	return DB_FAILED;
    }

    if (nrow == 0) {
	G_asprintf(&emsg, "Table %s doesn't exist\n", tname);
	report_error(emsg);
	G_free(emsg);

	return DB_FAILED;
    }

    ret = SQLFetchScroll(c->stmt, SQL_FETCH_NEXT, 0);
    ret = SQLGetData(c->stmt, 4, SQL_C_CHAR, ttype, sizeof(ttype), NULL);

    if (strcmp(ttype, "TABLE") == 0) {
	sprintf(cmd, "DROP TABLE %s", tname);
    }
    else if (strcmp(ttype, "VIEW") == 0) {
	sprintf(cmd, "DROP VIEW %s", tname);
    }
    else {
	G_asprintf(&emsg, "Table %s isn't 'TABLE' or 'VIEW' but %s\n", tname,
		   ttype);
	report_error(emsg);
	G_free(emsg);

	return DB_FAILED;
    }

    SQLCloseCursor(c->stmt);

    ret = SQLExecDirect(c->stmt, cmd, SQL_NTS);
    if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
	SQLGetDiagRec(SQL_HANDLE_STMT, c->stmt, 1, NULL, &err, msg,
		      sizeof(msg), NULL);
	G_asprintf(&emsg, "SQLExecDirect():\n%s\n%s (%d)\n", cmd, msg,
		   (int)err);
	report_error(emsg);
	G_free(emsg);

	return DB_FAILED;
    }

    free_cursor(c);

    return DB_OK;
}