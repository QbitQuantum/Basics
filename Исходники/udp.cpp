int
udp_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    ret_value = GetUdpStatistics(&udpstat);

    if ( ret_value < 0 ) {
        DEBUGMSGTL(("mibII/udpScalar", "Failed to load UDP scalar Group (win32)\n"));
    } else {
        DEBUGMSGTL(("mibII/udpScalar", "Loaded UDP scalar Group (win32)\n"));
    }
    return ret_value;
}