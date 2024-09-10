static PyObject* CnxnInfo_New(Connection* cnxn)
{
#ifdef _MSC_VER
#pragma warning(disable : 4365)
#endif
    CnxnInfo* p = PyObject_NEW(CnxnInfo, &CnxnInfoType);
    if (!p)
        return 0;
    Object info((PyObject*)p);

    // set defaults
    p->odbc_major             = 3;
    p->odbc_minor             = 50;
    p->supports_describeparam = false;
    p->datetime_precision     = 19; // default: "yyyy-mm-dd hh:mm:ss"
    p->need_long_data_len     = false;

    // WARNING: The GIL lock is released for the *entire* function here.  Do not touch any objects, call Python APIs,
    // etc.  We are simply making ODBC calls and setting atomic values (ints & chars).  Also, make sure the lock gets
    // released -- do not add an early exit.

    SQLRETURN ret;
    Py_BEGIN_ALLOW_THREADS

    char szVer[20];
    SQLSMALLINT cch = 0;
    ret = SQLGetInfo(cnxn->hdbc, SQL_DRIVER_ODBC_VER, szVer, _countof(szVer), &cch);
    if (SQL_SUCCEEDED(ret))
    {
        char* dot = strchr(szVer, '.');
        if (dot)
        {
            *dot = '\0';
            p->odbc_major=(char)atoi(szVer);
            p->odbc_minor=(char)atoi(dot + 1);
        }
    }

    char szYN[2];
    if (SQL_SUCCEEDED(SQLGetInfo(cnxn->hdbc, SQL_DESCRIBE_PARAMETER, szYN, _countof(szYN), &cch)))
        p->supports_describeparam = szYN[0] == 'Y';

    if (SQL_SUCCEEDED(SQLGetInfo(cnxn->hdbc, SQL_NEED_LONG_DATA_LEN, szYN, _countof(szYN), &cch)))
        p->need_long_data_len = (szYN[0] == 'Y');

    // These defaults are tiny, but are necessary for Access.
    p->varchar_maxlength = 255;
    p->wvarchar_maxlength = 255;
    p->binary_maxlength  = 510;

    HSTMT hstmt = 0;
    if (SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, cnxn->hdbc, &hstmt)))
    {
        SQLINTEGER columnsize;
        if (SQL_SUCCEEDED(SQLGetTypeInfo(hstmt, SQL_TYPE_TIMESTAMP)) && SQL_SUCCEEDED(SQLFetch(hstmt)))
            if (SQL_SUCCEEDED(SQLGetData(hstmt, 3, SQL_INTEGER, &columnsize, sizeof(columnsize), 0)))
                p->datetime_precision = (int)columnsize;

        if (SQL_SUCCEEDED(SQLGetTypeInfo(hstmt, SQL_VARCHAR)) && SQL_SUCCEEDED(SQLFetch(hstmt)))
            if (SQL_SUCCEEDED(SQLGetData(hstmt, 3, SQL_INTEGER, &columnsize, sizeof(columnsize), 0)))
                p->varchar_maxlength = (int)columnsize;

        if (SQL_SUCCEEDED(SQLGetTypeInfo(hstmt, SQL_WVARCHAR)) && SQL_SUCCEEDED(SQLFetch(hstmt)))
            if (SQL_SUCCEEDED(SQLGetData(hstmt, 3, SQL_INTEGER, &columnsize, sizeof(columnsize), 0)))
                p->wvarchar_maxlength = (int)columnsize;

        if (SQL_SUCCEEDED(SQLGetTypeInfo(hstmt, SQL_BINARY)) && SQL_SUCCEEDED(SQLFetch(hstmt)))
            if (SQL_SUCCEEDED(SQLGetData(hstmt, 3, SQL_INTEGER, &columnsize, sizeof(columnsize), 0)))
                p->binary_maxlength = (int)columnsize;

        SQLFreeStmt(hstmt, SQL_CLOSE);
    }

    Py_END_ALLOW_THREADS

    // WARNING: Released the lock now.

    return info.Detach();
}