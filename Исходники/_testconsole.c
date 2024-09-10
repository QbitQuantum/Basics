static PyObject *
_testconsole_write_input_impl(PyObject *module, PyObject *file,
                              PyBytesObject *s)
/*[clinic end generated code: output=48f9563db34aedb3 input=4c774f2d05770bc6]*/
{
    INPUT_RECORD *rec = NULL;
    
    if (!PyWindowsConsoleIO_Check(file)) {
        PyErr_SetString(PyExc_TypeError, "expected raw console object");
        return NULL;
    }

    const wchar_t *p = (const wchar_t *)PyBytes_AS_STRING(s);
    DWORD size = (DWORD)PyBytes_GET_SIZE(s) / sizeof(wchar_t);

    rec = (INPUT_RECORD*)PyMem_Malloc(sizeof(INPUT_RECORD) * size);
    if (!rec)
        goto error;
    memset(rec, 0, sizeof(INPUT_RECORD) * size);
    
    INPUT_RECORD *prec = rec;
    for (DWORD i = 0; i < size; ++i, ++p, ++prec) {
        prec->EventType = KEY_EVENT;
        prec->Event.KeyEvent.bKeyDown = TRUE;
        prec->Event.KeyEvent.wRepeatCount = 10;
        prec->Event.KeyEvent.uChar.UnicodeChar = *p;
    }

    HANDLE hInput = ((winconsoleio*)file)->handle;
    DWORD total = 0;
    while (total < size) {
        DWORD wrote;
        if (!WriteConsoleInputW(hInput, &rec[total], (size - total), &wrote)) {
            PyErr_SetFromWindowsErr(0);
            goto error;
        }
        total += wrote;
    }

    PyMem_Free((void*)rec);
    
    Py_RETURN_NONE;
error:
    if (rec)
        PyMem_Free((void*)rec);
    return NULL;
}