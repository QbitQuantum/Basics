// @pymethod <o PyIID>|pywintypes|CreateGuid|Creates a new, unique GUIID.
static PyObject *PyWin_CreateGuid(PyObject *self, PyObject *args)
{
	if (!PyArg_ParseTuple(args, ":CreateGuid"))
		return NULL;
	GUID guid;
	CoCreateGuid(&guid);
	return PyWinObject_FromIID(guid);
}