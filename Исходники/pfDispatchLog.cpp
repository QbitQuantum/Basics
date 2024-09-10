void plDispatchLog::LogStatusBarChange(const char* name, const char* action)
{
    fLog->AddLineF("----- Status bar '%s' %s -----", name, action);

#ifdef HS_BUILD_FOR_WIN32
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);

    MEMORY_BASIC_INFORMATION mbi;
    memset(&mbi, 0, sizeof(MEMORY_BASIC_INFORMATION));

    // Note: this will return shared mem too on Win9x.  There's a way to catch that, but it's too slow -Colin
    uint32_t processMemUsed = 0;
    void* curAddress = 0;
    while (VirtualQuery(curAddress, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION))
    {
        if (mbi.State == MEM_COMMIT && mbi.Type == MEM_PRIVATE)
            processMemUsed += mbi.RegionSize;
        curAddress = ((BYTE*)mbi.BaseAddress) + mbi.RegionSize;
    }
    
    #define ToMB(mem) float(mem) / (1024.f*1024.f)
    fLog->AddLineF("# Mem stats");
    fLog->AddLineF("#   Physical: %.1f MB used %.1f MB free", ToMB(ms.dwTotalPhys-ms.dwAvailPhys), ToMB(ms.dwAvailPhys));
    fLog->AddLineF("#   Virtual:  %.1f MB used %.1f MB free", ToMB(ms.dwTotalVirtual-ms.dwAvailVirtual), ToMB(ms.dwAvailVirtual));
    fLog->AddLineF("#   Pagefile: %.1f MB used %.1f MB free", ToMB(ms.dwTotalPageFile-ms.dwAvailPageFile), ToMB(ms.dwAvailPageFile));
    fLog->AddLineF("#   Process:  %.1f MB used", ToMB(processMemUsed));
#endif // HS_BUILD_FOR_WIN32
}