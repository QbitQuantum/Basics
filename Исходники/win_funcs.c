PyObject *
GetWindowChildsList(PyObject *self, PyObject *args)
{ 
	PyObject *pyWindowList;
	BOOL invisible=TRUE;
	HWND hWndParent;

	if (!PyArg_ParseTuple(args, "l|B", &hWndParent, &invisible))
		return NULL;
	pyWindowList = PyList_New(0);
	if (invisible)
		EnumChildWindows(hWndParent, (WNDENUMPROC) EnumAllWindowsProc, (LPARAM) pyWindowList);
	else
		EnumChildWindows(hWndParent, (WNDENUMPROC) EnumVisibleWindowsProc, (LPARAM) pyWindowList);
	return Py_BuildValue("O", pyWindowList);
}