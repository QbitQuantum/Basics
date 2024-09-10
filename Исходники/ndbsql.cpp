static int
do_connect(Con& con)
{
  int ret;

  // allocate an environment handle
  ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &con.henv);
  if (ret != SQL_SUCCESS)
    return -1;
  
  // set odbc version (required)
  ret = SQLSetEnvAttr(con.henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0); 
  if (ret != SQL_SUCCESS)
    return -1;
  
  // allocate a connection handle
  ret = SQLAllocHandle(SQL_HANDLE_DBC, con.henv, &con.hdbc);
  if (ret != SQL_SUCCESS)
    return -1;
  
  // connect to database
  SQLCHAR szConnStrOut[256];
  SQLSMALLINT cbConnStrOut;
  ret = SQLDriverConnect(con.hdbc, 0, (SQLCHAR*)con.dsn, SQL_NTS,
      szConnStrOut, sizeof(szConnStrOut), &cbConnStrOut, SQL_DRIVER_COMPLETE);
  if (ret != SQL_SUCCESS) {
    ndbout << "Connection failure: Could not connect to database" << endl;
    print_err(SQL_HANDLE_DBC, con.hdbc);
    return -1;
  }  

  return 0;
}