JSBool XPCDispConvert::COMArrayToJSArray(XPCCallContext& ccx,
                                         const VARIANT & src,
                                         jsval & dest, nsresult& err)
{
    err = NS_OK;
    // We only support one dimensional arrays for now
    if(SafeArrayGetDim(src.parray) != 1)
    {
        err = NS_ERROR_FAILURE;
        return JS_FALSE;
    }
    // Get the upper bound;
    long ubound;
    if(FAILED(SafeArrayGetUBound(src.parray, 1, &ubound)))
    {
        err = NS_ERROR_FAILURE;
        return JS_FALSE;
    }
    // Get the lower bound
    long lbound;
    if(FAILED(SafeArrayGetLBound(src.parray, 1, &lbound)))
    {
        err = NS_ERROR_FAILURE;
        return JS_FALSE;
    }
    // Create the JS Array
    JSObject * array = JS_NewArrayObject(ccx, ubound - lbound + 1, nsnull);
    if(!array)
    {
        err = NS_ERROR_OUT_OF_MEMORY;
        return JS_FALSE;
    }
    AUTO_MARK_JSVAL(ccx, OBJECT_TO_JSVAL(array));
    // Divine the type of our array
    VARTYPE vartype;
    if((src.vt & VT_ARRAY) != 0)
    {
        vartype = src.vt & ~VT_ARRAY;
    }
    else // This was maybe a VT_SAFEARRAY
    {
#ifndef WINCE
        if(FAILED(SafeArrayGetVartype(src.parray, &vartype)))
            return JS_FALSE;
#else
        return JS_FALSE;
#endif
    }
    jsval val = JSVAL_NULL;
    AUTO_MARK_JSVAL(ccx, &val);
    for(long index = lbound; index <= ubound; ++index)
    {
        HRESULT hr;
        _variant_t var;
        if(vartype == VT_VARIANT)
        {
            hr = SafeArrayGetElement(src.parray, &index, &var);
        }
        else
        {
            var.vt = vartype;
            hr = SafeArrayGetElement(src.parray, &index, &var.byref);
        }
        if(FAILED(hr))
        {
            err = NS_ERROR_FAILURE;
            return JS_FALSE;
        }
        if(!COMToJS(ccx, var, val, err))
            return JS_FALSE;
        JS_SetElement(ccx, array, index, &val);
    }
    dest = OBJECT_TO_JSVAL(array);
    return JS_TRUE;
}