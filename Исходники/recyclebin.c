static HRESULT WINAPI RecycleBin_CreateViewObject(IShellFolder2 *iface, HWND hwndOwner, REFIID riid, void **ppv)
{
    RecycleBin *This = impl_from_IShellFolder2(iface);
    HRESULT ret;
    TRACE("(%p, %p, %s, %p)\n", This, hwndOwner, debugstr_guid(riid), ppv);

    *ppv = NULL;
    if (IsEqualGUID(riid, &IID_IShellView))
    {
        IShellView *tmp;
        CSFV sfv;

        ZeroMemory(&sfv, sizeof(sfv));
        sfv.cbSize = sizeof(sfv);
        sfv.pshf = (IShellFolder *)This;

        TRACE("Calling SHCreateShellFolderViewEx\n");
        ret = SHCreateShellFolderViewEx(&sfv, &tmp);
        TRACE("Result: %08x, output: %p\n", (unsigned int)ret, tmp);
        *ppv = tmp;
        return ret;
    }

    return E_NOINTERFACE;
}