void* WinSockets::allocateSocketTable(unsigned long protocol,
                                      unsigned long family) {
    unsigned long ret = 0;
    unsigned long buffsize = 0;
    void* pSockTable = nullptr;

    /// Allocate the TCP Socket Tables
    if (protocol == IPPROTO_TCP) {
        ret = GetExtendedTcpTable(
                  pSockTable, &buffsize, true, family, TCP_TABLE_OWNER_PID_ALL, 0);
        if (ret == ERROR_INSUFFICIENT_BUFFER) {
            pSockTable = static_cast<void*>(malloc(buffsize));
            if (pSockTable == nullptr) {
                status_ = Status(
                              1, "Unable to allocate sufficient memory for the TCP socket table");
            }
        }
        ret = GetExtendedTcpTable(pSockTable,
                                  reinterpret_cast<PULONG>(&buffsize),
                                  true,
                                  family,
                                  TCP_TABLE_OWNER_PID_ALL,
                                  0);
        if (ret != NO_ERROR) {
            status_ = Status(1,
                             "Error retrieving the socket table: ( " +
                             std::to_string(GetLastError()) + " )");
        }
    }
    /// Allocate the UDP Socket Tables
    else {
        ret = GetExtendedUdpTable(pSockTable,
                                  reinterpret_cast<PULONG>(&buffsize),
                                  true,
                                  family,
                                  UDP_TABLE_OWNER_PID,
                                  0);
        if (ret == ERROR_INSUFFICIENT_BUFFER) {
            pSockTable = static_cast<void*>(malloc(buffsize));
            if (pSockTable == nullptr) {
                status_ = Status(
                              1, "Unable to allocate sufficient memory for the UDP socket table");
            }
        }
        ret = GetExtendedUdpTable(pSockTable,
                                  reinterpret_cast<PULONG>(&buffsize),
                                  true,
                                  family,
                                  UDP_TABLE_OWNER_PID,
                                  0);
        if (ret != NO_ERROR) {
            status_ = Status(1,
                             "Error retrieving the socket table: ( " +
                             std::to_string(GetLastError()) + " )");
        }
    }
    return pSockTable;
}