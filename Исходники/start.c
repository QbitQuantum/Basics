static PyObject *Py_SHGetSpecialFolderPath(PyObject *self, PyObject *args)
{
	wchar_t path[MAX_PATH];
	int nFolder;
	if (!PyArg_ParseTuple(args, "i", &nFolder))
		return NULL;
	SHGetSpecialFolderPathW(NULL, path, nFolder, TRUE);
	return PyUnicode_FromWideChar(path, -1);
}