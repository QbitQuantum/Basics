static size_t computeRAMSize()
{
#if OS(WINDOWS)
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    bool result = GlobalMemoryStatusEx(&status);
    if (!result)
        return ramSizeGuess;
    return status.ullTotalPhys;
#elif defined(USE_SYSTEM_MALLOC) && USE_SYSTEM_MALLOC
#if OS(LINUX)
    struct sysinfo si;
    sysinfo(&si);
    return si.totalram * si.mem_unit;
#else
#error "Missing a platform specific way of determining the available RAM"
#endif // OS(LINUX)
#else
    return bmalloc::api::availableMemory();
#endif
}