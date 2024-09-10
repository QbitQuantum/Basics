int
main (int argc, char *argv[])
{
  if (argc < 4)
    {
      fprintf (stderr,
	  "ERR : called as setcurs <dsn> <uid> <pwd> [<scroll>=1]\n");
      exit (-3);
    }
  rc = SQLAllocEnv (&henv);
  if (rc != SQL_SUCCESS)
    {
      fprintf (stderr, "ERR : cannot alloc ODBC environment\n");
      exit (-3);
    }
  rc = SQLAllocConnect (henv, &hdbc);
  CHK_ERR (SQL_NULL_HSTMT);
  rc = SQLConnect (hdbc, argv[1], SQL_NTS, argv[2], SQL_NTS, argv[3],
      SQL_NTS);
  CHK_ERR (SQL_NULL_HSTMT);
  /* Allocate the statements and set the cursor name. */

  rc = SQLAllocStmt (hdbc, &hstmtSelect);
  CHK_ERR (SQL_NULL_HSTMT);
  rc = SQLAllocStmt (hdbc, &hstmtUpdate);
  CHK_ERR (SQL_NULL_HSTMT);
  if (argc <= 4 || atoi (argv[4]) != 0)
    {
      rc = SQLSetStmtOption (hstmtSelect, SQL_CURSOR_TYPE, SQL_CURSOR_STATIC);
      CHK_ERR (hstmtSelect);
      rc = SQLSetScrollOptions (hstmtSelect, SQL_CONCUR_READ_ONLY, 1, 1);
      CHK_ERR (hstmtSelect);
    }
  rc = SQLSetCursorName (hstmtSelect, "C1", SQL_NTS);
  CHK_ERR (hstmtSelect);

  /* SELECT the result set and bind its columns to local buffers. */

  rc = SQLExecDirect (hstmtSelect, "SELECT NAME,PHONE from GOGO", SQL_NTS);
  CHK_ERR (hstmtSelect);
  rc = SQLBindCol (hstmtSelect, 1, SQL_C_CHAR, szName, NAME_LEN, &cbName);
  CHK_ERR (hstmtSelect);
  rc = SQLBindCol (hstmtSelect, 2, SQL_C_CHAR, szPhone, PHONE_LEN, &cbPhone);
  CHK_ERR (hstmtSelect);

  /* Read through the result set until the cursor is */
  /* positioned on the row for John Smith. */

  do
    retcode = SQLFetch (hstmtSelect);
  while ((retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) &&
      (strcmp (szName, "Smith, John") != 0));
  rc = retcode;
  CHK_ERR (hstmtSelect);
  /* Perform a positioned update of John Smith's name. */

  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
      rc = SQLExecDirect (hstmtUpdate,
	  "UPDATE GOGO SET PHONE='2064890154' WHERE CURRENT OF C1", SQL_NTS);
      CHK_ERR (hstmtUpdate);
    }
#if 0
  SQLFreeStmt (hstmtUpdate, SQL_DROP);
  SQLFreeStmt (hstmtSelect, SQL_DROP);
  SQLDisconnect (hdbc);
  SQLFreeConnect (hdbc);
#endif
  printf ("PASSED: SetCursorName Test\n");
  exit (0);
}