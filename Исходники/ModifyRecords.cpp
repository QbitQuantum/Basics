//  the main function 
void __cdecl main(int argc, char *argv[])

{

    DNS_STATUS status;               // return value of  DnsModifyRecordsInSet() function.
    PDNS_RECORD pmyDnsRecord = NULL; //pointer to DNS_RECORD structure
    PIP4_ARRAY pSrvList = NULL;      //pinter to IP4_ARRAY structure
    LPTSTR pOwnerName = NULL, pNameData = NULL;  //owner name and the data for CNAME resource record
    char HostipAddress[BUFFER_LEN];         //Ip address required to add host record
    char DnsServIp[BUFFER_LEN];             //DNS server ip address

    memset(HostipAddress, 0, sizeof(HostipAddress) );
    memset(DnsServIp, 0, sizeof(DnsServIp) );


    //Allocate memory for DNS_RECORD structure.

    pmyDnsRecord = (PDNS_RECORD) LocalAlloc( LPTR, sizeof( DNS_RECORD ) );

    if (!pmyDnsRecord) {
        printf("Memory allocaltion failed\n");
        exit(1);
    }

    if (argc > 8) {

        for (int i = 1; i < argc ; i++) {

            if ( (argv[i][0] == '-') || (argv[i][0] == '/') ) {

                switch (tolower(argv[i][1])) {
                
                case 'n':
                    pOwnerName = argv[++i];
                    pmyDnsRecord->pName = pOwnerName; //copy the Owner name information 
                    break;

                case 't':
                    if (!_stricmp(argv[i+1], "A") )
                        pmyDnsRecord->wType = DNS_TYPE_A; //add host records
                    else if (!_stricmp(argv[i+1], "CNAME") )
                        pmyDnsRecord->wType = DNS_TYPE_CNAME; //add CNAME records
                    else
                        Usage(argv[0]);
                    i++;
                    break;

                case 'l':
                    pmyDnsRecord->dwTtl = atoi(argv[++i]); // time to live value in seconds
                    break;
                case 'd':
                    if (pmyDnsRecord->wType == DNS_TYPE_A) {
                        pmyDnsRecord->wDataLength = sizeof(DNS_A_DATA); //data structure for A records
                        strncpy_s(HostipAddress, _countof(HostipAddress), argv[++i], _TRUNCATE);
                        HostipAddress[sizeof(HostipAddress)-1] = '\0';
                        pmyDnsRecord->Data.A.IpAddress = inet_addr(HostipAddress); //convert string to proper address
                        if ( pmyDnsRecord->Data.A.IpAddress == INADDR_NONE ) {
                            printf("Invalid IP address in A record data \n");
                            Usage(argv[0]);
                        }
                        break;
                    }
                    else {
                        pmyDnsRecord->wDataLength = sizeof(DNS_PTR_DATA); //data structure for CNAME records
                        pNameData = argv[++i];
                        pmyDnsRecord->Data.Cname.pNameHost = pNameData;
                        break;
                    }
                case 's':
                    // Allocate memory for IP4_ARRAY structure
                    pSrvList = (PIP4_ARRAY) LocalAlloc(LPTR,sizeof(IP4_ARRAY));
                    if (!pSrvList) {
                        printf("Memory allocation failed \n");
                        exit(1);
                    }
                    if (argv[++i]) {
                        strncpy_s(DnsServIp, _countof(DnsServIp), argv[i], _TRUNCATE);
                        DnsServIp[sizeof(DnsServIp)-1] = '\0';
                        pSrvList->AddrCount = 1;
                        pSrvList->AddrArray[0] = inet_addr(DnsServIp); //DNS server IP address
                        if ( pSrvList->AddrArray[0] == INADDR_NONE ) {
                            printf("Invalid DNS server IP address\n");
                            Usage(argv[0]);
                        }
                        break; 
                    }

                default:
                    Usage(argv[0]);
                    break;
                }
            }
            else
                Usage(argv[0]);


        }   

    }
    else {
        Usage(argv[0]);
    }



    // Calling function DNSModifyRecordsInSet_A to add Host or CNAME records    

    status = DnsModifyRecordsInSet_A(pmyDnsRecord,                     //pointer to DNS_RECORD
                                     NULL,                      
                                     DNS_UPDATE_SECURITY_USE_DEFAULT,  //do not attempt secure dynamic updates
                                     NULL,                             //use default credentials
                                     pSrvList,                         //contains DNS server IP address
                                     NULL);                            //reserved for future use

    if (status) {
        if (pmyDnsRecord->wType == DNS_TYPE_A)
            printf("Failed to add the host record for %s and the error is %d \n", pOwnerName, status);
        else
            printf("Failed to add the Cname record for %s and the error is %d \n", pOwnerName, status);
    }
    else {
        if (pmyDnsRecord->wType == DNS_TYPE_A)
            printf("Successfully added the host record for %s \n", pOwnerName);
        else
            printf("Successfully added the Cname record for %s \n", pOwnerName);
    }           


    LocalFree(pmyDnsRecord); // Free the memory allocated for DNS_RECORD structure
    LocalFree(pSrvList);     // Free the memory allocated for IP4_ARRAY structure


}