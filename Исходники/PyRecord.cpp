// @pymethod <o PyRecord>|pythoncom|GetRecordFromGuids|Creates a new record object from the given GUIDs
PyObject *pythoncom_GetRecordFromGuids(PyObject *self, PyObject *args)
{
	void *data = NULL;
	PyObject *obGuid, *obInfoGuid, *obdata=Py_None;
	int major, minor, lcid;
	int cb = 0;
	if (!PyArg_ParseTuple(args, "OiiiO|O:GetRecordFromGuids", 
		&obGuid, // @pyparm <o PyIID>|iid||The GUID of the type library
		&major, // @pyparm int|verMajor||The major version number of the type lib.
		&minor, // @pyparm int|verMinor||The minor version number of the type lib.
		&lcid, // @pyparm int|lcid||The LCID of the type lib.
		&obInfoGuid, // @pyparm <o PyIID>|infoIID||The GUID of the record info in the library
		&obdata)) // @pyparm string or buffer|data|None|The raw data to initialize the record with.
		return NULL;
	if (!PyWinObject_AsReadBuffer(obdata, &data, &cb, TRUE))
		return NULL;
	GUID guid, infoGuid;
	if (!PyWinObject_AsIID(obGuid, &guid))
		return NULL;
	if (!PyWinObject_AsIID(obInfoGuid, &infoGuid))
		return NULL;
	IRecordInfo *i = NULL;
	HRESULT hr = GetRecordInfoFromGuids(guid, major, minor, lcid, infoGuid, &i);
	if (FAILED(hr))
		return PyCom_BuildPyException(hr);
	PyObject *ret = PyObject_FromRecordInfo(i, data, cb);
	i->Release();
	return ret;
}