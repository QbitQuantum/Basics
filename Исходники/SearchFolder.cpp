// This helper creates the scope object that is a collection of shell items that
// define where the search will operate.
HRESULT CreateScope(IShellItemArray **ppsia)
{
    *ppsia = NULL;

    IObjectCollection *pObjects;
    HRESULT hr = CreateShellItemArray(IID_PPV_ARGS(&pObjects));
    if (SUCCEEDED(hr))
    {
        IShellItem *psi;
        if (SUCCEEDED(SHCreateItemInKnownFolder(FOLDERID_DocumentsLibrary, 0, NULL, IID_PPV_ARGS(&psi))))
        {
            pObjects->AddObject(psi);
            psi->Release();
        }

        // Other items can be added to pObjects similar to the code above.

        hr = pObjects->QueryInterface(ppsia);

        pObjects->Release();
    }
    return hr;
}