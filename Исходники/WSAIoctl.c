BOOL Test_WSAIoctl_InitTest(
    OUT PMIB_IPADDRTABLE* ppTable)
{
    PMIB_IPADDRROW pRow;
    DWORD ret, i1;
    ULONG TableSize;
    PMIB_IPADDRTABLE pTable;

    TableSize = 0;
    *ppTable = NULL;
    ret = GetIpAddrTable(NULL, &TableSize, FALSE);
    if (ret != ERROR_INSUFFICIENT_BUFFER)
    {
        skip("GetIpAddrTable failed with %ld. Abort Testing.\n", ret);
        return FALSE;
    }

    /* get sorted ip-address table. Sort order is the ip-address. */
    pTable = (PMIB_IPADDRTABLE)malloc(TableSize);
    *ppTable = pTable;
    ret = GetIpAddrTable(pTable, &TableSize, TRUE);
    if (ret != NO_ERROR) 
    {
        skip("GetIpAddrTable failed with %ld. Abort Testing.\n", ret);
        return FALSE;
    }

    if (winetest_debug >= 2)
    {
        trace("Result of GetIpAddrTable:\n");
        trace("Count: %ld\n", pTable->dwNumEntries);
        pRow = pTable->table;
        for (i1 = 0; i1 < pTable->dwNumEntries; i1++)
        {
            trace("** Entry %ld **\n", i1);
            trace("  dwAddr %lx\n", pRow->dwAddr);
            trace("  dwIndex %lx\n", pRow->dwIndex);
            trace("  dwMask %lx\n", pRow->dwMask);
            trace("  dwBCastAddr %lx\n", pRow->dwBCastAddr);
            trace("  dwReasmSize %lx\n", pRow->dwReasmSize);
            trace("  wType %x\n", pRow->wType);
            pRow++;
        }
        trace("END\n");
    }

    return TRUE;
}