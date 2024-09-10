HRESULT OpenSession(IDBCreateCommand **ppCreateCommand)
{
    *ppCreateCommand = NULL;

    CComPtr<IDataInitialize> spDataInit;
    CComPtr<IUnknown> spUnknownDBInitialize;
    CComPtr<IDBInitialize> spDBInitialize;
    CComPtr<IDBCreateSession> spDBCreateSession;

    HRESULT hr = CoCreateInstance(CLSID_MSDAINITIALIZE, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&spDataInit));
    if (SUCCEEDED(hr))
    {
        hr = spDataInit->GetDataSource( NULL, CLSCTX_INPROC_SERVER, L"provider=Search.CollatorDSO.1", __uuidof(IDBInitialize), &spUnknownDBInitialize);
    }
    if (SUCCEEDED(hr))
    {
        hr = spUnknownDBInitialize->QueryInterface(&spDBInitialize);
    }
    if (SUCCEEDED(hr))
    {
        hr = spDBInitialize->Initialize();
    }
    if (SUCCEEDED(hr))
    {
        hr = spDBInitialize->QueryInterface(&spDBCreateSession);
    }
    if (SUCCEEDED(hr))
    {
        CComPtr<IUnknown> spUnknownCreateCommand;
        hr = spDBCreateSession->CreateSession(0, __uuidof(IDBCreateCommand), &spUnknownCreateCommand);
        if (SUCCEEDED(hr))
        {
            hr = spUnknownCreateCommand->QueryInterface(ppCreateCommand);
        }
    }

    return hr;
}