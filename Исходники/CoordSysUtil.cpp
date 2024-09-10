//*****************************************************************************
INT64 GetAvailableMemory()
{
#ifdef _WIN32
    // Size of available memory in bytes, with an additional
    // 200Mb subtracted to take into account heap fragmentation,
    // and a 100Mb buffer for smaller allocations that may happen in
    // between checks.
    MEMORYSTATUSEX  statex;
    statex.dwLength = sizeof (statex);
    INT64 maxAvailable = 0L;
    if(GlobalMemoryStatusEx (&statex)) {
        maxAvailable = min(statex.ullAvailPhys + statex.ullAvailPageFile, statex.ullAvailVirtual);
        maxAvailable = (maxAvailable > 300000000L) ? maxAvailable - 300000000L : 0L;
    }
    return maxAvailable;
#else // LINUX
    throw new MgNotImplementedException(L"GetAvailableMemory", __LINE__, __WFILE__, NULL, L"", NULL);
#endif
}