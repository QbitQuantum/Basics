s_paus(char *s, ftnlen n)
#endif
{
	fprintf(stderr, "PAUSE ");
	if(n > 0)
		fprintf(stderr, " %.*s", (int)n, s);
	fprintf(stderr, " statement executed\n");
	if( ISATTY(FILENO(stdin)) )
		s_1paus(stdin);
	else {
#ifdef MSDOS
		FILE *fin;
		fin = fopen("con", "r");
		if (!fin) {
			fprintf(stderr, "s_paus: can't open con!\n");
			fflush(stderr);
			exit(1);
			}
		s_1paus(fin);
		fclose(fin);
#else
		fprintf(stderr,
		"To resume execution, execute a   kill -%d %d   command\n",
			PAUSESIG, getpid() );
		signal1(PAUSESIG, waitpause);
		fflush(stderr);
		pause();
#endif
		}
	fprintf(stderr, "Execution resumes after PAUSE.\n");
	fflush(stderr);
	return 0; /* NOT REACHED */
#ifdef __cplusplus
	}