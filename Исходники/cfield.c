static PyObject *
Z_get(void *ptr, Py_ssize_t size)
{
    wchar_t *p;
    p = *(wchar_t **)ptr;
    if (p) {
#if defined(MS_WIN32) && !defined(_WIN32_WCE)
        if (IsBadStringPtrW(*(wchar_t **)ptr, -1)) {
            PyErr_Format(PyExc_ValueError,
                         "invalid string pointer %p",
                         *(wchar_t **)ptr);
            return NULL;
        }
#endif
        return PyUnicode_FromWideChar(p, wcslen(p));
    } else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}