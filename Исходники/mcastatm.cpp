//
// Function: Server
//
// Description:
//    Bind to the local interface and then invite each leaf
//    address which was specified on the command line.
//    Once each connection is made, send some data.
//
void Server(SOCKET s, WSAPROTOCOL_INFO *lpSocketProtocol)
{
    // Server routine
    //
    SOCKADDR_ATM  atmleaf, atmroot;
    WSABUF        wsasend;
    char          sendbuf[BUFSIZE],
                  szAddr[BUFSIZE];
    DWORD         dwBytesSent,
                  dwAddrLen=BUFSIZE,
                  dwNumInterfaces,
                  i;
    int           ret;

    // If no specified local interface is given pick the first
    // one
    //
    memset(&atmroot, 0, sizeof(SOCKADDR_ATM));
    if (!bLocalAddress)
    {
        dwNumInterfaces = GetNumATMInterfaces(s);
        GetATMAddress(s, 0, &atmroot.satm_number);
    }
    else
        AtoH((char *)&atmroot.satm_number.Addr[0], szLocalAddress, 
            ATM_ADDR_SIZE-1);
    //
    // Set the port number in the address structure
    //
    AtoH((char *)&atmroot.satm_number.Addr[ATM_ADDR_SIZE-1], szPort, 1);
    //
    // Fill in the rest of the SOCKADDR_ATM structure
    //
    atmroot.satm_family                 = AF_ATM;
    atmroot.satm_number.AddressType     = ATM_NSAP;
    atmroot.satm_number.NumofDigits     = ATM_ADDR_SIZE;
    atmroot.satm_blli.Layer2Protocol    = SAP_FIELD_ANY;
    atmroot.satm_blli.Layer3Protocol    = SAP_FIELD_ABSENT;
    atmroot.satm_bhli.HighLayerInfoType = SAP_FIELD_ABSENT;
    //
    // Print out what we're binding to and bind()
    //
    if (WSAAddressToString((LPSOCKADDR)&atmroot, 
        sizeof(atmroot), lpSocketProtocol, szAddr, 
        &dwAddrLen))
    {
        printf("WSAAddressToString failed: %d\n", 
            WSAGetLastError());
    }
    printf("Binding to: <%s>\n", szAddr);

    if (bind(s, (SOCKADDR *)&atmroot, 
        sizeof(SOCKADDR_ATM)) == SOCKET_ERROR)
    {
        printf("bind() failed: %d\n", WSAGetLastError());
        return;
    }
    // Invite each leaf
    //
    for(i=0; i < dwAddrCount ;i++)
    {
        // Fill in the SOCKADR_ATM structure for each leaf
        //
        memset(&atmleaf, 0, sizeof(SOCKADDR_ATM));
        AtoH((char *)&atmleaf.satm_number.Addr[0], szLeafAddresses[i],
            ATM_ADDR_SIZE-1);
        AtoH((char *)&atmleaf.satm_number.Addr[ATM_ADDR_SIZE-1], szPort,
            1);

        atmleaf.satm_family                 = AF_ATM;
        atmleaf.satm_number.AddressType     = ATM_NSAP;
        atmleaf.satm_number.NumofDigits     = ATM_ADDR_SIZE;
        atmleaf.satm_blli.Layer2Protocol    = SAP_FIELD_ANY;
        atmleaf.satm_blli.Layer3Protocol    = SAP_FIELD_ABSENT;
        atmleaf.satm_bhli.HighLayerInfoType = SAP_FIELD_ABSENT;
        //
        // Print out clients address and the invite it
        //
        if (WSAAddressToString((LPSOCKADDR)&atmleaf, 
            sizeof(atmleaf), lpSocketProtocol, szAddr, 
            &dwAddrLen))
        {
            printf("WSAAddressToString failed: %d\n", 
                WSAGetLastError());
        }
        printf("[%02d] Inviting: <%s>\n", i, szAddr);
   
        if ((sLeafSock[i] = WSAJoinLeaf(s, 
            (SOCKADDR *)&atmleaf, sizeof(SOCKADDR_ATM), NULL, 
            NULL, NULL, NULL, JL_SENDER_ONLY)) 
            == INVALID_SOCKET)
        {
            printf("WSAJoinLeaf() failed: %d\n", 
                WSAGetLastError());
            WSACleanup();
            return;
        }
    }
    // Note that the ATM protocol is a bit different that TCP.
    // When the WSAJoinLeaf (or connect call) completes the
    // peer has not necessarily accepted the connection yet
    // so immediately sending data will result in an error 
    // which is why we wait a short bit.
    // 
    printf("Press a key to start sending.");
    getchar();
    printf("\n");
    //
    // Now send some data to the group address which will
    // be replicated to all clients
    //
    wsasend.buf = sendbuf;
    wsasend.len = 128;
    for(i=0; i < dwDataCount ;i++)
    {
        memset(sendbuf, 'a' + (i%26), 128);
        ret = WSASend(s, &wsasend, 1, &dwBytesSent, 0, NULL, 
            NULL);
        if (ret == SOCKET_ERROR)
        {
            printf("WSASend() failed: %d\n", WSAGetLastError());
            break;
        }
        printf("[%02d] Wrote: %d bytes\n", i, dwBytesSent);
        Sleep(500);
    }

    for(i=0; i < dwAddrCount ;i++)
        closesocket(sLeafSock[i]);
    return;
}