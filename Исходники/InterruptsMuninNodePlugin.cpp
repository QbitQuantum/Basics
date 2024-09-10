int InterruptsMuninNodePlugin::GetValues(char *buffer, int len)
{
    int index = 0;
    int ret;
    unsigned long interrupt_count = 0UL, context_switches = 0UL;
    SYSTEM_PERFORMANCE_INFORMATION_ spi = {0};
    NTSTATUS ntret;
    SYSTEM_PROCESSOR_TIMES spt[32];

    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);

    /* We have array for 32 processor only :( */
    if (SystemInfo.dwNumberOfProcessors <= 32) {

        ntret = NtQuerySystemInformation (SystemProcessorPerformanceInformation, (PVOID) spt,
                                          sizeof spt[0] * SystemInfo.dwNumberOfProcessors, NULL);
        if (ntret == NO_ERROR)
        {
            for (unsigned int i = 0; i < SystemInfo.dwNumberOfProcessors; i++)
            {
                interrupt_count += spt[i].InterruptCount;
            }
            ret = _snprintf(buffer, len, "intr.value %u\n", interrupt_count);
            len -= ret;
            buffer += ret;
        }
        ntret = NtQuerySystemInformation (SystemPerformanceInformation, (PVOID) &spi, sizeof spi, NULL);
        if (ntret == NO_ERROR)
        {
            ret = _snprintf(buffer, len, "ctx.value %u\n", spi.ContextSwitches);
            len -= ret;
            buffer += ret;
        }
    }
    strncat(buffer, ".\n", len);
    return 0;
}