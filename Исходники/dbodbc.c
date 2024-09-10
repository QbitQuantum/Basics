void
getPrimaryKey(char *tname, int *part1, int *part2, int *part3, int *part4)
{
    char colname[COLNAMELEN];
    SQLLEN pcbValue;
    char *dot;

    *part1 = *part2 = *part3 = *part4 = 0;
    newStatement();
    stmt_text = "get primary key";
    debugStatement();
    dot = strchr(tname, '.');
    if(dot)
	*dot++ = 0;

    rc = SQLPrimaryKeys(hstmt,
       NULL, SQL_NTS,
       (dot ? tname : NULL), SQL_NTS, (dot ? dot : tname), SQL_NTS);
    if(dot)
	dot[-1] = '.';
    if(rc)
	goto abort;

/* bind column 4, the name of the key column */
    rc =
       SQLBindCol(hstmt, 4, SQL_CHAR, (SQLPOINTER) & colname, sizeof (colname),
       &pcbValue);
    if(rc)
	goto abort;

/* I'm only grabbing the first 4 columns in a multi-column key */
    rc = SQLFetch(hstmt);
    if(rc == SQL_NO_DATA)
	goto done;
    if(rc)
	goto abort;
    *part1 = findColByName(colname) + 1;

    rc = SQLFetch(hstmt);
    if(rc == SQL_NO_DATA)
	goto done;
    if(rc)
	goto abort;
    *part2 = findColByName(colname) + 1;

    rc = SQLFetch(hstmt);
    if(rc == SQL_NO_DATA)
	goto done;
    if(rc)
	goto abort;
    *part3 = findColByName(colname) + 1;

    rc = SQLFetch(hstmt);
    if(rc == SQL_NO_DATA)
	goto done;
    if(rc)
	goto abort;
    *part4 = findColByName(colname) + 1;

    goto done;

  abort:
    errorTrap(0);
  done:
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return;
}				/* getPrimaryKey */