STDMETHODIMP nsXPCDispTestMethods::CreateError()
{
    CComBSTR someText(L"CreateError Test");
    ICreateErrorInfo * pCreateError;
    IErrorInfo * pError;
    HRESULT result = CreateErrorInfo(&pCreateError);
    if (FAILED(result))
        return E_NOTIMPL;
    result = pCreateError->QueryInterface(&pError);
    if (FAILED(result))
        return E_NOTIMPL;
    result = pCreateError->SetDescription(someText);
    if (FAILED(result))
        return E_NOTIMPL;
    result = pCreateError->SetGUID(IID_nsIXPCDispTestMethods);
    if (FAILED(result))
        return E_NOTIMPL;
    CComBSTR source(L"XPCIDispatchTest.nsXPCDispTestMethods.1");
    result = pCreateError->SetSource(source);
    if (FAILED(result))
        return E_NOTIMPL;
    result = SetErrorInfo(0, pError);
    if (FAILED(result))
        return E_NOTIMPL;
    pError->Release();
    pCreateError->Release();
    return E_FAIL;
}