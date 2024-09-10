void daemonize()
{
    pid_t pid, sid, parent;

    char *lockfile;

    lockfile = "/var/lock/subsys/" DAEMON_NAME;

    openlog(DAEMON_NAME, LOG_PID, LOG_LOCAL5);

    /* already a daemon */
    if ( getppid() == 1 ) return;

    /* Create the lock file as the current user */
/*
    if ( lockfile && lockfile[0] ) {
        lfp = open(lockfile,O_RDWR|O_CREAT,0660);
        if ( lfp < 0 ) {
            fprintf(stderr,"Unable to create lock file %s\n", lockfile);
            syslog( LOG_ERR, "unable to create lock file %s, code=%d (%s)",
                    lockfile, errno, strerror(errno) );
            exit(EXIT_FAILURE);
        }
    }
*/

    /* Drop user if there is one, and we were run as root */
    if ( getuid() == 0 || geteuid() == 0 ) {
        struct passwd *pw = getpwnam(RUN_AS_USER);
        if ( pw ) {
            syslog( LOG_NOTICE, "setting user to " RUN_AS_USER );
            setuid( pw->pw_uid );
        }
    }

    /* Trap signals that we expect to recieve */
    signal(SIGCHLD,child_handler);
    signal(SIGUSR1,child_handler);
    signal(SIGALRM,child_handler);

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        syslog( LOG_ERR, "unable to fork daemon, code=%d (%s)",
                errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {

        /* Wait for confirmation from the child via SIGTERM or SIGCHLD, or
           for two seconds to elapse (SIGALRM).  pause() should not return. */
        alarm(2);
        pause();

        exit(EXIT_FAILURE);
    }

    /* At this point we are executing as the child process */
    parent = getppid();

    syslog(LOG_INFO, "Starting daemon " DAEMON_NAME);

    /* Cancel certain signals */
    signal(SIGCHLD,SIG_DFL); /* A child process dies */
    signal(SIGTSTP,SIG_IGN); /* Various TTY signals */
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGHUP, SIG_IGN); /* Ignore hangup signal */
    signal(SIGTERM,sigterm_handler); /* Die on SIGTERM */

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        syslog( LOG_ERR, "unable to create a new session, code %d (%s)",
                errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        syslog( LOG_ERR, "unable to change directory to %s, code %d (%s)",
                "/", errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }

/*
    // write our pid to /var/run/DAEMON_NAME.pid 
    pid_filename = "/var/run/" DAEMON_NAME ".pid";
    pid_file = fopen(pid_filename, "w");
    if (pid_file != NULL)
    {
      fprintf(pid_file, "%d\n", getpid());
    } else {
      syslog (LOG_ERR, "Unable to create pid file %s %d %s", pid_filename,
                errno, strerror(errno));
    }
*/

    /* Redirect standard files to /dev/null */
    freopen( "/dev/null", "r", stdin);
    freopen( "/dev/null", "w", stdout);
    freopen( "/var/tmp/" DAEMON_NAME, "w", stderr);
    chmod( "/var/tmp/" DAEMON_NAME, 0660);

    /* Tell the parent process that we are A-okay */
    kill( parent, SIGUSR1 );
} // daemonize()