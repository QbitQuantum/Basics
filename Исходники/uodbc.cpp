SQLRETURN DataBase::connectExcel(const char *filename, int nTimeout)
{
    SQLRETURN status;

    //SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_hEnv);
    //SQLSetEnvAttr(_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, _hEnv, &_hConn);

    setLoginTimeout(nTimeout);

    char tmpStr[1024];
    sprintf(tmpStr, "Driver={Microsoft Excel Driver (*.xls)}; DBQ=%s; DriverID=790", filename);
    char maxStr[MAX_CONNECT_LEN];
    SQLSMALLINT returnSize;
    status = SQLDriverConnect(_hConn, NULL, (SQLCHAR *)tmpStr, strlen(tmpStr), (SQLCHAR *)maxStr, sizeof(maxStr), &returnSize, SQL_DRIVER_NOPROMPT );

    return status;
}