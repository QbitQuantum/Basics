int
main (int ac, char *av[])
{
  SQLRETURN rc;

  if (ac < 3)
    {
      err_printf ("***FAILED: usage : %s dsn uid pwd\n", av[0]);
      return (-1);
    }
  dsn = av[1];
  uid = av[2];
  pwd = av[3];
  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, (SQLHANDLE *) & henv);
  if (rc != SQL_SUCCESS)
    {
      err_printf ("SQLAllocHandle() failed.\n");
      return 1;
    }

  rc = SQLSetEnvAttr (henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3,
      SQL_IS_INTEGER);
  if (rc != SQL_SUCCESS)
    {
      err_printf ("SQLSetEnvAttr() failed.\n");
      return 1;
    }

  rc = SQLAllocHandle (SQL_HANDLE_DBC, (SQLHANDLE) henv,
      (SQLHANDLE *) & hdbc);
  if (rc != SQL_SUCCESS)
    {
      err_printf ("SQLAllocHandle() failed.\n");
      return 1;
    }

  rc = SQLConnect (hdbc, dsn, SQL_NTS, uid, SQL_NTS, pwd, SQL_NTS);
  if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
    {
      err_printf ("SQLConnect() failed.\n");
      error (SQL_HANDLE_DBC, (SQLHANDLE) hdbc);
      return 1;
    }
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, 0);
  if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
    {
      err_printf ("autocommit off() failed.\n");
      error (SQL_HANDLE_DBC, (SQLHANDLE) hdbc);
      return 1;
    }

  create_proc ();

  printf ("=====================================================\n");
  printf ("starting test\n");
  test ();
  printf ("test1 done\n");
  printf ("=====================================================\n");
  return 0;
}