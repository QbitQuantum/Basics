HRESULT SHELL32_BindToGuidItem(LPCITEMIDLIST pidlRoot,
                               PCUIDLIST_RELATIVE pidl,
                               LPBC pbcReserved,
                               REFIID riid,
                               LPVOID *ppvOut)
{
    CComPtr<IPersistFolder> pFolder;
    HRESULT hr;

    if (!pidlRoot || !ppvOut || !pidl || !pidl->mkid.cb)
        return E_INVALIDARG;

    *ppvOut = NULL;

    GUID *pGUID = _ILGetGUIDPointer(pidl);
    if (!pGUID)
    {
        ERR("SHELL32_BindToGuidItem called for non guid item!\n");
        return E_INVALIDARG;
    }

    hr = SHCoCreateInstance(NULL, pGUID, NULL, IID_PPV_ARG(IPersistFolder, &pFolder));
    if (FAILED(hr))
        return hr;

    if (_ILIsPidlSimple (pidl))
    {
        hr = pFolder->Initialize(ILCombine(pidlRoot, pidl));
        if (FAILED(hr))
            return hr;

        return pFolder->QueryInterface(riid, ppvOut);
    }
    else
    {
        LPITEMIDLIST pidlChild = ILCloneFirst (pidl);
        if (!pidlChild)
            return E_OUTOFMEMORY;

        hr = pFolder->Initialize(ILCombine(pidlRoot, pidlChild));
        ILFree(pidlChild);
        if (FAILED(hr))
            return hr;

        CComPtr<IShellFolder> psf;
        hr = pFolder->QueryInterface(IID_PPV_ARG(IShellFolder, &psf));
        if (FAILED(hr))
            return hr;

        return psf->BindToObject(ILGetNext (pidl), pbcReserved, riid, ppvOut);
    }
}