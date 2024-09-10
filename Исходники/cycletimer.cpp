bool CycleTimer::GetThreadCyclesS(unsigned __int64* cycles)
{
    BOOL res = FALSE;
    res = QueryThreadCycleTime(GetCurrentThread(), cycles);
    return res != FALSE;
}