void
CcpsShutdown(void)
{
    EventUnRegister(&gCcpCtrlEvent);
    close(gCcpCsock);
    gCcpCsock = -1;
    EventUnRegister(&gCcpDataEvent);
    close(gCcpDsock);
    gCcpDsock = -1;
}