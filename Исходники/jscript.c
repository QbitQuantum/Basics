static void test_script_dispatch(IDispatchEx *dispex)
{
    DISPPARAMS dp = {NULL,NULL,0,0};
    EXCEPINFO ei;
    BSTR str;
    DISPID id;
    VARIANT v;
    HRESULT hres;

    str = a2bstr("ActiveXObject");
    hres = IDispatchEx_GetDispID(dispex, str, fdexNameCaseSensitive, &id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    str = a2bstr("Math");
    hres = IDispatchEx_GetDispID(dispex, str, fdexNameCaseSensitive, &id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    memset(&ei, 0, sizeof(ei));
    hres = IDispatchEx_InvokeEx(dispex, id, 0, DISPATCH_PROPERTYGET, &dp, &v, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&v) == VT_DISPATCH, "V_VT(v) = %d\n", V_VT(&v));
    ok(V_DISPATCH(&v) != NULL, "V_DISPATCH(v) = NULL\n");
    VariantClear(&v);

    str = a2bstr("String");
    hres = IDispatchEx_GetDispID(dispex, str, fdexNameCaseSensitive, &id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    memset(&ei, 0, sizeof(ei));
    hres = IDispatchEx_InvokeEx(dispex, id, 0, DISPATCH_PROPERTYGET, &dp, &v, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&v) == VT_DISPATCH, "V_VT(v) = %d\n", V_VT(&v));
    ok(V_DISPATCH(&v) != NULL, "V_DISPATCH(v) = NULL\n");
    VariantClear(&v);
}