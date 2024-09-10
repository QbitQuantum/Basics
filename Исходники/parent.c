int main(int argc, char **argv)
{
	int pid, rc, status;
	security_context_t context_s;
	context_t context;

	if (argc != 3) {
		fprintf(stderr, "usage:  %s newdomain program\n", argv[0]);
		exit(-1);
	}

	rc = getcon(&context_s);
	if (rc < 0) {
		fprintf(stderr, "%s:  unable to get my context\n", argv[0]);
		exit(-1);

	}

	context = context_new(context_s);
	if (!context) {
		fprintf(stderr, "%s:  unable to create context structure\n", argv[0]);
		exit(-1);
	}

	if (context_type_set(context, argv[1])) {
		fprintf(stderr, "%s:  unable to set new type\n", argv[0]);
		exit(-1);
	}

	freecon(context_s);
	context_s = context_str(context);
	if (!context_s) {
		fprintf(stderr, "%s:  unable to obtain new context string\n", argv[0]);
		exit(-1);
	}

	rc = setexeccon(context_s);
	if (rc < 0) {
		fprintf(stderr, "%s:  unable to set exec context to %s\n", argv[0], context_s);
		exit(-1);
	}

	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(-1);
	} else if (pid == 0) {
		rc = execv(argv[2], argv + 2);
		perror(argv[3]);
		exit(1);
	}

	pid = wait(&status);
	if (pid < 0) {
		perror("wait");
		exit(1);
	}

	if (WIFEXITED(status)) {
		exit(WEXITSTATUS(status));
	}

	exit(-1);
}