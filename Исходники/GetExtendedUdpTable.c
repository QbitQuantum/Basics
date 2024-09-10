static DWORD GetExtendedUdpTableWithAlloc(PVOID *UdpTable, BOOL Order, DWORD Family, UDP_TABLE_CLASS Class)
{
    DWORD ret;
    DWORD Size = 0;

    *UdpTable = NULL;

    ret = GetExtendedUdpTable(*UdpTable, &Size, Order, Family, Class, 0);
    if (ret == ERROR_INSUFFICIENT_BUFFER)
    {
        *UdpTable = HeapAlloc(GetProcessHeap(), 0, Size);
        if (*UdpTable == NULL)
        {
            return ERROR_OUTOFMEMORY;
        }

        ret = GetExtendedUdpTable(*UdpTable, &Size, Order, Family, Class, 0);
        if (ret != NO_ERROR)
        {
            HeapFree(GetProcessHeap(), 0, *UdpTable);
            *UdpTable = NULL;
        }
    }

    return ret;
}