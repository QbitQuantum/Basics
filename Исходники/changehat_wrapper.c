int main(int argc, char *argv[]) {
	int rc;
	pid_t pid;
	int waitstatus;
	int filedes[2];
	int c, o;
	char buf[BUFSIZ];
	unsigned long magic_token = SD_ID_MAGIC+1;
	int manual = 0;
	int exit_hat = 0;
	char * manual_string;

	while ((c = getopt_long (argc, argv, "+", long_options, &o)) != -1) {
		if (c == 0) {
			switch (o) {
			    case 0: 
			    	magic_token = strtoul (optarg, NULL, 10);
				break;
			    case 1:
			    	manual = 1;
				manual_string = 
					(char *) malloc(strlen(optarg) + 1);
				if (!manual_string) {
					fprintf(stderr, "FAIL: malloc failed\n");
					exit(1);
				}
				strcpy(manual_string, optarg);
				break;
			    case 2:
			    	exit_hat = 1;
				break;
			    case 3:
			        usage(argv[0]);
				break;
			    default:
			        usage(argv[0]);
				break;
			}
		} else {
			usage(argv[0]);
		}
	}

	if (!argv[optind])
		usage(argv[0]);

	rc = pipe(filedes);
	if (rc != 0) {
		perror("FAIL: pipe failed");
		exit(1);
	}
	
	pid = fork();
	if (pid == -1) {
		fprintf(stderr, "FAIL: fork failed - %s\n",
			strerror(errno));
		exit(1);
	} else if (pid != 0) {
		/* parent */
		close(filedes[1]);
		read(filedes[0], &buf, sizeof(buf));
		rc = wait(&waitstatus);
		if (rc == -1){
			fprintf(stderr, "FAIL: wait failed - %s\n",
				strerror(errno));
			exit(1);
		}
	} else {
		/* child */
		char * pname = malloc (strlen(argv[optind]) + 3);
		if (!pname) {
			perror ("FAIL: child malloc");
			return -1;
		}
		sprintf (pname, "%s", argv[optind]);
		
		rc = !manual ? change_hat(argv[optind], magic_token) 
			     : manual_change_hat(argv[optind], manual_string); 
		if (rc != 0) {
			rc = !manual ? change_hat(NULL, magic_token) 
				     : manual_change_hat(NULL, manual_string); 
			fprintf(stderr, "FAIL: hat for %s does not exist\n",
				argv[optind]);
			exit(1);
		}		

		close(filedes[0]);
		fclose(stdout);
		rc = dup2(filedes[1], STDOUT_FILENO);
		if (rc < 0) {
			perror("FAIL: pipe failed");
			exit(1);
		}

		exit(execv(pname, &argv[optind]));
	}

	if (exit_hat) {
		rc = !manual ? change_hat(NULL, magic_token) 
			     : manual_change_hat(NULL, manual_string); 
		/* shouldn't fail, if it does, we've been killed */
		if (rc != 0) {
			fprintf(stderr, "FAIL: exiting hat '%s' failed\n",
				argv[optind]);
			exit(1);
		}
	}

	if ((WEXITSTATUS(waitstatus) == 0) && strcmp("PASS\n", buf) == 0) {
		printf("PASS\n");
	}

	return WEXITSTATUS(waitstatus);
}