unsigned long __stdcall ConnectThread(void * pParam)
{
	USES_CONVERSION;

    CoInitialize ((void*)COINIT_MULTITHREADED);

    tintin_puts2(rs::rs(1184));

    SOCKET sock;
    int connectresult;
    struct sockaddr_in sockaddr;

    if(iswdigit(*strConnectAddress)) {                            /* interprete host part */
        sockaddr.sin_addr.s_addr=inet_addr(W2A(strConnectAddress));

		struct hostent *hp;
		if((hp=gethostbyaddr((const char*)&sockaddr, sizeof(sockaddr), AF_INET))==NULL) {
            wcscpy(MUDHostName, strConnectAddress);
        } else {
			wcscpy(MUDHostName, A2W(hp->h_name));
        }	
    } else {
		wcscpy(MUDHostName, strConnectAddress);

        struct hostent *hp;
        if((hp=gethostbyname(W2A(strConnectAddress)))==NULL) {
            tintin_puts2(rs::rs(1185));
            return 0;
        } else {
    	    struct in_addr inad;
            wchar_t ipaddr[256];

	        inad.S_un.S_addr = *(long*)hp->h_addr_list[0];
            swprintf(ipaddr , rs::rs(1186) , A2W(inet_ntoa(inad)));
	        tintin_puts2(ipaddr); 
        }
        memcpy((char *)&sockaddr.sin_addr, hp->h_addr, sizeof(sockaddr.sin_addr));
    }

    if(iswdigit(*strConnectPort))
        sockaddr.sin_port=htons((short)_wtoi(strConnectPort));      /* inteprete port part */
    else {
        tintin_puts2(rs::rs(1187));
        return 0;
    }

START1:
    if((sock=socket(AF_INET, SOCK_STREAM, 0))<0)
        tintin_puts2(rs::rs(1188));

	BOOL enable_opt = TRUE;
	/*
	 Something more than TCP_NODELAY should be done in case MUD server frequently sends tiny packets.
	 For example, if server sends prompt-line and IAC-GA in separate calls of send() then the first
	 packet (prompt) wouldn't ACKed by windows core for 200 milliseconds regardless of Nagle's algorithm,
	 leading to IAC-GA delayed for the same time. It's not a problem for visualizing since now JMC
	 prints out all incoming data immidiately; but processing of prompt line in described situation
	 by #acion and jmc.Incoming handlers will be delayed for 200 ms or value of Uncomplete line delay
	 setting in case it is less than 200.
	 Setting registry value on the client's machine (TcpAckFrequency := 1) is ugly, but effective solution.
	 No other solution (i.e. disabling delayed acknowledgement for particular socket) was found for
	 WinSock/WinSock2, WinXP/Vista/Win7/Win8. So it is responsibility of MUD servers to do wise and
	 accurate TCP bufferisation, though obviously it is possible only in MUDs where the smallest time period
	 between events (game-state updating period, "tick", time-quant) is less than 200ms.
	 At this point I giving up to solve this issue completely and mark it as part 
	 of global MUD problem called "Telnet Curse".
	*/
	if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&enable_opt, sizeof(enable_opt))) {
		tintin_puts2(L"#Can't disable Nagle's algorithm");
	}

    sockaddr.sin_family=AF_INET;


	reset_telnet_protocol();
	multiline_length = 0;

	if (ulProxyAddress) {
		wchar_t buf[BUFFER_SIZE];
		swprintf(buf, rs::rs(1303),
			(ulProxyAddress >> 24) & 0xff, (ulProxyAddress >> 16) & 0xff, (ulProxyAddress >> 8) & 0xff, (ulProxyAddress >> 0) & 0xff);
		tintin_puts2(buf);
	} else {