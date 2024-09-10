int get_mac_address(char* address) {
#if defined(_WIN32)
    IP_ADAPTER_INFO AdapterInfo[16]; // Allocate information for up to 16 NICs
    DWORD dwBufLen = sizeof(AdapterInfo); // Save memory size of buffer
    // Call GetAdapterInfo
    DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);

    if(dwStatus != ERROR_SUCCESS) {
        return -1;
    }
    strcpy(address, "");
    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to current adapter info
    while (pAdapterInfo) {
        sprintf(address, "%02x:%02x:%02x:%02x:%02x:%02x",
            pAdapterInfo->Address[0], pAdapterInfo->Address[1], pAdapterInfo->Address[2], 
            pAdapterInfo->Address[3], pAdapterInfo->Address[4], pAdapterInfo->Address[5]
        );
        if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET) break;
        pAdapterInfo = pAdapterInfo->Next;
    }
    return 0;

#elif defined(__APPLE__)
    kern_return_t   kernResult = KERN_SUCCESS; // on PowerPC this is an int (4 bytes)
    /*
     *  error number layout as follows (see mach/error.h and IOKitLib/IOReturn.h):
     *
     *  hi            lo
     *  | system(6) | subsystem(12) | code(14) |
     */
    io_iterator_t   intfIterator;
    int retval = 0;

    kernResult = FindEthernetInterfaces(&intfIterator);
    if (KERN_SUCCESS != kernResult) {
        fprintf(stderr, "FindEthernetInterfaces returned 0x%08x\n", kernResult);
        retval = -1;
    } else {
        kernResult = GetMACAddress(intfIterator, address);
        if (KERN_SUCCESS != kernResult) {
            fprintf(stderr, "GetMACAddress returned 0x%08x\n", kernResult);
            retval = -1;
        }
    }
    IOObjectRelease(intfIterator);
    return retval;

#elif defined(SIOCGIFCONF) || defined(SIOCGLIFCONF)
    char          buf[1024];
#ifdef HAVE_STRUCT_LIFCONF
    struct lifconf ifc;
    struct lifreq *ifr;
#else
    struct ifconf ifc;
    struct ifreq *ifr;
#endif
    int           sck;
    int           nInterfaces;
    int           i;
    /* Get a socket handle. */
    sck = socket(AF_INET, SOCK_DGRAM, 0);
    if (sck < 0) {
        perror("socket");
        return -1;
    }
    /* Query available interfaces. */
#ifdef HAVE_STRUCT_LIFCONF
    ifc.lifc_len = sizeof(buf);
    ifc.lifc_buf = buf;
    if (ioctl(sck, SIOCGLIFCONF, &ifc) < 0) {
        perror("ioctl(SIOCGLIFCONF)");
        close(sck);
        return -1;
    }
#else
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sck, SIOCGIFCONF, &ifc) < 0) {
        perror("ioctl(SIOCGIFCONF)");
        close(sck);
        return -1;
    }
#endif

#ifdef HAVE_STRUCT_LIFCONF
    /* Iterate through the list of interfaces. */
    ifr         = ifc.lifc_req;
    nInterfaces = ifc.lifc_len / sizeof(struct lifreq);
#else
    ifr        = ifc.ifc_req;
    nInterfaces = ifc.ifc_len / sizeof(struct ifreq);
#endif
    strcpy(address, "");

    for (i = 0; i < nInterfaces; i++) {
#ifdef HAVE_STRUCT_LIFCONF
        struct lifreq *item = &ifr[i];
#else
        struct ifreq *item = &ifr[i];
#endif
        struct ether_addr *hw_addr; 
        /* Get the MAC address */
#ifdef SIOCGIFHWADDR
        if(ioctl(sck, SIOCGIFHWADDR, item) < 0) {
            perror("ioctl(SIOCGIFHWADDR)");
            close(sck);
            return -1;
        }
        hw_addr=(struct ether_addr *)(item->ifr_hwaddr.sa_data);
#elif  defined(SIOCGIFARP)
        if(ioctl(sck, SIOCGIFARP, item) < 0) {
            perror("ioctl(SIOCGIFARP)");
            close(sck);
            return -1;
        }
        hw_addr = (struct ether_addr *)&(item->lifr_lifru.lifru_enaddr);  
#endif
        strcpy(address, ether_ntoa(hw_addr));
#ifdef HAVE_STRUCT_LIFCONF
        if (strstr(item->lifr_name, "eth")) break;
#else
        if (strstr(item->ifr_name, "eth")) break;
#endif
    }
    close(sck);
    if (!strcmp(address, "")) return -1;
    if (!strcmp(address, "0:0:0:0:0:0")) return -1;

    return 0;
#else
#warning Don`t know how to obtain MAC address.  get_mac_address() will fail.
    return -1;
#endif
}