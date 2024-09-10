// @pymethod <o STATSTG>|PyILockBytes|Stat|Retrieves a <o STATSTG> structure for this byte array object.
PyObject *PyILockBytes::Stat(PyObject *self, PyObject *args)
{
	ILockBytes *pILB = GetI(self);
	if ( pILB == NULL )
		return NULL;
	// @pyparm int|grfStatFlag||Specifies that this method does not return some of the fields in the STATSTG structure, thus saving a memory allocation operation. Values are taken from the STATFLAG enumerationg
	DWORD grfStatFlag;
	if ( !PyArg_ParseTuple(args, "i:Stat", &grfStatFlag) )
		return NULL;
	STATSTG pstatstg;
	PY_INTERFACE_PRECALL;
	HRESULT hr = pILB->Stat( &pstatstg, grfStatFlag );
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pILB, IID_ILockBytes);

	PyObject *obpstatstg = PyCom_PyObjectFromSTATSTG(&pstatstg);
	// STATSTG doco says our responsibility to free
	if ((pstatstg).pwcsName) CoTaskMemFree((pstatstg).pwcsName);
	PyObject *pyretval = Py_BuildValue("O", obpstatstg);
	Py_XDECREF(obpstatstg);
	return pyretval;
}