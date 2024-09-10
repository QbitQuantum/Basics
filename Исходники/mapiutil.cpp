// @object PySPropTagArray|A sequence of integers
BOOL PyMAPIObject_AsSPropTagArray(PyObject *obta, SPropTagArray **ppta)
{
    if (obta==Py_None) {
        *ppta = NULL;
        return TRUE;
    }
    BOOL bSeq = TRUE;
    int seqLen;
    if (PySequence_Check(obta)) {
        seqLen = PySequence_Length(obta);
    } else if (PyInt_Check(obta)) {
        seqLen = 1;
        bSeq = FALSE;
    } else {
        PyErr_SetString(PyExc_TypeError, "SPropTagArray must be a sequence of integers");
        return FALSE;
    }

    DWORD cBytes = (seqLen * sizeof(ULONG)) + sizeof(ULONG);
    SPropTagArray *pta;
    HRESULT hr = MAPIAllocateBuffer(cBytes, (void **)&pta);
    if (FAILED(hr)) {
        OleSetOleError(hr);
        return FALSE;
    }
    pta->cValues = seqLen;
    if (bSeq) {
        for (ULONG i=0; i<(ULONG)seqLen; i++) {
            PyObject *obItem = PySequence_GetItem(obta, i);
            if (obItem==NULL) {
                MAPIFreeBuffer(pta);
                return FALSE;
            }
            pta->aulPropTag[i] = PyInt_AsLong(obItem);
            if (PyErr_Occurred()) {
                Py_DECREF(obItem);
                MAPIFreeBuffer(pta);
                return FALSE;
            }
            Py_DECREF(obItem);
        }
    } else {
        // Simple int.
        pta->aulPropTag[0] = PyInt_AsLong(obta);
    }
    *ppta = pta;
    return TRUE;
}