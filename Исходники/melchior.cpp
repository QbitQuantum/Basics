DWORD WINAPI ThreadFunc(PVOID)
{
  TCHAR szIPFrom[18];
      TCHAR szReply[128];
     
      CIcmpReply IcmpReply;
#pragma chMSG(Funzione schifo ma tanto va rifatta tutta...)
      HWND hwnd = GetForegroundWindow();

      GetDlgItemText(hwnd, IDC_IPFROM, szIPFrom, chDIMOF(szIPFrom));

      WSADATA wsadata;
	    if (WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
		    _tprintf(TEXT("WSAStartup %i\n"), WSAGetLastError());
      SOCKET s=WSASocket(AF_INET,SOCK_RAW,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED);

      CIcmp Icmp;

      CInetAddr InAddr;

      BOOL bStatus = InAddr.LookUp(szIPFrom);
      assert(bStatus);
      Icmp.SendEcho(InAddr, NULL, 0, 64, 0, 0, 1000, &IcmpReply);

      wsprintf(szReply, TEXT("Reply from %x TTL %i RoundTrip %i %i bytes"), 
                        IcmpReply.Address, 
                        IcmpReply.Ttl,
                        IcmpReply.RoundTripTime,
                        IcmpReply.DataSize);

      //GetDlgItemText(hwnd, IDC_IPFROM, szFrom, chDIMOF(szFrom));
      //SetDlgItemText(hwnd, IDC_IPTO, szFrom);
      HWND hwndLB = GetDlgItem(hwnd, IDC_LBREPLY);
      ListBox_SetCurSel(hwndLB, ListBox_AddString(hwndLB, szReply));

      SOCKADDR_IN if0;
      
      if0.sin_port=0;
      if0.sin_family=AF_INET;
      ZeroMemory(&if0.sin_zero, sizeof(if0.sin_zero));
      
      if0.sin_addr.S_un.S_addr = InAddr;
	//Attiva la comunicazione usando le strutture SOCKADDR e SOCKADDR_IN, le 
	//quali contengono le informazioni per risolvere gli address Internet domains.
      if (bind(s,(SOCKADDR *)&if0,sizeof(if0)) == SOCKET_ERROR)
      {
        _tprintf(TEXT("Bind %i\n"), WSAGetLastError());
      }

      DWORD dwBytesRet=0;

      int optval=1;   

      if(WSAIoctl(s,SIO_RCVALL,&optval,sizeof(optval),NULL,0,&dwBytesRet,NULL,NULL)==SOCKET_ERROR)
      {
        _tprintf(TEXT("WSAIoctl %i\n"), WSAGetLastError());
      }

      for(;;)
      {
        char buf[MAX_IP_SIZE];
        dwBytesRet=0;
        DWORD dwFlags=0;
        WSABUF wsb;

        wsb.buf = buf;  
        wsb.len = MAX_IP_SIZE;
    		memset(wsb.buf,0x0,MAX_IP_SIZE);

        if(SOCKET_ERROR==WSARecv(s,&wsb,1,&dwBytesRet,&dwFlags,NULL,NULL))
        {
          DWORD error = WSAGetLastError();
          _tprintf(TEXT("%i\n"), error);
          break;
        }

        IN_ADDR inaddr;
        

        TCHAR szMsg[MAX_IP_SIZE];
        PIPHEADER iphdr = (PIPHEADER)(wsb.buf);
        
        inaddr.S_un.S_addr = iphdr->dwDestIP;
        char buff[60];

        strcpy_s(buff, 60, inet_ntoa(inaddr));

        //struct hostent* hent = gethostbyaddr(buff, strlen(buff), 0);
        //ASSERT(hent != NULL);
          
        
        wsprintf(szMsg, TEXT("Packet: %x %x %x %x"), iphdr->dwSourceIP,
                                                     iphdr->dwDestIP,
                                                     iphdr->cbNextProtocol,
                                                     iphdr->wTotalLen);

        ListBox_SetCurSel(hwndLB, ListBox_AddString(hwndLB, szMsg));
      }
      return 0;
}