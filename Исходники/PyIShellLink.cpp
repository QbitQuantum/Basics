// @pymethod str, <o WIN32_FIND_DATA>|PyIShellLink|GetPath|Retrieves the target path and file name of a shell link object
// @comm The AlternateFileName (8.3) member of WIN32_FIND_DATA does not return information
PyObject *PyIShellLink::GetPath(PyObject *self, PyObject *args)
{
	IShellLink *pISL = GetI(self);
	if ( pISL == NULL )
		return NULL;
	WIN32_FIND_DATA fd;
	// @pyparm int|fFlags||One of the following values:
	// @flagh Value|Description
	// @flag SLGP_SHORTPATH|Retrieves the standard short (8.3 format) file name.  
	// @flag SLGP_UNCPRIORITY|Retrieves the Universal Naming Convention (UNC) path name of the file.  
	// @flag SLGP_RAWPATH|Retrieves the raw path name. A raw path is something that might not exist and may include environment variables that need to be expanded. 
	// @pyparm int|cchMaxPath|_MAX_PATH|Number of characters to allocate for returned filename
	int cchMaxPath = _MAX_PATH;
	DWORD fFlags;
	if ( !PyArg_ParseTuple(args, "l|i:GetPath", &fFlags, &cchMaxPath) )
		return NULL;
	HRESULT hr;
	TCHAR *pszFile = (TCHAR *)malloc(cchMaxPath * sizeof(TCHAR));
	if (pszFile==NULL) {
		PyErr_SetString(PyExc_MemoryError, "allocating string buffer");
		return NULL;
	}
	ZeroMemory(&fd, sizeof(fd));
	PY_INTERFACE_PRECALL;
	hr = pISL->GetPath( pszFile, cchMaxPath, &fd, fFlags );
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) ) {
		free(pszFile);
		return OleSetOleError(hr);
	}
	PyObject *ret = Py_BuildValue("NN",
		PyWinObject_FromTCHAR(pszFile),
		PyObject_FromWIN32_FIND_DATA(&fd));
	free(pszFile);
	return ret;
}