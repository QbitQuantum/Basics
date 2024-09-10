static int miscd_dodaemon(char *argv1, char *daemon)
{
    struct sigaction act;
    char *commandline;
    char commbuf[10];
    char ch;

	if (!check_file_writable(PASSFILE))
	{
		fprintf(stderr, "Error! File %s is not writable.\n", PASSFILE);
		exit(-1);
	}
	if (!check_file_writable(BOARDS))
	{
		fprintf(stderr, "Error! File %s is not writable.\n", BOARDS);
		exit(-1);
	}
	truncate(BOARDS, MAXBOARD * sizeof(struct boardheader));

    if (load_ucache() != 0) {
        printf("ft,load ucache error!");
        exit(-1);
    }

    /* init tmpfs */
    sprintf(genbuf1,"%s/home",TMPFSROOT);
    mkdir(genbuf1,0700);
    sprintf(genbuf1,"%s/boards",TMPFSROOT);
    mkdir(genbuf1,0700);
    for (ch='A';ch<='Z';ch++) {
    sprintf(genbuf1,"%s/home/%c",TMPFSROOT,ch);
    mkdir(genbuf1,0700);
    }

    resolve_boards();
    resolve_utmp();
    resolve_guest_table();

    if (argv1 != NULL) {
        switch (fork()) {
        case -1:
            printf("faint, i can't fork.\n");
            exit(0);
            break;
        case 0:
            break;
        default:
            exit(0);
            break;
        }
        commandline = argv1;
    } else {
        commandline = commbuf;
    }
    setsid();
#ifdef AIX
    setpgrp();
#elif defined FREEBSD
    setpgid(0, 0);
#else
    // by zixia setpgrp(0, 0);
    setpgrp();
#endif
#ifdef AIX
    act.sa_handler = NULL;
    act.sa_flags = SA_RESTART | SA_NOCLDWAIT;
    sigaction(SIGCHLD, &act, NULL);
#else
    act.sa_handler = reaper;
    act.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &act, NULL);
#endif
    if (((daemon == NULL) || (!strcmp(daemon, "timed"))) && ((argv1 == NULL) || fork())) {
        strcpy(commandline, "timed");
        timed();
        exit(0);
    }

    if (((daemon == NULL) || (!strcmp(daemon, "killd"))) && ((argv1 == NULL) || fork())) {
        strcpy(commandline, "killd");
        while (1) {
            time_t ft;

            ft = getnextday4am();
            do {
                sleep(ft - time(0));
            } while (ft > time(0));

            if (argv1 == NULL) {
                dokilluser();
                //doupdategiveupuser();
            } else {
                switch (fork()) {
                case -1:
                    bbslog("3error", "fork failed\n");
                    break;
                case 0:
                    dokilluser();
                    //doupdategiveupuser();
                    exit(0);
                    break;
                default:
                    break;
                }
            }
            switch (fork()) {
                case -1:
                    bbslog("3error", "fork failed\n");
                    break;
                case 0:
                    dokillalldir();
                    exit(0);
                    break;
                default:
                    break;
            }
        };
        exit(0);
    }
    if (((daemon == NULL) || (!strcmp(daemon, "userd"))) && ((argv1 == NULL) || fork())) {
        strcpy(commandline, "userd");
        userd();
        exit(0);
    }
    if ((daemon == NULL) || (!strcmp(daemon, "flushd"))) {
        strcpy(commandline, "flushd");
        flushd();
        exit(0);
    }
    return 0;
}