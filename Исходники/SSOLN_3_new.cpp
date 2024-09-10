IN_ADDR* Get_Table()
{
    PMIB_IPADDRTABLE pIPAddrTable;
    DWORD dwSize = 0;

    pIPAddrTable = (MIB_IPADDRTABLE *)MALLOC(sizeof (MIB_IPADDRTABLE));

    if (pIPAddrTable)
        if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER)
        {
            FREE(pIPAddrTable);
            pIPAddrTable = (MIB_IPADDRTABLE *)MALLOC(dwSize);
        }

    GetIpAddrTable(pIPAddrTable, &dwSize, 0);

    IN_ADDR* IPAddr = new IN_ADDR[pIPAddrTable->dwNumEntries];

    printf("List of the BroadCast Address: \n");
    for (int i = 0; i < (int)pIPAddrTable->dwNumEntries; i++)
    {
        IPAddr[i].S_un.S_addr = (u_long)pIPAddrTable->table[i].dwAddr | ~(u_long)pIPAddrTable->table[i].dwMask;
        printf("\tBroadCast[%d]: \t%s\n", i, inet_ntoa(IPAddr[i]));
    }

    FREE(pIPAddrTable);
    return IPAddr;
}