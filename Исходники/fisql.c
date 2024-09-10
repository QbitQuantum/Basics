int
main(int argc, char *argv[])
{
	int echo = 0;

#ifdef notyet
	int print_statistics = 0;
#endif
	int fipsflagger = 0;
	int perfstats = 0;
	int use_encryption = 0;
	int chained_transactions = 0;
	int headers = 0;
	char *columnwidth = NULL;
	const char *colseparator = " ";
	const char *lineseparator = "\n";
	int timeout = 0;
	char *username = NULL;
	char *password = NULL;
	char *server = NULL;
	DBCHAR *char_set = NULL;
	char *hostname = NULL;
	char *interfaces_filename = NULL;
	char *input_filename = NULL;
	char *output_filename = NULL;
	int logintime = -1;
	char *language = NULL;
	int size = 0;
	char *sybenv;
	LOGINREC *login;
	int printedlines;
	int i;
	int dbrc;
	int c;
	int errflg = 0;
	char *prbuf;
	int prbuflen;
	int num_cols;
	int selcol;
	int col;
	int collen;
	DBINT colid;
	const char *opname;
	char adbuf[512];
	DBINT convlen;
	int printedcompute = 0;
	char adash;
	const char *database_name = NULL;

	setlocale(LC_ALL, "");

#ifdef __VMS
	/* Convert VMS-style arguments to Unix-style */
	parse_vms_args(&argc, &argv);
#endif

	editor = getenv("EDITOR");
	if (!editor) {
		editor = getenv("VISUAL");
	}
	if (!editor) {
		editor = "vi";
	}

	opterr = 0;
	optarg = NULL;
	while (!errflg && (c = getopt(argc, argv, "eFgpnvXYa:c:D:E:h:H:i:I:J:l:m:o:P:s:S:t:U:w:y:z:A:"))
	       != -1) {
		switch (c) {
		case 'e':
			echo = 1;
			break;
		case 'F':
			fipsflagger = 1;
			break;
		case 'g':
			errflg++;
			break;
		case 'p':
			errflg++;
			perfstats = 1;
			break;
		case 'n':
			no_prompt = 1;
			break;
		case 'v':
			puts("fisql, a free isql replacement by Nicholas S. Castellano");
			return EXIT_SUCCESS;
			break;
		case 'X':
			/* XXX: We get a different error message than isql gives; neither seems
			 * to work
			 */
			use_encryption = 1;
			break;
		case 'Y':
			chained_transactions = 1;
			break;
		case 'c':
			cmdend = optarg;
			break;
		case 'E':
			editor = optarg;
			break;
		case 'h':
			headers = atoi(optarg);
			break;
		case 'H':
			hostname = optarg;
			break;
		case 'i':
			input_filename = optarg;
			break;
		case 'I':
			interfaces_filename = optarg;
			break;
		case 'J':
			errflg++;
			break;
		case 'l':
			logintime = atoi(optarg);
			break;
		case 'm':
			global_errorlevel = atoi(optarg);
			break;
		case 'o':
			output_filename = optarg;
			break;
		case 'P':
			password = optarg;
			break;
		case 's':
			colseparator = optarg;
			break;
		case 'S':
			server = optarg;
			break;
		case 't':
			timeout = atoi(optarg);
			break;
		case 'U':
			username = optarg;
			break;
		case 'w':
			columnwidth = optarg;
			break;
		case 'y':
			/* XXX: this doesn't seem to be what isql does with -y...it doesn't
			 * seem to do anything actually
			 */
			sybenv = (char *) xmalloc((strlen(optarg) + 8) * sizeof(char));
			strcpy(sybenv, "SYBASE=");
			strcat(sybenv, optarg);
			putenv(sybenv);
			break;
		case 'z':
			language = optarg;
			break;
		case 'A':
			size = atoi(optarg);
			break;
		case 'D':
			database_name = optarg;
			break;
		default:
			errflg++;
			break;
		}
	}

	if (errflg) {
		fprintf(stderr, "usage: fisql [-e] [-F] [-g] [-p] [-n] [-v] [-X] [-Y]\n");
		fprintf(stderr, "\t[-c cmdend] [-D database_name] [-E editor]\n");
		fprintf(stderr, "\t[-h headers] [-H hostname] [-i inputfile]\n");
		fprintf(stderr, "\t[-I interfaces_file] [-J client character set]\n");
		fprintf(stderr, "\t[-l login_timeout] [-m errorlevel]\n");
		fprintf(stderr, "\t[-o outputfile]\n");
		fprintf(stderr, "\t[-P password] [-s colseparator] [-S server]\n");
		fprintf(stderr, "\t[-t timeout] [-U username] [-w columnwidth]\n");
		fprintf(stderr, "\t[-y sybase_dir] [-z language]\n");
		return EXIT_FAILURE;
	}
	if (!(isatty(fileno(stdin)))) {
		no_prompt = 1;
		rl_outstream = fopen("/dev/null", "rw");
	}
	rl_readline_name = "fisql";
	rl_bind_key('\t', rl_insert);
	if (password == NULL) {
		password = (char *) xmalloc(READPASSPHRASE_MAXLEN);
		readpassphrase("Password: "******"r", stdin) == NULL) {
			/* XXX: sybase isql generates this error while parsing the options,
			 * but doesn't redirect the input until after the Password: prompt
			 */
			/* lack of newline for bug-compatibility with isql */
			fprintf(stderr, "Unable to open input file '%s'.", optarg);
			return EXIT_FAILURE;
		}
	}
	if (output_filename) {
		if (freopen(output_filename, "w", stdout) == NULL) {
			/* XXX: sybase isql generates this error while parsing the options,
			 * but doesn't redirect the output until after the Password: prompt
			 */
			/* lack of newline for bug-compatibility with isql */
			fprintf(stderr, "Unable to open output file '%s'.", output_filename);
			return EXIT_FAILURE;
		}
	}
	if (isatty(fileno(stdin))) {
		rl_outstream = stdout;
	}
	dbinit();
#if 0
#ifdef DBVERSION_100
	dbsetversion(DBVERSION_100);
#endif
#endif
	if ((login = dblogin()) == NULL) {
		reset_term();
		return EXIT_FAILURE;
	}
	dbmsghandle(msg_handler);
	dberrhandle(err_handler);
	DBSETLAPP(login, "fisql");
	if (username) {
		DBSETLUSER(login, username);
	}
	DBSETLPWD(login, password);
	memset(password, 0, strlen(password));

	if (char_set) {
		DBSETLCHARSET(login, char_set);
	}
	if (use_encryption) {
		DBSETLENCRYPT(login, TRUE);
	}
	if (hostname) {
		DBSETLHOST(login, hostname);
	}
	if (language) {
		DBSETLNATLANG(login, language);
	}
	if (size) {
		DBSETLPACKET(login, (short) size);
	}
	if (interfaces_filename) {
		dbsetifile(interfaces_filename);
	}
	dbsettime(timeout);
	if (logintime >= 0) {
		dbsetlogintime(logintime);
	}
	if (database_name) {
		DBSETLDBNAME(login, database_name);
	}
	if ((dbproc = dbopen(login, server)) == NULL) {
		fprintf(stderr, "fisql: dbopen() failed.\n");
		reset_term();
		return EXIT_FAILURE;
	}

	dbsetopt(dbproc, DBPRLINESEP, lineseparator, strlen(lineseparator));
	if (colseparator) {
		dbsetopt(dbproc, DBPRCOLSEP, colseparator, strlen(colseparator));
	}
	if (columnwidth) {
		dbsetopt(dbproc, DBPRLINELEN, columnwidth, 0);
	}
	if (chained_transactions) {
		dbsetopt(dbproc, DBCHAINXACTS, NULL, 0);
	}
	if (fipsflagger) {
		dbsetopt(dbproc, DBFIPSFLAG, NULL, 0);
	}
	if (perfstats) {
		dbsetopt(dbproc, DBSTAT, "time", 0);
	}

	while (1) {
		if (sigsetjmp(restart, 1)) {
			reset_ibuf();
			fputc('\n', stdout);
			rl_on_new_line();
			rl_reset_line_state();
		}
		dbcancel(dbproc);
		signal(SIGINT, inactive_interrupt_handler);

		read_sql_lines();

		dbfreebuf(dbproc);
		for (i = 0; i < ibuflines; i++) {
			if (echo) {
				puts(ibuf[i]);
			}
			dbcmd(dbproc, ibuf[i]);
			dbcmd(dbproc, "\n");
			free(ibuf[i]);
		}
		free(ibuf);
		ibuf = NULL;
		signal(SIGINT, active_interrupt_handler);
		dbsetinterrupt(dbproc, (void *) active_interrupt_pending, (void *) active_interrupt_servhandler);
		if (dbsqlexec(dbproc) == SUCCEED) {
			int status_printed = 0;

			maybe_handle_active_interrupt();
			while ((dbrc = dbresults(dbproc)) != NO_MORE_RESULTS) {
				printedlines = 0;
#define USE_DBPRROW 0
#if USE_DBPRROW
				dbprhead(dbproc);
				dbprrow(dbproc);
#else
				if ((dbrc == SUCCEED) && (DBROWS(dbproc) == SUCCEED)) {
					prbuflen = dbspr1rowlen(dbproc);
					prbuf = (char *) xmalloc(prbuflen * sizeof(char));
					dbsprhead(dbproc, prbuf, prbuflen);
					fputs(prbuf, stdout);
					fputc('\n', stdout);
					dbsprline(dbproc, prbuf, prbuflen, '-');
					fputs(prbuf, stdout);
					fputc('\n', stdout);
					maybe_handle_active_interrupt();
					while ((dbrc = dbnextrow(dbproc)) != NO_MORE_ROWS) {
						if (dbrc == FAIL) {
							break;
						}
						if (dbrc != REG_ROW) {
							num_cols = dbnumalts(dbproc, dbrc);
							for (selcol = col = 1; col <= num_cols; col++) {
								colid = dbaltcolid(dbproc, dbrc, col);
								while (selcol < colid) {
									collen = get_printable_column_size(dbproc, selcol);
									for (i = 0; i < collen; i++) {
										putchar(' ');
									}
									selcol++;
									printf("%s", colseparator);
								}
								opname = dbprtype(dbaltop(dbproc, dbrc, col));
								printf("%s", opname);
								collen = get_printable_column_size(dbproc, colid);
								collen -= strlen(opname);
								while (collen-- > 0) {
									putchar(' ');
								}
								selcol++;
								printf("%s", colseparator);
							}
							printf("%s", lineseparator);
							for (selcol = col = 1; col <= num_cols; col++) {
								colid = dbaltcolid(dbproc, dbrc, col);
								while (selcol < colid) {
									collen = get_printable_column_size(dbproc, selcol);
									for (i = 0; i < collen; i++) {
										putchar(' ');
									}
									selcol++;
									printf("%s", colseparator);
								}
								collen = get_printable_column_size(dbproc, colid);
								adash = '-';
								for (i = 0; i < collen; i++) {
									putchar(adash);
								}
								selcol++;
								printf("%s", colseparator);
							}
							printf("%s", lineseparator);
							for (selcol = col = 1; col <= num_cols; col++) {
								colid = dbaltcolid(dbproc, dbrc, col);
								while (selcol < colid) {
									collen = get_printable_column_size(dbproc, selcol);
									for (i = 0; i < collen; i++) {
										putchar(' ');
									}
									selcol++;
									printf("%s", colseparator);
								}
								convlen = dbconvert(dbproc,
										    dbalttype(dbproc, dbrc, col),
										    dbadata(dbproc, dbrc, col),
										    dbadlen(dbproc, dbrc, col),
										    SYBCHAR, (BYTE *) adbuf, sizeof(adbuf));
								printf("%.*s", (int) convlen, adbuf);
								collen = get_printable_column_size(dbproc, colid);
								collen -= convlen;
								while (collen-- > 0) {
									putchar(' ');
								}
								selcol++;
								printf("%s", colseparator);
							}
							printf("%s", lineseparator);
							printedcompute = 1;
							continue;
						}
						if (printedcompute || (headers && (printedlines >= headers)
								       && ((printedlines % headers) == 0))) {
							fputc('\n', stdout);
							dbsprhead(dbproc, prbuf, prbuflen);
							fputs(prbuf, stdout);
							fputc('\n', stdout);
							dbsprline(dbproc, prbuf, prbuflen, '-');
							fputs(prbuf, stdout);
							fputc('\n', stdout);
							printedcompute = 0;
						}
						printedlines++;
						dbspr1row(dbproc, prbuf, prbuflen);
						fputs(prbuf, stdout);
						fputc('\n', stdout);
						maybe_handle_active_interrupt();
					}
					fputc('\n', stdout);
					free(prbuf);
					maybe_handle_active_interrupt();
				}
#endif
				if (dbrc != FAIL) {
					if ((DBCOUNT(dbproc) >= 0) || dbhasretstat(dbproc)) {
						if (DBCOUNT(dbproc) >= 0) {
							fprintf(stdout, "(%d rows affected", (int) DBCOUNT(dbproc));
							if (dbhasretstat(dbproc)) {
								status_printed = 1;
								dbrc = dbretstatus(dbproc);
								fprintf(stdout, ", return status = %d", dbrc);
							}
							fprintf(stdout, ")\n");
						} else {
							if (dbhasretstat(dbproc)) {
								status_printed = 1;
								dbrc = dbretstatus(dbproc);
								fprintf(stdout, "(return status = %d)\n", dbrc);
							}
						}
					}
				}
			}
			if (!status_printed && dbhasretstat(dbproc)) {
				dbrc = dbretstatus(dbproc);
				fprintf(stdout, "(return status = %d)\n", dbrc);
			}
		} else {
			/* Something failed, so change the default
			 * exit status to reflect that.
			 */
			default_exit = EXIT_FAILURE;
		}
	}
	reset_term();
	dbexit();
	return EXIT_FAILURE;
}