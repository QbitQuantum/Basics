void test() {
	pid_t	pid;
	if((pid = fork()) < 0) {
		Perror("fork error");
	} else if(pid == 0) {
		do_lock("lock.dat");
	} else {
		sleep(2);
		do_lock("lock.dat");
	}
}