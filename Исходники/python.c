static PyObject *extfunc_InfoWindowWrite(PyObject *self, PyObject *args) {
	const char *str;
	wchar_t buffer[1024];

	if (!PyArg_ParseTuple(args, "s", &str))
		return NULL;

	memset(buffer, 0, sizeof(buffer));
	if (mbsrtowcs (buffer, &str, sizeof(buffer)/sizeof(wchar_t), NULL) == -1)
		wcscpy(buffer, L"[wide character conversion failed]");

	Melder_print (buffer);

	return Py_BuildValue("");
}