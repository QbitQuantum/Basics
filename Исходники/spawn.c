/*ARGSUSED*/
spawncli(f, n) {
	register void	(*oisig)();
	int		status;
#ifdef	EXTD_DIR
	ensurecwd();
#endif

	if (shellp == NULL) {
		shellp = getenv("SHELL");
		if (shellp == NULL)
			shellp = getenv("shell");
		if (shellp == NULL)
			shellp = "command.x";	/* Safer.		*/
	}
	ttcolor(CTEXT);
	ttnowindow();
	ttmove(nrow-1, 0);
	if (epresf != FALSE) {
		tteeol();
		epresf = FALSE;
	}
	ttclose();
	sgarbf = TRUE;				/* Force repaint.	*/
	oisig = signal(SIGINT,  SIG_IGN);
#ifdef	EXTD_DIR
	dirend();
#endif
	if (spawnlp(P_WAIT, shellp, shellp, NULL) == -1) {
		status = FALSE;
	} else {
		status = TRUE;
	}
	(VOID) signal(SIGINT,  oisig);
	ttopen();
	if(status == FALSE) {
		ewprintf("Failed to run %s", shellp);
		sleep(2);		/* Show this message for 2 sec	*/
					/* before refresh screen.	*/
	}
	dirinit();
	return (status);
}