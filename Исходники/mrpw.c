struct netif *netif_open(int timeout_ms)
{
    int inum = 0;
    int i = 0, total_interfaces = 0;
    struct netif *netif;
    IP_ADAPTER_INFO *AdapterInfo;
    IP_ADAPTER_INFO *Current;
    ULONG AIS;
    DWORD status;

    netif = (struct netif *)calloc(1, sizeof(struct netif));

    /* Retrieve the device list on the local machine */
    if (pcap_findalldevs(&netif->alldevs, netif->errbuf) == -1) {
        printf("Error finding interfaces\n");
        goto error_return;
    }

    /* Print the list */
    for (netif->d = netif->alldevs; netif->d; netif->d = netif->d->next) {
        /*printf("%d. %s", ++i, d->name); */
        printf("%d", ++i);
        if (netif->d->description)
            printf(" (%-70s)\n", netif->d->description);
        else
            printf(" (No description available)\n");
    }
    total_interfaces = i;

    if (i == 0) {
        printf
        ("\nNo interfaces found! Make sure WinPcap is installed.\n");
        goto error_return;
    }

    printf("Enter the interface number (1-%d):", i);
    scanf_s("%d", &inum);

    if (inum < 1 || inum > i) {
        printf("\nInterface number out of range.\n");
        /* Free the device list */
        pcap_freealldevs(netif->alldevs);
        goto error_return;
    }

    /* Jump to the selected adapter */
    for (netif->d = netif->alldevs, i = 0; i < inum - 1;
            netif->d = netif->d->next, i++) ;

    /* Open the device */
    if ((netif->pcap_interface = pcap_open_live(netif->d->name,	// name of the device
                                 65536,	// portion of the packet to capture
                                 // 65536 guarantees that the whole packet will be captured on all the link layers
                                 1,	// promiscuous mode
                                 timeout_ms,	// read timeout in ms
                                 netif->errbuf	// error buffer
                                               )) == NULL) {
        fprintf(stderr,
                "\nUnable to open the adapter. %s is not supported by WinPcap\n",
                netif->d->name);
        /* Free the device list */
        pcap_freealldevs(netif->alldevs);
        goto error_return;
    }

    /* lookup ip address */
    AdapterInfo =
        (IP_ADAPTER_INFO *) calloc(total_interfaces,
                                   sizeof(IP_ADAPTER_INFO));
    AIS = sizeof(IP_ADAPTER_INFO) * total_interfaces;
    status = GetAdaptersInfo(AdapterInfo, &AIS);
    if (status != ERROR_SUCCESS) {
        fprintf(stderr,
                "\nError, GetAdaptersInfo() call in netif_win32_pcap.c failed\n");
        free(AdapterInfo);
        goto error_return;
    }

    for (Current = AdapterInfo; Current != NULL; Current = Current->Next) {
        if (strstr(netif->d->name, Current->AdapterName) != 0) {
            uint32_t my_ip;
            ULONG len;
            uint8_t tmp[16];

            my_ip =
                inet_addr(Current->IpAddressList.IpAddress.String);
            len = sizeof(tmp);
            SendARP(my_ip, INADDR_ANY, tmp, &len);
            memcpy(netif->mac, &tmp[0], sizeof(netif->mac));
        }
    }
    free(AdapterInfo);
    return netif;

error_return:
    free(netif);
    return NULL;
}