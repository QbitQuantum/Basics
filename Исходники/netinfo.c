VOID
AddressDemo(
    VOID
    )
{
    NETIO_STATUS Status;
    PMIB_UNICASTIPADDRESS_TABLE UnicastTable = NULL;
    MIB_UNICASTIPADDRESS_ROW Row;
    ULONG i;
    IN6_ADDR Ipv6Address = {0xfe,0x3f,0,0,0,0,0,0,0,0,0,0,0,0,0x20,0x00};
    HANDLE Handle;
    NET_IFINDEX InterfaceIndex = 0;

    //
    // Retrieve all the IP addresses.
    //
    
    Status = 
        GetUnicastIpAddressTable(
            AF_UNSPEC, &UnicastTable);
    if (!WIN_SUCCESS(Status)) {
        printf(
            "GetUnicastAddressTable Failed. Error %d\n", 
            Status);
    } else {
        printf(
            "GetUnicastAddressTable Succeeded.\n");
        printf(
            "Total Number of all IP Address Entries: %d.\n",
            UnicastTable->NumEntries);
        for (i = 0; i < UnicastTable->NumEntries; i++) {
            printf("Address %2d:  ", i);
            PrintIpAddress(&UnicastTable->Table[i].Address);
			      printf("\n");
        }
        FreeMibTable(UnicastTable); 
        printf("\n\n");
    }   
    
    //
    // Retrieve IPv6 Only Addresses.
    //

    Status = 
        GetUnicastIpAddressTable(
            AF_INET6, &UnicastTable);
    if (!WIN_SUCCESS(Status)) {
        printf(
            "GetUnicastAddressTable Failed. Error %d\n", 
            Status);
    } else {
        printf(
            "GetUnicastAddressTable Succeeded.\n");
        printf(
            "Total Number of IPv6 Address Entries: %d.\n",
            UnicastTable->NumEntries);
        for (i = 0; i < UnicastTable->NumEntries; i++) {
            printf("Address %2d:  ", i);
            PrintIpAddress(&UnicastTable->Table[i].Address);
            printf("\n");
        }
        InterfaceIndex = UnicastTable->Table[i - 1].InterfaceIndex;
        FreeMibTable(UnicastTable);        
    }

    Status = 
        NotifyUnicastIpAddressChange(
            AF_UNSPEC, 
            //(PUNICAST_IPADDRESS_CHANGE_CALLBACK)AddressCallbackDemo,
            &AddressCallbackDemo,
            NULL,
            FALSE, 
            &Handle);

    if (!WIN_SUCCESS(Status)) {
        printf(
            "\nRegister address change failed. Error %d\n", 
            Status);
    } else {
        printf(
            "\nRegister address change succeeded.\n");     
    } 
    InitializeUnicastIpAddressEntry(&Row);
    Row.Address.si_family = AF_INET6;
    INETADDR_SET_ADDRESS((PSOCKADDR)&Row.Address, (PUCHAR)&Ipv6Address);
    Row.InterfaceIndex = InterfaceIndex;
    Status = 
        CreateUnicastIpAddressEntry(&Row);
    if (!WIN_SUCCESS(Status)) {
        printf("Create IPv6 unicast address entry failed. Error %d\n", 
            Status);
    } else {
        printf("Create IPv6 unicast address entry succeeded.\n"); 
    }

    Status = 
        GetUnicastIpAddressEntry(&Row);
    if (!WIN_SUCCESS(Status)) {
        printf("Get IPv6 unicast address failed. Error %d\n", Status);
    } else {
        printf("Get IPv6 unicast address entry succeeded.\n"); 
    }

    Row.PreferredLifetime = 500000;
    Status = 
        SetUnicastIpAddressEntry(&Row);
    if (!WIN_SUCCESS(Status)) {
        printf("Set IPv6 unicast address entry failed. Error %d\n", 
            Status);
    } else {
        printf("Set IPv6 unicast address entry succeeded.\n"); 
    }
    
    Status = 
        DeleteUnicastIpAddressEntry(&Row);
    if (!WIN_SUCCESS(Status)) {
        printf("Delete Ipv6 Unicast Address Failed. Error %d\n", 
            Status);
    } else {
        printf("Delete Ipv6 Unicast Address Succeeded.\n"); 
    }

    Sleep(2000);
    Status = CancelMibChangeNotify2(Handle);
    if (!WIN_SUCCESS(Status)) {
        printf(
            "Deregister address change failed. Error %d\n\n", 
            Status);
    } else {
        printf(
            "Deregister address change succeeded.\n\n");     
    }
}