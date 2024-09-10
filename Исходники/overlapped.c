static PyObject *
overlapped_UnregisterWait(PyObject *self, PyObject *args)
{
    HANDLE WaitHandle;
    BOOL ret;

    if (!PyArg_ParseTuple(args, F_HANDLE, &WaitHandle))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    ret = UnregisterWait(WaitHandle);
    Py_END_ALLOW_THREADS

    if (!ret)
        return SetFromWindowsErr(0);
    Py_RETURN_NONE;
}