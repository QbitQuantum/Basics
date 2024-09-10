EXTERN_C HRESULT WINAPI BKEngInitialize(Skylark::BKENG_PLATFORM_INIT* pInit)
{
    if (!g_hMod_bkeng)
        return E_HANDLE;

    
    PFN_BKEngInitialize pfn = (PFN_BKEngInitialize)::GetProcAddress(g_hMod_bkeng, FN_BKEngInitialize);
    if (!pfn)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


    return pfn(pInit);
}