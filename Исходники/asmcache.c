static HRESULT WINAPI IAssemblyCacheImpl_UninstallAssembly(IAssemblyCache *iface,
                                                           DWORD dwFlags,
                                                           LPCWSTR pszAssemblyName,
                                                           LPCFUSION_INSTALL_REFERENCE pRefData,
                                                           ULONG *pulDisposition)
{
    HRESULT hr;
    IAssemblyCacheImpl *cache = impl_from_IAssemblyCache(iface);
    IAssemblyName *asmname, *next = NULL;
    IAssemblyEnum *asmenum = NULL;
    WCHAR *p, *path = NULL;
    ULONG disp;
    DWORD len;

    TRACE("(%p, 0%08x, %s, %p, %p)\n", iface, dwFlags,
          debugstr_w(pszAssemblyName), pRefData, pulDisposition);

    if (pRefData)
    {
        FIXME("application reference not supported\n");
        return E_NOTIMPL;
    }
    hr = CreateAssemblyNameObject( &asmname, pszAssemblyName, CANOF_PARSE_DISPLAY_NAME, NULL );
    if (FAILED( hr ))
        return hr;

    cache_lock( cache );

    hr = CreateAssemblyEnum( &asmenum, NULL, asmname, ASM_CACHE_GAC, NULL );
    if (FAILED( hr ))
        goto done;

    hr = IAssemblyEnum_GetNextAssembly( asmenum, NULL, &next, 0 );
    if (hr == S_FALSE)
    {
        if (pulDisposition)
            *pulDisposition = IASSEMBLYCACHE_UNINSTALL_DISPOSITION_ALREADY_UNINSTALLED;
        goto done;
    }
    hr = IAssemblyName_GetPath( next, NULL, &len );
    if (hr != HRESULT_FROM_WIN32( ERROR_INSUFFICIENT_BUFFER ))
        goto done;

    if (!(path = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) )))
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }
    hr = IAssemblyName_GetPath( next, path, &len );
    if (FAILED( hr ))
        goto done;

    if (DeleteFileW( path ))
    {
        if ((p = strrchrW( path, '\\' )))
        {
            *p = 0;
            RemoveDirectoryW( path );
            if ((p = strrchrW( path, '\\' )))
            {
                *p = 0;
                RemoveDirectoryW( path );
            }
        }
        disp = IASSEMBLYCACHE_UNINSTALL_DISPOSITION_UNINSTALLED;
        hr = S_OK;
    }
    else
    {
        disp = IASSEMBLYCACHE_UNINSTALL_DISPOSITION_ALREADY_UNINSTALLED;
        hr = S_FALSE;
    }
    if (pulDisposition) *pulDisposition = disp;

done:
    IAssemblyName_Release( asmname );
    if (next) IAssemblyName_Release( next );
    if (asmenum) IAssemblyEnum_Release( asmenum );
    HeapFree( GetProcessHeap(), 0, path );
    cache_unlock( cache );
    return hr;
}