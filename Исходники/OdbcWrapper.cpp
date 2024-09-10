bool OdbcWrapper::connect(const char *server, const char *user, const char *password, const char *dbname,
                          const char *charset) {

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlenvhandle)) {
        close();
        return false;
    }
    if (SQL_SUCCESS != SQLSetEnvAttr(sqlenvhandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
        close();
        return false;
    }
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlenvhandle, &sqlconnectionhandle)) {
        close();
        return false;
    }

    SQLCHAR retconstring[1024];
    char addr[1024] = {0};
    sprintf(addr, "DRIVER={SQL Server};SERVER=%s;DATABASE=%s;UID=%s;PWD=%s;",server,dbname,user,password);
    switch (SQLDriverConnectA(sqlconnectionhandle,
                              NULL,
                              (SQLCHAR*) addr,
                              SQL_NTS,
                              retconstring,
                              1024,
                              NULL,
                              SQL_DRIVER_NOPROMPT)) {
        case SQL_SUCCESS_WITH_INFO:
            get_error(SQL_HANDLE_DBC, sqlconnectionhandle);
            break;
        case SQL_INVALID_HANDLE:
        case SQL_ERROR:
            get_error(SQL_HANDLE_DBC, sqlconnectionhandle);
            close();
            return false;
        default:
            break;
    }
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle)) {
        close();
        return false;
    }
    return true;
}