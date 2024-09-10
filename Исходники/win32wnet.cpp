// @pymethod int|win32wnet|Netbios|Executes a Netbios call.
PyObject *
PyWinMethod_Netbios(PyObject *self, PyObject *args)
{
	PyObject *obncb;
	// @pyparm <o NCB>|ncb||The NCB object to use for the call.
	if (!PyArg_ParseTuple(args, "O!:Netbios", &PyNCBType, &obncb))
		return NULL;
	PyNCB *pyncb = (PyNCB *)obncb;
	UCHAR rc;
	Py_BEGIN_ALLOW_THREADS
	rc = Netbios(&pyncb->m_ncb);
	Py_END_ALLOW_THREADS
	return PyInt_FromLong((long)rc);
}