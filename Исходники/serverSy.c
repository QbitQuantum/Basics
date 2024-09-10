void initConnection(char *empfIP,char *port, char* file, int fenstergroesse){
	struct request nachricht;
	char* reqChar;
	int retSend, reqLen,test;
	unsigned long addr;
	struct hostent *host_info;

	WSADATA wsaData;
	WORD wVersionRequested;
	FILE *fp;

	//komplett von http://msdn.microsoft.com/de-de/library/windows/desktop/ms738630(v=vs.85).aspx übernommen
	int RetVal,testi,AddrLen;
	ADDRINFO Hints, *AddrInfo;
	char AddrName[NI_MAXHOST];
	struct sockaddr_storage Addr;
	//komplett von http://msdn.microsoft.com/de-de/library/windows/desktop/ms738630(v=vs.85).aspx übernommen


	wVersionRequested = MAKEWORD(2,1);
	if( WSAStartup( wVersionRequested,&wsaData ) == SOCKET_ERROR ){
		printf( "Error: WSAStartup() throws error nr. %d!\n" ,WSAGetLastError());
		exit(-1);
	}

	//komplett von http://msdn.microsoft.com/de-de/library/windows/desktop/ms738630(v=vs.85).aspx übernommen
	memset(&Hints, 0, sizeof (Hints));
    Hints.ai_family = AF_INET6;
    Hints.ai_socktype = SOCK_DGRAM;
    RetVal = getaddrinfo(empfIP, port, &Hints, &AddrInfo);
    if (RetVal != 0) {
        fprintf(stderr,
                "Cannot resolve address [%s] and port [%s], error %d: %s\n",
                empfIP, port, RetVal, gai_strerror(RetVal));
        WSACleanup();
        exit(-1);
    }
	//
    // Try each address getaddrinfo returned, until we find one to which
    // we can successfully connect.
    //
	for (AI = AddrInfo; AI != NULL; AI = AI->ai_next) {
		// Open a socket with the correct address family for this address.
		ConnSocket = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
		printf("socket call with family: %d socktype: %d, protocol: %d\n",
               AI->ai_family, AI->ai_socktype, AI->ai_protocol);
        if (ConnSocket == INVALID_SOCKET)
            printf("socket call failed with %d\n", WSAGetLastError());
		 if (ConnSocket == INVALID_SOCKET) {
            fprintf(stderr, "Error Opening socket, error %d\n",
                    WSAGetLastError());
            continue;
        }
		  printf("Attempting to connect to: %s\n", empfIP ? empfIP : "localhost");
        if (connect(ConnSocket, AI->ai_addr, (int) AI->ai_addrlen) != SOCKET_ERROR)
            break;

        testi = WSAGetLastError();
        if (getnameinfo(AI->ai_addr, (int) AI->ai_addrlen, AddrName,
                        sizeof (AddrName), NULL, 0, NI_NUMERICHOST) != 0)
            strcpy_s(AddrName, sizeof (AddrName), UNKNOWN_NAME);
        fprintf(stderr, "connect() to %s failed with error %d\n",
                AddrName, testi);
        closesocket(ConnSocket);
    }

	 if (AI == NULL) {
        fprintf(stderr, "Fatal error: unable to connect to the server.\n");
        WSACleanup();
        exit(-1);
    }
	 AddrLen = sizeof (Addr);
    if (getpeername(ConnSocket, (LPSOCKADDR) & Addr, (int *) &AddrLen) == SOCKET_ERROR) {
        fprintf(stderr, "getpeername() failed with error %d\n",
                WSAGetLastError());
    } else {
        if (getnameinfo((LPSOCKADDR) & Addr, AddrLen, AddrName,
                        sizeof (AddrName), NULL, 0, NI_NUMERICHOST) != 0)
            strcpy_s(AddrName, sizeof (AddrName), UNKNOWN_NAME);
        printf("Connected to %s, port %d, protocol %s, protocol family %s\n",
               AddrName, ntohs(SS_PORT(&Addr)),
               (AI->ai_socktype == SOCK_STREAM) ? "TCP" : "UDP",
               (AI->ai_family == PF_INET) ? "PF_INET" : "PF_INET6");
    }
	//komplett von http://msdn.microsoft.com/de-de/library/windows/desktop/ms738630(v=vs.85).aspx übernommen

	
	//schicke erste nachricht
	nachricht.FlNr = (long) fenstergroesse; //fenstergröße
	if(file != NULL) memcpy(nachricht.fname,file,sizeof(nachricht.fname));//dateiname
	nachricht.fname[strlen(file)] = '\0';
	nachricht.ReqType = ReqHello;//nachrichtentyp
	nachricht.name[0] = '\0';

	fp = openFile(file);
	nachricht.SeNr = getFileSize();//größe der datei
	closeFile(fp);
	
	//umwandeln des struct request in char*
	reqChar = (char*) malloc(sizeof(nachricht));
	memcpy(reqChar,&nachricht,sizeof(nachricht));
	sizeof(nachricht);
	UserInformation(2,&nachricht,NULL);

	//senden der ersten nachricht
	retSend = sendto(ConnSocket,reqChar,sizeof(nachricht),0,AI->ai_addr, (int) AI->ai_addrlen);

	//auswerten des returnwertes von send
	if(retSend != sizeof(nachricht)){
		printf("Error: Es wurden nicht alle Daten versand!");
	}
	
}