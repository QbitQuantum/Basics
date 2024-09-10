HRESULT GetSelectionFromSite(IUnknown *punkSite, BOOL fNoneImpliesFolder, IShellItemArray **ppsia)
{
    *ppsia = NULL;
    IFolderView2 *pfv;
    HRESULT hr = IUnknown_QueryService(punkSite, SID_SFolderView, IID_PPV_ARGS(&pfv));
    if (SUCCEEDED(hr))
    {
        hr = pfv->GetSelection(fNoneImpliesFolder, ppsia);
        pfv->Release();
    }
    return hr;
}