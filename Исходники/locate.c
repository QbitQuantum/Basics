int
main(int argc, char **argv)
{
        register int ch;
        char **dbv = NULL;
#ifdef MMAP
        f_mmap = 1;		/* mmap is default */
#endif
	(void) setlocale(LC_ALL, "");

        while ((ch = getopt(argc, argv, "Scd:il:ms")) != -1)
                switch(ch) {
                case 'S':	/* statistic lines */   
                        f_statistic = 1;
                        break;
                case 'l': /* limit number of output lines, 0 == infinite */
                        f_limit = atoi(optarg);
                        break;
                case 'd':	/* database */
                        dbv = colon(dbv, optarg, _PATH_FCODES);
                        break;
                case 'i':	/* ignore case */
                        f_icase = 1;
                        break;
                case 'm':	/* mmap */
#ifdef MMAP
                        f_mmap = 1;
#else
						warnx("mmap(2) not implemented");
#endif
                        break;
                case 's':	/* stdio lib */
                        f_mmap = 0;
                        break;
                case 'c': /* suppress output, show only count of matches */
                        f_silent = 1;
                        break;
                default:
                        usage();
                }
        argv += optind;
        argc -= optind;

        /* to few arguments */
        if (argc < 1 && !(f_statistic))
                usage();

        /* no (valid) database as argument */
        if (dbv == NULL || *dbv == NULL) {
                /* try to read database from environment */
                if ((path_fcodes = getenv("LOCATE_PATH")) == NULL ||
		     *path_fcodes == '\0')
                        /* use default database */
                        dbv = colon(dbv, _PATH_FCODES, _PATH_FCODES);
                else		/* $LOCATE_PATH */
                        dbv = colon(dbv, path_fcodes, _PATH_FCODES);
        }

        if (f_icase && UCHAR_MAX < 4096) /* init tolower lookup table */
                for (ch = 0; ch < UCHAR_MAX + 1; ch++)
                        myctype[ch] = tolower(ch);

        /* foreach database ... */
        while((path_fcodes = *dbv) != NULL) {
                dbv++;

                if (!strcmp(path_fcodes, "-"))
                        f_stdin = 1;
		else
			f_stdin = 0;

#ifndef MMAP
		f_mmap = 0;	/* be paranoid */
#endif
                if (!f_mmap || f_stdin || f_statistic) 
			search_fopen(path_fcodes, argv);
                else 
			search_mmap(path_fcodes, argv);
        }

        if (f_silent)
                print_matches(counter);
        exit(0);
}