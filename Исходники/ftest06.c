int main(int ac, char *av[])
{
	int pid, child, status, count, k, j;
	char name[3];

	int lc;
	const char *msg;

	/*
	 * parse standard options
	 */
	if ((msg = parse_opts(ac, av, NULL, NULL)) != NULL)
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);

	/*
	 * Default values for run conditions.
	 */
	iterations = 50;
	nchild = 5;

	if (signal(SIGTERM, term) == SIG_ERR) {
		tst_resm(TBROK, "first signal failed");

	}

	/* use the default values for run conditions */
	for (lc = 0; TEST_LOOPING(lc); lc++) {

		local_flag = PASSED;
		/*
		 * Make a directory to do this in; ignore error if already exists.
		 */
		parent_pid = getpid();
		tst_tmpdir();

		if (!startdir[0]) {
			if (getcwd(startdir, MAXPATHLEN) == NULL) {
				tst_brkm(TFAIL | TERRNO, NULL, "getcwd failed");
			}
		}
		cwd = startdir;

		snprintf(dirname, ARRAY_SIZE(dirname),
			 "%s/ftest06.%d", cwd, getpid());
		snprintf(homedir, ARRAY_SIZE(homedir),
			 "%s/ftest06h.%d", cwd, getpid());

		mkdir(dirname, 0755);
		mkdir(homedir, 0755);

		if (chdir(dirname) < 0)
			tst_brkm(TFAIL | TERRNO, cleanup, "\tCan't chdir(%s)",
				 dirname);

		dirlen = strlen(dirname);

		if (chdir(homedir) < 0)
			tst_brkm(TFAIL | TERRNO, cleanup, "\tCan't chdir(%s)",
				 homedir);

		/* enter block */
		for (k = 0; k < nchild; k++) {
			if ((child = fork()) == 0) {
				dotest(k, iterations);
				tst_exit();
			}
			if (child < 0) {
				tst_brkm(TBROK | TERRNO, cleanup,
					 "fork failed");
			}
			pidlist[k] = child;
		}

		/*
		 * Wait for children to finish.
		 */
		count = 0;
		while ((child = wait(&status)) > 0) {
			//tst_resm(TINFO,"Test{%d} exited status = 0x%x", child, status);
			//fprintf(stdout, "status is %d",status);
			if (status) {
				tst_resm(TFAIL,
					 "Test{%d} failed, expected 0 exit.",
					 child);
				local_flag = FAILED;
			}
			++count;
		}

		/*
		 * Should have collected all children.
		 */
		if (count != nchild) {
			tst_resm(TFAIL,
				 "Wrong # children waited on, count = %d",
				 count);
			local_flag = FAILED;
		}

		if (local_flag == PASSED)
			tst_resm(TPASS, "Test passed.");
		else
			tst_resm(TFAIL, "Test failed.");

		if (iterations > 26)
			iterations = 26;

		for (k = 0; k < nchild; k++)
			for (j = 0; j < iterations + 1; j++) {
				ft_mkname(name, dirname, k, j);
				rmdir(name);
				unlink(name);
			}

		if (chdir(startdir) < 0)
			tst_brkm(TFAIL | TERRNO, cleanup, "Can't chdir(%s)",
				 startdir);

		pid = fork();
		if (pid < 0) {
			tst_brkm(TBROK | TERRNO, NULL, "fork failed");
		}

		if (pid == 0) {
			execl("/bin/rm", "rm", "-rf", homedir, NULL);

		} else
			wait(&status);

		if (status)
			tst_resm(TINFO,
				 "CAUTION - ftest06, '%s' may not have been removed.",
				 homedir);

		pid = fork();
		if (pid < 0) {
			tst_brkm(TBROK | TERRNO, NULL, "fork failed");
		}
		if (pid == 0) {
			execl("/bin/rm", "rm", "-rf", dirname, NULL);
			exit(1);
		} else
			wait(&status);
		if (status) {
			tst_resm(TWARN,
				 "CAUTION - ftest06, '%s' may not have been removed.",
				 dirname);
		}

		sync();

	}

	if (local_flag == FAILED)
		tst_resm(TFAIL, "Test failed.");
	else
		tst_resm(TPASS, "Test passed.");

	cleanup();
	tst_exit();
}