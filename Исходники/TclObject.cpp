static void
fillSafeArray (
    Tcl_Obj *pList,
    SAFEARRAY *psa,
    unsigned dim,
    long *pIndices,
    Tcl_Interp *interp,
    bool addRef)
{
    HRESULT hr;

    // Get index range.
    long lowerBound;
    hr = SafeArrayGetLBound(psa, dim, &lowerBound);
    if (FAILED(hr)) {
        _com_issue_error(hr);
    }

    long upperBound;
    hr = SafeArrayGetUBound(psa, dim, &upperBound);
    if (FAILED(hr)) {
        _com_issue_error(hr);
    }

    int numElements;
    Tcl_Obj **pElements;
    if (Tcl_ListObjGetElements(interp, pList, &numElements, &pElements)
        != TCL_OK) {
        _com_issue_error(E_INVALIDARG);
    }

    unsigned dim1 = dim - 1;
    if (dim < SafeArrayGetDim(psa)) {
        // Create list of list for multi-dimensional array.
        for (int i = 0; i < numElements; ++i) {
            pIndices[dim1] = i;
            fillSafeArray(pElements[i], psa, dim + 1, pIndices, interp, addRef);
        }

    } else {
        for (int i = 0; i < numElements; ++i) {
            TclObject element(pElements[i]); 
            NativeValue elementVar;
            element.toNativeValue(&elementVar, Type::variant(), interp, addRef);

            pIndices[dim1] = i;
            hr = SafeArrayPutElement(psa, pIndices, &elementVar);
            if (FAILED(hr)) {
                _com_issue_error(hr);
            }
        }
    }
}