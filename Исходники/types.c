/**
  Internal function to test sending a SQL_NUMERIC_STRUCT value.

  @todo Printing some additional output (sqlnum->val as hex, dec)

  @param[in]  hstmt       Statement handle
  @param[in]  numdata     Numeric data
  @param[in]  prec        Precision to send
  @param[in]  scale       Scale to send
  @param[in]  sign        Sign (1=+,0=-)
  @param[in]  outstr      Expected result string
  @param[in]  exptrunc    Expected truncation failure
  @return OK/FAIL just like a test.
*/
int sqlnum_test_to_str(SQLHANDLE Stmt, SQLCHAR *numdata, SQLCHAR prec,
                       SQLSCHAR scale, SQLCHAR sign, char *outstr,
                       char *exptrunc)
{
  SQL_NUMERIC_STRUCT *sqlnum= malloc(sizeof(SQL_NUMERIC_STRUCT));
  SQLCHAR obuf[30];
  SQLRETURN exprc= SQL_SUCCESS;

  /* TODO until sqlnum errors are supported */
  /*
  if (!strcmp("01S07", exptrunc))
    exprc= SQL_SUCCESS_WITH_INFO;
  else if (!strcmp("22003", exptrunc))
    exprc= SQL_ERROR;
  */

  sqlnum->sign= sign;
  memcpy(sqlnum->val, numdata, SQL_MAX_NUMERIC_LEN);

  CHECK_HANDLE_RC(SQL_HANDLE_STMT, Stmt, SQLBindParameter(Stmt, 1, SQL_PARAM_INPUT, SQL_C_NUMERIC,
                                  SQL_DECIMAL, prec, scale, sqlnum, 0, NULL));

  OK_SIMPLE_STMT(Stmt, "select ?");

  exprc= SQLFetch(Stmt);
  if (exprc != SQL_SUCCESS)
  {
    IS(check_sqlstate(Stmt, (char *)exptrunc) == OK);
  }
  if (exprc == SQL_ERROR)
    return OK;
  is_num(sqlnum->precision, prec);
  is_num(sqlnum->scale, scale);
  is_num(sqlnum->sign, sign);
  CHECK_HANDLE_RC(SQL_HANDLE_STMT, Stmt, SQLGetData(Stmt, 1, SQL_C_CHAR, obuf, sizeof(obuf), NULL));
  diag("compare %s - %s", obuf, outstr);
  IS_STR(obuf, outstr, strlen(outstr));
  FAIL_IF(memcmp(sqlnum->val, numdata, SQL_MAX_NUMERIC_LEN), "memcmp failed");

  CHECK_HANDLE_RC(SQL_HANDLE_STMT, Stmt, SQLFreeStmt(Stmt, SQL_CLOSE));

  free(sqlnum);
  return OK;
}