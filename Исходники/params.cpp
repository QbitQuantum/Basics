bool PrepareAndBind(Cursor* cur, PyObject* pSql, PyObject* original_params, bool skip_first)
{
    //
    // Normalize the parameter variables.
    //

    // Since we may replace parameters (we replace objects with Py_True/Py_False when writing to a bit/bool column),
    // allocate an array and use it instead of the original sequence.  Since we don't change ownership we don't bother
    // with incref.  (That is, PySequence_GetItem will INCREF and ~ObjectArrayHolder will DECREF.)

    int        params_offset = skip_first ? 1 : 0;
    Py_ssize_t cParams       = original_params == 0 ? 0 : PySequence_Length(original_params) - params_offset;

    PyObject** params = (PyObject**)malloc(sizeof(PyObject*) * cParams);
    if (!params)
    {
        PyErr_NoMemory();
        return 0;
    }
    
    for (Py_ssize_t i = 0; i < cParams; i++)
        params[i] = PySequence_GetItem(original_params, i + params_offset);

    ObjectArrayHolder holder(cParams, params);

    //
    // Prepare the SQL if necessary.
    //

    if (pSql == cur->pPreparedSQL)
    {
        // We've already prepared this SQL, so we don't need to do so again.  We've also cached the parameter
        // information in cur->paramdescs.

        if (cParams != cur->paramcount)
        {
            RaiseErrorV(0, ProgrammingError, "The SQL contains %d parameter markers, but %d parameters were supplied",
                        cur->paramcount, cParams);
            return false;
        }
    }
    else
    {
        FreeParameterInfo(cur);

        SQLRETURN ret;
        if (PyString_Check(pSql))
        {
            Py_BEGIN_ALLOW_THREADS
            ret = SQLPrepare(cur->hstmt, (SQLCHAR*)PyString_AS_STRING(pSql), SQL_NTS);
            Py_END_ALLOW_THREADS
        }
        else
        {
            Py_BEGIN_ALLOW_THREADS
            ret = SQLPrepareW(cur->hstmt, (SQLWCHAR*)PyUnicode_AsUnicode(pSql), SQL_NTS);
            Py_END_ALLOW_THREADS
        }
  
        if (cur->cnxn->hdbc == SQL_NULL_HANDLE)
        {
            // The connection was closed by another thread in the ALLOW_THREADS block above.
            RaiseErrorV(0, ProgrammingError, "The cursor's connection was closed.");
            return false;
        }

        if (!SQL_SUCCEEDED(ret))
        {
            RaiseErrorFromHandle("SQLPrepare", GetConnection(cur)->hdbc, cur->hstmt);
            return false;
        }
                
        if (!CacheParamDesc(cur))
            return false;

        cur->pPreparedSQL = pSql;
        Py_INCREF(cur->pPreparedSQL);
    }