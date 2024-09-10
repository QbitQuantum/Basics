BOOL PyObject_AsPROPVARIANT(PyObject *ob, PROPVARIANT *pVar)
{
	if (ob==Py_None) {
		PropVariantInit(pVar);
	} else if (ob==Py_True) {
		pVar->boolVal = -1;
		pVar->vt = VT_BOOL;
	} else if (ob==Py_False) {
		pVar->boolVal = 0;
		pVar->vt = VT_BOOL;
	} else if (PyLong_Check(ob)) {
		pVar->hVal.QuadPart = PyLong_AsLongLong(ob);
		if (pVar->hVal.QuadPart == -1 && PyErr_Occurred()){
		// Could still fit in an unsigned long long
			PyErr_Clear();
			pVar->uhVal.QuadPart = PyLong_AsUnsignedLongLong(ob);
			if (pVar->uhVal.QuadPart == -1 && PyErr_Occurred())
				return FALSE;
			pVar->vt = VT_UI8;
		}
		else{
			pVar->vt=VT_I8;
			// Could still fit in a regular long
			if (pVar->hVal.QuadPart >= LONG_MIN && pVar->hVal.QuadPart <= LONG_MAX){
				pVar->lVal = (long)pVar->hVal.QuadPart;
				pVar->vt = VT_I4;
			}
			// ... or an unsigned long
			else if (pVar->hVal.QuadPart >=0 && pVar->hVal.QuadPart <= ULONG_MAX){
				pVar->ulVal = (unsigned long)pVar->hVal.QuadPart;
				pVar->vt = VT_UI4;
			}
		}
#if (PY_VERSION_HEX < 0x03000000)
	// Not needed in Py3k, as PyInt_Check is defined to PyLong_Check
	} else if (PyInt_Check(ob)) {
		pVar->lVal = PyInt_AsLong(ob);
		pVar->vt = VT_I4;
#endif
	} else if (PyFloat_Check(ob)) {
		pVar->dblVal = PyFloat_AsDouble(ob);
		pVar->vt = VT_R8;
	} else if (PyUnicode_Check(ob) || PyString_Check(ob)) {
		PyWinObject_AsBstr(ob, &pVar->bstrVal);
		pVar->vt = VT_BSTR;
	} else {
		PyErr_SetString(PyExc_TypeError, "Unsupported object for PROPVARIANT");
		return FALSE;
	}
	return TRUE;
}