static HRESULT
Async(
    TkWinSendCom *obj,
    VARIANT Cmd,
    EXCEPINFO *pExcepInfo,
    UINT *puArgErr)
{
    HRESULT hr = S_OK;
    VARIANT vCmd;

    VariantInit(&vCmd);

    hr = VariantChangeType(&vCmd, &Cmd, 0, VT_BSTR);
    if (FAILED(hr)) {
	Tcl_SetObjResult(obj->interp, Tcl_NewStringObj(
		"invalid args: Async(command)", -1));
	TkWinSend_SetExcepInfo(obj->interp, pExcepInfo);
	hr = DISP_E_EXCEPTION;
    }

    if (SUCCEEDED(hr) && obj->interp) {
	Tcl_Obj *scriptPtr = Tcl_NewUnicodeObj(vCmd.bstrVal,
		(int) SysStringLen(vCmd.bstrVal));

	TkWinSend_QueueCommand(obj->interp, scriptPtr);
    }

    VariantClear(&vCmd);
    return hr;
}