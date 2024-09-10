HRESULT XPCDispObject::COMCreateInstance(XPCCallContext & ccx, BSTR className,
                                         PRBool enforceSecurity,
                                         IDispatch ** result)
{
    NS_ENSURE_ARG_POINTER(result);
    // Turn the string into a CLSID
    _bstr_t bstrName(className);
    CLSID classID = CLSID_NULL;
    HRESULT hr = CLSIDFromString(bstrName, &classID);
    if(FAILED(hr))
        hr = CLSIDFromProgID(bstrName, &classID);
    if(FAILED(hr) || ::IsEqualCLSID(classID, CLSID_NULL))
        return hr;
    
    // If the caller cares about security do the necessary checks
    // This results in the object being instantiated, so we'll use
    // it
    if(enforceSecurity)
        return SecurityCheck(ccx, classID, result);
    
    CComPtr<IDispatch> disp;
#ifdef JAXER
	hr = disp.CoCreateInstance(classID, NULL, CLSCTX_SERVER);
#else
    hr = disp.CoCreateInstance(classID);
#endif /* JAXER */
    if(FAILED(hr))
        return hr;

    disp.CopyTo(result);

    return S_OK;
}