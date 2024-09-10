int
tcp_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    ret_value = GetTcpStatistics(&tcpstat);

    if ( ret_value < 0 ) {
        DEBUGMSGTL(("mibII/tcpScalar", "Failed to load TCP scalar Group (win32)\n"));
    } else {
        DEBUGMSGTL(("mibII/tcpScalar", "Loaded TCP scalar Group (win32)\n"));
    }
    return ret_value;
}