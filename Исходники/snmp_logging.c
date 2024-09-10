void
snmp_disable_syslog_entry(netsnmp_log_handler *logh)
{
    if (!logh || !logh->enabled || logh->type != NETSNMP_LOGHANDLER_SYSLOG)
        return;

#ifdef WIN32
    if (logh->magic) {
        HANDLE eventlog_h = (HANDLE)logh->magic;
        CloseEventLog(eventlog_h);
        logh->magic = NULL;
    }
#else
    closelog();
    logh->imagic  = 0;
#endif

    netsnmp_disable_this_loghandler(logh);
}