/***********************************************************************
 * Main
 ***********************************************************************/
int main(int ac, char **av)
{
	int lc;			/* loop counter */
	char *msg;		/* message returned from parse_opts */
	char *fname;
	char *desc;
	int ind;
	struct stat *stbuf;
	struct sigaction sa, osa;

    /***************************************************************
     * parse standard options
     ***************************************************************/
	if ((msg = parse_opts(ac, av, (option_t *) NULL, NULL)) != (char *)NULL) {
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);
		tst_exit();
	}

    /***************************************************************
     * perform global setup for test
     ***************************************************************/
	setup();

	/* set the expected errnos... */
	TEST_EXP_ENOS(exp_enos);

    /***************************************************************
     * check looping state if -c option given
     ***************************************************************/
	for (lc = 0; TEST_LOOPING(lc); lc++) {

		/* reset Tst_count in case we are looping. */
		Tst_count = 0;

		for (ind = 0; Test_cases[ind].desc != NULL; ind++) {

			fname = Test_cases[ind].pathname;
			desc = Test_cases[ind].desc;
			stbuf = Test_cases[ind].stbuf;

			if (stbuf == (struct stat *)-1) {
				/* special sig11 case */
				sa.sa_handler = &sig11_handler;
				sigemptyset(&sa.sa_mask);
				sa.sa_flags = 0;

				sigaction(SIGSEGV, NULL, &osa);
				sigaction(SIGSEGV, &sa, NULL);

				if (setjmp(sig11_recover)) {
					TEST_RETURN = -1;
					TEST_ERRNO = EFAULT;
				} else {
					TEST(stat(fname, stbuf));
				}
				sigaction(SIGSEGV, &osa, NULL);
			} else {
				/*
				 *  Call stat(2)
				 */

				TEST(stat(fname, stbuf));
			}

			/* check return code */
			if (TEST_RETURN == -1) {
				if (STD_FUNCTIONAL_TEST) {
					if (TEST_ERRNO ==
					    Test_cases[ind].exp_errno)
						tst_resm(TPASS,
							 "stat(<%s>, &stbuf) Failed, errno=%d",
							 desc, TEST_ERRNO);
					else
						tst_resm(TFAIL,
							 "stat(<%s>, &stbuf) Failed, errno=%d, expected errno:%d",
							 desc, TEST_ERRNO,
							 Test_cases[ind].
							 exp_errno);
				} else
					Tst_count++;
			} else {
				tst_resm(TFAIL,
					 "stat(<%s>, &stbuf) returned %ld, expected -1, errno:%d",
					 desc, TEST_RETURN,
					 Test_cases[ind].exp_errno);
			}
		}

	}			/* End for TEST_LOOPING */

    /***************************************************************
     * cleanup and exit
     ***************************************************************/
	cleanup();

	return 0;
}				/* End main */