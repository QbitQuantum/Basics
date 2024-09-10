static PyObject*
GetDataLongLong(Cursor* cur, int iCol)
{
    ColumnInfo* pinfo = &cur->colinfos[iCol];

    INT64 value = 0;
    SQLLEN cbFetched = 0;
    SQLRETURN ret;

    SQLSMALLINT nCType = pinfo->is_unsigned ? SQL_C_UBIGINT : SQL_C_SBIGINT;

    Py_BEGIN_ALLOW_THREADS
    ret = SQLGetData(cur->hstmt, (SQLSMALLINT)(iCol+1), nCType, &value, sizeof(value), &cbFetched);
    Py_END_ALLOW_THREADS

    if (!SQL_SUCCEEDED(ret))
        return RaiseErrorFromHandle("SQLGetData", cur->cnxn->hdbc, cur->hstmt);

    if (cbFetched == SQL_NULL_DATA)
        Py_RETURN_NONE;

    if (pinfo->is_unsigned)
        return PyLong_FromLongLong(*(UINT64*)&value);

    return PyLong_FromLongLong(*(INT64*)&value);
}