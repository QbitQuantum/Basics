static bool Connect(PyObject* pConnectString, HDBC hdbc, bool fAnsi, long timeout)
{
    // This should have been checked by the global connect function.
    I(PyString_Check(pConnectString) || PyUnicode_Check(pConnectString));

    const int cchMax = 600;

    if (PySequence_Length(pConnectString) >= cchMax)
    {
        PyErr_SetString(PyExc_TypeError, "connection string too long");
        return false;
    }

    // The driver manager determines if the app is a Unicode app based on whether we call SQLDriverConnectA or
    // SQLDriverConnectW.  Some drivers, notably Microsoft Access/Jet, change their behavior based on this, so we try
    // the Unicode version first.  (The Access driver only supports Unicode text, but SQLDescribeCol returns SQL_CHAR
    // instead of SQL_WCHAR if we connect with the ANSI version.  Obviously this causes lots of errors since we believe
    // what it tells us (SQL_CHAR).)

    // Python supports only UCS-2 and UCS-4, so we shouldn't need to worry about receiving surrogate pairs.  However,
    // Windows does use UCS-16, so it is possible something would be misinterpreted as one.  We may need to examine
    // this more.

    SQLRETURN ret;

    if (timeout > 0)
    {
        //Py_BEGIN_ALLOW_THREADS
        ret = SQLSetConnectAttr(hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)timeout, SQL_IS_UINTEGER);
        //Py_END_ALLOW_THREADS
        if (!SQL_SUCCEEDED(ret))
            RaiseErrorFromHandle("SQLSetConnectAttr(SQL_ATTR_LOGIN_TIMEOUT)", hdbc, SQL_NULL_HANDLE);
    }

    if (!fAnsi)
    {
        SQLWChar connectString(pConnectString);
        //Py_BEGIN_ALLOW_THREADS
        ret = SQLDriverConnectW(hdbc, 0, connectString.get(), (SQLSMALLINT)connectString.size(), 0, 0, 0, SQL_DRIVER_NOPROMPT);
        //Py_END_ALLOW_THREADS
        if (SQL_SUCCEEDED(ret))
            return true;
        RaiseErrorFromHandle("SQLDriverConnect", hdbc, SQL_NULL_HANDLE);
        return false;

        // The Unicode function failed.  If the error is that the driver doesn't have a Unicode version (IM001), continue
        // to the ANSI version.
        //
        // I've commented this out since a number of common drivers are returning different errors.  The MySQL 5
        // driver, for example, returns IM002 "Data source name not found...".
        //
        // PyObject* error = GetErrorFromHandle("SQLDriverConnectW", hdbc, SQL_NULL_HANDLE);
        // if (!HasSqlState(error, "IM001"))
        // {
        //     RaiseErrorFromException(error);
        //     return false;
        // }
        // Py_XDECREF(error);
    }
    PyErr_SetString(PyExc_TypeError, "Non-unicode connection strings not supported.");
    return false;
}