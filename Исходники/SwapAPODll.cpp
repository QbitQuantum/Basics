HRESULT CSwapAPODllModule::DllUnregisterServer(BOOL bUnRegTypeLib) throw()
{
    HRESULT hResult;
    UINT32 u32APOUnregIndex = 0;

    // Unregister the module.
    hResult = CAtlDllModuleT<CSwapAPODllModule>::UnregisterServer(bUnRegTypeLib);
    if (FAILED(hResult))
    {
        goto Exit;
    }

    // Unregister all the APOs that are implemented in this module.
    for (u32APOUnregIndex = 0; u32APOUnregIndex < SIZEOF_ARRAY(gCoreAPOs); u32APOUnregIndex++)
    {
        hResult = UnregisterAPO(gCoreAPOs[u32APOUnregIndex]->clsid);
        ATLASSERT(SUCCEEDED(hResult));
    }

Exit:
    return hResult;
} // DllUnregisterServer