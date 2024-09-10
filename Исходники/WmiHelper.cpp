//
// Description:
//  Converts a BSTR to an equivalent PWSTR.
//
// Parameters:
//  bstr - A string represented as a BSTR.
//
//  ppWStr - On success, is set to the PWSTR equivalent of bstr. Caller must
//      free with HB_SAFE_FREE.
//
HRESULT BStrToPWchar(__in BSTR bstr, __out PWSTR* ppWStr)
{
    HRESULT hr;
    size_t cbWStr;
    PWSTR pWStrLocal = NULL;

    hr = SizeTMult(SysStringLen(bstr), sizeof(WCHAR), &cbWStr);
    if(HB_FAILED(hr)) {
        goto cleanexit;
    }

    //
    // Correct for additional NULL pointer
    //

    hr = SizeTAdd(cbWStr, sizeof(WCHAR), &cbWStr);
    if(HB_FAILED(hr)) {
        goto cleanexit;
    }

    pWStrLocal = (PWSTR)malloc(cbWStr);
    if(!pWStrLocal) {
        hr = E_OUTOFMEMORY;
        goto cleanexit;
    }

    hr =  StringCbCopy(pWStrLocal, cbWStr, static_cast<wchar_t*>(bstr));
    if(HB_FAILED(hr)) {
        goto cleanexit;
    }

    *ppWStr = pWStrLocal;
    pWStrLocal = NULL;

cleanexit:
    HB_SAFE_FREE(pWStrLocal);

    return hr;
}