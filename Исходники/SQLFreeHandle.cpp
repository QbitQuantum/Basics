SQLRETURN SQL_API SQLFreeHandle(SQLSMALLINT HandleType, SQLHANDLE Handle)
{
    o::SQLFreeHandle sqlFreeHandle(HandleType, Handle);
    return sqlFreeHandle();
}