static void
os_sockQueryInterfaceStatusReset(
    os_sockQueryInterfaceStatusInfo *info)
{
    HANDLE hand = NULL;
    DWORD ret;

    (void)WSAResetEvent(info->overlap.hEvent);
    (void)CancelIPChangeNotify(&info->overlap);
    ret = NotifyAddrChange(&hand, &info->overlap);
    if (ret != NO_ERROR) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
            os_report(OS_ERROR, "os_sockQueryInterfaceStatusReset", __FILE__, __LINE__, 0,
                          "Failed to reset notifications for network interface address changes");
        }
    }
}