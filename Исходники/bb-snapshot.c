int main(int argc, char *argv[])
{
	char dirid[PATH_MAX];
	char outdir[PATH_MAX];
	char bbgencmd[PATH_MAX];
	char bbwebenv[PATH_MAX];
	char bbgentimeopt[100];
	char *bbgen_argv[20];
	pid_t childpid;
	int childstat;
	char htmldelim[20];
	char startstr[20];
	int argi, newargi;
	char *envarea = NULL;
	char *useragent;
	int usemultipart = 1;

	newargi = 0;
	bbgen_argv[newargi++] = bbgencmd;
	bbgen_argv[newargi++] = bbgentimeopt;

	for (argi=1; (argi < argc); argi++) {
		if (argnmatch(argv[argi], "--env=")) {
			char *p = strchr(argv[argi], '=');
			loadenv(p+1, envarea);
		}
		else if (argnmatch(argv[argi], "--area=")) {
			char *p = strchr(argv[argi], '=');
			envarea = strdup(p+1);
		}
		else {
			bbgen_argv[newargi++] = argv[argi];
		}
	}
	bbgen_argv[newargi++] = outdir;
	bbgen_argv[newargi++] = NULL;

	redirect_cgilog("bb-snapshot");

	cgidata = cgi_request();
	if (cgidata == NULL) {
		/* Present the query form */
		sethostenv("", "", "", colorname(COL_BLUE), NULL);
		printf("Content-type: %s\n\n", xgetenv("HTMLCONTENTTYPE"));
		showform(stdout, "snapshot", "snapshot_form", COL_BLUE, getcurrenttime(NULL), NULL, NULL);
		return 0;
	}

	parse_query();

	useragent = getenv("HTTP_USER_AGENT");
	if (useragent && strstr(useragent, "KHTML")) {
		/* KHTML (Konqueror, Safari) cannot handle multipart documents. */
		usemultipart = 0;
	}

	/*
	 * Need to set these up AFTER putting them into bbgen_argv, since we
	 * need to have option parsing done first.
	 */
	if (xgetenv("BBGEN")) sprintf(bbgencmd, "%s", xgetenv("BBGEN"));
	else sprintf(bbgencmd, "%s/bin/bbgen", xgetenv("BBHOME"));

	sprintf(bbgentimeopt, "--snapshot=%u", (unsigned int)starttime);

	sprintf(dirid, "%u-%u", (unsigned int)getpid(), (unsigned int)getcurrenttime(NULL));
	sprintf(outdir, "%s/%s", xgetenv("BBSNAP"), dirid);
	if (mkdir(outdir, 0755) == -1) errormsg("Cannot create output directory");

	sprintf(bbwebenv, "BBWEB=%s/%s", xgetenv("BBSNAPURL"), dirid);
	putenv(bbwebenv);

	if (usemultipart) {
		/* Output the "please wait for report ... " thing */
		sprintf(htmldelim, "bbrep-%u-%u", (int)getpid(), (unsigned int)getcurrenttime(NULL));
		printf("Content-type: multipart/mixed;boundary=%s\n", htmldelim);
		printf("\n");
		printf("%s\n", htmldelim);
		printf("Content-type: %s\n\n", xgetenv("HTMLCONTENTTYPE"));

		/* It's ok with these hardcoded values, as they are not used for this page */
		sethostenv("", "", "", colorname(COL_BLUE), NULL);
		sethostenv_report(starttime, starttime, 97.0, 99.995);
		headfoot(stdout, "snapshot", "", "header", COL_BLUE);

		strftime(startstr, sizeof(startstr), "%b %d %Y", localtime(&starttime));
		printf("<CENTER><A NAME=begindata>&nbsp;</A>\n");
		printf("<BR><BR><BR><BR>\n");
		printf("<H3>Generating snapshot: %s<BR>\n", startstr);
		printf("<P><P>\n");
		fflush(stdout);
	}


	/* Go do the report */
	childpid = fork();
	if (childpid == 0) {
		execv(bbgencmd, bbgen_argv);
	}
	else if (childpid > 0) {
		wait(&childstat);

		/* Ignore SIGHUP so we dont get killed during cleanup of BBSNAP */
		signal(SIGHUP, SIG_IGN);

		if (WIFEXITED(childstat) && (WEXITSTATUS(childstat) != 0) ) {
			if (usemultipart) printf("%s\n\n", htmldelim);
			printf("Content-Type: %s\n\n", xgetenv("HTMLCONTENTTYPE"));
			errormsg("Could not generate report");
		}
		else {
			/* Send the browser off to the report */
			if (usemultipart) {
				printf("Done...<P></BODY></HTML>\n");
				fflush(stdout);
				printf("%s\n\n", htmldelim);
			}
			printf("Content-Type: %s\n\n", xgetenv("HTMLCONTENTTYPE"));
			printf("<HTML><HEAD>\n");
			printf("<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"0; URL=%s/%s/\"\n", 
					xgetenv("BBSNAPURL"), dirid);
			printf("</HEAD><BODY BGCOLOR=\"000000\"></BODY></HTML>\n");
			if (usemultipart) printf("\n%s\n", htmldelim);
			fflush(stdout);
		}

		cleandir(xgetenv("BBSNAP"));
	}
	else {
		if (usemultipart) printf("%s\n\n", htmldelim);
		printf("Content-Type: %s\n\n", xgetenv("HTMLCONTENTTYPE"));
		errormsg("Fork failed");
	}

	return 0;
}