void main(int argc, char *argv[]) {
    ULONG NTEContext = 0;
    ULONG NTEInstance;
    IPAddr NewIP;
    IPAddr NewMask;
    DWORD Index;
    DWORD Context;
    CHAR NewIPStr[IPADDR_BUF_SIZE];
    CHAR NewMaskStr[IPADDR_BUF_SIZE];

    PIP_ADAPTER_INFO pAdapterInfo, pAdapt;
    PIP_ADDR_STRING pAddrStr;
    DWORD AdapterInfoSize;
    DWORD Err;
    BOOL OptList = FALSE;
    BOOL OptAdd = FALSE;
    BOOL OptDel = FALSE;

    NewIPStr[0] = '\0';
    NewMaskStr[0] = '\0';
    Context = Index = (DWORD)-1;
    for (int i = 1; i < argc; i++)
    {
        if ((argv[i][0] == '-') || (argv[i][0] == '/')) 
        {
            switch(tolower(argv[i][1])) 
            {
                case 'l':
                    OptList = TRUE;
                    break;
                case 'a':
                    OptAdd = TRUE;
                    break;
                case 'c':
                    if (strlen(argv[i]) > 2)
                        Context = atoi(&argv[i][2]);
                    break; 
                case 'd':
                    OptDel = TRUE;
                    break;
                case 'i':
                    if (strlen(argv[i]) > 2)
                        strcpy_s(NewIPStr, IPADDR_BUF_SIZE, &argv[i][2]);
                    break;
                case 'm':
                    if (strlen(argv[i]) > 2)
                        strcpy_s(NewMaskStr, IPADDR_BUF_SIZE, &argv[i][2]);
                    break;
                case 'n':
                    if (strlen(argv[i]) > 2)
                        Index = atoi(&argv[i][2]);
                    break;
                default:
                    printf("default\n");
                    Usage();
                    return;
                }
        }
        else
        {
            printf("else\n");
            Usage();
            return;
        }
    }

    // Check options
    if ((OptAdd && (Index == -1 || NewIPStr[0] == '\0' || NewMaskStr[0] == '\0'))
        || (OptDel && Context == -1))
    {
        Usage();
        return;
    }

    // Get sizing information about all adapters
    AdapterInfoSize = 0;
    if ((Err = GetAdaptersInfo(NULL, &AdapterInfoSize)) != 0)
    {
        if (Err != ERROR_BUFFER_OVERFLOW)
        {
            printf("GetAdaptersInfo sizing failed with error %d\n", Err);
            return;
        }
    }

    // Allocate memory from sizing information
    if ((pAdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc(GPTR, AdapterInfoSize)) == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    // Get actual adapter information
    if ((Err = GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize)) != 0)
    {
        printf("GetAdaptersInfo failed with error %d\n", Err);
        return;
    }

    if (OptList)
    {
        printf("MAC Address - Adapter\n"
            "Index     Context   Ip Address          Subnet Mask\n"
            "--------------------------------------------------------------\n");

        pAdapt = pAdapterInfo;

        while (pAdapt)
        {
            for (UINT i=0; i<pAdapt->AddressLength; i++)
            {
                if (i == (pAdapt->AddressLength - 1))
                    printf("%.2X - ",(int)pAdapt->Address[i]);
                else
                    printf("%.2X-",(int)pAdapt->Address[i]);
            }
            printf("%s\n", pAdapt->Description);

            pAddrStr = &(pAdapt->IpAddressList);
            while(pAddrStr)
            {
                printf("%-10.d%-10.d%-20.20s%s\n", pAdapt->Index, pAddrStr->Context, pAddrStr->IpAddress.String, pAddrStr->IpMask.String);
                pAddrStr = pAddrStr->Next;
            }

            pAdapt = pAdapt->Next;
        }
    }

    if (OptAdd)
    {
        NewIP = inet_addr(NewIPStr);
        NewMask = inet_addr(NewMaskStr);
        if ((Err = AddIPAddress(NewIP, NewMask, Index, &NTEContext, &NTEInstance)) != 0)
        {
            printf("AddIPAddress failed with error %d, %d\n", NTEContext, Err);
            return;
        }
    }

    if (OptDel)
    {
        if ((Err = DeleteIPAddress(Context)) != 0)
            printf("DeleteIPAddress failed %d\n", Err);
    }
}