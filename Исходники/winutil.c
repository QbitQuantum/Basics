static PyObject *
winutil_internet_connected(PyObject *self, PyObject *args) {
    DWORD flags;
    BOOL ans = InternetGetConnectedState(&flags, 0);
    if (ans) Py_RETURN_TRUE;
    Py_RETURN_FALSE;
}