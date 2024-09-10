int callapi(char *command, char *host, short int port)
{
	char buf[RECVSIZE+1];
	struct hostent *ip;
	struct sockaddr_in serv;
	SOCKETTYPE sock;
	int ret = 0;
	int n, p;

	SOCKETINIT;

	ip = gethostbyname(host);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVSOCK) {
		printf("Socket initialisation failed: %s\n", SOCKERRMSG);
		return 1;
	}

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr = *((struct in_addr *)ip->h_addr);
	serv.sin_port = htons(port);

	if (SOCKETFAIL(connect(sock, (struct sockaddr *)&serv, sizeof(struct sockaddr)))) {
		printf("Socket connect failed: %s\n", SOCKERRMSG);
		return 1;
	}

	n = send(sock, command, strlen(command), 0);
	if (SOCKETFAIL(n)) {
		printf("Send failed: %s\n", SOCKERRMSG);
		ret = 1;
	}
	else {
		p = 0;
		buf[0] = '\0';
		while (p < RECVSIZE) {
			n = recv(sock, &buf[p], RECVSIZE - p , 0);

			if (SOCKETFAIL(n)) {
				printf("Recv failed: %s\n", SOCKERRMSG);
				ret = 1;
				break;
			}

			if (n == 0)
				break;

			p += n;
			buf[p] = '\0';
		}

		if (ONLY)
			printf("%s\n", buf);
		else {
			printf("Reply was '%s'\n", buf);
			display(buf);
		}
	}

	CLOSESOCKET(sock);

	return ret;
}