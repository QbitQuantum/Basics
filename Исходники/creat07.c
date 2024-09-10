int main(int ac, char **av)
{
	int lc;			/* loop counter */
	char *msg;		/* message returned from parse_opts */
	int retval = 0, status;
	pid_t pid, pid2;

	if ((msg = parse_opts(ac, av, NULL, NULL)) != NULL)
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);

	setup(av[0]);

	TEST_EXP_ENOS(exp_enos);

	for (lc = 0; TEST_LOOPING(lc); lc++) {

		Tst_count = 0;

		if ((pid = FORK_OR_VFORK()) == -1)
			tst_brkm(TBROK|TERRNO, cleanup, "fork #1 failed");

		if (pid == 0) {
			char *av[1];
			av[0] = basename(test_app);
			(void)execve(test_app, av, NULL);
			perror("execve failed");
			exit(1);
		}

		if ((pid2 = FORK_OR_VFORK()) == -1)
			tst_brkm(TBROK, cleanup, "fork #2 failed");

		if (pid2 == 0) {
			sleep(10);

			TEST(creat(test_app, O_WRONLY));

			if (TEST_RETURN != -1) {
				retval = 1;
				printf("creat didn't fail as expected\n");
			} else if (TEST_ERRNO == ETXTBSY)
				printf("received ETXTBSY\n");
			else {
				retval = 1;
				perror("creat failed unexpectedly");
			}

			if (kill(pid, SIGKILL) == -1) {
				retval = 1;
				perror("kill failed");
			}
			exit(retval);
		}
		if (wait(&status) == -1)
			tst_brkm(TBROK|TERRNO, cleanup, "wait failed");
		if (WIFEXITED(status) || WEXITSTATUS(status) == 0)
			tst_resm(TPASS, "creat functionality correct");
		else
			tst_resm(TFAIL, "creat functionality incorrect");
	}
	cleanup();

	tst_exit();
}