static int
pyuv_setmaxstdio(void)
{
    if (_setmaxstdio(PYUV_MAXSTDIO) != PYUV_MAXSTDIO) {
        if (errno) {
            PyErr_SetFromErrno(PyExc_WindowsError);
        }
        else {
            PyErr_SetString(PyExc_WindowsError, "_setmaxstdio failed");
        }
        return -1;
    }
    return 0;
}