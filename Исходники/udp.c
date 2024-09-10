long
read_udp_stat(UDP_STAT_STRUCTURE * udpstat, int magic)
{
    long            ret_value = -1;
#if (defined(CAN_USE_SYSCTL) && defined(UDPCTL_STATS))
    static int      sname[4] =
        { CTL_NET, PF_INET, IPPROTO_UDP, UDPCTL_STATS };
    size_t          len = sizeof(*udpstat);
#endif
#ifdef solaris2
    static mib2_ip_t ipstat;
#endif

#ifdef hpux11
    int             fd;
    struct nmparms  p;
    unsigned int    ulen;

    if ((fd = open_mib("/dev/ip", O_RDONLY, 0, NM_ASYNC_OFF)) < 0)
        return (-1);            /* error */

    switch (magic) {
    case UDPINDATAGRAMS:
        p.objid = ID_udpInDatagrams;
        break;
    case UDPNOPORTS:
        p.objid = ID_udpNoPorts;
        break;
    case UDPOUTDATAGRAMS:
        p.objid = ID_udpOutDatagrams;
        break;
    case UDPINERRORS:
        p.objid = ID_udpInErrors;
        break;
    default:
        *udpstat = 0;
        close_mib(fd);
        return (0);
    }

    p.buffer = (void *) udpstat;
    ulen = sizeof(UDP_STAT_STRUCTURE);
    p.len = &ulen;
    ret_value = get_mib_info(fd, &p);
    close_mib(fd);

    return (ret_value);         /* 0: ok, < 0: error */
#else                           /* hpux11 */

    if (udp_stats_cache_marker &&
        (!atime_ready
         (udp_stats_cache_marker, UDP_STATS_CACHE_TIMEOUT * 1000)))
#ifdef solaris2
        return (magic == UDPNOPORTS ? ipstat.udpNoPorts : 0);
#else
        return 0;
#endif

    if (udp_stats_cache_marker)
        atime_setMarker(udp_stats_cache_marker);
    else
        udp_stats_cache_marker = atime_newMarker();

#ifdef linux
    ret_value = linux_read_udp_stat(udpstat);
#endif

#ifdef WIN32
    ret_value = GetUdpStatistics(udpstat);
#endif

#ifdef solaris2
    if (magic == UDPNOPORTS) {
        if (getMibstat
            (MIB_IP, &ipstat, sizeof(mib2_ip_t), GET_FIRST,
             &Get_everything, NULL) < 0)
            ret_value = -1;
        else
            ret_value = ipstat.udpNoPorts;
    } else
        ret_value = getMibstat(MIB_UDP, udpstat, sizeof(mib2_udp_t),
                               GET_FIRST, &Get_everything, NULL);
#endif

#ifdef HAVE_SYS_TCPIPSTATS_H
    ret_value = sysmp(MP_SAGET, MPSA_TCPIPSTATS, udpstat, sizeof *udpstat);
#endif

#if defined(CAN_USE_SYSCTL) && defined(UDPCTL_STATS)
    ret_value = sysctl(sname, 4, udpstat, &len, 0, 0);
#endif

#ifdef UDPSTAT_SYMBOL
    if (auto_nlist(UDPSTAT_SYMBOL, (char *) udpstat, sizeof(*udpstat)))
        ret_value = 0;
#endif

    if (ret_value == -1) {
        free(udp_stats_cache_marker);
        udp_stats_cache_marker = NULL;
    }
    return ret_value;
#endif                          /* hpux11 */
}