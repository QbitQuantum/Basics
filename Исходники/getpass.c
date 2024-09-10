char *
lutil_getpass( const char *prompt )
{
#if !defined(HAVE_POSIX_TERMIOS) && !defined(HAVE_SGTTY_H)
	static char buf[256];
	int i, c;

	if( prompt == NULL ) prompt = "Password: "******"->getpass(%s)\n", prompt);
#endif

	printf("%s", prompt);
	i = 0;
	while ( (c = getch()) != EOF && c != '\n' && c != '\r' )
		buf[i++] = c;
	if ( c == EOF )
		return( NULL );
	buf[i] = '\0';
	return (buf);
#else
	int no_pass = 0;
	char i, j, k;
	TERMIO_TYPE ttyb;
	TERMFLAG_TYPE flags;
	static char pbuf[513];
	register char *p;
	register int c;
	FILE *fi;
	RETSIGTYPE (*sig)( int sig );

	if( prompt == NULL ) prompt = "Password: "******"->getpass(%s)\n", prompt);
#endif
	/*
	 *  Stolen from the getpass() routine.  Can't use the plain
	 *  getpass() for two reasons.  One is that LDAP passwords
	 *  can be really, really long - much longer than 8 chars.
	 *  The second is that we like to make this client available
	 *  out of inetd via a Merit asynch port, and we need to be
	 *  able to do telnet control codes to turn on and off line
	 *  blanking.
	 */
	if ((fi = fdopen(open("/dev/tty", 2), "r")) == NULL)
		fi = stdin;
	else
		setbuf(fi, (char *)NULL);
	sig = SIGNAL (SIGINT, SIG_IGN);
	if (fi != stdin) {
		if (GETATTR(fileno(fi), &ttyb) < 0)
			perror("GETATTR");
	}
	flags = GETFLAGS( ttyb );
	SETFLAGS( ttyb, flags & ~ECHO );
	if (fi != stdin) {
		if (SETATTR(fileno(fi), &ttyb) < 0)
			perror("SETATTR");
	}

	/*  blank the line if through Merit */
	if (fi == stdin) {
		printf("%c%c%c", 255, 251, 1);
		fflush(stdout);
		(void) scanf("%c%c%c", &i, &j, &k);
		fflush(stdin);
	}

	/* fetch the password */
	fprintf(stdout, "%s", prompt); 
	fflush(stdout);
	for (p=pbuf; (c = getc(fi))!='\n' && c!=EOF;) {
		if (c == '\r')
			break;
		if (p < &pbuf[512])
			*p++ = c;
	}
	if (c == EOF)
		no_pass = 1;
	else {
		*p = '\0';
		if (*(p - 1) == '\r')
			*(p - 1) = '\0';
	}

	/*  unblank the line if through Merit */
	if (fi == stdin) {
		printf("%c%c%c", 255, 252, 1);
		fflush(stdout);
		(void) scanf("%c%c%c", &i, &j, &k);
		fflush(stdin);
		printf("\n"); fflush(stdout);
	}
	fprintf(stdout, "\n"); 
	fflush(stdout);

	/* tidy up */
	SETFLAGS( ttyb, flags );
	if (fi != stdin) {
		if (SETATTR(fileno(fi), &ttyb) < 0)
			perror("SETATTR");
	}
	(void) SIGNAL (SIGINT, sig);
	if (fi != stdin)
		(void) fclose(fi);
	else
		i = getchar();
	if (no_pass)
		return(NULL);
	return(pbuf);
#endif
}