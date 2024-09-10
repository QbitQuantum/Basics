static BOOL
test_driver_connect (TDSNCHOOSER *choose_t, char *connstr)
{
  HENV henv;
  HDBC hdbc;

#if (ODBCVER < 0x300)
  if (SQLAllocEnv (&henv) != SQL_SUCCESS)
#else
  if (SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv) != SQL_SUCCESS)
#endif
    {
      _iodbcdm_nativeerrorbox (choose_t->mainwnd,
	  henv, SQL_NULL_HDBC, SQL_NULL_HSTMT);
      return FALSE;
    }

#if (ODBCVER < 0x300)
  if (SQLAllocConnect (henv, &hdbc) != SQL_SUCCESS)
#else
  SQLSetEnvAttr (henv, SQL_ATTR_ODBC_VERSION,
      (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_UINTEGER);
  if (SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc) != SQL_SUCCESS)
#endif
    {
      _iodbcdm_nativeerrorbox (choose_t->mainwnd, henv, hdbc, SQL_NULL_HSTMT);
      SQLFreeEnv (henv);
      return FALSE;
    }

  SQLSetConfigMode (ODBC_BOTH_DSN);

  if (SQLDriverConnect (hdbc, choose_t->mainwnd, connstr, SQL_NTS,
          NULL, 0, NULL, SQL_DRIVER_PROMPT) != SQL_SUCCESS)
    {
      _iodbcdm_nativeerrorbox (choose_t->mainwnd, henv, hdbc, SQL_NULL_HSTMT);
      SQLFreeEnv (henv);
      return FALSE;
    }
  else
    {
      SQLDisconnect (hdbc);
    }

#if (ODBCVER < 0x300)
  SQLFreeConnect (hdbc);
  SQLFreeEnv (henv);
#else
  SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
  SQLFreeHandle (SQL_HANDLE_ENV, henv);
#endif

  return TRUE;
}