static PyObject*
PyLocale_strxfrm(PyObject* self, PyObject* args)
{
    char *s, *buf;
    size_t n1, n2;
    PyObject *result;

    if (!PyArg_ParseTuple(args, "s:strxfrm", &s))
        return NULL;

    /* assume no change in size, first */
    n1 = strlen(s) + 1;
    buf = PyMem_Malloc(n1);
    if (!buf)
        return PyErr_NoMemory();
    n2 = strxfrm(buf, s, n1);
    if (n2 > n1) {
        /* more space needed */
        buf = PyMem_Realloc(buf, n2);
        if (!buf)
            return PyErr_NoMemory();
        strxfrm(buf, s, n2);
    }
    result = PyString_FromString(buf);
    PyMem_Free(buf);
    return result;
}