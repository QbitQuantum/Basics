int main(int argc, char **argv)
{
	/* The following things are used for getopt: */
	extern char *optarg;
	extern int optind;
	extern int opterr;
	int ch;

        in_addr_t dest;
        struct sockaddr_in destaddr,fromaddr,servaddr;
        socklen_t fromlen;
        int sockfd_r;
        struct hostent *hp;
        char *buf;
        char dest_str[16];
#define RBLEN 500
        char recbuf[RBLEN+1];
        ssize_t recmegslen;


        fromlen = sizeof(fromaddr); // this is important otherwise recvfrom will return "Invalid argument"
	opterr = 0;
	while ((ch = getopt(argc, argv, "hp:")) != -1) {
		switch (ch) {
			case 'p':
				sscanf(optarg,"%d",&portnum);
				break;
			case 'h':
				help();
			case '?':
				fprintf(stderr, "ERROR: No such option. -h for help.\n");
				exit(1);
			/*no default action for case */
			}
	}
	if (optind != argc -2){
		/* exactly two arguments must be given */
		help();
	}
        if (strlen(argv[optind])>45){
                fprintf(stderr,"Error: command too long. Max is 45\n");
                exit(1);
        }
        buf=argv[optind];
        //
        hp=gethostbyname(argv[optind+1]);
        if (hp==NULL){
                fprintf(stderr,"Error: %s is not a IP address and not a resolvable hostname\n",argv[optind+1]);
                exit(1);
        }
        // take the first address:
        strncpy(dest_str,inet_ntoa(*(struct in_addr*)hp->h_addr_list[0]),sizeof(dest_str));
        dest_str[sizeof(dest_str)-1]='\0';
        dest=inet_addr(dest_str);
        if (dest==INADDR_NONE){
                fprintf(stderr,"Error: IP addr. not valid\n");
                exit(1);
        }
        //
        printf("II: data: %s, ip: %s port: %d\n",argv[optind],dest_str,portnum);
        /* initialize the socket address for the destination: */
        destaddr.sin_family = AF_INET;
        destaddr.sin_addr.s_addr = dest;
        destaddr.sin_port = htons(portnum); // dest port
        /* initialize the socket address for this server: */
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
        servaddr.sin_port = htons(portnum); // source port
	memset(&servaddr.sin_zero, 0, sizeof(servaddr.sin_zero)); // zero fill

        if ((sockfd_r = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        {
                perror("open socket failed");
                exit(1);
        }
        if (bind(sockfd_r, (struct sockaddr *)&servaddr, sizeof(servaddr))){
                perror("bind socket failed");
                exit(1);
        }
        // we are bound. The parent will get the message even if the sender
	// sends it before we call recvfrom
	/* the closing \0 will be sent as well: */
	if(sendto(sockfd_r,buf,strlen(buf)+1,0,(struct sockaddr *)&destaddr,sizeof(destaddr)) == -1){
		perror("sendto failed");
		exit(1);
	}
        // we will timeout if there is no answer after a few sec
        signal(SIGALRM, &timeout_handler);
        alarm(3);
        recmegslen=recvfrom(sockfd_r,recbuf,RBLEN-1,0,(struct sockaddr *)&fromaddr,&fromlen);
        if(recmegslen == -1){
                perror("recvfrom failed");
                exit(1);
        }
        close(sockfd_r);
        recbuf[recmegslen]='\0';
        printf("OK: %s: %s\n",inet_ntoa(fromaddr.sin_addr),recbuf);
        //
        return(0);
}