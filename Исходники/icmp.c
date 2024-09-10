int
icmp_load(netsnmp_cache *cache, void *vmagic)
{
    long            ret_value = -1;

    ret_value = GetIcmpStatistics(&icmpstat);

    if ( ret_value < 0 ) {
        DEBUGMSGTL(("mibII/icmp", "Failed to load ICMP Group (win32)\n"));
    } else {
        DEBUGMSGTL(("mibII/icmp", "Loaded ICMP Group (win32)\n"));
    }
    return ret_value;
}