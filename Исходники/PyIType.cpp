// @pymethod <o PyUnicode>|pythoncom|QueryPathOfRegTypeLib|Retrieves the path of a registered type library.
PyObject *pythoncom_querypathofregtypelib(PyObject *self, PyObject *args)
{
	PyObject *obIID;
	int major, minor;
	LCID lcid = LOCALE_USER_DEFAULT;
	// @pyparm <o PyIID>|iid||The IID of the type library.
	// @pyparm int|versionMajor||The major version number of the library
	// @pyparm int|versionMinor||The minor version number of the library
	// @pyparm int|lcid|LOCALE_USER_DEFAULT|The locale ID to use.
	if (!PyArg_ParseTuple(args, "Oii|i",
		&obIID,
		&major,
		&minor,
		&lcid))
		return NULL;

	CLSID clsid;
	if (!PyWinObject_AsIID(obIID, &clsid))
		return NULL;

	BSTR result;
	PY_INTERFACE_PRECALL;
	HRESULT hr = QueryPathOfRegTypeLib(clsid, major, minor, lcid, &result);
	PY_INTERFACE_POSTCALL;
	if (FAILED(hr))
		return PyCom_BuildPyException(hr);
	return PyWinObject_FromBstr( result, TRUE );
}