void NdbMem_Free(void* ptr)
{
    // VirtualFree(ptr, 0, MEM_DECOMMIT|MEM_RELEASE);
    
    // Address Windowing Extensions
    struct AWEINFO* pAWEinfo = 0;
    size_t i;
    HANDLE hProcess;

    for(i=0; i<gNdbMem_nAWEinfo; ++i)
    {
        if(ptr==gNdbMem_pAWEinfo[i].pRegionReserved)
        {
            pAWEinfo = gNdbMem_pAWEinfo+i;
        }
    }
    if(!pAWEinfo)
    {
        ShowLastError("NdbMem_Free", "ptr is not AWE memory");
    }

    hProcess = GetCurrentProcess();
    if(!MapUserPhysicalPages(ptr, pAWEinfo->nNumberOfPagesActual, 0))
    {
        ShowLastError("NdbMem_Free", "MapUserPhysicalPages");
    }
    
    if(!VirtualFree(ptr, 0, MEM_RELEASE))
    {
        ShowLastError("NdbMem_Free", "VirtualFree");
    }
    
    pAWEinfo->nNumberOfPagesFreed = pAWEinfo->nNumberOfPagesActual;
    if(!FreeUserPhysicalPages(hProcess, &(pAWEinfo->nNumberOfPagesFreed), pAWEinfo->pnPhysicalMemoryPageArray))
    {
        ShowLastError("NdbMem_Free", "FreeUserPhysicalPages");
    }
    
    VirtualFree(pAWEinfo->pnPhysicalMemoryPageArray, 0, MEM_DECOMMIT|MEM_RELEASE);
}