DWORD MyGetUdpStatistics(PMIB_UDPSTATS& pUdpStats)
{
    pUdpStats = (PMIB_UDPSTATS)malloc(sizeof(MIB_UDPSTATS));
    assert(pUdpStats != NULL);
    return GetUdpStatistics(pUdpStats);
}