// @pymethod <o PyILockBytes>|pythoncom|CreateILockBytesOnHGlobal|Creates an ILockBytes interface based on global memory
PyObject *pythoncom_CreateILockBytesOnHGlobal(PyObject *self, PyObject *args)
{
	PyObject *obhglobal=Py_None;
	HGLOBAL hglobal=NULL;
	BOOL bdelete=TRUE;
	ILockBytes *pILockBytes=NULL;
	if (!PyArg_ParseTuple(args, "|Ol:CreateILockBytesOnHGlobal",
		&obhglobal,	// @pyparm <o PyHANDLE>|hGlobal|None|Global memory handle.  If None, a new global memory object is allocated.
		&bdelete))	// @pyparm bool|DeleteOnRelease|True|Indicates if global memory should be freed when interface is released.
		return NULL;
	if (!PyWinObject_AsHANDLE(obhglobal, &hglobal))
		return NULL;
	PY_INTERFACE_PRECALL;
	HRESULT hr = CreateILockBytesOnHGlobal(hglobal, bdelete, &pILockBytes);
	PY_INTERFACE_POSTCALL;
	if (FAILED(hr))
		return PyCom_BuildPyException(hr);
	return PyCom_PyObjectFromIUnknown(pILockBytes, IID_ILockBytes, FALSE);
}