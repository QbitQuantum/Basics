static HRESULT WINAPI FolderItemImpl_get_Path(FolderItem *iface, BSTR *pbs)
{
    FolderItemImpl *This = impl_from_FolderItem(iface);
    HRESULT ret = S_OK;
    WCHAR *pathW;
    int len;

    TRACE("(%p,%p)\n", iface, pbs);

    *pbs = NULL;
    if (V_VT(&This->dir) == VT_I4)
    {
        pathW = HeapAlloc(GetProcessHeap(), 0, MAX_PATH * sizeof(WCHAR));
        if (!pathW) return E_OUTOFMEMORY;
        ret = SHGetFolderPathW(NULL, V_I4(&This->dir), NULL, SHGFP_TYPE_CURRENT,
                pathW);
        if (ret == S_OK)
            *pbs = SysAllocString(pathW);
        else if (ret == E_INVALIDARG)
        {
            FIXME("not implemented for %#x\n", V_I4(&This->dir));
            ret = E_NOTIMPL;
        }
        HeapFree(GetProcessHeap(), 0, pathW);
    }
    else /* VT_BSTR */
    {
        pathW = V_BSTR(&This->dir);
        len = lstrlenW(pathW);
        *pbs = SysAllocStringLen(pathW, pathW[len - 1] == '\\' ? len - 1 : len);
    }
    if (ret == S_OK && !*pbs)
        ret = E_OUTOFMEMORY;
    return ret;
}