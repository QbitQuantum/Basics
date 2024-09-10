// @pymethod |PyIServerSecurity|RevertToSelf|Ends impersonation of client
PyObject *PyIServerSecurity::RevertToSelf(PyObject *self, PyObject *args)
{
	IServerSecurity *pISS = GetI(self);
	if ( pISS == NULL )
		return NULL;

	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pISS->RevertToSelf( );

	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pISS, IID_IServerSecurity );
	Py_INCREF(Py_None);
	return Py_None;
}