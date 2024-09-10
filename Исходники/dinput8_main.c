/******************************************************************************
 *	DirectInput8Create (DINPUT8.@)
 */
HRESULT WINAPI DECLSPEC_HOTPATCH DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riid, LPVOID *ppDI, LPUNKNOWN punkOuter) {
    IDirectInputA *pDI;
    HRESULT hr, hrCo;

    TRACE("hInst (%p), dwVersion: %d, riid (%s), punkOuter (%p)\n", hinst, dwVersion, debugstr_guid(riid), punkOuter);

    if (!ppDI)
        return E_POINTER;

    if (!IsEqualGUID(&IID_IDirectInput8A, riid) &&
        !IsEqualGUID(&IID_IDirectInput8W, riid) &&
        !IsEqualGUID(&IID_IUnknown, riid))
    {
        *ppDI = NULL;
        return DIERR_NOINTERFACE;
    }

    hrCo = CoInitialize(NULL);

    hr = CoCreateInstance(&CLSID_DirectInput, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectInputA, (void **)&pDI);

    /* Ensure balance of calls. */
    if (SUCCEEDED(hrCo))
        CoUninitialize();

    if (FAILED(hr)) {
        ERR("CoCreateInstance failed with hr = 0x%08x\n", hr);
        return hr;
    }

    hr = IDirectInput_QueryInterface(pDI, riid, ppDI);
    IDirectInput_Release(pDI);

    if (FAILED(hr))
        return hr;

    /* When aggregation is used (punkOuter!=NULL) the application needs to manually call Initialize. */
    if(punkOuter == NULL && IsEqualGUID(&IID_IDirectInput8A, riid)) {
        IDirectInput8A *DI = *ppDI;

        hr = IDirectInput8_Initialize(DI, hinst, dwVersion);
        if (FAILED(hr))
        {
            IDirectInput8_Release(DI);
            *ppDI = NULL;
            return hr;
        }
    }

    if(punkOuter == NULL && IsEqualGUID(&IID_IDirectInput8W, riid)) {
        IDirectInput8W *DI = *ppDI;

        hr = IDirectInput8_Initialize(DI, hinst, dwVersion);
        if (FAILED(hr))
        {
            IDirectInput8_Release(DI);
            *ppDI = NULL;
            return hr;
        }
    }

    return S_OK;
}