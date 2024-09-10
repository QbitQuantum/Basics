static HRESULT pidl_to_shellfolder(LPITEMIDLIST pidl, LPWSTR *displayname, IShellFolder **out_folder)
{
    IShellFolder* parent_folder=NULL;
    LPCITEMIDLIST relative_pidl=NULL;
    STRRET strret;
    HRESULT hr;

    hr = SHBindToParent(pidl, &IID_IShellFolder, (void**)&parent_folder, &relative_pidl);

    if (displayname)
    {
        if (SUCCEEDED(hr))
            hr = IShellFolder_GetDisplayNameOf(parent_folder, relative_pidl, SHGDN_INFOLDER, &strret);

        if (SUCCEEDED(hr))
            hr = StrRetToStrW(&strret, NULL, displayname);
    }

    if (SUCCEEDED(hr))
        hr = IShellFolder_BindToObject(parent_folder, relative_pidl, NULL, &IID_IShellFolder, (void**)out_folder);

    if (parent_folder)
        IShellFolder_Release(parent_folder);

    return hr;
}