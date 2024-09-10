static PyObject*
l_ldap_set_option(PyObject* self, PyObject *args)
{
    PyObject *value;
    int option;

    if (!PyArg_ParseTuple(args, "iO:set_option", &option, &value))
	return NULL;
    if (!LDAP_set_option(NULL, option, value))
	return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}