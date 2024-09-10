void LocalGlob(LineListPtr fileList, char *pattern)
{
	string pattern2;
	string cmd;
	longstring gfile;
	FILE *volatile fp;
	volatile Sig_t si, sp;

	STRNCPY(pattern2, pattern);	/* Don't nuke the original. */
	
	/* Pre-process for ~'s. */ 
	ExpandTilde(pattern2, sizeof(pattern2));
	
	/* Initialize the list. */
	fileList->first = fileList->last = NULL;
	
	if (GLOBCHARSINSTR(pattern2)) {
		/* Do it the easy way and have the shell do the dirty
		 * work for us.
		 */
		sprintf(cmd, "%s -d %s", LS, pattern2);

		fp = NULL;
		if (setjmp(gLocalGlobJmp) == 0) {			
			fp = POpen(cmd, "r", 0);
			if (fp == NULL) {
				DebugMsg("Could not lglob: %s\n", cmd);
				return;
			}
			sp = SIGNAL(SIGPIPE, LGlobHandler);
			si = SIGNAL(SIGINT, LGlobHandler);
			while (FGets(gfile, sizeof(gfile), (FILE *) fp) != NULL) {
				TraceMsg("Lglob [%s]\n", gfile);
				AddLine(fileList, gfile);
			}
		}
		(void) SIGNAL(SIGPIPE, SIG_IGN);
		if (fp != NULL)
			(void) PClose((FILE *) fp);
		(void) SIGNAL(SIGPIPE, sp);
		(void) SIGNAL(SIGINT, si);
	} else {
		/* Or, if there were no globbing characters in 'pattern', then the
		 * pattern is really just a single pathname.
		 */
		AddLine(fileList, pattern2);
	}
}	/* LocalGlob */