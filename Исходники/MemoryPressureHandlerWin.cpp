void MemoryPressureHandler::windowsMeasurementTimerFired()
{
    setUnderMemoryPressure(false);

    BOOL memoryLow;

    if (QueryMemoryResourceNotification(m_lowMemoryHandle.get(), &memoryLow) && memoryLow) {
        setUnderMemoryPressure(true);
        releaseMemory(Critical::Yes);
        return;
    }

#if CPU(X86)
    PROCESS_MEMORY_COUNTERS_EX counters;

    if (!GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&counters), sizeof(counters)))
        return;

    // On Windows, 32-bit processes have 2GB of memory available, where some is used by the system.
    // Debugging has shown that allocations might fail and cause crashes when memory usage is > ~1GB.
    // We should start releasing memory before we reach 1GB.
    const int maxMemoryUsageBytes = 0.9 * 1024 * 1024 * 1024;

    if (counters.PrivateUsage > maxMemoryUsageBytes) {
        setUnderMemoryPressure(true);
        releaseMemory(Critical::Yes);
    }
#endif
}