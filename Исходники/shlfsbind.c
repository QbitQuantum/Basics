HRESULT WINAPI IFileSystemBindData_Constructor(const WIN32_FIND_DATAW *find_data, LPBC *ppV)
{
    FileSystemBindData *This;
    HRESULT ret;

    TRACE("(%p %p)\n", find_data, ppV);

    if (!ppV)
       return E_INVALIDARG;

    *ppV = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IFileSystemBindData_iface.lpVtbl = &FileSystemBindDataVtbl;
    This->ref = 1;
    IFileSystemBindData_SetFindData(&This->IFileSystemBindData_iface, find_data);

    ret = CreateBindCtx(0, ppV);
    if (SUCCEEDED(ret))
    {
        static const WCHAR nameW[] = {
            'F','i','l','e',' ','S','y','s','t','e','m',' ','B','i','n','d',' ','D','a','t','a',0};
        BIND_OPTS bindOpts;

        bindOpts.cbStruct = sizeof(BIND_OPTS);
        bindOpts.grfFlags = 0;
        bindOpts.grfMode = STGM_CREATE;
        bindOpts.dwTickCountDeadline = 0;
        IBindCtx_SetBindOptions(*ppV, &bindOpts);
        IBindCtx_RegisterObjectParam(*ppV, (WCHAR*)nameW, (IUnknown*)&This->IFileSystemBindData_iface);

        IFileSystemBindData_Release(&This->IFileSystemBindData_iface);
    }
    else
        HeapFree(GetProcessHeap(), 0, This);
    return ret;
}