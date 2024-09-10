//Basic execute function. Ripped straigh from the old source
void execute(char ***argv, int background, char **env) {
	pid_t pid;

	int status;

	if ((pid = fork()) < 0) {
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	} else if (pid == 0) {
		errno = 0;

		if (execvpe(**argv, *argv, env) < 0) {
			printf("%s\n", strerror(errno));
			exit(1);
		}
	} else {
		if (background == FALSE)
			while (wait(&status) != pid)
				;
		else
			printf("[1] %i\n", pid);
	}

	return;
}