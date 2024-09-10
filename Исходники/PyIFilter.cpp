static PyObject *pyBindIFilterFromStream(PyObject *self, PyObject *args)
{
	HRESULT hr;
	IUnknown *pOb = NULL;
	PyObject *obStg;
	
	PyObject *ret;
	long lres = 0;
	if (!PyArg_ParseTuple(args, "O:BindIFilterFromStream", &obStg)) 
		return NULL;

	IStream *pstm;
	BOOL bPythonIsHappy = TRUE;
	if (!PyCom_InterfaceFromPyObject(obStg, IID_IStream, (void **)&pstm, FALSE /* bNoneOK */))
		bPythonIsHappy = FALSE;

	if (!bPythonIsHappy)
		return NULL;

	Py_BEGIN_ALLOW_THREADS;
	hr = BindIFilterFromStream( pstm , NULL , (void**)&pOb ); 
	pstm->Release();
	Py_END_ALLOW_THREADS;
	if (FAILED(hr))
		ret = OleSetOleError(hr);
	else
		ret = PyCom_PyObjectFromIUnknown(pOb, IID_IFilter, FALSE);
	return ret;
}