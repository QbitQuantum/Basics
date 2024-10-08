static Machine *
findMachineType()
{
    // Search for an exact match by SysParam stuff
    wchar_t oeminfo[128], platform[128];
    SystemParametersInfo(SPI_GETOEMINFO, sizeof(oeminfo), oeminfo, 0);
    SystemParametersInfo(SPI_GETPLATFORMTYPE, sizeof(platform), platform, 0);
    Output("Trying to detect machine (Plat='%ls' OEM='%ls')"
           , platform, oeminfo);

    // Try to lookup processor type.
    PROCESSOR_INFO pinfo;
    DWORD rsize;
    memset(&pinfo, sizeof(pinfo), 0);
    int ret = KernelIoControl(IOCTL_PROCESSOR_INFORMATION, NULL, 0
                    , &pinfo, sizeof(pinfo), &rsize);
    if (ret)
        Output("Wince reports processor: core=%ls name=%ls cat=%ls vend=%ls"
               , pinfo.szProcessCore, pinfo.szProcessorName
               , pinfo.szCatalogNumber, pinfo.szVendor);

    Machine **p = mach_start;
    while (p < &mach_end) {
        Machine *m = *p;
        p++;
        Output("Looking at machine %s", m->name);
        if (wcscmp(platform, m->PlatformType) != 0)
            continue;
        for (uint32 j=0; j<ARRAY_SIZE(m->OEMInfo) && m->OEMInfo[j]; j++) {
            int len = wcslen(m->OEMInfo[j]);
            if (_wcsnicmp(oeminfo, m->OEMInfo[j], len) == 0)
                // Match
                return m;
        }
    }

    // Couldn't find a machine - try by architecture.
    p = mach_start;
    while (p < &mach_end) {
        Machine *m = *p;
        p++;
        if (m->OEMInfo[0])
            // Not an architecture.
            continue;
        Output("Looking at arch %s", m->name);
        for (uint32 j=0; j<ARRAY_SIZE(m->CPUInfo) && m->CPUInfo[j]; j++) {
            int len = wcslen(m->CPUInfo[j]);
            if (_wcsnicmp(pinfo.szProcessorName, m->CPUInfo[j], len) == 0
                || _wcsnicmp(pinfo.szProcessCore, m->CPUInfo[j], len) == 0)
                // Match
                return m;
        }
        int ret = 0;
        TRY_EXCEPTION_HANDLER {
            ret = m->detect();
        } CATCH_EXCEPTION_HANDLER {
            Output("Exception on arch %s detect", m->name);
        }
        if (ret)
            // Match
            return m;
    }

    // Nothing matched - use generic default.
    return &RefMachine;
}