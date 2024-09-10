int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "give 2 args\n");
		exit(-1);
	}
    pid2_t = mmap(NULL, sizeof(*pid2_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    pid_t lpid1, lpid2;
	char file2[FILE_NAME_SIZE];
    strncpy(file2, argv[2], FILE_NAME_SIZE);
	char input[256];
    strncpy(file1, argv[1], FILE_NAME_SIZE);
	pipe(pipe1);
	pipe(pipe2);

	signal(SIGINT, terminate);
    
	if ((lpid1 = fork()) == 0)
	{
		int read_bytes = 0;
		char c;
        printf("1 process pid is %d\n", getpid());
		signal(SIGUSR1, switch_files);
		fd1 = open(file1, O_RDONLY);
		if (fd1 < 0)
		{
			fprintf(stderr, "error opening file %s\n", file1);
			return -1;
		}
		while(1)
		{
			read_bytes = read(fd1, &c, 1);
			if (read_bytes > 0)
			{ 
    		    fprintf(stdout, "%c\n", toupper(c));
			}
			usleep(500000);			
		}
		close(fd1);
		printf("fd1 closed\n");
		return 0;
	} else {
        pid1 = lpid1;
    }

	if ((lpid2 = fork()) == 0)
	{
		int read_bytes = 0;
		char c;
		printf("2 process pid is %d\n", getpid());
		signal(SIGUSR2, switch_files);
		fd2 = open(file2, O_RDONLY);
		if (fd2 < 0)
		{
			fprintf(stderr, "error opening file %s\n", file2);
			return -1;
		}
		while(1)
		{
			read_bytes = read(fd2, &c, 1);
			if (read_bytes > 0)
			{
    		    fprintf(stdout, "\t%c\n", tolower(c));
			}
			usleep(500000);
		}
		close(fd2);
		printf("fd2 closed\n");
		return 0;
	} else {
        *pid2_t = lpid2;
        pid2 = lpid2;
    }
    
    printf("%d %d\n", pid1, pid2);
	while(scanf("%s", input) > 0)
	{
		write(pipe1[1], input, strlen(input) + 1);
		kill(pid1, SIGUSR1);
	}

	waitpid(pid1, 0, 0);
	waitpid(pid2, 0, 0);
	printf("exit\n");
}