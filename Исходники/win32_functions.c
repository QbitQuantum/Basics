static PyObject *
win32_SetNamedPipeHandleState(PyObject *self, PyObject *args)
{
    HANDLE hNamedPipe;
    PyObject *oArgs[3];
    DWORD dwArgs[3], *pArgs[3] = {NULL, NULL, NULL};
    int i;

    if (!PyArg_ParseTuple(args, F_HANDLE "OOO",
                          &hNamedPipe, &oArgs[0], &oArgs[1], &oArgs[2]))
        return NULL;

    PyErr_Clear();

    for (i = 0 ; i < 3 ; i++) {
        if (oArgs[i] != Py_None) {
            dwArgs[i] = PyInt_AsUnsignedLongMask(oArgs[i]);
            if (PyErr_Occurred())
                return NULL;
            pArgs[i] = &dwArgs[i];
        }
    }

    if (!SetNamedPipeHandleState(hNamedPipe, pArgs[0], pArgs[1], pArgs[2]))
        return PyErr_SetFromWindowsErr(0);

    Py_RETURN_NONE;
}