int
main(int ac, char **av)
{
	int lc;			/* loop counter */
	char *msg;		/* message returned from parse_opts */
	char *file_name;	/* testfile name */
	char *test_desc;	/* test specific error message */
	int ind;		/* counter to test different test conditions */
	int pid;
    
	/* Parse standard options given to run the test. */
	msg = parse_opts(ac, av, (option_t *) NULL, NULL);
	if (msg != (char *) NULL) {
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);
		tst_exit();
	}

	/* Perform global setup for test */
	setup();

	/* set the expected errnos... */
	TEST_EXP_ENOS(exp_enos);

	pid = FORK_OR_VFORK();

	if (pid == -1) {
		tst_brkm(TBROK, cleanup, "fork() failed");
		/*NOTREACHED*/
	} else if (pid == 0) {
		if ((ltpuser = getpwnam(LTPUSER1)) == NULL) {
			tst_brkm(TBROK,cleanup,"%s not found in /etc/passwd",
				LTPUSER1);
			/*NOTREACHED*/
		}

		/* get uid of user */
		user_uid = ltpuser->pw_uid;

		seteuid(user_uid);

		/* Check looping state if -i option given */
		for (lc = 0; TEST_LOOPING(lc); lc++) {
			/* Reset Tst_count in case we are looping. */
			Tst_count=0;

			for (ind = 0; Test_cases[ind].desc != NULL; ind++) {
				file_name = Test_cases[ind].pathname;
				test_desc = Test_cases[ind].desc;

				/*
				 * Call utime(2) to test different test
				 * conditions. Verify that it fails with -1
				 * return value and sets appropriate errno.
				 */
				TEST(utime(file_name, NULL));

				/* Check return code from utime(2) */
				if (TEST_RETURN == -1) {
					TEST_ERROR_LOG(TEST_ERRNO);
					if (TEST_ERRNO ==
						Test_cases[ind].exp_errno) {
						tst_resm(TPASS, "utime() "
							"fails, %s, errno:%d",
							test_desc, TEST_ERRNO);
					} else {
						tst_resm(TFAIL, "utime(2) "
							"fails, %s, errno:%d, "
							"expected errno:%d",
							test_desc, TEST_ERRNO,
							Test_cases[ind].exp_errno);
					}
				} else {
					tst_resm(TFAIL, "utime(2) returned %d, "
						"expected -1, errno:%d",
						TEST_RETURN,
						Test_cases[ind].exp_errno);
				}
			}	/* End of TEST CASE LOOPING. */

			Tst_count++;		/* incr TEST_LOOP counter */

		}	/* End for TEST_LOOPING */
	} else {
		waitpid(pid, &status, 0);
		_exit(0);       /*
				 * Exit here and let the child clean up.
				 * This allows the errno information set
				 * by the TEST_ERROR_LOG macro and the
				 * PASS/FAIL status to be preserved for
				 * use during cleanup.
				 */
	}
	/* Call cleanup() to undo setup done for the test. */
	cleanup();
	/*NOTREACHED*/


  return(0);

}	/* End main */