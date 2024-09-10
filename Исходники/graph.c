static MIB_IFROW QueryInterfaceRowXP(
    _Inout_ PPH_NETADAPTER_SYSINFO_CONTEXT Context
    )
{    
    MIB_IFROW interfaceRow;

    memset(&interfaceRow, 0, sizeof(MIB_IFROW));

    interfaceRow.dwIndex = Context->AdapterEntry->InterfaceIndex;

    GetIfEntry(&interfaceRow);

    //MIB_IPINTERFACE_ROW table;
    //memset(&table, 0, sizeof(MIB_IPINTERFACE_ROW));
    //table.Family = AF_INET;
    //table.InterfaceIndex = Context->AdapterEntry->InterfaceIndex;
    //GetIpInterfaceEntry(&table);

    return interfaceRow;
}