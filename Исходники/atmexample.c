// Function: main()
// Description:
//    This function parses arguments and starts either the client or server
//    depending on the arguments. The server will enumerate local ATM
//    interfaces if necessary and bind to a local address and wait for
//    client connections. The server handles the client connection in the
//    same thread as the listening socket. The client only handles one
//    connection and then exits. If running the client, create a socket
//    and connect to the server. Once connected, send a message and read it back
int main_atm(int argc, char **argv)
{
    WSADATA      wsd;
    SOCKET       s;
    DWORD        dwAddrLen = sizeof(SOCKADDR_ATM);
    SOCKADDR_ATM atm_addr;
    int          ret, i;
    char         szAddress[41];
 
    // Initialize Winsock and parse command line arguments
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
    {
       printf("WSAStartup() failed with error code %d\n", WSAGetLastError());
       return -1;
    }
    else
       printf("WSAStartup() is OK!\n");
 
    // Find the protocol entry supporting ATM and create a socket
    lpSocketProtocol = FindProtocol_atm();
    if (lpSocketProtocol == NULL)
    {
       printf("FindProtocol() returned NULL!\n");
       return -1;
    }
    else
       printf("FindProtocol() is OK!\n");
 
    s = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO,
                  lpSocketProtocol, 0, WSA_FLAG_OVERLAPPED);
    if (s == INVALID_SOCKET)
    {
       printf("WSASocket() failed with error code %d\n", WSAGetLastError());
       return -1;
    }
    else
       printf("WSASocket() is OK!\n");
 
    ValidateArgs_atm(argc, argv);

    ZeroMemory((PVOID)&atm_addr, sizeof(atm_addr));
    atm_addr.satm_family                 = AF_ATM;
    atm_addr.satm_number.AddressType     = ATM_NSAP;
    atm_addr.satm_number.NumofDigits     = 20;
    atm_addr.satm_blli.Layer2Protocol    = SAP_FIELD_ABSENT;
    atm_addr.satm_blli.Layer3Protocol    = SAP_FIELD_ABSENT;
    atm_addr.satm_bhli.HighLayerInfoType = SAP_FIELD_ABSENT;
    // If an interface number was not supplied (i.e. a 38 character NSAP ATM address was supplied)
    if ((!bServer) || (dwInterface == -1))
    {
        strncpy_s(&szAddress[0], sizeof(szAddress[0]),szServerAddr, 38);
        strncpy_s(&szAddress[38], sizeof(szAddress[38]),szPort, 2);
        szAddress[40] = 0;
        AtoH_atm((char *) &atm_addr.satm_number.Addr[0], szAddress, 20);
    }
    else
    {
        // An index was supplied, look it up and get its address
        if (GetATMAddress_atm(s, dwInterface, &atm_addr.satm_number) == FALSE)
        {
            printf("Unable to get ATM interface!\n");
        }
        AtoH_atm((char *) &atm_addr.satm_number.Addr[19], szPort, 1);
    }
   
    if (bServer)
    {
        SOCKET        sclient;
        SOCKADDR_ATM  atm_client;
        int           atmaddrsz = sizeof(SOCKADDR_ATM);
        DWORD         dwClientAddrLen=MAX_ATM_ADDR_LEN;
        struct fd_set fdaccept;
        char          recvbuf[MAX_BUFFER], szClientAddr[MAX_ATM_ADDR_LEN], szAddr[MAX_BUFFER];
        dwAddrLen   = MAX_BUFFER;
 
        // Print out the address we're binding to
        if (WSAAddressToString((LPSOCKADDR)&atm_addr, sizeof(atm_addr), lpSocketProtocol, (LPWSTR)szAddr, &dwAddrLen))
        {
			printf("WSAAddressToString() failed with error code %d\n", WSAGetLastError());
        }
        else
            printf("WSAAddressToString() is OK!\n");
 
        printf("Binding to: <%s>\n", szAddr);

        if (bind(s, (SOCKADDR *)&atm_addr, sizeof(atm_addr)) == SOCKET_ERROR)
        {
            printf("bind() failed with error code %d\n", WSAGetLastError());
            return -1;
        }
        else
            printf("bind() should be fine!\n");
 
        if(listen(s, 7) == SOCKET_ERROR)
            printf("listen() failed with error code %d\n", WSAGetLastError());
        else
            printf("listen() is OK! I am listening...\n");

        FD_ZERO(&fdaccept);
        FD_SET(s, &fdaccept);

        if (select(0, &fdaccept, NULL, NULL, NULL) == SOCKET_ERROR)
            printf("Something wrong with select() with error code %d\n", WSAGetLastError());
        else if (select(0, &fdaccept, NULL, NULL, NULL) == 0)
            printf("select() - the time limit expired!\n");
        else
            printf("select() should be OK!\n");
 
        sclient = WSAAccept(s, (SOCKADDR *)&atm_client, &atmaddrsz, NULL, 0);
 
        if (sclient == INVALID_SOCKET)
        {
            printf("WSAAccept() failed with error code %d\n", WSAGetLastError());
            return -1;
        }
        else
            printf("WSAAccept() should be OK!\n");

        ZeroMemory((PVOID)szClientAddr, MAX_ATM_ADDR_LEN);
        if (WSAAddressToString((LPSOCKADDR)&atm_client, sizeof(atm_client), lpSocketProtocol, (LPWSTR)szClientAddr, &dwClientAddrLen))
        {
            printf("WSAAddressToString() failed with herror code %d\n", WSAGetLastError());
        }
        else
            printf("WSAAddressToString() is OK!\n");

        printf("Client's ATM ADDRESS: <%s>\n", szClientAddr);
 
        // Handle the client connection until it closes
        while (1)
        {
			ret = recv(sclient, recvbuf, MAX_BUFFER, 0);
			if (ret == SOCKET_ERROR)
			{
				if(WSAEDISCON == WSAGetLastError())
					printf("recv() - a connection closed by peer...\n");
				else
					printf("recv() failed with error code %d\n", WSAGetLastError());
				return -1;
			}
			else if (ret == 0)
			{
				printf("recv() - a graceful close!\n");
				break;
			}
			else
				printf("recv() is OK!\n");
 
            recvbuf[ret] = '\0';
            printf("Read: '%s'\n", recvbuf);
 
            ret = send(sclient, recvbuf, ret, 0);
 
            if (ret == SOCKET_ERROR)
            {
				if(WSAEDISCON == WSAGetLastError())
					printf("send() - a connection closed by peer!\n");
				else
					printf("send() failed with error code %d\n", WSAGetLastError());
				return -1;
            }
            else
                printf("send() should be OK!\n");

            printf("wrote %d bytes...\n", ret);
        }
        closesocket(sclient);
    }
    else
    {
        char     sendbuf[MAX_BUFFER], szAddr[MAX_BUFFER];
        dwAddrLen = MAX_BUFFER;

        // Connect and then send and recv data
        if (WSAAddressToString((LPSOCKADDR)&atm_addr, sizeof(atm_addr), lpSocketProtocol, (LPWSTR)szAddr, &dwAddrLen))
        {
            printf("WSAAddressToString() failed with error code %d\n", WSAGetLastError());
        }
        else
            printf("WSAAddressToString() is OK\n");
 
        printf("Connect to: <%s>\n", szAddr);
        if (connect(s, (SOCKADDR *)&atm_addr, sizeof(atm_addr)) == SOCKET_ERROR)
        {
            printf("connect() failed with error code %d\n", WSAGetLastError());
            return -1;
        }
        else
			printf("connect() is OK!\n");
 
        memset(sendbuf, '$', 512);
        for(i=0; i < 10 ;i++)
        {
            ret = send(s, sendbuf, 64, 0);
            if (ret == SOCKET_ERROR)
            {
                if(WSAEDISCON == WSAGetLastError())
					printf("send() - connection closed by peer!\n");
                else
                    printf("send() failed with error code %d\n", WSAGetLastError());
                return -1;
            }
			else
				printf("send() should be OK!\n");
 
			printf("Sent %d bytes\n", ret);
 
            ret = recv(s, sendbuf, ret, 0);
            if (ret == SOCKET_ERROR)
            {
				if(WSAEDISCON == WSAGetLastError())
					printf("recv() - connection closed by peer!\n");
				else
					printf("recv() failed with error code %d\n", WSAGetLastError());
				return -1;
            }
            else if (ret == 0)
            {
                printf("recv() - a graceful close\n");
                break;
            }
            else
                printf("recv() is OK!\n");
            sendbuf[ret] = '\0';
            printf("Read: '%s'\n", sendbuf);
        }
   }
   closesocket(s);
   WSACleanup();
   return 0;
}