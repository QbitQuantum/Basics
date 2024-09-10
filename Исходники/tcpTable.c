int
tcpTable_load(netsnmp_cache *cache, void *vmagic)
{
    PMIB_TCPTABLE pTcpTable = NULL;
    DWORD         dwActualSize = 0;
    DWORD         status = NO_ERROR;

    /*
     * query for the buffer size needed
     */
    status = GetTcpTable(pTcpTable, &dwActualSize, TRUE);
    if (status == ERROR_INSUFFICIENT_BUFFER) {
        pTcpTable = (PMIB_TCPTABLE) malloc(dwActualSize);
        if (pTcpTable != NULL) {
            /*
             * Get the sorted TCP table
             */
            status = GetTcpTable(pTcpTable, &dwActualSize, TRUE);
        }
    }

    if (status == NO_ERROR) {
        int           i;

        DEBUGMSGTL(("mibII/tcpTable", "Loaded TCP Table (WIN32)\n"));
        tcp_size = pTcpTable->dwNumEntries -1;  /* entries are counted starting with 0 */
        tcp_head = pTcpTable->table;

        /*
         * Count the number of established connections
         * Probably not actually necessary for Windows
         */
        for (i = 0; i < tcp_size; i++) {
            if (tcp_head[i].dwState == 5 /* established */ ||
                    tcp_head[i].dwState == 8 /*  closeWait  */ )
                tcp_estab++;
        }
        return 0;
    }

    DEBUGMSGTL(("mibII/tcpTable", "Failed to load TCP Table (win32)\n"));
    if (pTcpTable)
        free(pTcpTable);
    return -1;
}