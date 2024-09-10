/****************************************************************************
 * parent() : wait for "ready" from child, send signals to child, wait for
 *    child to exit and report what happened.
 ***************************************************************************/
static void parent()
{
	int term_stat;		/* child return status */
	int rv;			/* function return value */
	int sig;		/* current signal number */
	char *str;		/* string returned from read_pipe() */
	int *array;		/* pointer to sig_array returned from child */
	int fail = FALSE;	/* flag indicating test item failure */
	char big_mesg[MAXMESG * 6];	/* storage for big failure message */
	int caught_sigs;

	/* wait for "ready" message from child */
	if ((str = read_pipe(pipe_fd[0])) == NULL) {
		/* read_pipe() failed. */
		tst_brkm(TBROK, getout, "%s", mesg);
	}

	if (strcmp(str, READY) != 0) {
		/* child setup did not go well */
		tst_brkm(TBROK, getout, "%s", str);
	}

	/*
	 * send signals to child and see if it holds them
	 */

	for (sig = 1; sig < NUMSIGS; sig++) {
		if (choose_sig(sig)) {
			if (kill(pid, sig) < 0) {
				if (errno == ESRCH) {
					if (kill(pid, SIGTERM) < 0)
						tst_brkm(TBROK|TERRNO, getout,
							"kill(%d, %d) and kill(%d, SIGTERM) failed", pid, sig, pid);
					else
						tst_brkm(TBROK|TERRNO, getout,
							"kill(%d, %d) failed, but kill(%d, SIGTERM) worked", pid, sig, pid);
				} else
					tst_brkm(TBROK|TERRNO, getout, "kill(%d, %d) failed", pid, sig);
			}
		}
	}

	if (write_pipe(pipe_fd2[1], READY) < 0) {
		tst_brkm(TBROK|TERRNO, getout, "Unable to tell child to go, write to pipe failed");
	}

	/*
	 * child is now releasing signals, wait and check exit value
	 */
	if (wait(&term_stat) < 0)
		tst_brkm(TBROK|TERRNO, getout, "wait() failed");

	/* check child's signal exit value */
	if ((sig = CHILD_SIG(term_stat)) != 0)
		/* the child was zapped by a signal */
		tst_brkm(TBROK, cleanup, "Unexpected signal %d killed child", sig);

	/* get child exit value */

	rv = CHILD_EXIT(term_stat);

	switch (rv) {
	case EXIT_OK:
		/* sig_array sent back on pipe, check it out */
		if ((array = (int *)read_pipe(pipe_fd[0])) == NULL) {
			/* read_pipe() failed. */
			tst_resm(TBROK, "%s", mesg);
			break;
		}
#if DEBUG > 1
		for (sig = 1; sig < NUMSIGS; sig++) {
			printf("array[%d] = %d\n", sig, array[sig]);
		}
#endif
		caught_sigs = 0;
		for (sig = 1; sig < NUMSIGS; sig++) {
			if (choose_sig(sig)) {
				if (array[sig] != 1) {
					/* sig was not caught or caught too many times */
					(void)sprintf(mesg,
						      "\tsignal %d caught %d times (expected 1).\n",
						      sig, array[sig]);
					(void)strcat(big_mesg, mesg);
					fail = TRUE;
				} else {
					caught_sigs++;
				}
			}
		}		/* endfor */

		if (fail == TRUE)
			tst_resm(TFAIL, "%s", big_mesg);
		else
			tst_resm(TPASS,
				 "sigrelse() released all %d signals under test.",
				 caught_sigs);
		break;

	case TBROK:
		/* get BROK message from pipe */
		if ((str = read_pipe(pipe_fd[0])) == NULL) {
			/* read_pipe() failed. */
			tst_resm(TBROK, "%s", mesg);
			break;
		}

		/* call tst_res: str contains the message */
		tst_resm(TBROK, "%s", str);
		break;
	case SIG_CAUGHT:
		/* a signal was caught before it was released */
		tst_resm(TBROK, "A signal was caught before being released.");
		break;
	case WRITE_BROK:
		/* the write() call failed in child's write_pipe */
		tst_resm(TBROK, "write() pipe failed for child.");
		break;
	case HANDLE_ERR:
		/* more than one signal tried to be handled at the same time */
		tst_resm(TBROK, "Error occured in signal handler.");
		break;
	default:
		tst_resm(TBROK, "Unexpected exit code %d from child", rv);
		break;
	}

}				/* end of parent */