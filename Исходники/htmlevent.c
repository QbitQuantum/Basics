static HRESULT call_disp_func(IDispatch *disp, DISPPARAMS *dp, VARIANT *retv)
{
    IDispatchEx *dispex;
    EXCEPINFO ei;
    HRESULT hres;

    memset(&ei, 0, sizeof(ei));

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    if(SUCCEEDED(hres)) {
        hres = IDispatchEx_InvokeEx(dispex, 0, GetUserDefaultLCID(), DISPATCH_METHOD, dp, retv, &ei, NULL);
        IDispatchEx_Release(dispex);
    }else {
        TRACE("Could not get IDispatchEx interface: %08x\n", hres);
        hres = IDispatch_Invoke(disp, 0, &IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
                dp, retv, &ei, NULL);
    }

    return hres;
}