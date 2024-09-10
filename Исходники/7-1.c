int main(void)
{
	sem_t *mysemp;
	char semname[28];
	int pid, status;

	sprintf(semname, "/" FUNCTION "_" TEST "_%d", getpid());

	mysemp = sem_open(semname, O_CREAT, 0, 1);
	if (mysemp == SEM_FAILED || mysemp == NULL) {
		perror(ERROR_PREFIX "sem_open");
		return PTS_UNRESOLVED;
	}

	if (sem_wait(mysemp) == -1) {
		perror(ERROR_PREFIX "sem_wait");
		return PTS_UNRESOLVED;
	}

	pid = fork();
	if (pid == 0) {		// child create the semaphore.
		struct sigaction act;

		act.sa_handler = handler;
		act.sa_flags = 0;
		if (sigemptyset(&act.sa_mask) == -1) {
			perror("Error calling sigemptyset\n");
			return CHILDFAIL;
		}
		if (sigaction(SIGABRT, &act, 0) == -1) {
			perror("Error calling sigaction\n");
			return CHILDFAIL;
		}

		sem_wait(mysemp);

		if (errno == EINTR) {
			printf("Test PASSED\n");
			return (CHILDPASS);
		}
		puts("TEST FAILED: errno != EINTR");
		return (CHILDFAIL);

	} else {		// parent to send a signal to child
		int i;
		sleep(1);
		status = kill(pid, SIGABRT);	// send signal to child
		if (wait(&i) == -1) {
			perror("Error waiting for child to exit\n");
			return PTS_UNRESOLVED;
		}

		if (!WEXITSTATUS(i)) {
			return PTS_FAIL;
		}
		puts("TEST PASSED");
		sem_unlink(semname);
		return PTS_PASS;
	}

	return PTS_UNRESOLVED;
}