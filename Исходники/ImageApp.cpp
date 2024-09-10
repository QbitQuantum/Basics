STDMETHODIMP CImageApp::BindToObjectMoniker(IMoniker* moniker, IBindCtx* bindctx, IUnknown* *pVal)
{
    HRESULT hr = 0;

    CComPtr<IUnknown> spUnknown;
    spUnknown.CoCreateInstance(CLSID_ImageDocument);

    CComQIPtr<IPersistMoniker> persist = spUnknown;
    persist->Load(TRUE, moniker, bindctx, 0);

    /*
    hr =  moniker->BindToObject(bindctx, NULL, IID_IUnknown, (void**)&spUnknown);
    if (SUCCEEDED(hr))
    {
    	CComQIPtr<IEDocument> document = spUnknown;
    	document->SetApp(this);
    }
    */

    *pVal = spUnknown;
    if (*pVal) (*pVal)->AddRef();

    return hr;
}