// @pymethod <o PyCRYPTKEY>|PyCRYPTKEY|CryptDuplicateKey|Creates an independent copy of the key
PyObject *PyCRYPTKEY::PyCryptDuplicateKey(PyObject *self, PyObject *args, PyObject *kwargs)
{
	static char *keywords[]={"Reserved", "Flags", NULL};
	PyObject *ret=NULL;
	DWORD dwFlags=0, dwReserved=0;
	HCRYPTKEY hcryptkey, hcryptkeydup;
	hcryptkey=((PyCRYPTKEY *)self)->GetHCRYPTKEY();

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|kk:CryptDuplicateKey", keywords,
		&dwReserved,	// @pyparm int|Reserved|0|Use 0 if passed in
		&dwFlags))		// @pyparm int|Flags|0|Also reserved, use 0
		return NULL;
	if (CryptDuplicateKey(hcryptkey, &dwReserved, dwFlags, &hcryptkeydup))
		ret = new PyCRYPTKEY(hcryptkeydup, ((PyCRYPTKEY *)self)->obcryptprov);
	else
		PyWin_SetAPIError("CryptDuplicateKey",GetLastError());
	return ret;
}