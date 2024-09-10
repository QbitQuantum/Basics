void ODBCHandler::listDrivers()
{
     SQLHENV env;
     SQLCHAR driver[256];
     //char attr[256];
     SQLCHAR attr[256];
     SQLSMALLINT driver_ret;
     SQLSMALLINT attr_ret;
     SQLUSMALLINT direction;
     SQLRETURN ret;

     SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
     SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

     direction = SQL_FETCH_FIRST;
     while(SQL_SUCCEEDED(ret = SQLDrivers(env, direction,
                          driver, sizeof(driver), &driver_ret,
                          attr, sizeof(attr), &attr_ret))) {
       direction = SQL_FETCH_NEXT;
       fprintf(stderr, "%s - %s\n", driver, attr);
       if (ret == SQL_SUCCESS_WITH_INFO) fprintf(stderr, "\tdata truncation\n");
     }
}