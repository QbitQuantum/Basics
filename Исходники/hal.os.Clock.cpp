void hal::os::Clock::ReadCounters(s64 & tsc, s64 & pc)
{
    u64           rdtsc_a, rdtsc_b;
    LARGE_INTEGER pca;
    int           count = 0;
again:
    rdtsc_a = __rdtsc();
    ::NtQueryPerformanceCounter(&pca, 0);
    rdtsc_b = __rdtsc();
    if (rdtsc_b - rdtsc_a > 100000 && count++ < 5 ) goto again;
    tsc = s64((rdtsc_a + rdtsc_b)/2ULL);
    pc  = s64(pca.QuadPart);
}