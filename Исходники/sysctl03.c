int main(int ac, char **av)
{
	int exp_eno;
	int lc;
	char *msg;

	char osname[OSNAMESZ];
	int osnamelth, status;
	int name[] = { CTL_KERN, KERN_OSTYPE };
	pid_t pid;
	struct passwd *ltpuser;

	if ((msg = parse_opts(ac, av, NULL, NULL)) != NULL) {
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);
	}

	setup();

	if ((tst_kvercmp(2, 6, 32)) <= 0) {
		exp_eno = EPERM;
	} else {
		/* ^^ Look above this warning. ^^ */
		tst_resm(TWARN,
			 "this test's results are based on potentially undocumented behavior in the kernel. read the NOTE in the source file for more details");
		exp_eno = EACCES;
		exp_enos[0] = EACCES;
	}

	TEST_EXP_ENOS(exp_enos);

	for (lc = 0; TEST_LOOPING(lc); lc++) {

		/* reset Tst_count in case we are looping */
		Tst_count = 0;

		strcpy(osname, "Linux");
		osnamelth = SIZE(osname);

		TEST(sysctl(name, SIZE(name), 0, 0, osname, osnamelth));

		if (TEST_RETURN != -1) {
			tst_resm(TFAIL, "sysctl(2) succeeded unexpectedly");
		} else {
			TEST_ERROR_LOG(TEST_ERRNO);

			if (TEST_ERRNO == exp_eno) {
				tst_resm(TPASS | TTERRNO, "Got expected error");
			} else if (errno == ENOSYS) {
				tst_resm(TCONF,
					 "You may need to make CONFIG_SYSCTL_SYSCALL=y"
					 " to your kernel config.");
			} else {
				tst_resm(TFAIL | TTERRNO,
					 "Got unexpected error");
			}
		}

		osnamelth = SIZE(osname);
		if ((ltpuser = getpwnam("nobody")) == NULL) {
			tst_brkm(TBROK, cleanup, "getpwnam() failed");
		}

		/* set process ID to "ltpuser1" */
		if (seteuid(ltpuser->pw_uid) == -1) {
			tst_brkm(TBROK, cleanup,
				 "seteuid() failed, errno %d", errno);
		}

		if ((pid = FORK_OR_VFORK()) == -1) {
			tst_brkm(TBROK, cleanup, "fork() failed");
		}

		if (pid == 0) {
			TEST(sysctl(name, SIZE(name), 0, 0, osname, osnamelth));

			if (TEST_RETURN != -1) {
				tst_resm(TFAIL, "call succeeded unexpectedly");
			} else {
				TEST_ERROR_LOG(TEST_ERRNO);

				if (TEST_ERRNO == exp_eno) {
					tst_resm(TPASS | TTERRNO,
						 "Got expected error");
				} else if (TEST_ERRNO == ENOSYS) {
					tst_resm(TCONF,
						 "You may need to make CONFIG_SYSCTL_SYSCALL=y"
						 " to your kernel config.");
				} else {
					tst_resm(TFAIL | TTERRNO,
						 "Got unexpected error");
				}
			}

			cleanup();

		} else {
			/* wait for the child to finish */
			wait(&status);
		}

		/* set process ID back to root */
		if (seteuid(0) == -1) {
			tst_brkm(TBROK, cleanup, "seteuid() failed");
		}
	}
	cleanup();
	tst_exit();
}