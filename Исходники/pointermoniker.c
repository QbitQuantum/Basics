static HRESULT WINAPI PointerMonikerCF_CreateInstance(LPCLASSFACTORY iface,
    LPUNKNOWN pUnk, REFIID riid, LPVOID *ppv)
{
    IMoniker *pMoniker;
    HRESULT  hr;

    TRACE("(%p, %s, %p)\n", pUnk, debugstr_guid(riid), ppv);

    *ppv = NULL;

    if (pUnk)
        return CLASS_E_NOAGGREGATION;

    hr = CreatePointerMoniker(NULL, &pMoniker);
    if (FAILED(hr))
        return hr;

    hr = IMoniker_QueryInterface(pMoniker, riid, ppv);

    if (FAILED(hr))
        IMoniker_Release(pMoniker);

    return hr;
}