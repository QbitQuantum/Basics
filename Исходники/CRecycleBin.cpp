HRESULT WINAPI CRecycleBin::CreateViewObject(HWND hwndOwner, REFIID riid, void **ppv)
{
    CComPtr<IShellView> pShellView;
    HRESULT hr = E_NOINTERFACE;

    TRACE("(%p, %p, %s, %p)\n", this, hwndOwner, debugstr_guid(&riid), ppv);

    if (!ppv)
        return hr;

    *ppv = NULL;

    if (IsEqualIID (riid, IID_IDropTarget))
    {
        hr = CRecyclerDropTarget_CreateInstance(riid, ppv);
    }
    else if (IsEqualIID (riid, IID_IContextMenu) || IsEqualIID (riid, IID_IContextMenu2))
    {
        hr = this->QueryInterface(riid, ppv);
    }
    else if (IsEqualIID (riid, IID_IShellView))
    {
        SFV_CREATE sfvparams = {sizeof(SFV_CREATE), this};
        hr = SHCreateShellFolderView(&sfvparams, (IShellView**)ppv);
    }
    else
        return hr;

    TRACE ("-- (%p)->(interface=%p)\n", this, ppv);
    return hr;

}