static PyObject* mod_drivers(PyObject* self)
{
    UNUSED(self);

    if (henv == SQL_NULL_HANDLE && !AllocateEnv())
        return 0;

    Object result(PyList_New(0));
    if (!result)
        return 0;

    SQLCHAR szDriverDesc[500];
    SWORD cbDriverDesc;
    SWORD cbAttrs;

    SQLRETURN ret;
    SQLUSMALLINT nDirection = SQL_FETCH_FIRST;

    for (;;)
    {
        Py_BEGIN_ALLOW_THREADS
        ret = SQLDrivers(henv, nDirection, szDriverDesc, _countof(szDriverDesc), &cbDriverDesc, 0, 0, &cbAttrs);
        Py_END_ALLOW_THREADS

        if (!SQL_SUCCEEDED(ret))
            break;

        // REVIEW: This is another reason why we really need a factory that we can use.  At this
        // point we don't have a global text encoding that we can assume for this.  Somehow it
        // seems to be working to use UTF-8, even on Windows.
        Object name(PyString_FromString((const char*)szDriverDesc));
        if (!name)
            return 0;

        if (PyList_Append(result, name.Get()) != 0)
            return 0;
        name.Detach();

        nDirection = SQL_FETCH_NEXT;
    }

    if (ret != SQL_NO_DATA)
    {
        Py_DECREF(result);
        return RaiseErrorFromHandle(0, "SQLDrivers", SQL_NULL_HANDLE, SQL_NULL_HANDLE);
    }

    return result.Detach();
}