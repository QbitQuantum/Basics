HRESULT CDS_IDLDropTarget_Create(HWND hwndOwner, IDropTargetVtbl *lpVtbl,
                              LPCITEMIDLIST pidl, LPDROPTARGET *ppdropt)
{
    LPIDLDROPTARGET pidldt = (void*)LocalAlloc(LPTR, SIZEOF(CIDLDropTarget));
    if (pidldt)
    {
        pidldt->pidl = ILClone(pidl);
        if (pidldt->pidl)
        {
            pidldt->dropt.lpVtbl = lpVtbl;
            pidldt->cRef = 1;
            pidldt->hwndOwner = hwndOwner;

            Assert(pidldt->pdtgAgr == NULL);

            *ppdropt = &pidldt->dropt;

            return S_OK;
        }
        else
            LocalFree((HLOCAL)pidldt);
    }
    *ppdropt = NULL;
    return E_OUTOFMEMORY;
}