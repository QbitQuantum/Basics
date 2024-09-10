VOID ShowUdpStatistics()
{
    PMIB_UDPSTATS pUdpStats;
    DWORD dwRetVal;

    pUdpStats = (MIB_UDPSTATS*) HeapAlloc(GetProcessHeap(), 0, sizeof(MIB_UDPSTATS));

    if ((dwRetVal = GetUdpStatistics(pUdpStats)) == NO_ERROR)
    {
        _tprintf(_T("\nUDP Statistics for IPv4\n\n"));
        _tprintf(_T("  %-21s = %lu\n"), _T("Datagrams Received"), pUdpStats->dwInDatagrams);
        _tprintf(_T("  %-21s = %lu\n"), _T("No Ports"), pUdpStats->dwNoPorts);
        _tprintf(_T("  %-21s = %lu\n"), _T("Receive Errors"), pUdpStats->dwInErrors);
        _tprintf(_T("  %-21s = %lu\n"), _T("Datagrams Sent"), pUdpStats->dwOutDatagrams);
    }
    else
        DoFormatMessage(dwRetVal);

    HeapFree(GetProcessHeap(), 0, pUdpStats);
}