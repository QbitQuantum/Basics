/**
 * Sets the COM error from a result code and text message. This is the base
 * implementation for subsequent string based overrides
 * @param hResult the COM error code to be used
 * @param message the message to put in the error
 * @return the error code passed in via hResult
 */
static HRESULT Error(HRESULT hResult, const CComBSTR & message)
{
    CComPtr<ICreateErrorInfo> pCreateError;
    CComPtr<IErrorInfo> pError;
    HRESULT result = CreateErrorInfo(&pCreateError);
    if(FAILED(result))
        return E_NOTIMPL;
    result = pCreateError->QueryInterface(&pError);
    if(FAILED(result))
        return E_NOTIMPL;
    result = pCreateError->SetDescription(message);
    if(FAILED(result))
        return E_NOTIMPL;
    result = pCreateError->SetGUID(IID_IDispatch);
    if(FAILED(result))
        return E_NOTIMPL;
    CComBSTR source(L"@mozilla.XPCDispatchTearOff");
    result = pCreateError->SetSource(source);
    if(FAILED(result))
        return E_NOTIMPL;
    result = SetErrorInfo(0, pError);
    if(FAILED(result))
        return E_NOTIMPL;
    return hResult;
}