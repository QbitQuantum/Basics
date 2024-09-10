//------------------------------------------------------------------*
STDMETHODIMP
   CCustomConnect::CreateControlManagement(/*[in, string]*/ BSTR sInit, /*[out]*/ IUnknown **ppControlMgt)
{
    USES_CONVERSION;
    CSingleLock lock(&cs, TRUE);
    if (ppControlMgt == NULL)
        return E_POINTER;
    CString strInit = StripCommParam(sInit);
    if (!CheckInitString(strInit))
        return E_INVALIDARG;
    CLSID guid;
    TCHAR szProgID[256];
    lstrcpy(szProgID, g_ProgID_ControlMgt);
    lstrcat(szProgID, strInit);
    LPCWSTR lpwstrProgID = T2W(szProgID);
    HRESULT hr = CLSIDFromProgID(lpwstrProgID, &guid);
    if (FAILED(hr)) {
        hr = _Module.RegisterServerInstance(strInit);
        hr = CLSIDFromProgID(lpwstrProgID, &guid);
        for(int i=0; FAILED(hr) && i<100; i++) { // W2K: SP2-HACK
            Sleep(100);
            hr = CLSIDFromProgID(lpwstrProgID, &guid);
        }
    }
    if (FAILED(hr))
        return hr;

    //try to avoid second instance...
    CComPtr<IUnknown> pDummy;
    hr = CreateVarSession(sInit, &pDummy);
    if (FAILED(hr))
        return hr;

    return CoCreateInstance(guid, NULL, CLSCTX_ALL, IID_IUnknown, (void**)ppControlMgt);
}