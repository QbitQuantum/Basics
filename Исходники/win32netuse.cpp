// @pymethod dict|win32net|NetUseGetInfo|Retrieves information about the configuration elements for a workstation
PyObject *
PyNetUseGetInfo(PyObject *self, PyObject *args)
{
	WCHAR *szServer = NULL, *szUse = NULL;
	PyObject *obServer, *obUse;
	PyNET_STRUCT *pInfo;
	BYTE *buf = NULL;
	PyObject *ret = NULL;
	int level = 0;
	DWORD err;
	// @pyparm string/<o PyUnicode>|server||The name of the server to execute on, or None.
	// @pyparm string/<o PyUnicode>|usename||The name of the locally mapped resource.
	// @pyparm int|level|0|The information level contained in the data. NOTE: levels 302 and 402 don't seem to work correctly. They return error 124. So currently these info levels are not available.
	if (!PyArg_ParseTuple(args, "OO|i", &obServer, &obUse, &level))
		return NULL;

	if (!PyWinObject_AsWCHAR(obServer, &szServer, TRUE))
		goto done;
	if (!PyWinObject_AsWCHAR(obUse, &szUse, TRUE))
		goto done;
	if (!FindNET_STRUCT(level, use_infos, &pInfo))
		goto done;

	err = NetUseGetInfo(szServer, szUse, level, &buf);

	if (err) {
		ReturnNetError("NetUseGetInfo",err);
		goto done;
	}
	ret= PyObject_FromNET_STRUCT(pInfo, buf);
done:
	if (buf) NetApiBufferFree(buf);
	PyWinObject_FreeWCHAR(szServer);
	PyWinObject_FreeWCHAR(szUse);
	return ret;
	// @pyseeapi NetUseGetInfo
	// @rdesc The result will be a dictionary in one of the <o PyUSE_INFO_*>
	// formats, depending on the level parameter.
}