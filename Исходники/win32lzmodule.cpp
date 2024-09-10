// @pymethod |win32lz|Close|Closes a handle to an LZ file.
static PyObject *
PyLZClose(PyObject *self, PyObject *args)
{
	int h;
	if (!PyArg_ParseTuple(args, "i:Close", &h )) // @pyparm int|handle||The handle of the LZ file to close.
		return NULL;

	// @pyseeapi LZClose
	LZClose(h);
	Py_INCREF(Py_None);
	return (Py_None);
}