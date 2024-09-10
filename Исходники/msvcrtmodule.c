static PyObject *
msvcrt_ungetwch_impl(PyModuleDef *module, int unicode_char)
/*[clinic end generated code: output=1ee7674710322bd1 input=83ec0492be04d564]*/
{
    if (_ungetwch(unicode_char) == WEOF)
        return PyErr_SetFromErrno(PyExc_IOError);
    Py_RETURN_NONE;
}