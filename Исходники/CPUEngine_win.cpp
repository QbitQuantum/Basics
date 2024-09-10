int CPUEngine_win::getSPPI()
{
    if (!pNtQuerySystemInformation)
        return getSystemTimes();

    ULONG retlen = 0;
    NTSTATUS status = pNtQuerySystemInformation(
            (SYSTEM_INFORMATION_CLASS) 8/*SystemProcessorPerformanceInformation*/,
            m_sppi_ptr,
            (ULONG) m_sppi_cb,
            &retlen);
    if (retlen) {
        if (retlen % sizeof(LH_SPPI))
            qFatal("CPUEngine_win: retlen %lu is not a multiple of %u", retlen, sizeof(LH_SPPI));
        if (retlen != m_sppi_cb) {
            m_sppi_ptr = realloc(m_sppi_ptr, retlen);
            m_sppi_cb = m_sppi_ptr ? retlen : 0;
            return getSPPI();
        }
    }
    if (status)
        qFatal("CPUEngine_win: NTSTATUS %ld received", (long) status);
    return (int) (m_sppi_cb / sizeof(LH_SPPI));
}