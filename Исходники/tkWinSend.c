void
TkWinSend_SetExcepInfo(
    Tcl_Interp *interp,
    EXCEPINFO *pExcepInfo)
{
    Tcl_Obj *opError, *opErrorInfo, *opErrorCode;
    ICreateErrorInfo *pCEI;
    IErrorInfo *pEI, **ppEI = &pEI;
    HRESULT hr;

    if (!pExcepInfo) {
	return;
    }

    opError = Tcl_GetObjResult(interp);
    opErrorInfo = Tcl_GetVar2Ex(interp, "errorInfo", NULL, TCL_GLOBAL_ONLY);
    opErrorCode = Tcl_GetVar2Ex(interp, "errorCode", NULL, TCL_GLOBAL_ONLY);

    /*
     * Pack the trace onto the end of the Tcl exception descriptor.
     */

    opErrorCode = Tcl_DuplicateObj(opErrorCode);
    Tcl_IncrRefCount(opErrorCode);
    Tcl_ListObjAppendElement(interp, opErrorCode, opErrorInfo);
    /* TODO: Handle failure to append */

    pExcepInfo->bstrDescription = SysAllocString(Tcl_GetUnicode(opError));
    pExcepInfo->bstrSource = SysAllocString(Tcl_GetUnicode(opErrorCode));
    Tcl_DecrRefCount(opErrorCode);
    pExcepInfo->scode = E_FAIL;

    hr = CreateErrorInfo(&pCEI);
    if (!SUCCEEDED(hr)) {
	return;
    }

    hr = pCEI->lpVtbl->SetGUID(pCEI, &IID_IDispatch);
    hr = pCEI->lpVtbl->SetDescription(pCEI, pExcepInfo->bstrDescription);
    hr = pCEI->lpVtbl->SetSource(pCEI, pExcepInfo->bstrSource);
    hr = pCEI->lpVtbl->QueryInterface(pCEI, &IID_IErrorInfo, (void **) ppEI);
    if (SUCCEEDED(hr)) {
	SetErrorInfo(0, pEI);
	pEI->lpVtbl->Release(pEI);
    }
    pCEI->lpVtbl->Release(pCEI);
}