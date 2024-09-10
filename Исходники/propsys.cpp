// @pymethod <o PyPROPVARIANT>|propsys|StgDeserializePropVariant|Creates a <o PyPROPVARIANT> from a serialized buffer
static PyObject *PyStgDeserializePropVariant(PyObject *self, PyObject *args)
{
	PROPVARIANT pv;
	SERIALIZEDPROPERTYVALUE *pspv;
	ULONG bufsize;
	PyObject *ob;
	HRESULT hr;
	if (!PyArg_ParseTuple(args, "O:StgDeserializePropVariant", &ob))
		return NULL;
	// @pyparm bytes|prop||Buffer or bytes object (or str in Python 2) containing a serialized value
	if (!PyWinObject_AsReadBuffer(ob, (void **)&pspv, &bufsize))
		return NULL;
	PY_INTERFACE_PRECALL;
	hr = StgDeserializePropVariant(pspv, bufsize, &pv);
	PY_INTERFACE_POSTCALL;
	if (FAILED(hr))
		return PyCom_BuildPyException(hr);
	return PyWinObject_FromPROPVARIANT(&pv);
};